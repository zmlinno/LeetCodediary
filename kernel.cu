
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<cusparse.h>
#include<stdio.h>
#include<iostream>
#include<chrono>
#include<algorithm>
#include<vector>
#include<device_atomic_functions.h>
#include<device_functions.h>
#include<cusparse_v2.h>
#include<sstream>
#include<fstream>
using namespace std;
//今天也不能忘了
// 错误检查宏
// 错误检查宏
#define CUDA_CHECK(err) \
    if (err != cudaSuccess) { \
        std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl; \
        exit(EXIT_FAILURE); \
    }

#define CUSPARSE_CHECK(err) \
    if (err != CUSPARSE_STATUS_SUCCESS) { \
        std::cerr << "cuSPARSE Error: " << err << std::endl; \
        exit(EXIT_FAILURE); \
    }

// 解析 Matrix Market 格式文件
void readMatrixMarket(const std::string & filename, int& rows, int& cols, int& nnz,
    std::vector<int>&row_indices, std::vector<int>&col_indices, std::vector<float>&values) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0] != '%') break; // 跳过注释行
    }

    std::istringstream iss(line);
    iss >> rows >> cols >> nnz;

    if (rows <= 0 || cols <= 0 || nnz <= 0) {
        std::cerr << "Error: Invalid matrix dimensions or non-zero count." << std::endl;
        exit(EXIT_FAILURE);
    }

    row_indices.reserve(nnz);
    col_indices.reserve(nnz);
    values.reserve(nnz);

    int row, col;
    float value;
    while (file >> row >> col >> value) {
        if (row <= 0 || col <= 0) {
            std::cerr << "Error: Matrix Market file contains invalid indices." << std::endl;
            exit(EXIT_FAILURE);
        }
        row_indices.push_back(row - 1); // 转换为 0-based 索引
        col_indices.push_back(col - 1);
        values.push_back(value);
    }

    if (row_indices.size() != nnz || col_indices.size() != nnz || values.size() != nnz) {
        std::cerr << "Error: Parsed data does not match expected nnz." << std::endl;
        exit(EXIT_FAILURE);
    }

    file.close();
}

int main() {
    // 1. 读取 Matrix Market 文件
    std::string filename = "C:/Users/ASUS/Downloads/radfr1.tar/radfr1/radfr1.mtx";
    int rows, cols, nnz;
    std::vector<int> row_indices, col_indices;
    std::vector<float> values;

    readMatrixMarket(filename, rows, cols, nnz, row_indices, col_indices, values);

    // 2. 转换为 CSR 格式
    std::vector<int> csrRowPtr(rows + 1, 0);
    for (int i = 0; i < nnz; ++i) {
        ++csrRowPtr[row_indices[i] + 1];
    }
    for (int i = 1; i <= rows; ++i) {
        csrRowPtr[i] += csrRowPtr[i - 1];
    }

    // 3. 在设备上分配内存
    float* d_csrValA, * d_x, * d_y;
    int* d_csrRowPtrA, * d_csrColIndA;
    CUDA_CHECK(cudaMalloc((void**)&d_csrValA, nnz * sizeof(float)));
    CUDA_CHECK(cudaMalloc((void**)&d_csrRowPtrA, (rows + 1) * sizeof(int)));
    CUDA_CHECK(cudaMalloc((void**)&d_csrColIndA, nnz * sizeof(int)));
    CUDA_CHECK(cudaMalloc((void**)&d_x, cols * sizeof(float)));
    CUDA_CHECK(cudaMalloc((void**)&d_y, rows * sizeof(float)));

    CUDA_CHECK(cudaMemcpy(d_csrValA, values.data(), nnz * sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_csrRowPtrA, csrRowPtr.data(), (rows + 1) * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_csrColIndA, col_indices.data(), nnz * sizeof(int), cudaMemcpyHostToDevice));

    // 初始化稠密向量
    std::vector<float> h_x(cols, 1.0f);
    CUDA_CHECK(cudaMemcpy(d_x, h_x.data(), cols * sizeof(float), cudaMemcpyHostToDevice));

    // 4. 创建 cuSPARSE 描述符
    cusparseHandle_t handle;
    CUSPARSE_CHECK(cusparseCreate(&handle));

    cusparseSpMatDescr_t matA;
    cusparseDnVecDescr_t vecX, vecY;
    CUSPARSE_CHECK(cusparseCreateCsr(&matA, rows, cols, nnz,
        d_csrRowPtrA, d_csrColIndA, d_csrValA,
        CUSPARSE_INDEX_32I, CUSPARSE_INDEX_32I,
        CUSPARSE_INDEX_BASE_ZERO, CUDA_R_32F));
    CUSPARSE_CHECK(cusparseCreateDnVec(&vecX, cols, d_x, CUDA_R_32F));
    CUSPARSE_CHECK(cusparseCreateDnVec(&vecY, rows, d_y, CUDA_R_32F));

    // 5. 稀疏矩阵-稠密向量乘法，添加计时器
    const float alpha = 1.0f, beta = 0.0f;
    size_t bufferSize = 0;
    void* dBuffer = nullptr;
    CUSPARSE_CHECK(cusparseSpMV_bufferSize(handle,
        CUSPARSE_OPERATION_NON_TRANSPOSE,
        &alpha, matA, vecX, &beta, vecY,
        CUDA_R_32F, CUSPARSE_SPMV_ALG_DEFAULT, &bufferSize));
    CUDA_CHECK(cudaMalloc(&dBuffer, bufferSize));

    // 使用 CUDA 事件测量时间
    cudaEvent_t start, stop;
    CUDA_CHECK(cudaEventCreate(&start));
    CUDA_CHECK(cudaEventCreate(&stop));

    CUDA_CHECK(cudaEventRecord(start, 0));
    CUSPARSE_CHECK(cusparseSpMV(handle,
        CUSPARSE_OPERATION_NON_TRANSPOSE,
        &alpha, matA, vecX, &beta, vecY,
        CUDA_R_32F, CUSPARSE_SPMV_ALG_DEFAULT, dBuffer));
    CUDA_CHECK(cudaEventRecord(stop, 0));
    CUDA_CHECK(cudaEventSynchronize(stop));

    float milliseconds = 0;
    CUDA_CHECK(cudaEventElapsedTime(&milliseconds, start, stop));
    std::cout << "Sparse Matrix-Vector Multiplication Time: " << milliseconds << " ms" << std::endl;

    // 6. 清理资源
    CUDA_CHECK(cudaFree(d_csrValA));
    CUDA_CHECK(cudaFree(d_csrRowPtrA));
    CUDA_CHECK(cudaFree(d_csrColIndA));
    CUDA_CHECK(cudaFree(d_x));
    CUDA_CHECK(cudaFree(d_y));
    CUDA_CHECK(cudaFree(dBuffer));
    CUSPARSE_CHECK(cusparseDestroySpMat(matA));
    CUSPARSE_CHECK(cusparseDestroyDnVec(vecX));
    CUSPARSE_CHECK(cusparseDestroyDnVec(vecY));
    CUSPARSE_CHECK(cusparseDestroy(handle));
    CUDA_CHECK(cudaEventDestroy(start));
    CUDA_CHECK(cudaEventDestroy(stop));

    return 0;
}

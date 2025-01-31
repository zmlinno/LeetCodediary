//
//  Shaders.metal
//  SPMVGpu
//
//  Created by 张木林 on 1/10/25.
//

#include <metal_stdlib>
using namespace metal;
// Kernel function for SpMV using CSR format
kernel void spmv_csr(
    device const float* values [[buffer(0)]],
    device const int* columnIndices [[buffer(1)]],
    device const int* rowPointers [[buffer(2)]],
    device const float* x [[buffer(3)]],
    device float* y [[buffer(4)]],
    uint gid [[thread_position_in_grid]]
) {
    if (gid >= rowPointers[3]) return;  // 防止访问越界

    float sum = 0.0;
    int row_start = rowPointers[gid];
    int row_end = rowPointers[gid + 1];

    for (int i = row_start; i < row_end; i++) {
        sum += values[i] * x[columnIndices[i]];
    }

    y[gid] = sum;
}

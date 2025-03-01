//随便写点，凑个绿点！
//  main.m
//  MetalGPU
//
//  Created by 张木林 on 1/10/25.
// Just
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

// Helper function to create a Metal buffer
id<MTLBuffer> createBuffer(id<MTLDevice> device, const void* data, size_t size) {
    return [device newBufferWithBytes:data length:size options:MTLResourceStorageModeShared];
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Step 1: Initialize Metal
        id<MTLDevice> device = MTLCreateSystemDefaultDevice();
        id<MTLCommandQueue> commandQueue = [device newCommandQueue];
        NSError *error = nil;

        // Load the Metal library
        NSString *metalFilePath = [[NSBundle mainBundle] pathForResource:@"SpMV" ofType:@"metal"];
        NSString *metalSource = [NSString stringWithContentsOfFile:metalFilePath encoding:NSUTF8StringEncoding error:&error];
        id<MTLLibrary> library = [device newLibraryWithSource:metalSource options:nil error:&error];
        if (!library) {
            NSLog(@"Failed to load Metal library: %@", error);
            return -1;
        }

        id<MTLFunction> kernelFunction = [library newFunctionWithName:@"spmv_csr"];
        id<MTLComputePipelineState> pipelineState = [device newComputePipelineStateWithFunction:kernelFunction error:&error];
        if (!pipelineState) {
            NSLog(@"Failed to create pipeline state: %@", error);
            return -1;
        }

        // Step 2: Define CSR data
        float values[] = {1.0, 2.0, 3.0, 4.0};       // Non-zero values
        int columnIndices[] = {0, 1, 1, 2};          // Column indices of values
        int rowOffsets[] = {0, 2, 4};                // Row offsets
        float vector[] = {1.0, 2.0, 3.0};            // Dense vector
        float result[2] = {0.0};                     // Output result

        // Create Metal buffers
        id<MTLBuffer> valuesBuffer = createBuffer(device, values, sizeof(values));
        id<MTLBuffer> columnIndicesBuffer = createBuffer(device, columnIndices, sizeof(columnIndices));
        id<MTLBuffer> rowOffsetsBuffer = createBuffer(device, rowOffsets, sizeof(rowOffsets));
        id<MTLBuffer> vectorBuffer = createBuffer(device, vector, sizeof(vector));
        id<MTLBuffer> resultBuffer = createBuffer(device, result, sizeof(result));

        // Step 3: Configure and dispatch Metal kernel
        id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
        id<MTLComputeCommandEncoder> computeEncoder = [commandBuffer computeCommandEncoder];
        [computeEncoder setComputePipelineState:pipelineState];
        [computeEncoder setBuffer:valuesBuffer offset:0 atIndex:0];
        [computeEncoder setBuffer:columnIndicesBuffer offset:0 atIndex:1];
        [computeEncoder setBuffer:rowOffsetsBuffer offset:0 atIndex:2];
        [computeEncoder setBuffer:vectorBuffer offset:0 atIndex:3];
        [computeEncoder setBuffer:resultBuffer offset:0 atIndex:4];

        MTLSize gridSize = MTLSizeMake(2, 1, 1); // Number of rows
        MTLSize threadGroupSize = MTLSizeMake(1, 1, 1);
        [computeEncoder dispatchThreads:gridSize threadsPerThreadgroup:threadGroupSize];
        [computeEncoder endEncoding];
        [commandBuffer commit];
        [commandBuffer waitUntilCompleted];

        // Step 4: Print results
        float *output = (float *)[resultBuffer contents];
        NSLog(@"Result: [%f, %f]", output[0], output[1]);
    }
    return 0;
}

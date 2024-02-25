//
// Created by Yohandi on 2023/10/27.
// Email: yohandi@link.cuhk.edu.cn
//
// GPU Matrix Multiplication
//

#include "../matrix.hpp"
#include <chrono>
#include <cuda_runtime.h>
#include <iostream>
#include <stdexcept>

__global__ void matrixMultiply(int *matrix1, int *matrix2, int *result,
                               size_t M, size_t N, size_t K) {
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  if (row < M && col < N) {
    int sum = 0;
    for (size_t k = 0; k < K; k++) {
      sum += matrix1[row * K + k] * matrix2[k * N + col];
    }

    result[row * N + col] = sum;
  }
}

int main(int argc, char **argv) {
  const std::string matrix1_path = argv[1];
  const std::string matrix2_path = argv[2];
  const std::string result_path = argv[3];

  Matrix matrix1 = Matrix::loadFromFile(matrix1_path);
  Matrix matrix2 = Matrix::loadFromFile(matrix2_path);

  size_t M = matrix1.getRows();
  size_t N = matrix2.getCols();
  size_t K = matrix1.getCols();

  int *d_matrix1, *d_matrix2;
  int *d_result;

  cudaMalloc((void **)&d_matrix1, M * K * sizeof(int));
  cudaMalloc((void **)&d_matrix2, K * N * sizeof(int));
  cudaMalloc((void **)&d_result, M * N * sizeof(int));

  int *flat_matrix1, *flat_matrix2;
  cudaMallocManaged(&flat_matrix1, M * K * sizeof(int));
  cudaMallocManaged(&flat_matrix2, K * N * sizeof(int));

  for (int i = 0; i < M; i++)
    for (int j = 0; j < K; j++)
      flat_matrix1[i * K + j] = matrix1[i][j];

  for (int i = 0; i < K; i++)
    for (int j = 0; j < N; j++)
      flat_matrix2[i * N + j] = matrix2[i][j];

  cudaMemcpy(d_matrix1, flat_matrix1, M * K * sizeof(int),
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_matrix2, flat_matrix2, K * N * sizeof(int),
             cudaMemcpyHostToDevice);

  cudaEvent_t start, stop;
  float gpuDuration;

  dim3 threadsPerBlock(32, 32);
  dim3 blocks((N + threadsPerBlock.x - 1) / threadsPerBlock.x,
              (M + threadsPerBlock.y - 1) / threadsPerBlock.y);

  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start, 0);

  matrixMultiply<<<blocks, threadsPerBlock>>>(d_matrix1, d_matrix2, d_result, M,
                                              N, K);

  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&gpuDuration, start, stop);

  int *flat_result = (int *)malloc(M * N * sizeof(int));
  if (flat_result == NULL) {
    std::cerr << "Memory allocation failed!" << std::endl;
    exit(1);
  }
  cudaMemcpy(flat_result, d_result, M * N * sizeof(int),
             cudaMemcpyDeviceToHost);

  Matrix result(M, N);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      result[i][j] = flat_result[i * N + j];
    }
  }

  result.saveToFile(result_path);

  std::cout << "Output file to: " << result_path << std::endl;

  std::cout << "Multiplication Complete!" << std::endl;
  std::cout << "GPU Execution Time: " << gpuDuration << " milliseconds"
            << std::endl;

  cudaFree(flat_matrix1);
  cudaFree(flat_matrix2);
  delete[] flat_result;

  cudaEventDestroy(start);
  cudaEventDestroy(stop);

  return 0;
}

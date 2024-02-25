//
// Created by Yohandi on 2023/10/27.
// Email: yohandi@link.cuhk.edu.cn
//
// Template is provided by Yang Yufan
// Email: yufanyang1@link.cuhk.edu.cn
//
// Reordering Matrix Multiplication
//

#include "matrix.hpp"
#include <chrono>
#include <stdexcept>


Matrix matrix_multiply_locality(const Matrix &matrix1, const Matrix &matrix2) {
  if (matrix1.getCols() != matrix2.getRows()) {
    throw std::invalid_argument(
        "Matrix dimensions are not compatible for multiplication.");
  }

  size_t M = matrix1.getRows(), K = matrix1.getCols(), N = matrix2.getCols();

  Matrix result(M, N);

  const size_t BLOCK_SIZE = 1024;
  for (size_t kk = 0; kk < K; kk += BLOCK_SIZE) {
    for (size_t ii = 0; ii < M; ii += BLOCK_SIZE) {
      for (size_t jj = 0; jj < N; jj += BLOCK_SIZE) {
        size_t k_end = std::min(kk + BLOCK_SIZE, K);
        for (size_t k = kk; k < k_end; ++k) {
          const int *matrix2_k = matrix2[k];

          size_t i_end = std::min(ii + BLOCK_SIZE, M);
          for (size_t i = ii; i < i_end; ++i) {
            int *result_i = result[i];
            int matrix1_ik = matrix1[i][k];

            size_t j = jj;
            size_t j_end = std::min(jj + BLOCK_SIZE, N);
            for (; j + 4 < j_end; j += 4) {
              result_i[j] += matrix1_ik * matrix2_k[j];
              result_i[j + 1] += matrix1_ik * matrix2_k[j + 1];
              result_i[j + 2] += matrix1_ik * matrix2_k[j + 2];
              result_i[j + 3] += matrix1_ik * matrix2_k[j + 3];
            }
            for (; j < std::min(jj + BLOCK_SIZE, N); ++j) {
              result_i[j] += matrix1_ik * matrix2_k[j];
            }
          }
        }
      }
    }
  }

  return result;
}

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 4) {
    throw std::invalid_argument(
        "Invalid argument, should be: ./executable "
        "/path/to/matrix1 /path/to/matrix2 /path/to/multiply_result\n");
  }

  const std::string matrix1_path = argv[1];

  const std::string matrix2_path = argv[2];

  const std::string result_path = argv[3];

  Matrix matrix1 = Matrix::loadFromFile(matrix1_path);

  Matrix matrix2 = Matrix::loadFromFile(matrix2_path);

  auto start_time = std::chrono::high_resolution_clock::now();

  Matrix result = matrix_multiply_locality(matrix1, matrix2);

  auto end_time = std::chrono::high_resolution_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  result.saveToFile(result_path);

  std::cout << "Output file to: " << result_path << std::endl;

  std::cout << "Multiplication Complete!" << std::endl;
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
            << std::endl;

  return 0;
}
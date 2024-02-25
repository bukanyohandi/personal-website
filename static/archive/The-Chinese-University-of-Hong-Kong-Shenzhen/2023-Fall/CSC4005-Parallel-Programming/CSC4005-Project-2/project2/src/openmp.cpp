//
// Created by Yohandi on 2023/10/27.
// Email: yohandi@link.cuhk.edu.cn
//
// Template is provided by Yang Yufan
// Email: yufanyang1@link.cuhk.edu.cn
//
// OpenMp + SIMD + Reordering Matrix Multiplication
//

#include "matrix.hpp"
#include <chrono>
#include <immintrin.h>
#include <omp.h>
#include <stdexcept>

Matrix matrix_multiply_openmp(const Matrix &matrix1, const Matrix &matrix2) {
  if (matrix1.getCols() != matrix2.getRows()) {
    throw std::invalid_argument(
        "Matrix dimensions are not compatible for multiplication.");
  }

  size_t M = matrix1.getRows(), K = matrix1.getCols(), N = matrix2.getCols();
  Matrix result(M, N);

#pragma omp parallel for schedule(dynamic)                                     \
    shared(M, N, K, matrix1, matrix2, result)
  for (size_t i = 0; i < M; ++i) {
    int *result_i = result[i];
    for (size_t k = 0; k < K; ++k) {
      int matrix1_ik = matrix1[i][k];
      const int *matrix2_k = matrix2[k];
      __m256i vec_matrix1_ik = _mm256_set1_epi32(matrix1_ik);

      size_t j = 0;
      for (; j < N; j += 8) {
        __m256i vec_matrix2 = _mm256_loadu_si256(
            reinterpret_cast<const __m256i *>(&matrix2_k[j]));
        __m256i vec_product = _mm256_mullo_epi32(vec_matrix2, vec_matrix1_ik);
        __m256i vec_result =
            _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&result_i[j]));
        vec_result = _mm256_add_epi32(vec_result, vec_product);
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(&result_i[j]),
                            vec_result);
      }
    }
  }

  return result;
}

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 5) {
    throw std::invalid_argument(
        "Invalid argument, should be: ./executable thread_num"
        "/path/to/matrix1 /path/to/matrix2 /path/to/multiply_result\n");
  }

  int thread_num = atoi(argv[1]);
  omp_set_num_threads(thread_num);

  const std::string matrix1_path = argv[2];

  const std::string matrix2_path = argv[3];

  const std::string result_path = argv[4];

  Matrix matrix1 = Matrix::loadFromFile(matrix1_path);

  Matrix matrix2 = Matrix::loadFromFile(matrix2_path);

  auto start_time = std::chrono::high_resolution_clock::now();

  Matrix result = matrix_multiply_openmp(matrix1, matrix2);

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

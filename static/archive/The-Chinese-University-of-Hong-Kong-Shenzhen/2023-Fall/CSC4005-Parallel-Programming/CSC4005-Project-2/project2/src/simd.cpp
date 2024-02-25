//
// Created by Yohandi on 2023/10/27.
// Email: yohandi@link.cuhk.edu.cn
//
// Template is provided by Yang Yufan
// Email: yufanyang1@link.cuhk.edu.cn
//
// SIMD + Reordering Matrix Multiplication
//

#include "matrix.hpp"
#include <chrono>
#include <immintrin.h>
#include <stdexcept>


Matrix matrix_multiply_simd(const Matrix &matrix1, const Matrix &matrix2) {
  if (matrix1.getCols() != matrix2.getRows()) {
    throw std::invalid_argument(
        "Matrix dimensions are not compatible for multiplication.");
  }

  size_t M = matrix1.getRows(), K = matrix1.getCols(), N = matrix2.getCols();
  Matrix result(M, N);

  const size_t BLOCK_SIZE = 256;
  const size_t TILE_SIZE = 32;

  for (size_t kk = 0; kk < K; kk += BLOCK_SIZE) {
    for (size_t ii = 0; ii < M; ii += BLOCK_SIZE) {
      for (size_t jj = 0; jj < N; jj += BLOCK_SIZE) {

        size_t k_end = std::min(kk + BLOCK_SIZE, K);
        size_t i_end = std::min(ii + BLOCK_SIZE, M);
        size_t j_end = std::min(jj + BLOCK_SIZE, N);

        for (size_t k = kk; k < k_end; k += TILE_SIZE) {
          for (size_t i = ii; i < i_end; i += TILE_SIZE) {
            for (size_t j = jj; j < j_end; j += TILE_SIZE) {

              size_t kt_end = std::min(k + TILE_SIZE, k_end);
              size_t it_end = std::min(i + TILE_SIZE, i_end);
              size_t jt_end = std::min(j + TILE_SIZE, j_end);

              for (size_t kt = k; kt < kt_end; ++kt) {
                const int *matrix2_k = matrix2[kt];
                for (size_t it = i; it < it_end; ++it) {
                  int *result_i = result[it];
                  int matrix1_ik = matrix1[it][kt];
                  __m512i vec_matrix1_ik = _mm512_set1_epi32(matrix1_ik);
                  size_t jt = j;

                  for (; jt + 31 < jt_end; jt += 32) {
                    __m512i vec_matrix2 = _mm512_loadu_si512(
                        reinterpret_cast<const __m512i *>(&matrix2_k[jt]));
                    __m512i vec_product =
                        _mm512_mullo_epi32(vec_matrix2, vec_matrix1_ik);
                    __m512i vec_result = _mm512_loadu_si512(
                        reinterpret_cast<const __m512i *>(&result_i[jt]));
                    vec_result = _mm512_add_epi32(vec_result, vec_product);
                    _mm512_storeu_si512(
                        reinterpret_cast<__m512i *>(&result_i[jt]), vec_result);

                    vec_matrix2 = _mm512_loadu_si512(
                        reinterpret_cast<const __m512i *>(&matrix2_k[jt + 16]));
                    vec_product =
                        _mm512_mullo_epi32(vec_matrix2, vec_matrix1_ik);
                    vec_result = _mm512_loadu_si512(
                        reinterpret_cast<const __m512i *>(&result_i[jt + 16]));
                    vec_result = _mm512_add_epi32(vec_result, vec_product);
                    _mm512_storeu_si512(
                        reinterpret_cast<__m512i *>(&result_i[jt + 16]),
                        vec_result);
                  }

                  for (; jt < jt_end; ++jt) {
                    result_i[jt] += matrix1_ik * matrix2_k[jt];
                  }
                }
              }
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

  Matrix result = matrix_multiply_simd(matrix1, matrix2);

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
//
// Created by Yohandi on 2023/10/27.
// Email: yohandi@link.cuhk.edu.cn
//
// Template is provided by Yang Yufan
// Email: yufanyang1@link.cuhk.edu.cn
//
// MPI + OpenMp + SIMD + Reordering Matrix Multiplication
//

#include "matrix.hpp"
#include <chrono>
#include <immintrin.h>
#include <mpi.h> // MPI Header
#include <omp.h>
#include <stdexcept>


#define MASTER 0

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 5) {
    throw std::invalid_argument(
        "Invalid argument, should be: ./executable thread_num "
        "/path/to/matrix1 /path/to/matrix2 /path/to/multiply_result\n");
  }

  // Start the MPI
  MPI_Init(&argc, &argv);

  int thread_num = atoi(argv[1]);
  omp_set_num_threads(thread_num);

  // Read Matrix
  const std::string matrix1_path = argv[2];
  const std::string matrix2_path = argv[3];
  const std::string result_path = argv[4];

  Matrix matrix1 = Matrix::loadFromFile(matrix1_path);
  Matrix matrix2 = Matrix::loadFromFile(matrix2_path);

  auto start_time = std::chrono::high_resolution_clock::now();

  size_t M = matrix1.getRows(), K = matrix1.getCols(), N = matrix2.getCols();

  // How many processes are running
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // What's my rank?
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // Which node am I running on?
  int len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(hostname, &len);
  MPI_Status status;

  size_t rows_per_process = M / size;
  size_t start_row = rank * rows_per_process;
  size_t end_row = (rank == size - 1) ? M : start_row + rows_per_process;

  Matrix local_result(end_row - start_row, N);

  const size_t BLOCK_SIZE = 128;
  const size_t TILE_SIZE = 32;

#pragma omp parallel for collapse(3) schedule(dynamic)
  for (size_t kk = 0; kk < K; kk += BLOCK_SIZE) {
    for (size_t ii = start_row; ii < end_row; ii += BLOCK_SIZE) {
      for (size_t jj = 0; jj < N; jj += BLOCK_SIZE) {
        size_t k_end = std::min(kk + BLOCK_SIZE, K);
        size_t i_end = std::min(ii + BLOCK_SIZE, end_row);
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
                  int *result_i = local_result[it - start_row];
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

  if (rank == MASTER) {
    Matrix result(M, N);

    for (size_t i = 0; i < end_row - start_row; i++)
      for (size_t j = 0; j < N; j++)
        result[i][j] = local_result[i][j];

    size_t rows_per_process = matrix1.getRows() / size;
    for (int source = 1; source < size; source++) {
      size_t start_row = source * rows_per_process;
      size_t end_row = (source == size - 1) ? matrix1.getRows()
                                            : start_row + rows_per_process;

      for (size_t i = start_row; i < end_row; i++) {
        MPI_Recv(result[i], N, MPI_INT, source, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
      }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    result.saveToFile(result_path);

    std::cout << "Output file to: " << result_path << std::endl;

    std::cout << "Multiplication Complete!" << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
              << std::endl;
  } else {
    for (size_t i = 0; i < local_result.getRows(); i++) {
      MPI_Send(local_result[i], N, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}

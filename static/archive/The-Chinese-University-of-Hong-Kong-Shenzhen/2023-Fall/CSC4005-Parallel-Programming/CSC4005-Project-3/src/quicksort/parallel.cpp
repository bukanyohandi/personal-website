//
// Created by Yang Yufan on 2023/10/31.
// Email: yufanyang1@link.cuhk.edu.cn
//
// Parallel Quick Sort
//

#include <iostream>
#include <vector>
#include "../utils.hpp"

const int MAX_DEPTH = 4;
const int SMALL_SIZE = 10000;

int partition(std::vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void quickSort(std::vector<int> &vec, int low, int high);

void parallelQuickSort(std::vector<int> &vec, int low, int high, int depth = 0) {
    if (low < high) {
        int pivotIndex = partition(vec, low, high);

        if (depth < MAX_DEPTH) {
            #pragma omp task shared(vec) if(high - low > SMALL_SIZE)
            parallelQuickSort(vec, low, pivotIndex - 1, depth + 1);

            #pragma omp task shared(vec) if(high - low > SMALL_SIZE)
            parallelQuickSort(vec, pivotIndex + 1, high, depth + 1);

            #pragma omp taskwait
        } else {
            quickSort(vec, low, pivotIndex - 1);
            quickSort(vec, pivotIndex + 1, high);
        }
    }
}

void quickSort(std::vector<int> &vec, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(vec, low, high);
        quickSort(vec, low, pivotIndex - 1);
        quickSort(vec, pivotIndex + 1, high);
    }
}

int main(int argc, char** argv) {
    // Verify input argument format
    if (argc != 3) {
        throw std::invalid_argument(
            "Invalid argument, should be: ./executable threads_num vector_size\n"
            );
    }

    const int thread_num = atoi(argv[1]);

    const int size = atoi(argv[2]);

    const int seed = 4005;

    std::vector<int> vec = createRandomVec(size, seed);
    std::vector<int> vec_clone = vec;

    auto start_time = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelQuickSort(vec, 0, size - 1, 0);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    std::cout << "Quick Sort Complete!" << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
              << std::endl;

    checkSortResult(vec_clone, vec);

    return 0;
}
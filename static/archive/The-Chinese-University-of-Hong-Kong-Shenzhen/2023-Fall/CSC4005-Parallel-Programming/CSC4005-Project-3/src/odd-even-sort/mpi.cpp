//
// Created by Yang Yufan on 2023/10/31.
// Email: yufanyang1@link.cuhk.edu.cn
//
// Parallel Odd-Even Sort with MPI
//

#include <iostream>
#include <vector>
#include <mpi.h>
#include "../utils.hpp"

#define MASTER 0

#include <vector>
#include <mpi.h>

void oddEvenSort(std::vector<int>& vec, int numtasks, int taskid, MPI_Status* status) {
    int n = (int)vec.size();
    int chunk = n / numtasks;
    int leftover = n % numtasks;
    std::vector<int> from(numtasks, 0), to(numtasks, 0);
    for(int i = 0; i < numtasks; ++i){
        to[i] = from[i] + chunk;
        if(i < leftover)
            to[i]++;
        if(i + 1 != numtasks)
            from[i + 1] = to[i];
    }

    bool sorted = false, globallySorted = false;
    int received;

    int start = from[taskid];
    int end = to[taskid];

    int reduceCnt = 0;
    int reduceCntStopper = 32 * 32;

    while (true) {
        sorted = true;

        // Perform the odd phase
        for (int i = start + (1 - start % 2); i + 1 < end; i += 2) {
            if (vec[i] > vec[i + 1]) {
                int tmp = vec[i + 1];
                vec[i + 1] = vec[i];
                vec[i] = tmp;
                sorted = false;
            }
        }

        if(end != n && end % 2 == 0){
            MPI_Send(&vec[end - 1], 1, MPI_INT, taskid + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&vec[end], 1, MPI_INT, taskid + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(vec[end] < vec[end - 1]){
                vec[end - 1] = vec[end];
                sorted = false;
            }
        }
        if(start != 0 && start % 2 == 0){
            MPI_Recv(&vec[start - 1], 1, MPI_INT, taskid - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&vec[start], 1, MPI_INT, taskid - 1, 0, MPI_COMM_WORLD);
            if(vec[start - 1] > vec[start]){
                vec[start] = vec[start - 1];
            }
        }

        // Perform the even phase
        for (int i = start + (start % 2); i + 1 < end; i += 2) {
            if (vec[i] > vec[i + 1]) {
                int tmp = vec[i + 1];
                vec[i + 1] = vec[i];
                vec[i] = tmp;
                sorted = false;
            }
        }

        if(end != n && end % 2 == 1){
            MPI_Send(&vec[end - 1], 1, MPI_INT, taskid + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&vec[end], 1, MPI_INT, taskid + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(vec[end] < vec[end - 1]){
                vec[end - 1] = vec[end];
                sorted = false;
            }
        }
        if(start != 0 && start % 2 == 1){
            MPI_Recv(&vec[start - 1], 1, MPI_INT, taskid - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&vec[start], 1, MPI_INT, taskid - 1, 0, MPI_COMM_WORLD);
            if(vec[start - 1] > vec[start]){
                vec[start] = vec[start - 1];
            }
        }

        if(reduceCnt == reduceCntStopper){
            reduceCnt = 0;
            bool global;
            MPI_Allreduce(&sorted, &global, 1, MPI_C_BOOL, MPI_LAND, MPI_COMM_WORLD);
            if(global) break;
        } else {
            reduceCnt++;
        }
    }

    if(taskid == MASTER){
        for(int i = 1; i < numtasks; ++i){
            MPI_Recv(&vec[from[i]], to[i] - from[i], MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else {
        MPI_Send(&vec[start], end - start, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
    }
}

int main(int argc, char** argv) {
    // Verify input argument format
    if (argc != 2) {
        throw std::invalid_argument(
            "Invalid argument, should be: ./executable vector_size\n"
            );
    }
    // Start the MPI
    MPI_Init(&argc, &argv);
    // How many processes are running
    int numtasks;
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    // What's my rank?
    int taskid;
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    // Which node am I running on?
    int len;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(hostname, &len);
    MPI_Status status;

    const int size = atoi(argv[1]);

    const int seed = 4005;

    std::vector<int> vec = createRandomVec(size, seed);
    std::vector<int> vec_clone = vec;

    auto start_time = std::chrono::high_resolution_clock::now();

    oddEvenSort(vec, numtasks, taskid, &status);

    if (taskid == MASTER) {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        std::cout << "Odd-Even Sort Complete!" << std::endl;
        std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
                << std::endl;
        
        checkSortResult(vec_clone, vec);
    }

    MPI_Finalize();
    return 0;
}
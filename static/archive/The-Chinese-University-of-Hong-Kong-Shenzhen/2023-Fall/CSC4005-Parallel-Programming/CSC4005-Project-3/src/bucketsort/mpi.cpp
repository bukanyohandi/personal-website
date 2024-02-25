//
// Created by Yang Yufan on 2023/10/31.
// Email: yufanyang1@link.cuhk.edu.cn
//
// Parallel Bucket Sort with MPI
//

#include <iostream>
#include <vector>
#include <mpi.h>
#include "../utils.hpp"

#define MASTER 0

void insertionSort(std::vector<int>& bucket) {
    for (int i = 1; i < bucket.size(); ++i) {
        int key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }

        bucket[j + 1] = key;
    }
}

void bucketSort(std::vector<int>& vec, int num_buckets, int numtasks, int taskid, MPI_Status* status) {
    int num_buckets_chunk = num_buckets / numtasks;
    int num_buckets_leftover = num_buckets % numtasks;
    std::vector<int> num_buckets_from(numtasks, 0), num_buckets_to(numtasks, 0);
    for(int i = 0; i < numtasks; ++i){
        num_buckets_to[i] = num_buckets_from[i] + num_buckets_chunk;
        if(i < num_buckets_leftover)
            num_buckets_to[i]++;
        if(i + 1 != numtasks)
            num_buckets_from[i + 1] = num_buckets_to[i];
    }

    int current_num_buckets = num_buckets_to[taskid] - num_buckets_from[taskid];
    if(current_num_buckets == 0){
        return;
    }

    int max_val = *std::max_element(vec.begin(), vec.end()) + 1;
    int min_val = *std::min_element(vec.begin(), vec.end());

    int range = max_val - min_val;
    int range_chunk = range / num_buckets;
    int range_leftover = range % num_buckets;
    std::vector<int> range_from(num_buckets, 0), range_to(num_buckets, 0);
    for(int i = 0; i < num_buckets; ++i){
        range_to[i] = range_from[i] + range_chunk;
        if(i < range_leftover)
            range_to[i]++;
        if(i + 1 != num_buckets)
            range_from[i + 1] = range_to[i];
    }

    int range_bucket = range_to[num_buckets_to[taskid] - 1] - range_from[num_buckets_from[taskid]];

    std::vector<int> range_bucket_from(current_num_buckets, 0), range_bucket_to(current_num_buckets, 0);
    int range_bucket_chunk = range_bucket / current_num_buckets;
    int range_bucket_leftover = range_bucket % current_num_buckets;
    range_bucket_from[0] = min_val + range_from[num_buckets_from[taskid]];
    for(int i = 0; i < current_num_buckets; ++i){
        range_bucket_to[i] = range_bucket_from[i] + range_bucket_chunk;
        if(i < range_bucket_leftover)
            range_bucket_to[i]++;
        if(i + 1 != current_num_buckets)
            range_bucket_from[i + 1] = range_bucket_to[i];
    }

    std::vector<std::vector<int>> buckets(current_num_buckets);
    for(int num: vec){
        if(num < min_val + range_from[num_buckets_from[taskid]] || num >= min_val + range_to[num_buckets_to[taskid] - 1]) continue;

        int index;
        if(num - min_val < range_bucket_leftover * (range_bucket_chunk + 1)){
            index = (num - min_val) / (range_bucket_chunk + 1);  
        } else {
            index = range_bucket_leftover + (num - range_bucket_from[range_bucket_leftover]) / range_bucket_chunk;
        }
        buckets[index].push_back(num);
    }

    int current_n = 0;
    for(int i = 0; i < current_num_buckets; ++i){
        current_n += (int)buckets[i].size();
        insertionSort(buckets[i]);
    }

    int ptr = 0;
    int *arr = new int[current_n];
    for(std::vector<int> bucket: buckets){
        for(int num: bucket){
            arr[ptr++] = num;
        }
    }
    
    if(taskid == MASTER){
        for(int i = 0; i < current_n; ++i){
            vec[i] = arr[i];
        }
        int local_size = current_n;
        for(int i = 1; i < numtasks; ++i){
            if(num_buckets_to[i] - num_buckets_from[i] == 0){
                continue;
            }

            int local_n;
            MPI_Recv(&local_n, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&vec[local_size], local_n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            local_size += local_n;
        }
    } else {
        MPI_Send(&current_n, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
        MPI_Send(arr, current_n, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
    }

    return;
}

int main(int argc, char** argv) {
    // Verify input argument format
    if (argc != 3) {
        throw std::invalid_argument(
            "Invalid argument, should be: ./executable vector_size bucket_num\n"
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

    const int bucket_num = atoi(argv[2]);

    const int seed = 4005;

    std::vector<int> vec = createRandomVec(size, seed);
    std::vector<int> vec_clone = vec;

    auto start_time = std::chrono::high_resolution_clock::now();

    bucketSort(vec, bucket_num, numtasks, taskid, &status);

    if (taskid == MASTER) {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        std::cout << "Bucket Sort Complete!" << std::endl;
        std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
                << std::endl;
        
        checkSortResult(vec_clone, vec);
    }

    MPI_Finalize();
    return 0;
}
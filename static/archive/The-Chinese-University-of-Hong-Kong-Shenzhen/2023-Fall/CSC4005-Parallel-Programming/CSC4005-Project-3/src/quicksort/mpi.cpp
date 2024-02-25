//
// Created by Yang Yufan on 2023/10/31.
// Email: yufanyang1@link.cuhk.edu.cn
//
// Parallel Quick Sort with MPI
//


#include <iostream>
#include <vector>
#include <mpi.h>
#include "../utils.hpp"
using namespace std;

#define MASTER 0

void swap(int *a, int *b){
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

struct heap{
    int n = 0;
    int arr_key[32], arr_part[32];

    int parent(int idx){
        return (idx - 1) / 2;
    }
    int left(int idx){
        return 2 * idx + 1;
    }
    int right(int idx){
        return 2 * idx + 2;
    }

    void insert(int key, int part){
        n++;

        int idx = n - 1;
        arr_key[idx] = key;
        arr_part[idx] = part;

        while(idx != 0 && arr_key[parent(idx)] > arr_key[idx]){
            swap(&arr_key[parent(idx)], &arr_key[idx]);
            swap(&arr_part[parent(idx)], &arr_part[idx]);

            idx = parent(idx);
        }
    }

    void heapify(int idx){
        int le = left(idx);
        int ri = right(idx);
        int current = idx;
        if(le < n && arr_key[le] < arr_key[current]){
            current = le;
        }
        if(ri < n && arr_key[ri] < arr_key[current]){
            current = ri;
        }
        if(current != idx){
            swap(&arr_key[idx], &arr_key[current]);
            swap(&arr_part[idx], &arr_part[current]);

            heapify(current);
        }
    }

    void getTop(int &key, int &part){
        key = arr_key[0];
        part = arr_part[0];

        arr_key[0] = arr_key[n - 1];
        arr_part[0] = arr_part[n - 1];
        n--;

        if(n > 0){
            heapify(0);
        }
    }
};

int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);
    return i + 1;
}

void quickSort(vector<int> &vec, int low, int high){
    if(low < high){
        int mid = partition(vec, low, high);
        quickSort(vec, low, mid - 1);
        quickSort(vec, mid + 1, high);
    }

    return;
}

void quickSort(vector<int>& vec, int numtasks, int taskid, MPI_Status* status) {
    /*
       Implement parallel quick sort with MPI
    */

    int n = (int)vec.size();
    vector<int> low(numtasks, 0), high(numtasks, 0);

    int chunk = n / numtasks;
    int leftover = n % numtasks;
    for(int i = 0; i < numtasks; ++i){
        high[i] = low[i] + chunk;
        if(i < leftover)
            high[i]++;
        if(i + 1 != numtasks)
            low[i + 1] = high[i];
    }

    quickSort(vec, low[taskid], high[taskid] - 1);
    if(taskid == MASTER){
        for(int i = 1; i < numtasks; ++i){
            MPI_Recv(&vec[low[i]], high[i] - low[i], MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        int p[numtasks];
        heap bucket;
        for(int i = 0; i < numtasks; ++i){
            if(high[i] - low[i] != 0){
                bucket.insert(vec[low[i]], i);
                p[i] = low[i] + 1;
            }
        }

        vector<int> result;
        while(bucket.n > 0){
            int key, part;
            bucket.getTop(key, part);

            if(p[part] < high[part]){
                bucket.insert(vec[p[part]], part);
                p[part]++;
            }

            result.push_back(key);
        }
        swap(vec, result);
    } else {
        MPI_Send(&vec[low[taskid]], high[taskid] - low[taskid], MPI_INT, MASTER, 0, MPI_COMM_WORLD);
    }

    return;
}

int main(int argc, char** argv) {
    // Verify input argument format
    if (argc != 2) {
        throw invalid_argument(
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

    vector<int> vec = createRandomVec(size, seed);
    vector<int> vec_clone = vec;

    auto start_time = chrono::high_resolution_clock::now();

    quickSort(vec, numtasks, taskid, &status);

    if (taskid == MASTER) {
        auto end_time = chrono::high_resolution_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(
            end_time - start_time);
        
        cout << "Quick Sort Complete!" << endl;
        cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
                << endl;
        
        checkSortResult(vec_clone, vec);
    }

    MPI_Finalize();
    return 0;
}
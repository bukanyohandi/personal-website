//
// Created by Yang Yufan on 2023/10/31.
// Email: yufanyang1@link.cuhk.edu.cn
//
// Parallel Merge Sort
//

#include "../utils.hpp"
#include <algorithm>
#include <chrono>
#include <climits>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <future>
#include "omp.h"

class ThreadPool {
public:
    ThreadPool(): stop(false) {}
    void set(size_t threads) {
        n = threads;
        for(size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while(true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    int size(){
      return n;
    }

    template<class F, class... Args>
    auto enqueue(F f, Args... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            [f, args...] { return f(args...); }
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task] { (*task)(); });
        }
        condition.notify_one();
        return res;
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &worker: workers)
            worker.join();
    }
private:
    int n;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

ThreadPool pool;

const int BORDER = 1000000;

int findMedian(const std::vector<int> &left, int l_1, int r_1,
               const std::vector<int> &right, int l_2, int r_2) {
  int m = r_1 - l_1;
  int n = r_2 - l_2;

  if(m < n){
    return -right[(l_2 + r_2) / 2];
  }
  return left[(l_1 + r_1) / 2];
}

void mergeHalf(std::vector<int> &vec, int start, std::vector<int> &L, int l_1,
               int r_1, std::vector<int> &R, int l_2, int r_2) {
  for (int i = r_2 - 1; i >= l_2; i--) {
      int j, last = L[r_1 - 1];
      for (j = r_1 - 2; j >= 0 && L[j] > R[i]; j--)
          L[j + 1] = L[j];

      if (last > R[i]) {
          L[j + 1] = R[i];
          R[i] = last;
      }
  }
}

void parallelMerge(std::vector<int> &vec, int start, std::vector<int> &vec_1,
                   int l_1, int r_1, std::vector<int> &vec_2, int l_2, int r_2) {
  if (r_1 - l_1 + r_2 - l_2 <= BORDER) {
    return mergeHalf(vec, start, vec_1, l_1, r_1, vec_2, l_2, r_2);
  }

  int median = findMedian(vec_1, l_1, r_1, vec_2, l_2, r_2);
  int m1, m2;
  if(median < 0){
    median = -median;
    m1 = std::lower_bound(vec_1.begin() + l_1, vec_1.begin() + r_1, median) -
           vec_1.begin() - l_1;
    m2 = (l_2 + r_2) / 2 - l_2;
  } else {
    m1 = (l_1 + r_1) / 2 - l_1;
    m2 = std::lower_bound(vec_2.begin() + l_2, vec_2.begin() + r_2, median) -
           vec_2.begin() - l_2;
  }

  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      parallelMerge(vec, start, vec_1, l_1, l_1 + m1, vec_2, l_2, l_2 + m2);
      #pragma omp section
      parallelMerge(vec, start + m1 + m2, vec_1, l_1 + m1, r_1, vec_2, l_2 + m2, r_2);
    }
  }
}

void copyChunk(const std::vector<int>& src, std::vector<int>& dest, int start, int end, int offset) {
    for (int i = start; i < end; ++i) {
        dest[i - offset] = src[i];
    }
}

void parallelCopy(const std::vector<int>& src, std::vector<int>& dest, int l, int r) {
    int n = r - l + 1;
    int chunkSize = n / pool.size();

    std::vector<std::future<void>> futures;
    for (int i = 0; i < pool.size(); ++i) {
        int start = l + i * chunkSize;
        int end = (i == pool.size() - 1) ? r + 1 : start + chunkSize;
        futures.emplace_back(pool.enqueue(copyChunk, std::ref(src), std::ref(dest), start, end, l));
    }

    for (auto& fut : futures) {
        fut.get();
    }
}

void parallelMerge(std::vector<int> &vec, int l, int m, int r) {
  return parallelMerge(vec, l, vec, 0, m - l + 1, vec, m - l + 1, r - l + 1);
}

void mergeSortParallel(std::vector<int> &vec, int l, int r, int depth) {
  if (l < r) {
    int m = (l + r) / 2;
    
    if(depth > 0){
      auto fut_1 = pool.enqueue(mergeSortParallel, std::ref(vec), l, m, depth - 1);
      mergeSortParallel(vec, m + 1, r, depth - 1);
      fut_1.get();
    } else {
      mergeSortParallel(vec, l, m, 0);
      mergeSortParallel(vec, m + 1, r, 0);
    }

    // if(r - l + 1 >= 2 * BORDER){
      // parallelMerge(vec, l, m, r);
    // } else {
      inplace_merge(vec.begin() + l, vec.begin() + m + 1, vec.begin() + r + 1);
    // }
  }
}

void mergeSort(std::vector<int> &vec, int l, int r, int thread_num) {
  thread_num = 4 * thread_num;
  pool.set(thread_num);

  int depth = 0;
  while ((1 << depth) < thread_num) {
    depth++;
  }
  mergeSortParallel(vec, 0, vec.size() - 1, depth);
}

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 3) {
    throw std::invalid_argument(
        "Invalid argument, should be: ./executable threads_num vector_size\n");
  }

  int thread_num = atoi(argv[1]);

  const int size = atoi(argv[2]);

  const int seed = 4005;

  std::vector<int> vec = createRandomVec(size, seed);
  std::vector<int> vec_clone = vec;

  std::vector<int> S(size);
  std::vector<int> L(size);
  std::vector<int> results(size);

  auto start_time = std::chrono::high_resolution_clock::now();

  mergeSort(vec, 0, size - 1, thread_num);

  auto end_time = std::chrono::high_resolution_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  std::cout << "Merge Sort Complete!" << std::endl;
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
            << std::endl;

  checkSortResult(vec_clone, vec);
}
#!/bin/bash
#SBATCH -o ./Project3-Perf-Result.txt
#SBATCH -p Project
#SBATCH -J Project3
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --gres=gpu:1

CURRENT_DIR=$(pwd)/build/src
QUICK_SIZE=100000000
BUCKET_SIZE=100000000
BUCKETS=1000000
ODD_EVEN_SIZE=200000
MERGE_SIZE=100000000

# Task 1
# echo "Quick Sort MPI (Optimized with -O2)"
# for num_cores in 1 2 4 8 16 32
# do
#   echo "Number of cores: $num_cores"
#   srun -n $num_cores --cpus-per-task 1 --mpi=pmi2 perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/quicksort/quicksort_mpi ${QUICK_SIZE}
# done
# echo ""

# Task 2
# echo "Bucket Sort MPI (Optimized with -O2)"
# for num_cores in 1 2 4 8 16 32
# do
#   echo "Number of cores: $num_cores"
#   srun -n $num_cores --cpus-per-task 1 --mpi=pmi2 perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/bucketsort/bucketsort_mpi ${BUCKET_SIZE} ${BUCKETS}
# done
# echo ""

# Task 3
# echo "Odd-Even Sort MPI (Optimized with -O2)"
# for num_cores in 1 2 4 8 16 32
# do
#   echo "Number of cores: $num_cores"
#   srun -n $num_cores --cpus-per-task 1 --mpi=pmi2 perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/odd-even-sort/odd-even-sort_mpi ${ODD_EVEN_SIZE}
# done
# echo ""

# Task 4
echo "Merge Sort Parallel (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task=$num_cores perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/mergesort/mergesort_parallel ${num_cores} ${MERGE_SIZE}
done
echo ""

# Task 5
echo "Quick Sort Parallel (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task=$num_cores perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/quicksort/quicksort_parallel $num_cores ${QUICK_SIZE}
done
echo ""
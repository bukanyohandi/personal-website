#!/bin/bash
#SBATCH -o ./Project3-Result.txt
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

# Quick Sort
# MPI
echo "Quick Sort MPI (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n $num_cores --cpus-per-task 1 --mpi=pmi2 ${CURRENT_DIR}/quicksort/quicksort_mpi ${QUICK_SIZE}
done
echo ""

# Bucket Sort
# MPI
echo "Bucket Sort MPI (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n $num_cores --cpus-per-task 1 --mpi=pmi2 ${CURRENT_DIR}/bucketsort/bucketsort_mpi ${BUCKET_SIZE} ${BUCKETS}
done
echo ""

# Odd-Even Sort
# MPI
echo "Odd-Even Sort MPI (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n $num_cores --cpus-per-task 1 --mpi=pmi2 ${CURRENT_DIR}/odd-even-sort/odd-even-sort_mpi ${ODD_EVEN_SIZE}
done
echo ""

# Merge Sort
# Sequential vs. Parallel
echo "Merge Sort Sequential vs. Parallel 32 Cores (Optimized with -O2)"
for size in 1000 5000 10000 50000 100000 500000 1000000 5000000 10000000 50000000
do
  echo "SIZE = ${size}"
  srun -n 1 --cpus-per-task=32 ${CURRENT_DIR}/mergesort/mergesort_sequential ${size}
  srun -n 1 --cpus-per-task=32 ${CURRENT_DIR}/mergesort/mergesort_parallel 32 ${size}
done
echo ""
# Parallel
echo "Merge Sort Parallel (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task=$num_cores ${CURRENT_DIR}/mergesort/mergesort_parallel ${num_cores} ${MERGE_SIZE}
done
echo ""

# Quick Sort
# Sequential vs. Parallel
echo "Quick Sort Sequential vs. Parallel 32 Cores (Optimized with -O2)"
for size in 1000 5000 10000 50000 100000 500000 1000000 5000000 10000000 50000000
do
  echo "SIZE = ${size}"
  srun -n 1 --cpus-per-task=32 ${CURRENT_DIR}/quicksort/quicksort_sequential ${size}
  srun -n 1 --cpus-per-task=32 ${CURRENT_DIR}/quicksort/quicksort_parallel 32 ${size}
done
echo ""
# Parallel
echo "Quick Sort Parallel (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task=$num_cores ${CURRENT_DIR}/quicksort/quicksort_parallel $num_cores ${QUICK_SIZE}
done
echo ""

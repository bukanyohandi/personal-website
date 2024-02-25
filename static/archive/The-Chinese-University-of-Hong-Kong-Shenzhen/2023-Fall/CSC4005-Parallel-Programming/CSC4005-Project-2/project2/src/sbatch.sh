#!/bin/bash

# SLURM configurations
#SBATCH -o ./Project2-Results.txt
#SBATCH -p Project
#SBATCH -J Project2
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --gres=gpu:1

CURRENT_DIR=$(pwd)/src

# Global constants for matrices
MATRIX_A="${CURRENT_DIR}/../matrices/matrix5.txt"
MATRIX_B="${CURRENT_DIR}/../matrices/matrix6.txt"

# Naive
echo "Naive Matrix Multiplication (Optimized with -O2)"
srun -n 1 --cpus-per-task 1 ${CURRENT_DIR}/../build/src/naive $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-naive.txt
echo ""

# Memory Locality
echo "Memory Locality Matrix Multiplication (Optimized with -O2)"
srun -n 1 --cpus-per-task 1 ${CURRENT_DIR}/../build/src/locality $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-locality.txt
echo ""

# SIMD + Reordering
echo "SIMD + Memory Locality Matrix Multiplication (Optimized with -O2)"
srun -n 1 --cpus-per-task 1 ${CURRENT_DIR}/../build/src/simd $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-simd.txt
echo ""

# OpenMP + SIMD + Reordering
echo "OpenMP + SIMD + Memory Locality Matrix Multiplication (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task $num_cores ${CURRENT_DIR}/../build/src/openmp $num_cores $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-openmp.txt
  echo ""
done

# MPI + OpenMP + SIMD + Reordering
for num_cores in 1 2 4 8 16 32
do
  num_threads=$((32 / num_cores))

  echo "MPI + OpenMP + SIMD + Memory Locality Matrix Multiplication (Optimized with -O2)"
  echo "Number of Processes: $num_cores, Number of Threads: $num_threads"
  srun -n $num_cores --cpus-per-task $num_threads --mpi=pmi2 ${CURRENT_DIR}/../build/src/mpi $num_threads $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-mpi.txt
  echo ""
done

# CUDA
echo "CUDA"
srun -n 1 --gpus 1 ${CURRENT_DIR}/../build/src/gpu/cuda $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-cuda.txt
echo ""

g++ src/validator.cpp -o validator
./validator

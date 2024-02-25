#!/bin/bash

# SLURM configurations
#SBATCH -o ./Project2-Results-Perf.txt
#SBATCH -p Project
#SBATCH -J Project2
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --gres=gpu:1

CURRENT_DIR=$(pwd)/src

# Global constants for matrices
MATRIX_A="${CURRENT_DIR}/../matrices/matrix5.txt"
MATRIX_B="${CURRENT_DIR}/../matrices/matrix6.txt"

# Memory Locality
echo "Memory Locality Matrix Multiplication (Optimized with -O2) with Perf Stats"
srun -n 1 --cpus-per-task 1 perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/../build/src/locality $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-locality.txt
echo ""

# SIMD + Reordering
echo "SIMD + Memory Locality Matrix Multiplication (Optimized with -O2) with Perf Stats"
srun -n 1 --cpus-per-task 1 perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/../build/src/simd $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-simd.txt
echo ""

# OpenMP + SIMD + Reordering
echo "OpenMP + SIMD + Memory Locality Matrix Multiplication (Optimized with -O2) with Perf Stats"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task $num_cores perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/../build/src/openmp $num_cores $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-openmp.txt
  echo ""
done

# MPI + OpenMP + SIMD + Reordering
for num_cores in 1 2 4 8 16 32
do
  num_threads=$((32 / num_cores))

  echo "MPI + OpenMP + SIMD + Memory Locality Matrix Multiplication (Optimized with -O2) with Perf Stats"
  echo "Number of Processes: $num_cores, Number of Threads: $num_threads"
  srun -n $num_cores --cpus-per-task $num_threads --mpi=pmi2 perf stat -e cpu-cycles,cache-misses,page-faults ${CURRENT_DIR}/../build/src/mpi $num_threads $MATRIX_A $MATRIX_B ${CURRENT_DIR}/../matrices/result-mpi.txt
  echo ""
done

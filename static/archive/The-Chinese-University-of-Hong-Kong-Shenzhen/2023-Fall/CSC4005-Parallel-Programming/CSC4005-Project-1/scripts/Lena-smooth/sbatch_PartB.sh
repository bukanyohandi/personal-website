#!/bin/bash
#SBATCH -o ./Project1-PartB-Results.txt
#SBATCH -p Project
#SBATCH -J Project1-PartB
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --gres=gpu:1

# Image names as variables
INPUT_IMAGE_NAME="Lena-RGB.jpg"
OUTPUT_IMAGE_NAME="results/Lena-smooth"

# Get the current directory
CURRENT_DIR=$(pwd)/src/scripts
echo "Current directory: ${CURRENT_DIR}"

# Sequential PartB
echo "Sequential PartB (Optimized with -O2)"
srun -n 1 --cpus-per-task 1 ${CURRENT_DIR}/../../build/src/cpu/sequential_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-sequential.jpg
echo ""

# SIMD PartB
echo "SIMD(AVX2) PartB (Optimized with -O2)"
srun -n 1 --cpus-per-task 1 ${CURRENT_DIR}/../../build/src/cpu/simd_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-simd.jpg
echo ""

# MPI PartB
echo "MPI PartB (Optimized with -O2)"
for num_processes in 1 2 4 8 16 32
do
  echo "Number of processes: $num_processes"
  srun -n $num_processes --cpus-per-task 1 --mpi=pmi2 ${CURRENT_DIR}/../../build/src/cpu/mpi_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-mpi-${num_processes}.jpg
  echo ""
done

# Pthread PartB
echo "Pthread PartB (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task $num_cores ${CURRENT_DIR}/../../build/src/cpu/pthread_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-pthread-${num_cores}.jpg ${num_cores}
  echo ""
done

# OpenMP PartB
echo "OpenMP PartB (Optimized with -O2)"
for num_cores in 1 2 4 8 16 32
do
  echo "Number of cores: $num_cores"
  srun -n 1 --cpus-per-task $num_cores ${CURRENT_DIR}/../../build/src/cpu/openmp_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-openmp-${num_cores}.jpg
  echo ""
done

# CUDA PartB
echo "CUDA PartB"
srun -n 1 --gpus 1 ${CURRENT_DIR}/../../build/src/gpu/cuda_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-cuda.jpg
echo ""

# OpenACC PartB
echo "OpenACC PartB"
srun -n 1 --gpus 1 ${CURRENT_DIR}/../../build/src/gpu/openacc_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-openacc.jpg
echo ""

# MPI + OpenMP PartB
echo "MPI+OpenMP PartB (Optimized with -O2)"
for num in 1 2 4 8 16 32
do
    omp_threads=$(( 32 / num ))
    echo "Number of MPI processes: $num, Number of OpenMP threads per process: $omp_threads"
    export OMP_NUM_THREADS=$omp_threads
    srun -n $num --cpus-per-task $omp_threads --mpi=pmi2 ${CURRENT_DIR}/../../build/src/cpu/mpi_openmp_PartB ${CURRENT_DIR}/../../images/${INPUT_IMAGE_NAME} ${CURRENT_DIR}/../../images/${OUTPUT_IMAGE_NAME}-mpi-openmp-${num}x${omp_threads}.jpg
    echo ""
done

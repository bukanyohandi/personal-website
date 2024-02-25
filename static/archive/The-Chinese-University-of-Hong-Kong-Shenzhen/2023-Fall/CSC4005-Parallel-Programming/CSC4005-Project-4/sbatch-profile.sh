#!/bin/bash
#SBATCH -o ./Project4-Profile-Results.txt
#SBATCH -p Project
#SBATCH -J Project4
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --gres=gpu:1

# Get the current directory
CURRENT_DIR=$(pwd)
echo "Current directory: ${CURRENT_DIR}"

TRAIN_X=./dataset/training/train-images.idx3-ubyte
TRAIN_Y=./dataset/training/train-labels.idx1-ubyte
TEST_X=./dataset/testing/t10k-images.idx3-ubyte
TEST_Y=./dataset/testing/t10k-labels.idx1-ubyte

echo "Softmax OpenACC"
srun -n 1 --gpus 1 nsys profile -t cuda,nvtx,osrt,openacc -o ./softmax_openacc.qdrep ${CURRENT_DIR}/build/softmax_openacc $TRAIN_X $TRAIN_Y $TEST_X $TEST_Y
echo ""

echo "NN OpenACC"
srun -n 1 --gpus 1 nsys profile -t cuda,nvtx,osrt,openacc -o ./nn_openacc.qdrep ${CURRENT_DIR}/build/nn_openacc $TRAIN_X $TRAIN_Y $TEST_X $TEST_Y
echo ""

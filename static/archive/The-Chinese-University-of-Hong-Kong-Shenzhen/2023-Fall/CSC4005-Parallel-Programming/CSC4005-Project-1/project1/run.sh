scancel -u {username} # to cancel submitted batch jobs
mkdir build
cd build
cmake ..
make -j4
cd ..
sbatch ./src/scripts/sbatch_PartA.sh
sbatch ./src/scripts/sbatch_PartB.sh
squeue # to check batch jobs queue

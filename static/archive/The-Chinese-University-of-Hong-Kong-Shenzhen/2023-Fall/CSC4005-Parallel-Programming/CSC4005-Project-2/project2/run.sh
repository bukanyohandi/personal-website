scancel -u 120040025
mkdir build
cd build
cmake ..
make -j4
cd ..
sbatch src/sbatch.sh
squeue

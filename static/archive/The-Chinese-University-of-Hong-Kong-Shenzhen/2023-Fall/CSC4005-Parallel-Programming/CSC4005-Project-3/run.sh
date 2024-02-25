scancel -u 120040025
mkdir build
cd build
cmake ..
make -j4
cd ..
sbatch sbatch.sh
sbatch sbatch-perf.sh
squeue -o "%.18i %.9P %.25j %.9u %.2t %.10M %.6D %R"

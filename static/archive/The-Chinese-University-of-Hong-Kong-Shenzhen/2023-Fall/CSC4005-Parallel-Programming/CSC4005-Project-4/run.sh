scancel -u 120040025
bash ./test.sh
squeue -o "%.18i %.9P %.25j %.9u %.2t %.10M %.6D %R"

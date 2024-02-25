mkdir -p build
cd src

# cnn
g++ simple_ml_ext.cpp ml_ext.cpp cnn_classifier.cpp -O2 -o ../build/cnn
pgc++ -acc simple_ml_ext.cpp simple_ml_openacc.cpp ml_openacc.cpp cnn_classifier_openacc.cpp -o ../build/cnn_openacc

# simple
g++ simple_ml_ext.cpp softmax_classifier.cpp -O2 -o ../build/softmax
pgc++ -acc simple_ml_ext.cpp simple_ml_openacc.cpp softmax_classifier_openacc.cpp -o ../build/softmax_openacc

# nn
g++ simple_ml_ext.cpp simple_ml_openacc.cpp nn_classifier.cpp -O2 -o ../build/nn
pgc++ -acc simple_ml_ext.cpp simple_ml_openacc.cpp nn_classifier_openacc.cpp  -o ../build/nn_openacc

rm *.o

cd ..

sbatch sbatch.sh
sbatch sbatch-profile.sh
sbatch sbatch-bonus.sh

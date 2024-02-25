#include "simple_ml_openacc.hpp"
#include "ml_ext.hpp"
#include <string>
#include <cfloat>  // Include for FLT_MAX
#include <cmath>   // Include for sqrt
using namespace std;

// class DataSet
// {
// public:
//     float *images_matrix;
//     unsigned char *labels_array;
//     size_t images_num;
//     size_t input_dim;

//     DataSet(size_t images_num, size_t input_dim);
//     ~DataSet();
// };

uint32_t swap_endian(uint32_t val);

DataSet *parse_mnist(const std::string &image_filename, const std::string &label_filename);

void print_matrix(float *A, size_t m, size_t n);

void conv2d_openacc(const float* input, const float* filters, float* output, 
            size_t batch_size, size_t input_dim, size_t num_filters, size_t filter_size);

void flatten_openacc(const float* input, float* output, size_t batch_size, size_t pool_output_dim);

void ReLU_cnn_openacc(float *M, size_t size);

void compute_obj_grad_cnn_openacc(const DataSet *data, float *W1, float *W2,
                      size_t num_classes, size_t hidden_dim, float *result);

void max_pooling_openacc(const float* input, float* output, size_t batch_size, 
                 size_t conv_output_dim, size_t pool_size);

void backprop_cnn_openacc(const float *X, const unsigned char *y, const float *output, 
                  float *ConvFilters, float *FCWeights, size_t m, size_t n, 
                  size_t num_filters, size_t filter_size, size_t num_classes, 
                  size_t batch, float lr);

void cnn_epoch__openacc(const float *X,
                  const unsigned char *y,
                  float *W1,
                  float *W2,
                  size_t m,
                  size_t n,
                  size_t l,
                  size_t k,
                  float lr,
                  size_t batch);

void train_cnn_openacc(const DataSet *train_data, const DataSet *test_data,
                   size_t num_classes, size_t hidden_dim = 500,
                   size_t epochs = 10, float lr = 0.5, size_t batch = 100);

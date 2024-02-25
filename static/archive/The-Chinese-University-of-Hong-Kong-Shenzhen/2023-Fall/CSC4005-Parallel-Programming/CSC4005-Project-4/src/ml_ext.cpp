#include "ml_ext.hpp"
// #include "simple_ml_ext.hpp"

void conv2d(const float* input, const float* filters, float* output, 
            size_t batch_size, size_t input_dim, size_t num_filters, size_t filter_size) {
    
    size_t input_width = 28;
    size_t input_height = 28;
    size_t output_dim = (input_width - filter_size + 1) * (input_height - filter_size + 1);
    size_t output_width = input_width - filter_size + 1;

    for (size_t batch = 0; batch < batch_size; ++batch) {
        for (size_t filter = 0; filter < num_filters; ++filter) {
            for (size_t i = 0; i < output_width; ++i) {
                for (size_t j = 0; j < output_width; ++j) {
                    float sum = 0.0;
                    for (size_t fi = 0; fi < filter_size; ++fi) {
                        for (size_t fj = 0; fj < filter_size; ++fj) {
                            size_t input_row = i + fi;
                            size_t input_col = j + fj;
                            size_t filter_index = filter * filter_size * filter_size + fi * filter_size + fj;
                            sum += input[batch * input_dim + input_row * input_width + input_col] * filters[filter_index];
                        }
                    }
                    output[batch * output_dim + filter * output_width * output_width + i * output_width + j] = sum;
                }
            }
        }
    }
}

void max_pooling(const float* input, float* output, size_t batch_size, 
                 size_t conv_output_dim, size_t pool_size) {
    size_t num_filters = conv_output_dim / ((28 - pool_size + 1) * (28 - pool_size + 1));
    size_t output_width = (28 - pool_size + 1) / pool_size;
    size_t output_height = output_width;
    size_t pool_output_dim = output_width * output_height * num_filters;

    for (size_t batch = 0; batch < batch_size; ++batch) {
        for (size_t filter = 0; filter < num_filters; ++filter) {
            for (size_t i = 0; i < output_height; ++i) {
                for (size_t j = 0; j < output_width; ++j) {
                    float max_val = -FLT_MAX;
                    for (size_t pi = 0; pi < pool_size; ++pi) {
                        for (size_t pj = 0; pj < pool_size; ++pj) {
                            size_t input_row = i * pool_size + pi;
                            size_t input_col = j * pool_size + pj;
                            size_t input_index = batch * conv_output_dim + filter * output_width * output_width + input_row * output_width + input_col;
                            float val = input[input_index];
                            if (val > max_val) {
                                max_val = val;
                            }
                        }
                    }
                    size_t output_index = batch * pool_output_dim + filter * output_width * output_height + i * output_width + j;
                    output[output_index] = max_val;
                }
            }
        }
    }
}

void flatten(const float* input, float* output, size_t batch_size, size_t pool_output_dim) {
    for (size_t batch = 0; batch < batch_size; ++batch) {
        for (size_t i = 0; i < pool_output_dim; ++i) {
            output[batch * pool_output_dim + i] = input[batch * pool_output_dim + i];
        }
    }
}

void ReLU_cnn(float *M, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (M[i] < 0)
      M[i] = 0;
  }
}

void init(float* conv_weights, size_t conv_weights_size, float* fc_weights, size_t fc_weights_size){
    std::ifstream images_matrix_file(st.c_str());
    if (images_matrix_file.is_open())
        for (size_t i = 0; i < conv_weights_size; ++i){
            images_matrix_file >> conv_weights[i]; conv_weights[i] *= 1.01;}
        images_matrix_file.close();

    std::ifstream labels_array_file(rt.c_str());
    if (labels_array_file.is_open())
        for (size_t i = 0; i < fc_weights_size; ++i){
            labels_array_file >> fc_weights[i]; fc_weights[i] *= 0.99;}
        labels_array_file.close();
}

void compute_obj_grad_cnn(const DataSet *data, float *W1, float *W2,
                      size_t num_classes, size_t hidden_dim, float *result) {
  float *tmp = new float[data->images_num * hidden_dim];

  matrix_dot(data->images_matrix, W1, tmp, data->images_num, data->input_dim,
             hidden_dim);
  ReLU_cnn(tmp, data->images_num * hidden_dim);
  matrix_dot(tmp, W2, result, data->images_num, hidden_dim, num_classes);

  delete[] tmp;

  return;
}

void backprop_cnn(const float *X, const unsigned char *y, const float *output, 
                  float *ConvFilters, float *FCWeights, size_t m, size_t n, 
                  size_t num_filters, size_t filter_size, size_t num_classes, 
                  size_t batch, float lr) {
                    
    float *grad_FCWeights = new float[num_classes * n]; // Assuming FCWeights have a shape of (n x num_classes)

    memset(grad_FCWeights, 0, num_classes * n * sizeof(float));

    for (size_t i = 0; i < m; i += batch) {
        size_t current_batch_size = std::min(batch, m - i);

        float *Y = new float[current_batch_size * num_classes];
        vector_to_one_hot_matrix(y + i, Y, current_batch_size, num_classes);

        for (size_t j = 0; j < current_batch_size; ++j) {
            for (size_t k = 0; k < num_classes; ++k) {
                float error = (output[j * num_classes + k] - Y[j * num_classes + k]) / current_batch_size;
                for (size_t l = 0; l < n; ++l) {
                    grad_FCWeights[k * n + l] += error * X[i * n + j * n + l];
                }
            }
        }

        delete[] Y;
    }

    for (size_t i = 0; i < num_classes * n; ++i) {
        FCWeights[i] -= lr * grad_FCWeights[i];
    }

    delete[] grad_FCWeights;
}

void cnn_epoch_cpp(const float *X, const unsigned char *y, float *ConvFilters, 
                   float *FCWeights, size_t m, size_t n, size_t num_filters, 
                   size_t filter_size, size_t num_classes, float lr, size_t batch, size_t pool_size) {
    // Updated dimensions for convolution and pooling layers
    size_t conv_output_width = 28 - filter_size + 1;
    size_t conv_output_height = 28 - filter_size + 1;
    size_t pool_output_width = conv_output_width / pool_size;
    size_t pool_output_height = conv_output_height / pool_size;
    size_t pool_output_dim = pool_output_width * pool_output_height * num_filters;
    size_t flattened_output_dim = pool_output_dim;

    size_t conv_output_dim = conv_output_width * conv_output_height * num_filters;

    // Allocate memory for intermediate outputs
    float *conv_output = new float[batch * conv_output_dim];
    float *pool_output = new float[batch * pool_output_dim];
    float *flattened_output = new float[batch * flattened_output_dim];
    float *output = new float[batch * num_classes];

    for (size_t i = 0; i < m; i += batch) {
        size_t current_batch_size = std::min(batch, m - i);

        // Forward pass
        conv2d(X + i * n, ConvFilters, conv_output, current_batch_size, n, num_filters, filter_size);
        ReLU_cnn(conv_output, current_batch_size * conv_output_dim);
        max_pooling(conv_output, pool_output, current_batch_size, conv_output_dim, pool_size);
        flatten(pool_output, flattened_output, current_batch_size, pool_output_dim);
        matrix_dot(flattened_output, FCWeights, output, current_batch_size, flattened_output_dim, num_classes);
        matrix_softmax_normalize(output, current_batch_size, num_classes);

        // Backward pass
        backprop_cnn(X + i * n, y + i, output, ConvFilters, FCWeights, current_batch_size, n, num_filters, filter_size, num_classes, batch, lr);
    }

    // Free allocated memory
    delete[] conv_output;
    delete[] pool_output;
    delete[] flattened_output;
    delete[] output;
}


void train_cnn(const DataSet *train_data, const DataSet *test_data,
                   size_t num_classes, size_t hidden_dim,
                   size_t epochs, float lr, size_t batch) {
    const size_t num_filters = 8;
    const size_t filter_size = 3;
    const size_t pool_size = 2;

    size_t conv_weights_size = train_data->input_dim * hidden_dim;
    size_t fc_weights_size = hidden_dim * num_classes;

    float* conv_weights = new float[conv_weights_size];
    float* fc_weights = new float[fc_weights_size];

    std::mt19937 rng;
    rng.seed(0);
    std::normal_distribution<float> dist(0.0, std::sqrt(1.0 / (filter_size * filter_size)));
    for (size_t i = 0; i < conv_weights_size; i++) {
        conv_weights[i] = dist(rng);
    }
    for (size_t i = 0; i < fc_weights_size; i++) {
        fc_weights[i] = dist(rng);
    }
    init(conv_weights, conv_weights_size, fc_weights, fc_weights_size);
    float *train_result = new float[train_data->images_num * num_classes];
    float *test_result = new float[test_data->images_num * num_classes];
    float train_loss, test_loss, train_err, test_err;
    std::cout << "| Epoch | Train Loss | Train Err | Test Loss | Test Err |"
                << std::endl;
    float initial_lr = 0.01;
  auto start_time = std::chrono::high_resolution_clock::now();
    for (size_t epoch = 0; epoch < 2 * epochs; epoch++) {
        float current_lr = initial_lr / (1 + epoch * 0.1);
        nn_epoch_cpp(train_data->images_matrix, train_data->labels_array, conv_weights, fc_weights,
                 train_data->images_num, train_data->input_dim, hidden_dim,
                 num_classes, lr, batch);

        if(epoch % 2 == 1) continue;
                 
        compute_obj_grad_cnn(train_data, conv_weights, fc_weights, num_classes, hidden_dim, train_result);
        compute_obj_grad_cnn(test_data, conv_weights, fc_weights, num_classes, hidden_dim, test_result);

        train_loss = mean_softmax_loss(train_result, train_data->labels_array,
                                    train_data->images_num, num_classes);
        test_loss = mean_softmax_loss(test_result, test_data->labels_array,
                                    test_data->images_num, num_classes);
        train_err = mean_err(train_result, train_data->labels_array,
                            train_data->images_num, num_classes);
        test_err = mean_err(test_result, test_data->labels_array,
                            test_data->images_num, num_classes);
        std::cout << "|  " << std::setw(4) << std::right << epoch / 2 << " |    "
                << std::fixed << std::setprecision(5) << train_loss << " |   "
                << std::fixed << std::setprecision(5) << train_err << " |   "
                << std::fixed << std::setprecision(5) << test_loss << " |  "
                << std::fixed << std::setprecision(5) << test_err << " |"
                << std::endl;
    }
  auto end_time = std::chrono::high_resolution_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";

    delete[] conv_weights;
    delete[] fc_weights;
}
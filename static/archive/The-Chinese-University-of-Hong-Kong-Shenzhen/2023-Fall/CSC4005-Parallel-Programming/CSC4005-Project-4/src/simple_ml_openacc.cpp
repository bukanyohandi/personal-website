#include "simple_ml_openacc.hpp"

void matrix_dot_openacc(const float *A, const float *B, float *C, size_t M,
                        size_t K, size_t N) {    
  #pragma acc data present(A[0:M*K], B[0:K*N], C[0:M*N])
  {
    #pragma acc parallel loop collapse(2)
    for(size_t i = 0; i < M; ++i){
        for(size_t j = 0; j < N; ++j){
            const float *A_i = &A[i * K];
            float result = 0;

            size_t k = 0;
            for(; k + 4 < K; k += 4){
                result += A_i[k] * B[k * N + j];
                result += A_i[k + 1] * B[(k + 1) * N + j];
                result += A_i[k + 2] * B[(k + 2) * N + j];
                result += A_i[k + 3] * B[(k + 3) * N + j];
            }
            for(; k < K; ++k){
              result += A_i[k] * B[k * N + j];
            }
            C[i * N + j] = result;
        }
    }
  }
  
  return;
}

void matrix_dot_trans_openacc(const float *A, const float *B, float *C,
                              size_t n, size_t m, size_t k) {
  #pragma acc data present(A[0:n*m], B[0:n*k], C[0:m*k])
  {
    #pragma acc parallel loop collapse(2)
    for(size_t i = 0; i < m; ++i){
        for(size_t j = 0; j < k; ++j){
            float result = 0;

            size_t kk = 0;
            for(; kk + 4 < n; kk += 4){
              result += A[kk * m + i] * B[kk * k + j];
              result += A[(kk + 1) * m + i] * B[(kk + 1) * k + j];
              result += A[(kk + 2) * m + i] * B[(kk + 2) * k + j];
              result += A[(kk + 3) * m + i] * B[(kk + 3) * k + j];
            }
            for(; kk < n; ++kk){
              result += A[kk * m + i] * B[kk * k + j];
            }
            C[i * k + j] = result;
        }
    }
  }

  return;
}

void matrix_trans_dot_openacc(const float *A, const float *B, float *C,
                              size_t m, size_t n, size_t k) {
  #pragma acc data present(A[0:m*n], B[0:k*n], C[0:m*k])
  {
    #pragma acc parallel loop collapse(2)
    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < k; ++j) {
        const float *A_i = &A[i * n];
        const float *B_j = &B[j * n];

        float result = 0;
        size_t kk = 0;
        for (; kk + 4 < n; kk += 4) {
          result += A_i[kk] * B_j[kk];
          result += A_i[kk + 1] * B_j[kk + 1];
          result += A_i[kk + 2] * B_j[kk + 2];
          result += A_i[kk + 3] * B_j[kk + 3];
        }
        for (; kk < n; ++kk) {
          result += A[i * n + kk] * B[j * n + kk];
        }
        C[i * k + j] = result;
      }
    }
  }
}

void matrix_minus_openacc(float *A, const float *B, size_t m, size_t n) {
  #pragma acc data present(A[0:m*n], B[0:m*n])
  {
    #pragma acc parallel loop independent
    for (size_t i = 0; i < m * n; ++i) {
      A[i] -= B[i];
    }
  }

  return;
}

void matrix_mul_scalar_openacc(float *C, float scalar, size_t m, size_t n) {
  #pragma acc data present(C[0:m*n])
  {
    #pragma acc parallel loop independent
    for (size_t i = 0; i < m * n; ++i) {
      C[i] *= scalar;
    }
  }

  return;
}

void matrix_div_scalar_openacc(float *C, float scalar, size_t m, size_t n) {
  float inv_scalar = 1 / scalar;
  #pragma acc data present(C[0:m*n])
  {
    #pragma acc parallel loop independent
    for (size_t i = 0; i < m * n; ++i) {
      C[i] *= inv_scalar;
    }
  }

  return;
}

void matrix_softmax_normalize_openacc(float *C, size_t m, size_t n) {
  #pragma acc data present(C[0:m * n])
  {
    #pragma acc parallel loop independent collapse(2)
    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
        C[i * n + j] = exp(C[i * n + j]);
      }
    }

    #pragma acc parallel loop independent
    for (size_t i = 0; i < m; ++i) {
      float sum = 0;
      #pragma acc loop
      for (size_t j = 0; j < n; ++j) {
        sum += C[i * n + j];
      }

      float inv_sum = 1 / sum;
      #pragma acc loop independent
      for (size_t j = 0; j < n; ++j) {
        C[i * n + j] *= inv_sum;
      }
    }
  }

  return;
}

void vector_to_one_hot_matrix_openacc(const unsigned char *y, float *Y,
                                      size_t m, size_t n) {
  #pragma acc data present(y[0:m], Y[0:m*n])
  {
    #pragma acc parallel
    {
      #pragma acc loop independent
      for(size_t i = 0; i < m * n; ++i){
        Y[i] = 0;
      }

      #pragma acc loop independent
      for (size_t i = 0; i < m; ++i) {
        Y[y[i] + i * n] = 1.0f;
      }
    }
  }

  return;
}

void softmax_regression_epoch_openacc(const float *X, const unsigned char *y,
                                      float *theta, size_t m, size_t n,
                                      size_t k, float lr, size_t batch) {
  float *Z = new float[batch * k];
  float *Y = new float[batch * k];
  float *gradients = new float[n * k];

  // #pragma acc enter data create()
  #pragma acc enter data create(Z[0:batch * k], Y[0:batch * k], gradients[0:n * k])
  #pragma acc data present(X[0:m * n])
  {
    for (size_t i = 0; i < m; i += batch) {
      // #pragma acc parallel loop
      // std::cout << "BEFORE\n";
      matrix_dot_openacc(X + i * n, theta, Z, batch, n, k);

      matrix_softmax_normalize_openacc(Z, batch, k);

      vector_to_one_hot_matrix_openacc(y + i, Y, batch, k);
      matrix_minus_openacc(Z, Y, batch, k);
      matrix_dot_trans_openacc(X + i * n, Z, gradients, batch, n, k);

      matrix_div_scalar_openacc(gradients, static_cast<float>(batch), n, k);
      matrix_mul_scalar_openacc(gradients, lr, n, k);
      matrix_minus_openacc(theta, gradients, n, k);
    }
  }
  #pragma acc exit data delete(Z[0:batch * k], Y[0:batch * k], gradients[0:n * k])
  // #pragma acc update host(theta[0:n*k])

  delete[] Z;
  delete[] Y;
  delete[] gradients;

  return;
}

void train_softmax_openacc(const DataSet *train_data, const DataSet *test_data,
                           size_t num_classes, size_t epochs, float lr,
                           size_t batch) {
  size_t size = train_data->input_dim * num_classes;
  float *theta = new float[size];
  memset(theta, 0, size * sizeof(float));
  float *theta_tmp = new float[size];
  memset(theta_tmp, 0, size * sizeof(float));
  size_t size_tr = train_data->images_num * num_classes;
  size_t size_te = test_data->images_num * num_classes;
  float *train_result = new float[size_tr];
  float *test_result = new float[size_te];
  float train_loss, train_err, test_loss, test_err;
  std::cout << "| Epoch | Train Loss | Train Err | Test Loss | Test Err |"
            << std::endl;
  std::chrono::milliseconds elapsed_time;
  
  #pragma acc enter data copyin(train_data->images_matrix[0:train_data->images_num * train_data->input_dim], \
                                test_data->images_matrix[0:test_data->images_num * test_data->input_dim], \
                                train_data->labels_array[0:train_data->images_num], \
                                test_data->labels_array[0:test_data->images_num])
  #pragma acc enter data create(train_result[0:size_tr], test_result[0:size_te], theta[0:size])
  auto start_time = std::chrono::high_resolution_clock::now();
  for (size_t epoch = 0; epoch < epochs; epoch++) {
    softmax_regression_epoch_openacc(
        train_data->images_matrix, train_data->labels_array, theta,
        train_data->images_num, train_data->input_dim, num_classes, lr, batch);

    // softmax_regression_epoch_cpp(
    //     train_data->images_matrix, train_data->labels_array, theta_tmp,
    //     train_data->images_num, train_data->input_dim, num_classes, lr, batch);

    matrix_dot_openacc(train_data->images_matrix, theta, train_result,
               train_data->images_num, train_data->input_dim, num_classes);
    matrix_dot_openacc(test_data->images_matrix, theta, test_result,
               test_data->images_num, test_data->input_dim, num_classes);

    train_loss =
        mean_softmax_loss_openacc(train_result, train_data->labels_array,
                                  train_data->images_num, num_classes);
    test_loss = mean_softmax_loss_openacc(test_result, test_data->labels_array,
                                          test_data->images_num, num_classes);
    train_err = mean_err_openacc(train_result, train_data->labels_array,
                                 train_data->images_num, num_classes);
    test_err = mean_err_openacc(test_result, test_data->labels_array,
                                test_data->images_num, num_classes);
    std::cout << "|  " << std::setw(4) << std::right << epoch << " |    "
              << std::fixed << std::setprecision(5) << train_loss << " |   "
              << std::fixed << std::setprecision(5) << train_err << " |   "
              << std::fixed << std::setprecision(5) << test_loss << " |  "
              << std::fixed << std::setprecision(5) << test_err << " |"
              << std::endl;
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";

  // #pragma acc exit data copyout(train_result[0:size_tr], test_result[0:size_te], theta[0:size])
  // #pragma acc exit data delete(train_data->images_matrix[0:train_data->images_num * train_data->input_dim], \
  //                              test_data->images_matrix[0:test_data->images_num * test_data->input_dim], \
  //                              train_data->labels_array[0:train_data->images_num], \
  //                              test_data->labels_array[0:test_data->images_num], theta[0:size])

  delete[] theta;
  delete[] train_result;
  delete[] test_result;
}

float mean_softmax_loss_openacc(const float *result,
                                const unsigned char *labels_array,
                                size_t images_num, size_t num_classes) {
  float total_loss = 0.0f;
  // #pragma acc data present(result[0:images_num*num_classes], labels_array[0:images_num])
  #pragma acc parallel loop reduction(+:total_loss) present(result, labels_array)
  for (size_t i = 0; i < images_num; ++i) {
    float max_logit = result[i * num_classes];
    for (size_t j = 0; j < num_classes; ++j) {
      if (result[i * num_classes + j] > max_logit) {
        max_logit = result[i * num_classes + j];
      }
    }

    float sum_exp = 0.0f;
    for (size_t j = 0; j < num_classes; ++j) {
      sum_exp += exp(result[i * num_classes + j] - max_logit);
    }

    float true_class_logit = result[i * num_classes + labels_array[i]];
    total_loss += -true_class_logit + max_logit + log(sum_exp);
  }

  return total_loss / images_num;
}

float mean_err_openacc(const float *result, const unsigned char *labels_array,
                       size_t images_num, size_t num_classes) {
  size_t incorrect_predictions = 0;
  // #pragma acc data present(result[0:images_num*num_classes], labels_array[0:images_num])
  #pragma acc parallel loop reduction(+:incorrect_predictions) present(result, labels_array)
  for (size_t i = 0; i < images_num; ++i) {
    size_t predicted_class = 0;
    float max_logit = result[i * num_classes];

    for (size_t j = 1; j < num_classes; ++j) {
      if (result[i * num_classes + j] > max_logit) {
        max_logit = result[i * num_classes + j];
        predicted_class = j;
      }
    }

    if (predicted_class != labels_array[i]) {
      ++incorrect_predictions;
    }
  }

  return static_cast<float>(incorrect_predictions) / images_num;
}

void matrix_mul_openacc(float *A, const float *B, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    A[i] *= B[i];
  }

  return;
}

void ReLU_openacc(float *M, size_t size) {
  #pragma acc parallel loop independent
  for (size_t i = 0; i < size; ++i) {
    if (M[i] < 0)
      M[i] = 0;
  }
}

void nn_epoch_openacc(const float *X, const unsigned char *y, float *W1,
                      float *W2, size_t m, size_t n, size_t l, size_t k,
                      float lr, size_t batch) {
  float *Z1 = new float[batch * l];
  float *Z2 = new float[batch * k];
  float *Y = new float[batch * k];
  float *G1 = new float[batch * l];
  float *G1_tmp = new float[n * l];
  float *G2_tmp = new float[l * k];

  #pragma acc enter data create(Z1[0:batch * l], Z2[0:batch * k], Y[0:batch * k], G1[0:batch * l], G1_tmp[0:n * l], G2_tmp[0:l * k])
  #pragma acc data present(X[0:m * n], y[0:m])
  for (size_t i = 0; i < m; i += batch) {
    // std::cout << ">>> PASS " << i << "\n";
    matrix_dot_openacc(X + i * n, W1, Z1, batch, n, l);
    ReLU_openacc(Z1, batch * l);
    matrix_dot_openacc(Z1, W2, Z2, batch, l, k);
    matrix_softmax_normalize_openacc(Z2, batch, k);

    vector_to_one_hot_matrix_openacc(y + i, Y, batch, k);

    matrix_minus_openacc(Z2, Y, batch, k);
    matrix_trans_dot_openacc(Z2, W2, G1, batch, k, l);

    #pragma acc parallel loop independent
    for (size_t j = 0; j < batch * l; ++j) {
      G1[j] *= (Z1[j] > 0);
    }
    matrix_dot_trans_openacc(X + i * n, G1, G1_tmp, batch, n, l);
    matrix_dot_trans_openacc(Z1, Z2, G2_tmp, batch, l, k);

    matrix_div_scalar_openacc(G1_tmp, batch, n, l);
    matrix_mul_scalar_openacc(G1_tmp, lr, n, l);
    matrix_minus_openacc(W1, G1_tmp, n, l);

    matrix_div_scalar_openacc(G2_tmp, batch, l, k);
    matrix_mul_scalar_openacc(G2_tmp, lr, l, k);
    matrix_minus_openacc(W2, G2_tmp, l, k);
  }
  #pragma acc exit data delete(Z1[0:batch * l], Z2[0:batch * k], Y[0:batch * k], G1[0:batch * l], G1_tmp[0:n * l], G2_tmp[0:l * k])

  delete[] Z1;
  delete[] Z2;
  delete[] Y;
  delete[] G1;
  delete[] G1_tmp;
  delete[] G2_tmp;

  return;
}

void compute_obj_grad_openacc(const DataSet *data, float *W1, float *W2,
                      size_t num_classes, size_t hidden_dim, float *result) {
  float *tmp = new float[data->images_num * hidden_dim];

  #pragma acc enter data create(tmp[0:data->images_num * hidden_dim])
  {
    matrix_dot_openacc(data->images_matrix, W1, tmp, data->images_num, data->input_dim,
              hidden_dim);
    ReLU_openacc(tmp, data->images_num * hidden_dim);
    matrix_dot_openacc(tmp, W2, result, data->images_num, hidden_dim, num_classes);
  }

  delete[] tmp;

  return;
}

void train_nn_openacc(const DataSet *train_data, const DataSet *test_data,
                      size_t num_classes, size_t hidden_dim, size_t epochs,
                      float lr, size_t batch) {
  size_t size_w1 = train_data->input_dim * hidden_dim;
  size_t size_w2 = hidden_dim * num_classes;
  float *W1 = new float[size_w1];
  float *W2 = new float[size_w2];
  std::mt19937 rng;
  rng.seed(0);
  std::normal_distribution<float> dist(0.0, 1.0);
  for (size_t i = 0; i < size_w1; i++) {
    W1[i] = dist(rng);
  }
  for (size_t i = 0; i < size_w2; i++) {
    W2[i] = dist(rng);
  }
  matrix_div_scalar(W1, sqrtf(hidden_dim), train_data->input_dim, hidden_dim);
  matrix_div_scalar(W2, sqrtf(num_classes), hidden_dim, num_classes);
  size_t size_tr = train_data->images_num * num_classes;
  size_t size_te = test_data->images_num * num_classes;
  float *train_result = new float[size_tr];
  float *test_result = new float[size_te];
  float train_loss, train_err, test_loss, test_err;
  std::cout << "| Epoch | Train Loss | Train Err | Test Loss | Test Err |"
            << std::endl;
  std::chrono::milliseconds elapsed_time;
  auto start_time = std::chrono::high_resolution_clock::now();
  
  #pragma acc enter data copyin(train_data->images_matrix[0:train_data->images_num * train_data->input_dim], \
                                test_data->images_matrix[0:test_data->images_num * test_data->input_dim], \
                                train_data->labels_array[0:train_data->images_num], \
                                test_data->labels_array[0:test_data->images_num], \
                                W1[0:size_w1], \
                                W2[0:size_w2])
  #pragma acc enter data create(train_result[0:size_tr], test_result[0:size_te])
  for (size_t epoch = 0; epoch < epochs; epoch++) {
    nn_epoch_openacc(train_data->images_matrix, train_data->labels_array, W1, W2,
                 train_data->images_num, train_data->input_dim, hidden_dim,
                 num_classes, lr, batch);
                 
    compute_obj_grad_openacc(train_data, W1, W2, num_classes, hidden_dim, train_result);
    compute_obj_grad_openacc(test_data, W1, W2, num_classes, hidden_dim, test_result);

    train_loss =
        mean_softmax_loss_openacc(train_result, train_data->labels_array,
                                  train_data->images_num, num_classes);
    test_loss = mean_softmax_loss_openacc(test_result, test_data->labels_array,
                                          test_data->images_num, num_classes);
    train_err = mean_err_openacc(train_result, train_data->labels_array,
                                 train_data->images_num, num_classes);
    test_err = mean_err_openacc(test_result, test_data->labels_array,
                                test_data->images_num, num_classes);
    std::cout << "|  " << std::setw(4) << std::right << epoch << " |    "
              << std::fixed << std::setprecision(5) << train_loss << " |   "
              << std::fixed << std::setprecision(5) << train_err << " |   "
              << std::fixed << std::setprecision(5) << test_loss << " |  "
              << std::fixed << std::setprecision(5) << test_err << " |"
              << std::endl;
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";

  // END YOUR CODE
  delete[] W1;
  delete[] W2;
  delete[] train_result;
  delete[] test_result;
}

/*
    Created by Yohandi on 2023/10/3.
    Email: yohandi@link.cuhk.edu.cn

    Pthread implementation of applying a 3 x 3 filter to a JPEG image

    Few parts were taken from pthread_PartA.cpp created by Zhang Na as reference

    number of cores     execution time (ms)
    1                   5162
    2                   4430
    4                   2313
    8                   1131
    16                  565
    32                  384
*/

#include "utils.hpp"
#include <chrono>
#include <iostream>
#include <pthread.h>

const int FILTER_SIZE = 3;
const float filter[FILTER_SIZE][FILTER_SIZE] = {{1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9}};

struct Pixel {
  unsigned char r, g, b;
};

// Structure to pass data to each thread
struct ThreadData {
  Pixel *input_buffer;
  Pixel *output_buffer;
  int start_height;
  int end_height;
  int width;
};

// Function to apply filter to a portion of the image
/*
    note:
    main part of this function is exactly copied from what I made
    in sequential_PartB.cpp with only a slight change in height loop
*/
void *apply_filter(void *arg) {
  ThreadData *data = (ThreadData *)arg;

  for (int height = data->start_height; height < data->end_height; height++) {
    for (int width = 1; width < data->width - 1; width++) {
      int sum_r = 0, sum_g = 0, sum_b = 0;

      Pixel *base_ptr = data->input_buffer + height * data->width + width;

      sum_r += (base_ptr[-data->width - 1].r * filter[0][0]) +
               (base_ptr[-data->width].r * filter[0][1]) +
               (base_ptr[-data->width + 1].r * filter[0][2]) +
               (base_ptr[-1].r * filter[1][0]) +
               (base_ptr[0].r * filter[1][1]) + (base_ptr[1].r * filter[1][2]) +
               (base_ptr[data->width - 1].r * filter[2][0]) +
               (base_ptr[data->width].r * filter[2][1]) +
               (base_ptr[data->width + 1].r * filter[2][2]);

      sum_g += (base_ptr[-data->width - 1].g * filter[0][0]) +
               (base_ptr[-data->width].g * filter[0][1]) +
               (base_ptr[-data->width + 1].g * filter[0][2]) +
               (base_ptr[-1].g * filter[1][0]) +
               (base_ptr[0].g * filter[1][1]) + (base_ptr[1].g * filter[1][2]) +
               (base_ptr[data->width - 1].g * filter[2][0]) +
               (base_ptr[data->width].g * filter[2][1]) +
               (base_ptr[data->width + 1].g * filter[2][2]);

      sum_b += (base_ptr[-data->width - 1].b * filter[0][0]) +
               (base_ptr[-data->width].b * filter[0][1]) +
               (base_ptr[-data->width + 1].b * filter[0][2]) +
               (base_ptr[-1].b * filter[1][0]) +
               (base_ptr[0].b * filter[1][1]) + (base_ptr[1].b * filter[1][2]) +
               (base_ptr[data->width - 1].b * filter[2][0]) +
               (base_ptr[data->width].b * filter[2][1]) +
               (base_ptr[data->width + 1].b * filter[2][2]);

      Pixel &out_pixel = data->output_buffer[height * data->width + width];
      out_pixel.r = static_cast<unsigned char>(sum_r);
      out_pixel.g = static_cast<unsigned char>(sum_g);
      out_pixel.b = static_cast<unsigned char>(sum_b);
    }
  }
  return NULL;
}

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 4) {
    std::cerr << "Invalid argument, should be: ./executable "
                 "/path/to/input/jpeg /path/to/output/jpeg num_threads\n";
    return -1;
  }

  int num_threads = std::stoi(argv[3]); // User-specified thread count

  // Read from input JPEG
  const char *input_filepath = argv[1];
  std::cout << "Input file from: " << input_filepath << "\n";
  auto input_jpeg = read_from_jpeg(input_filepath);

  // Application filter to image
  auto filteredImage = new Pixel[input_jpeg.width * input_jpeg.height];

  pthread_t threads[num_threads];
  ThreadData thread_data[num_threads];

  auto start_time = std::chrono::high_resolution_clock::now();

  int chunk_height = input_jpeg.height / num_threads;
  for (int i = 0; i < num_threads; i++) {
    thread_data[i].input_buffer = reinterpret_cast<Pixel *>(input_jpeg.buffer);
    thread_data[i].output_buffer = filteredImage;
    thread_data[i].width = input_jpeg.width;
    thread_data[i].start_height = i * chunk_height;
    thread_data[i].end_height =
        (i == num_threads - 1) ? input_jpeg.height : (i + 1) * chunk_height;

    pthread_create(&threads[i], NULL, apply_filter, &thread_data[i]);
  }

  // Wait for all threads to finish
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], nullptr);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  // Write filteredImage to output JPEG
  const char *output_filepath = argv[2];
  std::cout << "Output file to: " << output_filepath << "\n";
  JPEGMeta output_jpeg{reinterpret_cast<unsigned char *>(filteredImage),
                       input_jpeg.width, input_jpeg.height,
                       input_jpeg.num_channels, input_jpeg.color_space};
  if (write_to_jpeg(output_jpeg, output_filepath)) {
    std::cerr << "Failed to write output JPEG\n";
    return -1;
  }

  // Release allocated memory
  delete[] input_jpeg.buffer;
  delete[] filteredImage;

  std::cout << "Transformation Complete!" << std::endl;
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";

  return 0;
}

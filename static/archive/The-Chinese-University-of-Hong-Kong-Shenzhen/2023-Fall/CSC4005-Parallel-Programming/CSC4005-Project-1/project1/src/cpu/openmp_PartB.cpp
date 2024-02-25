/*
    Created by Yohandi on 2023/10/4.
    Email: yohandi@link.cuhk.edu.cn

    OpenMP implementation of applying a 3 x 3 filter to a JPEG image

    Few parts were taken from openmp_PartA.cpp created by Zhang Na as reference

    number of cores     execution time (ms)
    1                   5967
    2                   5952
    4                   3120
    8                   1559
    16                  893
    32                  424
*/

#include "utils.hpp"
#include <chrono>
#include <iostream>
#include <omp.h> // OpenMP header

const int FILTER_SIZE = 3;
const float filter[FILTER_SIZE][FILTER_SIZE] = {{1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9}};

struct Pixel {
  unsigned char r, g, b;
};

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 3) {
    std::cerr << "Invalid argument, should be: ./executable "
                 "/path/to/input/jpeg /path/to/output/jpeg\n";
    return -1;
  }
  // Read input JPEG image
  const char *input_filepath = argv[1];
  std::cout << "Input file from: " << input_filepath << "\n";
  auto input_jpeg = read_from_jpeg(input_filepath);
  if (input_jpeg.buffer == NULL) {
    std::cerr << "Failed to read input JPEG image\n";
    return -1;
  }

  // Application filter to image
  auto filteredImage = new Pixel[input_jpeg.width * input_jpeg.height];
  auto start_time = std::chrono::high_resolution_clock::now();

/*
    note:
    main part of this loop is similarly copied
    from what I made in sequential_PartB.cpp
*/
#pragma omp parallel for default(none) shared(filteredImage, input_jpeg, filter)
  for (int i = 0; i < (input_jpeg.width - 2) * (input_jpeg.height - 2); i++) {
    int height = i / (input_jpeg.width - 2) + 1;
    int width = i % (input_jpeg.width - 2) + 1;
    int sum_r = 0, sum_g = 0, sum_b = 0;

    Pixel *base_ptr = reinterpret_cast<Pixel *>(input_jpeg.buffer) +
                      height * input_jpeg.width + width;

    sum_r += (base_ptr[-input_jpeg.width - 1].r * filter[0][0]) +
             (base_ptr[-input_jpeg.width].r * filter[0][1]) +
             (base_ptr[-input_jpeg.width + 1].r * filter[0][2]) +
             (base_ptr[-1].r * filter[1][0]) + (base_ptr[0].r * filter[1][1]) +
             (base_ptr[1].r * filter[1][2]) +
             (base_ptr[input_jpeg.width - 1].r * filter[2][0]) +
             (base_ptr[input_jpeg.width].r * filter[2][1]) +
             (base_ptr[input_jpeg.width + 1].r * filter[2][2]);

    sum_g += (base_ptr[-input_jpeg.width - 1].g * filter[0][0]) +
             (base_ptr[-input_jpeg.width].g * filter[0][1]) +
             (base_ptr[-input_jpeg.width + 1].g * filter[0][2]) +
             (base_ptr[-1].g * filter[1][0]) + (base_ptr[0].g * filter[1][1]) +
             (base_ptr[1].g * filter[1][2]) +
             (base_ptr[input_jpeg.width - 1].g * filter[2][0]) +
             (base_ptr[input_jpeg.width].g * filter[2][1]) +
             (base_ptr[input_jpeg.width + 1].g * filter[2][2]);

    sum_b += (base_ptr[-input_jpeg.width - 1].b * filter[0][0]) +
             (base_ptr[-input_jpeg.width].b * filter[0][1]) +
             (base_ptr[-input_jpeg.width + 1].b * filter[0][2]) +
             (base_ptr[-1].b * filter[1][0]) + (base_ptr[0].b * filter[1][1]) +
             (base_ptr[1].b * filter[1][2]) +
             (base_ptr[input_jpeg.width - 1].b * filter[2][0]) +
             (base_ptr[input_jpeg.width].b * filter[2][1]) +
             (base_ptr[input_jpeg.width + 1].b * filter[2][2]);

    Pixel &out_pixel = filteredImage[height * input_jpeg.width + width];
    out_pixel.r = static_cast<unsigned char>(sum_r);
    out_pixel.g = static_cast<unsigned char>(sum_g);
    out_pixel.b = static_cast<unsigned char>(sum_b);
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
    std::cerr << "Failed to save output JPEG image\n";
    return -1;
  }

  // Release the allocated memory
  delete[] input_jpeg.buffer;
  delete[] filteredImage;

  std::cout << "Transformation Complete!" << std::endl;
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";
  return 0;
}

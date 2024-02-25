/*
    Created by Yohandi on 2023/10/6.
    Email: yohandi@link.cuhk.edu.cn

    OpenACC implementation of applying a 3 x 3 filter to a JPEG image

    Few parts were taken from openacc_PartA.cpp created by Zhong Yebin as
   reference

    GPU execution time: 24 ms
*/

#include <chrono>
#include <iostream>

#include "utils.hpp"
// #include <openacc.h> // OpenACC Header

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
  // Read from input JPEG
  const char *input_filepath = argv[1];
  std::cout << "Input file from: " << input_filepath << "\n";
  JPEGMeta input_jpeg = read_from_jpeg(input_filepath);
  // Apply filter to RGB
  int width = input_jpeg.width;
  int height = input_jpeg.height;
  int num_channels = input_jpeg.num_channels;
  auto filteredImage = new unsigned char[width * height * num_channels];
  unsigned char *buffer = new unsigned char[width * height * num_channels];
  for (int i = 0; i < width * height * num_channels; i++) {
    buffer[i] = input_jpeg.buffer[i];
  }
#pragma acc enter data copyin(filteredImage [0:width * height * num_channels], \
                              buffer [0:width * height * num_channels])

#pragma acc update device(filteredImage [0:width * height * num_channels],     \
                          buffer [0:width * height * num_channels])

  auto start_time = std::chrono::high_resolution_clock::now();
#pragma acc parallel present(filteredImage [0:width * height * num_channels],  \
                             buffer [0:width * height * num_channels])         \
    num_gangs(1024)
  {
#pragma acc loop independent
    for (int i = width + 1; i < width * (height - 1); i++) {
      if (i % width == 0 || i % width == height - 1) // border
        continue;

      int x = i % width;
      int y = i / width;

      int sum_r = 0, sum_g = 0, sum_b = 0;

      Pixel *base_ptr = reinterpret_cast<Pixel *>(buffer) + y * width + x;

      sum_r += (base_ptr[-width - 1].r * filter[0][0]) +
               (base_ptr[-width].r * filter[0][1]) +
               (base_ptr[-width + 1].r * filter[0][2]) +
               (base_ptr[-1].r * filter[1][0]) +
               (base_ptr[0].r * filter[1][1]) + (base_ptr[1].r * filter[1][2]) +
               (base_ptr[width - 1].r * filter[2][0]) +
               (base_ptr[width].r * filter[2][1]) +
               (base_ptr[width + 1].r * filter[2][2]);

      sum_g += (base_ptr[-width - 1].g * filter[0][0]) +
               (base_ptr[-width].g * filter[0][1]) +
               (base_ptr[-width + 1].g * filter[0][2]) +
               (base_ptr[-1].g * filter[1][0]) +
               (base_ptr[0].g * filter[1][1]) + (base_ptr[1].g * filter[1][2]) +
               (base_ptr[width - 1].g * filter[2][0]) +
               (base_ptr[width].g * filter[2][1]) +
               (base_ptr[width + 1].g * filter[2][2]);

      sum_b += (base_ptr[-width - 1].b * filter[0][0]) +
               (base_ptr[-width].b * filter[0][1]) +
               (base_ptr[-width + 1].b * filter[0][2]) +
               (base_ptr[-1].b * filter[1][0]) +
               (base_ptr[0].b * filter[1][1]) + (base_ptr[1].b * filter[1][2]) +
               (base_ptr[width - 1].b * filter[2][0]) +
               (base_ptr[width].b * filter[2][1]) +
               (base_ptr[width + 1].b * filter[2][2]);

      Pixel *output_pixels = reinterpret_cast<Pixel *>(filteredImage);
      Pixel &out_pixel = output_pixels[i];

      out_pixel.r = static_cast<unsigned char>(sum_r);
      out_pixel.g = static_cast<unsigned char>(sum_g);
      out_pixel.b = static_cast<unsigned char>(sum_b);
    }
  }
  auto end_time = std::chrono::high_resolution_clock::now();
#pragma acc update self(filteredImage [0:width * height * num_channels],       \
                        buffer [0:width * height * num_channels])

#pragma acc exit data copyout(filteredImage [0:width * height * num_channels])

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
  delete[] buffer;
  std::cout << "Transformation Complete!" << std::endl;
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";
  return 0;
}

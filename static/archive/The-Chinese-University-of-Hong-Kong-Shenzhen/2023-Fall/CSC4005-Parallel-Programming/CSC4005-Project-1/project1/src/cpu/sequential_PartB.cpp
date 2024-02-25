/*
    This code is modified by Yohandi on 2023/10/3.
    Email: yohandi@link.cuhk.edu.cn

    11000 ms -> 4728 ms
*/

#include "utils.hpp"
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

const int FILTER_SIZE = 3;
const float filter[FILTER_SIZE][FILTER_SIZE] = {{1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9}};

struct Pixel {
  unsigned char r, g, b;
};

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Invalid argument, should be: ./executable "
                 "/path/to/input/jpeg /path/to/output/jpeg\n";
    return -1;
  }

  const char *input_filename = argv[1];
  std::cout << "Input file from: " << input_filename << "\n";
  auto input_jpeg = read_from_jpeg(input_filename);

  auto filteredImage = new Pixel[input_jpeg.width * input_jpeg.height];

  auto start_time = std::chrono::high_resolution_clock::now();

  for (int height = 1; height < input_jpeg.height - 1; height++) {
    for (int width = 1; width < input_jpeg.width - 1; width++) {
      int sum_r = 0, sum_g = 0, sum_b = 0;

      Pixel *base_ptr = reinterpret_cast<Pixel *>(input_jpeg.buffer) +
                        height * input_jpeg.width + width;

      sum_r += (base_ptr[-input_jpeg.width - 1].r * filter[0][0]) +
               (base_ptr[-input_jpeg.width].r * filter[0][1]) +
               (base_ptr[-input_jpeg.width + 1].r * filter[0][2]) +
               (base_ptr[-1].r * filter[1][0]) +
               (base_ptr[0].r * filter[1][1]) + (base_ptr[1].r * filter[1][2]) +
               (base_ptr[input_jpeg.width - 1].r * filter[2][0]) +
               (base_ptr[input_jpeg.width].r * filter[2][1]) +
               (base_ptr[input_jpeg.width + 1].r * filter[2][2]);

      sum_g += (base_ptr[-input_jpeg.width - 1].g * filter[0][0]) +
               (base_ptr[-input_jpeg.width].g * filter[0][1]) +
               (base_ptr[-input_jpeg.width + 1].g * filter[0][2]) +
               (base_ptr[-1].g * filter[1][0]) +
               (base_ptr[0].g * filter[1][1]) + (base_ptr[1].g * filter[1][2]) +
               (base_ptr[input_jpeg.width - 1].g * filter[2][0]) +
               (base_ptr[input_jpeg.width].g * filter[2][1]) +
               (base_ptr[input_jpeg.width + 1].g * filter[2][2]);

      sum_b += (base_ptr[-input_jpeg.width - 1].b * filter[0][0]) +
               (base_ptr[-input_jpeg.width].b * filter[0][1]) +
               (base_ptr[-input_jpeg.width + 1].b * filter[0][2]) +
               (base_ptr[-1].b * filter[1][0]) +
               (base_ptr[0].b * filter[1][1]) + (base_ptr[1].b * filter[1][2]) +
               (base_ptr[input_jpeg.width - 1].b * filter[2][0]) +
               (base_ptr[input_jpeg.width].b * filter[2][1]) +
               (base_ptr[input_jpeg.width + 1].b * filter[2][2]);

      Pixel &out_pixel = filteredImage[height * input_jpeg.width + width];
      out_pixel.r = static_cast<unsigned char>(sum_r);
      out_pixel.g = static_cast<unsigned char>(sum_g);
      out_pixel.b = static_cast<unsigned char>(sum_b);
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  const char *output_filepath = argv[2];
  std::cout << "Output file to: " << output_filepath << "\n";
  JPEGMeta output_jpeg{reinterpret_cast<unsigned char *>(filteredImage),
                       input_jpeg.width, input_jpeg.height,
                       input_jpeg.num_channels, input_jpeg.color_space};
  if (write_to_jpeg(output_jpeg, output_filepath)) {
    std::cerr << "Failed to write output JPEG\n";
    return -1;
  }

  delete[] input_jpeg.buffer;
  delete[] filteredImage;
  std::cout << "Transformation Complete!" << std::endl;
  std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds\n";
  return 0;
}

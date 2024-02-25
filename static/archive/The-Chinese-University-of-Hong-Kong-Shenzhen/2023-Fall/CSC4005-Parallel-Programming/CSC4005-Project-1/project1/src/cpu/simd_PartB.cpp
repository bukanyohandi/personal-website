/*
    Created by Yohandi on 2023/10/7.
    Email: yohandi@link.cuhk.edu.cn

    SIMD (AVX2) implementation of applying a 3 x 3 filter to a JPEG image

    Few parts were taken from simd_PartA.cpp created by Yang Yufan as reference

    execution time: 1195 ms
*/

#include <chrono>
#include <immintrin.h>
#include <iomanip>
#include <iostream>

#include "utils.hpp"

const int FILTER_SIZE = 3;
const float filter[FILTER_SIZE][FILTER_SIZE] = {{1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9},
                                                {1.0f / 9, 1.0f / 9, 1.0f / 9}};

int main(int argc, char **argv) {
  // Verify input argument format
  if (argc != 3) {
    std::cerr << "Invalid argument, should be: ./executable "
                 "/path/to/input/jpeg /path/to/output/jpeg\n";
    return -1;
  }
  // Read JPEG File
  const char *input_filepath = argv[1];
  std::cout << "Input file from: " << input_filepath << "\n";
  auto input_jpeg = read_from_jpeg(input_filepath);
  if (input_jpeg.buffer == NULL) {
    std::cerr << "Failed to read input JPEG image\n";
    return -1;
  }

  // Apply filter for the RGB Contents
  auto filteredImage = new unsigned char[input_jpeg.width * input_jpeg.height *
                                             input_jpeg.num_channels +
                                         8];

  // Prepross, store reds, greens and blues separately
  auto reds = new unsigned char[input_jpeg.width * input_jpeg.height + 16];
  auto greens = new unsigned char[input_jpeg.width * input_jpeg.height + 16];
  auto blues = new unsigned char[input_jpeg.width * input_jpeg.height + 16];

  for (int i = 0; i < input_jpeg.width * input_jpeg.height; i++) {
    reds[i] = input_jpeg.buffer[i * input_jpeg.num_channels];
    greens[i] = input_jpeg.buffer[i * input_jpeg.num_channels + 1];
    blues[i] = input_jpeg.buffer[i * input_jpeg.num_channels + 2];
  }

  // Set SIMD scalars, we use AVX2 instructions
  __m256 __filter[3][3];

  __filter[0][0] = _mm256_set1_ps(filter[0][0]);
  __filter[0][1] = _mm256_set1_ps(filter[0][1]);
  __filter[0][2] = _mm256_set1_ps(filter[0][2]);

  __filter[1][0] = _mm256_set1_ps(filter[1][0]);
  __filter[1][1] = _mm256_set1_ps(filter[1][1]);
  __filter[1][2] = _mm256_set1_ps(filter[1][2]);

  __filter[2][0] = _mm256_set1_ps(filter[2][0]);
  __filter[2][1] = _mm256_set1_ps(filter[2][1]);
  __filter[2][2] = _mm256_set1_ps(filter[2][2]);

  // Mask used for shuffling when store int32s to u_int8 arrays
  // |0|0|0|4|0|0|0|3|0|0|0|2|0|0|0|1| -> |4|3|2|1|
  __m128i shuffle = _mm_setr_epi8(0, 4, 8, 12, -1, -1, -1, -1, -1, -1, -1, -1,
                                  -1, -1, -1, -1);

  // Using SIMD to accelerate the transformation
  auto start_time =
      std::chrono::high_resolution_clock::now(); // Start recording time

  for (int i = input_jpeg.width + 1;
       i < input_jpeg.width * (input_jpeg.height - 1); i += 8) {
    // Load the 8 red chars to a 256 bits float register
    __m128i red_chars[3][3];

    red_chars[0][0] =
        _mm_loadu_si128((__m128i *)(reds + i - input_jpeg.width - 1));
    red_chars[0][1] = _mm_loadu_si128((__m128i *)(reds + i - input_jpeg.width));
    red_chars[0][2] =
        _mm_loadu_si128((__m128i *)(reds + i - input_jpeg.width + 1));
    red_chars[1][0] = _mm_loadu_si128((__m128i *)(reds + i - 1));
    red_chars[1][1] = _mm_loadu_si128((__m128i *)(reds + i));
    red_chars[1][2] = _mm_loadu_si128((__m128i *)(reds + i + 1));
    red_chars[2][0] =
        _mm_loadu_si128((__m128i *)(reds + i + input_jpeg.width - 1));
    red_chars[2][1] = _mm_loadu_si128((__m128i *)(reds + i + input_jpeg.width));
    red_chars[2][2] =
        _mm_loadu_si128((__m128i *)(reds + i + input_jpeg.width + 1));

    __m256i red_ints[3][3];
    __m256 red_floats[3][3];

    red_ints[0][0] = _mm256_cvtepu8_epi32(red_chars[0][0]);
    red_floats[0][0] = _mm256_cvtepi32_ps(red_ints[0][0]);
    red_ints[0][1] = _mm256_cvtepu8_epi32(red_chars[0][1]);
    red_floats[0][1] = _mm256_cvtepi32_ps(red_ints[0][1]);
    red_ints[0][2] = _mm256_cvtepu8_epi32(red_chars[0][2]);
    red_floats[0][2] = _mm256_cvtepi32_ps(red_ints[0][2]);
    red_ints[1][0] = _mm256_cvtepu8_epi32(red_chars[1][0]);
    red_floats[1][0] = _mm256_cvtepi32_ps(red_ints[1][0]);
    red_ints[1][1] = _mm256_cvtepu8_epi32(red_chars[1][1]);
    red_floats[1][1] = _mm256_cvtepi32_ps(red_ints[1][1]);
    red_ints[1][2] = _mm256_cvtepu8_epi32(red_chars[1][2]);
    red_floats[1][2] = _mm256_cvtepi32_ps(red_ints[1][2]);
    red_ints[2][0] = _mm256_cvtepu8_epi32(red_chars[2][0]);
    red_floats[2][0] = _mm256_cvtepi32_ps(red_ints[2][0]);
    red_ints[2][1] = _mm256_cvtepu8_epi32(red_chars[2][1]);
    red_floats[2][1] = _mm256_cvtepi32_ps(red_ints[2][1]);
    red_ints[2][2] = _mm256_cvtepu8_epi32(red_chars[2][2]);
    red_floats[2][2] = _mm256_cvtepi32_ps(red_ints[2][2]);

    // Multiply the red floats to the red scalar
    __m256 red_results[3][3];
    red_results[0][0] = _mm256_mul_ps(red_floats[0][0], __filter[0][0]);
    red_results[0][1] = _mm256_mul_ps(red_floats[0][1], __filter[0][1]);
    red_results[0][2] = _mm256_mul_ps(red_floats[0][2], __filter[0][2]);
    red_results[1][0] = _mm256_mul_ps(red_floats[1][0], __filter[1][0]);
    red_results[1][1] = _mm256_mul_ps(red_floats[1][1], __filter[1][1]);
    red_results[1][2] = _mm256_mul_ps(red_floats[1][2], __filter[1][2]);
    red_results[2][0] = _mm256_mul_ps(red_floats[2][0], __filter[2][0]);
    red_results[2][1] = _mm256_mul_ps(red_floats[2][1], __filter[2][1]);
    red_results[2][2] = _mm256_mul_ps(red_floats[2][2], __filter[2][2]);

    // Load the 8 green chars to a 256 bits float register
    __m128i green_chars[3][3];

    green_chars[0][0] =
        _mm_loadu_si128((__m128i *)(greens + i - input_jpeg.width - 1));
    green_chars[0][1] =
        _mm_loadu_si128((__m128i *)(greens + i - input_jpeg.width));
    green_chars[0][2] =
        _mm_loadu_si128((__m128i *)(greens + i - input_jpeg.width + 1));
    green_chars[1][0] = _mm_loadu_si128((__m128i *)(greens + i - 1));
    green_chars[1][1] = _mm_loadu_si128((__m128i *)(greens + i));
    green_chars[1][2] = _mm_loadu_si128((__m128i *)(greens + i + 1));
    green_chars[2][0] =
        _mm_loadu_si128((__m128i *)(greens + i + input_jpeg.width - 1));
    green_chars[2][1] =
        _mm_loadu_si128((__m128i *)(greens + i + input_jpeg.width));
    green_chars[2][2] =
        _mm_loadu_si128((__m128i *)(greens + i + input_jpeg.width + 1));

    __m256i green_ints[3][3];
    __m256 green_floats[3][3];

    green_ints[0][0] = _mm256_cvtepu8_epi32(green_chars[0][0]);
    green_floats[0][0] = _mm256_cvtepi32_ps(green_ints[0][0]);
    green_ints[0][1] = _mm256_cvtepu8_epi32(green_chars[0][1]);
    green_floats[0][1] = _mm256_cvtepi32_ps(green_ints[0][1]);
    green_ints[0][2] = _mm256_cvtepu8_epi32(green_chars[0][2]);
    green_floats[0][2] = _mm256_cvtepi32_ps(green_ints[0][2]);
    green_ints[1][0] = _mm256_cvtepu8_epi32(green_chars[1][0]);
    green_floats[1][0] = _mm256_cvtepi32_ps(green_ints[1][0]);
    green_ints[1][1] = _mm256_cvtepu8_epi32(green_chars[1][1]);
    green_floats[1][1] = _mm256_cvtepi32_ps(green_ints[1][1]);
    green_ints[1][2] = _mm256_cvtepu8_epi32(green_chars[1][2]);
    green_floats[1][2] = _mm256_cvtepi32_ps(green_ints[1][2]);
    green_ints[2][0] = _mm256_cvtepu8_epi32(green_chars[2][0]);
    green_floats[2][0] = _mm256_cvtepi32_ps(green_ints[2][0]);
    green_ints[2][1] = _mm256_cvtepu8_epi32(green_chars[2][1]);
    green_floats[2][1] = _mm256_cvtepi32_ps(green_ints[2][1]);
    green_ints[2][2] = _mm256_cvtepu8_epi32(green_chars[2][2]);
    green_floats[2][2] = _mm256_cvtepi32_ps(green_ints[2][2]);

    // Multiply the green floats to the green scalar
    __m256 green_results[3][3];
    green_results[0][0] = _mm256_mul_ps(green_floats[0][0], __filter[0][0]);
    green_results[0][1] = _mm256_mul_ps(green_floats[0][1], __filter[0][1]);
    green_results[0][2] = _mm256_mul_ps(green_floats[0][2], __filter[0][2]);
    green_results[1][0] = _mm256_mul_ps(green_floats[1][0], __filter[1][0]);
    green_results[1][1] = _mm256_mul_ps(green_floats[1][1], __filter[1][1]);
    green_results[1][2] = _mm256_mul_ps(green_floats[1][2], __filter[1][2]);
    green_results[2][0] = _mm256_mul_ps(green_floats[2][0], __filter[2][0]);
    green_results[2][1] = _mm256_mul_ps(green_floats[2][1], __filter[2][1]);
    green_results[2][2] = _mm256_mul_ps(green_floats[2][2], __filter[2][2]);

    // Load the 8 blue chars to a 256 bits float register
    __m128i blue_chars[3][3];

    blue_chars[0][0] =
        _mm_loadu_si128((__m128i *)(blues + i - input_jpeg.width - 1));
    blue_chars[0][1] =
        _mm_loadu_si128((__m128i *)(blues + i - input_jpeg.width));
    blue_chars[0][2] =
        _mm_loadu_si128((__m128i *)(blues + i - input_jpeg.width + 1));
    blue_chars[1][0] = _mm_loadu_si128((__m128i *)(blues + i - 1));
    blue_chars[1][1] = _mm_loadu_si128((__m128i *)(blues + i));
    blue_chars[1][2] = _mm_loadu_si128((__m128i *)(blues + i + 1));
    blue_chars[2][0] =
        _mm_loadu_si128((__m128i *)(blues + i + input_jpeg.width - 1));
    blue_chars[2][1] =
        _mm_loadu_si128((__m128i *)(blues + i + input_jpeg.width));
    blue_chars[2][2] =
        _mm_loadu_si128((__m128i *)(blues + i + input_jpeg.width + 1));

    __m256i blue_ints[3][3];
    __m256 blue_floats[3][3];

    blue_ints[0][0] = _mm256_cvtepu8_epi32(blue_chars[0][0]);
    blue_floats[0][0] = _mm256_cvtepi32_ps(blue_ints[0][0]);
    blue_ints[0][1] = _mm256_cvtepu8_epi32(blue_chars[0][1]);
    blue_floats[0][1] = _mm256_cvtepi32_ps(blue_ints[0][1]);
    blue_ints[0][2] = _mm256_cvtepu8_epi32(blue_chars[0][2]);
    blue_floats[0][2] = _mm256_cvtepi32_ps(blue_ints[0][2]);
    blue_ints[1][0] = _mm256_cvtepu8_epi32(blue_chars[1][0]);
    blue_floats[1][0] = _mm256_cvtepi32_ps(blue_ints[1][0]);
    blue_ints[1][1] = _mm256_cvtepu8_epi32(blue_chars[1][1]);
    blue_floats[1][1] = _mm256_cvtepi32_ps(blue_ints[1][1]);
    blue_ints[1][2] = _mm256_cvtepu8_epi32(blue_chars[1][2]);
    blue_floats[1][2] = _mm256_cvtepi32_ps(blue_ints[1][2]);
    blue_ints[2][0] = _mm256_cvtepu8_epi32(blue_chars[2][0]);
    blue_floats[2][0] = _mm256_cvtepi32_ps(blue_ints[2][0]);
    blue_ints[2][1] = _mm256_cvtepu8_epi32(blue_chars[2][1]);
    blue_floats[2][1] = _mm256_cvtepi32_ps(blue_ints[2][1]);
    blue_ints[2][2] = _mm256_cvtepu8_epi32(blue_chars[2][2]);
    blue_floats[2][2] = _mm256_cvtepi32_ps(blue_ints[2][2]);

    // Multiply the blue floats to the blue scalar
    __m256 blue_results[3][3];
    blue_results[0][0] = _mm256_mul_ps(blue_floats[0][0], __filter[0][0]);
    blue_results[0][1] = _mm256_mul_ps(blue_floats[0][1], __filter[0][1]);
    blue_results[0][2] = _mm256_mul_ps(blue_floats[0][2], __filter[0][2]);
    blue_results[1][0] = _mm256_mul_ps(blue_floats[1][0], __filter[1][0]);
    blue_results[1][1] = _mm256_mul_ps(blue_floats[1][1], __filter[1][1]);
    blue_results[1][2] = _mm256_mul_ps(blue_floats[1][2], __filter[1][2]);
    blue_results[2][0] = _mm256_mul_ps(blue_floats[2][0], __filter[2][0]);
    blue_results[2][1] = _mm256_mul_ps(blue_floats[2][1], __filter[2][1]);
    blue_results[2][2] = _mm256_mul_ps(blue_floats[2][2], __filter[2][2]);

    // Add red, green and blue results, respectively
    __m256 sum_red = _mm256_setzero_ps();
    sum_red = _mm256_add_ps(sum_red, red_results[0][0]);
    sum_red = _mm256_add_ps(sum_red, red_results[0][1]);
    sum_red = _mm256_add_ps(sum_red, red_results[0][2]);
    sum_red = _mm256_add_ps(sum_red, red_results[1][0]);
    sum_red = _mm256_add_ps(sum_red, red_results[1][1]);
    sum_red = _mm256_add_ps(sum_red, red_results[1][2]);
    sum_red = _mm256_add_ps(sum_red, red_results[2][0]);
    sum_red = _mm256_add_ps(sum_red, red_results[2][1]);
    sum_red = _mm256_add_ps(sum_red, red_results[2][2]);

    __m256 sum_green = _mm256_setzero_ps();
    sum_green = _mm256_add_ps(sum_green, green_results[0][0]);
    sum_green = _mm256_add_ps(sum_green, green_results[0][1]);
    sum_green = _mm256_add_ps(sum_green, green_results[0][2]);
    sum_green = _mm256_add_ps(sum_green, green_results[1][0]);
    sum_green = _mm256_add_ps(sum_green, green_results[1][1]);
    sum_green = _mm256_add_ps(sum_green, green_results[1][2]);
    sum_green = _mm256_add_ps(sum_green, green_results[2][0]);
    sum_green = _mm256_add_ps(sum_green, green_results[2][1]);
    sum_green = _mm256_add_ps(sum_green, green_results[2][2]);

    __m256 sum_blue = _mm256_setzero_ps();
    sum_blue = _mm256_add_ps(sum_blue, blue_results[0][0]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[0][1]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[0][2]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[1][0]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[1][1]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[1][2]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[2][0]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[2][1]);
    sum_blue = _mm256_add_ps(sum_blue, blue_results[2][2]);

    // Convert the float32 results to int32
    __m256i sum_red_ints = _mm256_cvtps_epi32(sum_red);
    __m256i sum_green_ints = _mm256_cvtps_epi32(sum_green);
    __m256i sum_blue_ints = _mm256_cvtps_epi32(sum_blue);

    int red_values[8], green_values[8], blue_values[8];

    // Step 1: Convert the SIMD values into arrays.
    _mm256_storeu_si256((__m256i *)red_values, sum_red_ints);
    _mm256_storeu_si256((__m256i *)green_values, sum_green_ints);
    _mm256_storeu_si256((__m256i *)blue_values, sum_blue_ints);

    // Step 2: Perform the interleaving using array indexing.
    for (int j = 0; j < 8; ++j) {
      filteredImage[i * 3 + j * 3] = (unsigned char)red_values[j];
      filteredImage[i * 3 + j * 3 + 1] = (unsigned char)green_values[j];
      filteredImage[i * 3 + j * 3 + 2] = (unsigned char)blue_values[j];
    }

    // for(int j = 0; j < 24; ++j){
    //     std::cout << (int)filteredImage[i * 3 + j] << " ";
    // }
    // std::cout << "\t";
    // int tmp[8];
    // _mm256_storeu_si256((__m256i*)tmp, sum_red_ints);
    // std::cout << std::fixed << std::setprecision(0);
    // for(int j = 0; j < 8; ++j){
    //     std::cout << tmp[j] << " ";
    // }
    // std::cout << "\t";
    // _mm256_storeu_si256((__m256i*)tmp, sum_green_ints);
    // for(int j = 0; j < 8; ++j){
    //     std::cout << tmp[j] << " ";
    // }
    // std::cout << "\t";
    // _mm256_storeu_si256((__m256i*)tmp, sum_blue_ints);
    // for(int j = 0; j < 8; ++j){
    //     std::cout << tmp[j] << " ";
    // }
    // std::cout << "\n";
  }

  auto end_time =
      std::chrono::high_resolution_clock::now(); // Stop recording time
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  // Save the filtered Image
  const char *output_filepath = argv[2];
  std::cout << "Output file to: " << output_filepath << "\n";
  JPEGMeta output_jpeg{filteredImage, input_jpeg.width, input_jpeg.height,
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

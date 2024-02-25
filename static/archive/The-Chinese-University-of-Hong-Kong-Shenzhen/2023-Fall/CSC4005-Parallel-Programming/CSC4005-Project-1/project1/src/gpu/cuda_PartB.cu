/*
    Created by Yohandi on 2023/10/5.
    Email: yohandi@link.cuhk.edu.cn

    CUDA implementation of applying a 3 x 3 filter to a JPEG image

    Few parts were taken from cuda_PartA.cpp created by Yang Yufan as reference

    GPU execution time: 23 ms
*/

#include <iostream>

#include <cuda_runtime.h> // CUDA Header

#include "utils.hpp"

const int FILTER_SIZE = 3;
__constant__ float filter[FILTER_SIZE][FILTER_SIZE] = {
    {1.0f / 9, 1.0f / 9, 1.0f / 9},
    {1.0f / 9, 1.0f / 9, 1.0f / 9},
    {1.0f / 9, 1.0f / 9, 1.0f / 9}};

struct Pixel {
  unsigned char r, g, b;
};

// CUDA kernel functon：filter RGB
__global__ void filterRGB(unsigned char *input, unsigned char *output,
                          int width, int height, int num_channels) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;

  if (idx < width || idx >= width * (height - 1) || idx % width == 0 || idx % width == height - 1) // border
    return;

  if (idx < width * height) {
    Pixel *base_ptr = reinterpret_cast<Pixel *>(input) + idx;
    int sum_r = 0, sum_g = 0, sum_b = 0;

    sum_r += (base_ptr[-width - 1].r * filter[0][0]) +
             (base_ptr[-width].r * filter[0][1]) +
             (base_ptr[-width + 1].r * filter[0][2]) +
             (base_ptr[-1].r * filter[1][0]) + (base_ptr[0].r * filter[1][1]) +
             (base_ptr[1].r * filter[1][2]) +
             (base_ptr[width - 1].r * filter[2][0]) +
             (base_ptr[width].r * filter[2][1]) +
             (base_ptr[width + 1].r * filter[2][2]);

    sum_g += (base_ptr[-width - 1].g * filter[0][0]) +
             (base_ptr[-width].g * filter[0][1]) +
             (base_ptr[-width + 1].g * filter[0][2]) +
             (base_ptr[-1].g * filter[1][0]) + (base_ptr[0].g * filter[1][1]) +
             (base_ptr[1].g * filter[1][2]) +
             (base_ptr[width - 1].g * filter[2][0]) +
             (base_ptr[width].g * filter[2][1]) +
             (base_ptr[width + 1].g * filter[2][2]);

    sum_b += (base_ptr[-width - 1].b * filter[0][0]) +
             (base_ptr[-width].b * filter[0][1]) +
             (base_ptr[-width + 1].b * filter[0][2]) +
             (base_ptr[-1].b * filter[1][0]) + (base_ptr[0].b * filter[1][1]) +
             (base_ptr[1].b * filter[1][2]) +
             (base_ptr[width - 1].b * filter[2][0]) +
             (base_ptr[width].b * filter[2][1]) +
             (base_ptr[width + 1].b * filter[2][2]);

    Pixel *output_pixels = reinterpret_cast<Pixel *>(output);
    Pixel &out_pixel = output_pixels[idx];

    out_pixel.r = static_cast<unsigned char>(sum_r);
    out_pixel.g = static_cast<unsigned char>(sum_g);
    out_pixel.b = static_cast<unsigned char>(sum_b);
  }
}

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
  auto input_jpeg = read_from_jpeg(input_filepath);
  // Allocate memory on host (CPU)
  auto filteredImage = new unsigned char[input_jpeg.width * input_jpeg.height *
                                         input_jpeg.num_channels];
  // Allocate memory on device (GPU)
  unsigned char *d_input;
  unsigned char *d_output;
  cudaMalloc((void **)&d_input, input_jpeg.width * input_jpeg.height *
                                    input_jpeg.num_channels *
                                    sizeof(unsigned char));
  cudaMalloc((void **)&d_output, input_jpeg.width * input_jpeg.height *
                                     input_jpeg.num_channels *
                                     sizeof(unsigned char));
  // Copy input data from host to device
  cudaMemcpy(d_input, input_jpeg.buffer,
             input_jpeg.width * input_jpeg.height * input_jpeg.num_channels *
                 sizeof(unsigned char),
             cudaMemcpyHostToDevice);

  // Apply filter to RGB
  cudaEvent_t start, stop;
  float gpuDuration;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  int blockSize = 128; // 256
  int numBlocks =
      (input_jpeg.width * input_jpeg.height * input_jpeg.num_channels +
       blockSize - 1) /
      blockSize;
  // int numBlocks = (input_jpeg.width * input_jpeg.height *
  // input_jpeg.num_channels) / blockSize + 1;
  cudaEventRecord(start, 0); // GPU start time
  filterRGB<<<numBlocks, blockSize>>>(d_input, d_output, input_jpeg.width,
                                      input_jpeg.height,
                                      input_jpeg.num_channels);
  cudaEventRecord(stop, 0); // GPU end time
  cudaEventSynchronize(stop);
  // Print the result of the GPU computation
  cudaEventElapsedTime(&gpuDuration, start, stop);
  // Copy output data from device to host
  cudaMemcpy(filteredImage, d_output,
             input_jpeg.width * input_jpeg.height * input_jpeg.num_channels,
             cudaMemcpyDeviceToHost);
  // Write filteredImage to output JPEG
  const char *output_filepath = argv[2];
  std::cout << "Output file to: " << output_filepath << "\n";
  JPEGMeta output_jpeg{filteredImage, input_jpeg.width, input_jpeg.height,
                       input_jpeg.num_channels, input_jpeg.color_space};
  if (write_to_jpeg(output_jpeg, output_filepath)) {
    std::cerr << "Failed to write output JPEG\n";
    return -1;
  }
  // Release allocated memory on device and host
  cudaFree(d_input);
  cudaFree(d_output);
  delete[] input_jpeg.buffer;
  delete[] filteredImage;
  std::cout << "Transformation Complete!" << std::endl;
  std::cout << "GPU Execution Time: " << gpuDuration << " milliseconds"
            << std::endl;
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  return 0;
}
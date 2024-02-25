/*
    Created by Yohandi on 2023/10/5.
    Email: yohandi@link.cuhk.edu.cn

    MPI + OpenMP hybrid implementation of applying a 3 x 3 filter to a JPEG
   image

    Few parts were taken from mpi_PartA.cpp created by Yang Yufan as reference

    number of cores     execution time (ms)
    1                   7192
    2                   6066
    4                   3253
    8                   1841
    16                  1098
    32                  900
*/

#include <chrono>
#include <iostream>
#include <vector>

#include <mpi.h> // MPI Header
#include <omp.h> // OpenMP Header

#include "utils.hpp"

#define MASTER 0
#define TAG_GATHER 0

const int FACTOR = 16;
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
  // Start the MPI
  MPI_Init(&argc, &argv);
  // How many processes are running
  int numtasks;
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  // What's my rank?
  int taskid;
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  // Which node am I running on?
  int len;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(hostname, &len);
  MPI_Status status;

  JPEGMeta input_jpeg;

  if (taskid == MASTER) {
    // Read JPEG File
    const char *input_filepath = argv[1];
    std::cout << "Input file from: " << input_filepath << "\n";
    input_jpeg = read_from_jpeg(input_filepath);
    if (input_jpeg.buffer == NULL) {
      std::cerr << "Failed to read input JPEG image\n";
      return -1;
    }
  }

  // Broadcast the metadata
  MPI_Bcast(&input_jpeg.width, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(&input_jpeg.height, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(&input_jpeg.num_channels, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

  // Allocate memory for buffer in non-MASTER tasks
  if (taskid != MASTER) {
    input_jpeg.buffer = new unsigned char[input_jpeg.width * input_jpeg.height *
                                          input_jpeg.num_channels];
  }

  // Broadcast the image data
  MPI_Bcast(input_jpeg.buffer,
            input_jpeg.width * input_jpeg.height * input_jpeg.num_channels,
            MPI_CHAR, MASTER, MPI_COMM_WORLD);

  MPI_Datatype MPI_PIXEL;
  int lengths[] = {1, 1, 1};
  MPI_Aint offsets[] = {offsetof(Pixel, r), offsetof(Pixel, g),
                        offsetof(Pixel, b)};
  MPI_Datatype types[] = {MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR,
                          MPI_UNSIGNED_CHAR};

  MPI_Type_create_struct(3, lengths, offsets, types, &MPI_PIXEL);
  MPI_Type_commit(&MPI_PIXEL);

  auto start_time = std::chrono::high_resolution_clock::now();

  // Divide the task
  // For example, there are 11 pixels and 3 tasks,
  // we try to divide to 4 4 3 instead of 3 3 5
  int total_pixel_num = input_jpeg.width * (input_jpeg.height - 1);
  int pixel_num_per_task = total_pixel_num / numtasks;
  int left_pixel_num = total_pixel_num % numtasks;

  std::vector<int> cuts(numtasks + 1, 0);
  int divided_left_pixel_num = 0;

  for (int i = 0; i < numtasks; i++) {
    if (divided_left_pixel_num < left_pixel_num) {
      cuts[i + 1] = cuts[i] + pixel_num_per_task + 1;
      divided_left_pixel_num++;
    } else {
      cuts[i + 1] = cuts[i] + pixel_num_per_task;
    }
  }

  // The tasks for the master executor
  // 1. Apply filter to the first division of the RGB contents
  // 2. Receive the transformed contents from slave executors
  // 3. Write the filtered contents to the JPEG File
  if (taskid == MASTER) {
    // Apply filter to the first division of the RGB contents
    auto filteredImage = new Pixel[input_jpeg.width * input_jpeg.height];

    int num_threads = omp_get_max_threads();
    int chunk_size = (cuts[MASTER + 1] - cuts[MASTER]) / (num_threads * FACTOR);

#pragma omp parallel for default(none)                                         \
    shared(input_jpeg, filteredImage, taskid, filter, cuts, chunk_size)        \
        schedule(guided)
    for (int i = cuts[MASTER]; i < cuts[MASTER + 1]; i++) {
      int height = i / input_jpeg.width;
      int width = i % input_jpeg.width;

      if (height == 0 || height == input_jpeg.height - 1 || width == 0 ||
          width == input_jpeg.width - 1) {
        Pixel &out_pixel = filteredImage[height * input_jpeg.width + width];
        out_pixel.r = static_cast<unsigned char>(0);
        out_pixel.g = static_cast<unsigned char>(0);
        out_pixel.b = static_cast<unsigned char>(0);
        continue;
      }

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

    // Receive the transformed contents from slave executors
    for (int i = MASTER + 1; i < numtasks; i++) {
      Pixel *start_pos = filteredImage + cuts[i];
      int length = cuts[i + 1] - cuts[i];
      MPI_Recv(start_pos, length, MPI_PIXEL, i, TAG_GATHER, MPI_COMM_WORLD,
               &status);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    // Save the filtered Image
    const char *output_filepath = argv[2];
    std::cout << "Output file to: " << output_filepath << "\n";
    JPEGMeta output_jpeg{reinterpret_cast<unsigned char *>(filteredImage),
                         input_jpeg.width, input_jpeg.height,
                         input_jpeg.num_channels, input_jpeg.color_space};
    if (write_to_jpeg(output_jpeg, output_filepath)) {
      std::cerr << "Failed to write output JPEG to file\n";
      MPI_Finalize();
      return -1;
    }

    // Release the memory
    MPI_Type_free(&MPI_PIXEL);
    delete[] input_jpeg.buffer;
    delete[] filteredImage;
    std::cout << "Transformation Complete!" << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count()
              << " milliseconds\n";
  }
  // The tasks for the slave executor
  // 1. Apply filter to the first division of the RGB contents
  // 2. Send the transformed contents back to the master executor
  else {
    // Apply filter to the first division of the RGB contents
    int length = cuts[taskid + 1] - cuts[taskid];
    auto filteredImage = new Pixel[length];

    int num_threads = omp_get_max_threads();
    int chunk_size = length / (num_threads * FACTOR);

#pragma omp parallel for default(none)                                         \
    shared(input_jpeg, filteredImage, taskid, filter, cuts, chunk_size)        \
        schedule(guided)
    for (int i = cuts[taskid]; i < cuts[taskid + 1]; i++) {
      int height = i / input_jpeg.width;
      int width = i % input_jpeg.width;

      if (height == 0 || height == input_jpeg.height - 1 || width == 0 ||
          width == input_jpeg.width - 1) {
        Pixel &out_pixel = filteredImage[i - cuts[taskid]];
        out_pixel.r = static_cast<unsigned char>(0);
        out_pixel.g = static_cast<unsigned char>(0);
        out_pixel.b = static_cast<unsigned char>(0);
        continue;
      }

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

      int j = i - cuts[taskid];
      Pixel &out_pixel = filteredImage[j];
      out_pixel.r = static_cast<unsigned char>(sum_r);
      out_pixel.g = static_cast<unsigned char>(sum_g);
      out_pixel.b = static_cast<unsigned char>(sum_b);
    }

    // Send the transformed contents back to the master executor
    MPI_Send(filteredImage, length, MPI_PIXEL, MASTER, TAG_GATHER,
             MPI_COMM_WORLD);

    // Release the memory
    MPI_Type_free(&MPI_PIXEL);
    delete[] filteredImage;
  }

  MPI_Finalize();
  return 0;
}

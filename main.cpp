#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

void blur(unsigned char* input, unsigned char* output, int width, int height, int channels, int radius) {       
    for (int i = 0; i < width * height * channels; i++) {
        output[i] = input[i];
        }   
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                int index = (y * width + x) * channels;
                int rSum = 0, gSum = 0, bSum = 0;
                int count = 0;
                for(int dy = -radius; dy <= radius; dy++){
                    for(int dx = -radius; dx <= radius; dx++){
                        int nx = x + dx;
                        if (nx < 0) nx = 0;
                        else if (nx >= width) nx = width - 1;

                        int ny = y + dy;
                        if (ny < 0) ny = 0;
                        else if (ny >= height) ny = height - 1;

                        int n_index = (ny * width + nx) * channels;

                        rSum += input[n_index];
                        gSum += input[n_index + 1];
                        bSum += input[n_index + 2];

                        count++;
                    }
                }
                output[index] = rSum / count;
                output[index + 1] = gSum / count;
                output[index + 2] = bSum / count;
            }
    }
}

void blurRange(unsigned char* input, unsigned char* output, int width, int height, int channels, int radius, int yStart, int yEnd) {       
    for (int i = 0; i < width * height * channels; i++) {
        output[i] = input[i];
        }   
        for(int y = yStart; y < yEnd; y++){
            for(int x = 0; x < width; x++){
                int index = (y * width + x) * channels;
                int rSum = 0, gSum = 0, bSum = 0;
                int count = 0;
                for(int dy = -radius; dy <= radius; dy++){
                    for(int dx = -radius; dx <= radius; dx++){
                        int nx = x + dx;
                        if (nx < 0) nx = 0;
                        else if (nx >= width) nx = width - 1;

                        int ny = y + dy;
                        if (ny < 0) ny = 0;
                        else if (ny >= height) ny = height - 1;

                        int n_index = (ny * width + nx) * channels;

                        rSum += input[n_index];
                        gSum += input[n_index + 1];
                        bSum += input[n_index + 2];

                        count++;
                    }
                }
                output[index] = rSum / count;
                output[index + 1] = gSum / count;
                output[index + 2] = bSum / count;
            }
    }
}




int main() {
    int width, height, channels;
    int R, G, B;
    int radius = 10;
    unsigned char* data = stbi_load("JPTest.jpg", &width, &height, &channels, 0);
    unsigned char* output = new unsigned char[width * height * channels];

    int numThreads = 10;
    int rowsPerThread = height / numThreads;
    
    std::vector<std::thread> threads;

    

    if (data == nullptr) {
        cout << "Failed to load image\n";
    }
    else {
        std::cout << "Width: " << width << "\n" << "Height: " << height << "\n" << "Channels: " << channels << "\n";
        auto start = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < numThreads; t++) {
            int yStart = t * rowsPerThread;
            int yEnd = (t == numThreads - 1) ? height : yStart + rowsPerThread;

            threads.emplace_back(blurRange, data, output, width, height, channels, radius, yStart, yEnd);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms\n";
        

        //Grayscale
        /* for (int i =0; i < width * height * channels; i += channels) {
            R = data[i];
            G = data[i+1];
            B = data[i+2];
            float gray = ((0.299 * R) + (0.587 * G) + (0.114 * B));
            data[i] = gray;
            data[i+1] = gray;
            data[i+2] = gray; */

        //Inverter
        /*for (int i=0; i < width * height * channels; i += channels) {
            R = data[i];
            G = data[i+1];
            B = data[i+2];
            data[i] = 255 - R;
            data[i+1] = 255 - G;
            data[i+2] = 255 - B;
        }*/

        //Blur
        /*Blur();*/
        }

       
        int write = stbi_write_jpg("BlurTest.jpg", width, height, channels, output, 90);
        if (write) {
            cout << "Saved Output.jpg successfully\n";
        }
        else {
            cout << "Failed: Output.jpg was not saved\n";
        }

        stbi_image_free(data);
        return 0;
    }

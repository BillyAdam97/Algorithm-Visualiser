#ifndef diffuseFuncs_hpp
#define diffuseFuncs_hpp
#include "Pixel.hpp"
#include <vector>

std::vector<std::vector<std::unique_ptr<Pixel>>> make_pixels(int width, int height, int rows);
void diffuse(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid, std::vector<std::vector<Pixel>>& next, float feed, float kill);
void drawpixels(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid);
float laplaceA(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid, int x, int y);
float laplaceB(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid, int x, int y);
float constain(float num, float low, float high);
void start_diffuse(int width, float feed, float kill);
void diffusionChoice(int& width, int& height);
#endif /* diffuseFuncs_hpp */

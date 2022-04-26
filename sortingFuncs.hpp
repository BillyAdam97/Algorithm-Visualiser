#ifndef sortingFuncs_hpp
#define sortingFuncs_hpp
#include "raylib.h"
#include "Bar.hpp"
#include <memory>
#include <vector>
#include <random>
#include <ctime>

std::vector<std::unique_ptr<Bar>> make_list(int columns, int width, int height);
void draw(std::vector<std::unique_ptr<Bar>>& alist);
void bubblesort(std::vector<std::unique_ptr<Bar>>& alist);
void start_bubble();
#endif /* sortingFuncs_hpp */

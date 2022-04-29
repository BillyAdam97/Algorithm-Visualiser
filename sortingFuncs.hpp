#ifndef sortingFuncs_hpp
#define sortingFuncs_hpp
#include "raylib.h"
#include "Bar.hpp"
#include <memory>
#include <vector>
#include <random>
#include <ctime>

std::vector<std::shared_ptr<Bar>> make_list(int columns, int width, int height);
void draw(std::vector<std::shared_ptr<Bar>>& alist);
void bubblesort(std::vector<std::shared_ptr<Bar>>& alist);
void start_bubble();
void quicksort(std::vector<std::shared_ptr<Bar>>& alist, int low, int high);
int partition(std::vector<std::shared_ptr<Bar>>& alist, int low, int high);
void start_quicksort();
void merge(std::vector<std::shared_ptr<Bar>>& alist, int begin, int mid, int end);
void mergeSort(std::vector<std::shared_ptr<Bar>>& alist, int begin, int end);
void start_merge();

#endif /* sortingFuncs_hpp */

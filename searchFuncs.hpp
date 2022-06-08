#ifndef searchFuncs_hpp
#define searchFuncs_hpp
#include "raylib.h"
#include "Bar.hpp"
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Bar>> makeSorted(int columns, int width, int height);
void drawSorted(std::vector<std::shared_ptr<Bar>>& alist);
void linearSearch(std::vector<std::shared_ptr<Bar>>& alist, std::shared_ptr<Bar>& chosen);
void startLinear(int width);
int getbar(Vector2 mouse, int columns, int width);

void binarySearch(std::vector<std::shared_ptr<Bar>>& alist, std::shared_ptr<Bar>& chosen);
void startBinary(int width);

void chooseSearch(int& width, int& height);
void searchControls(int& width, int& height);
#endif /* searchFuncs_hpp */

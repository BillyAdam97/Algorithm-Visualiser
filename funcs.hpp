#ifndef funcs_hpp
#define funcs_hpp
#include <utility>
#include <cmath>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Square.hpp"

//Utility
double h(std::shared_ptr<Square> a, std::shared_ptr<Square> b);
std::vector<std::vector<std::shared_ptr<Square>>> make_grid(int rows, int width);
void draw_grid(int rows, int width);
void draw(std::vector<std::vector<std::shared_ptr<Square>>>& grid, int rows, int width);
std::pair<int,int> get_clicked(Vector2 mousepos, int rows, int width);
void constructPath(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::unordered_map<int, std::shared_ptr<Square>>& came_from, std::shared_ptr<Square> end);

//A Star
void start_astar(int width);
bool algorithm(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::shared_ptr<Square> start, std::shared_ptr<Square> end);

//Dijkstras
void start_dijkstra(int width);
bool dijkstras(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::shared_ptr<Square> start, std::shared_ptr<Square> end);


//Game of Life
void start_gol(int width);
void gameoflife(std::vector<std::vector<std::shared_ptr<Square>>>& grid, int rows, int width);



#endif /* funcs_hpp */



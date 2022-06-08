#ifndef funcs_hpp
#define funcs_hpp
#include <utility>
#include <cmath>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Square.hpp"
#include "Tile.hpp"
#include "Entity.hpp"
#include <array>

//Choice menus
void choosePSA(int& width, int& height);
void chooseCA(int& width, int& height);
void psaControls(int& width, int& height);
void caControls(int& width, int& height);

//Utility - A Star & Dijkstras
double h(std::shared_ptr<Square> a, std::shared_ptr<Square> b);
std::vector<std::vector<std::shared_ptr<Square>>> make_Squares(int rows, int width);
void draw(std::vector<std::vector<std::shared_ptr<Square>>>& grid, int rows, int width);
void constructPath(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::unordered_map<int, std::shared_ptr<Square>>& came_from, std::shared_ptr<Square> end);
void randomWalls(std::vector<std::vector<std::shared_ptr<Square>>>& grid);

//Utility - All
void draw_grid(int rows, int width);
std::pair<int,int> get_clicked(Vector2 mousepos, int rows, int width);
void correct_bound(Vector2& mouse, int width, int height);

//Utility - GOL
std::vector<std::vector<std::shared_ptr<Entity>>> make_Entities(int rows, int width);
void draw(std::vector<std::vector<std::shared_ptr<Entity>>>& grid, int rows, int width);

//Utility - MapG
std::vector<std::vector<std::unique_ptr<Tile>>> make_map(int rows, int width, int density, int seed);
void draw(std::vector<std::vector<std::unique_ptr<Tile>>>& grid, int rows, int width);

//A Star
void start_astar(int width);
bool algorithm(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::shared_ptr<Square> start, std::shared_ptr<Square> end);

//Dijkstras
void start_dijkstra(int width);
bool dijkstras(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::shared_ptr<Square> start, std::shared_ptr<Square> end);


//Game of Life
void start_gol(int width);
void gameoflife(std::vector<std::vector<std::shared_ptr<Entity>>>& grid, int rows, int width);

//Wolfam
void ruleCA(std::vector<std::vector<std::shared_ptr<Entity>>>& grid, int rows, int width, int rule);
bool rules(bool left, bool mid, bool right, int rule);
void start_rule(int width, int rule);
void choose_rule(int width);

//Map Generator
void start_MapG(int width);
std::vector<std::vector<char>> make_temp(std::vector<std::vector<std::unique_ptr<Tile>>>& grid);
void map_gen(std::vector<std::vector<std::unique_ptr<Tile>>>& grid, int count);

#endif /* funcs_hpp */



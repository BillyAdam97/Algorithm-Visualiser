#ifndef mstfuncs_hpp
#define mstfuncs_hpp
#include "raylib.h"
#include "Node.hpp"
#include <queue>
#include <stack>

void drawGraph(std::vector<std::shared_ptr<Node>>& nodes);
void mst(std::vector<std::shared_ptr<Node>>& nodes, std::vector<float>& key, std::vector<bool>& mstSet);
int minKey(std::vector<float>& key, std::vector<bool>& mstSet);
void start_prims();
void start_bfs();
void bfs(std::vector<std::shared_ptr<Node>>& nodes);

void chooseMST(int& width, int& height);
void mstControls(int& width, int& height);

void dfs(std::vector<std::shared_ptr<Node>>& nodes);
void start_dfs();
#endif /* mstfuncs_hpp */

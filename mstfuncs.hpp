#ifndef mstfuncs_hpp
#define mstfuncs_hpp
#include "raylib.h"
#include "Node.hpp"

void drawGraph(std::vector<std::shared_ptr<Node>>& nodes);
void mst(std::vector<std::shared_ptr<Node>>& nodes, std::vector<float>& key, std::vector<bool>& mstSet);
int minKey(std::vector<float>& key, std::vector<bool>& mstSet);
void start_prims();
#endif /* mstfuncs_hpp */

#include "mazefuncs.hpp"
#include "raygui.h"

void removeWalls(std::shared_ptr<Cell>& cell1, std::shared_ptr<Cell>& cell2) {
    
    int x = cell1->row-cell2->row;
    if (x == 1) {
        cell1->walls[3] = false;
        cell2->walls[1] = false;
    }
    else if (x==-1) {
        cell1->walls[1] = false;
        cell2->walls[3] = false;
    }
    
    int y = cell1->col-cell2->col;
    if (y==1) {
        cell1->walls[0] = false;
        cell2->walls[2] = false;
    }
    else if (y==-1) {
        cell1->walls[2] = false;
        cell2->walls[0] = false;
    }
}

bool in_bounds(Vector2 pos, int width, int height) {
    if (pos.x<=0 || pos.x>=width || pos.y<=0 || pos.y>=height ) {
        return false;
    }
    return true;
}

std::vector<std::vector<std::shared_ptr<Cell>>> setup(int width, int height) {
    
    int cols = width/20;
    int rows = height/20;
    std::vector<std::vector<std::shared_ptr<Cell>>> grid;
    std::vector<std::shared_ptr<Cell>> line;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            line.emplace_back(std::make_shared<Cell>(i,j));
        }
        grid.emplace_back(line);
        line.clear();
    }
    return grid;
}

void drawgrid(std::vector<std::vector<std::shared_ptr<Cell>>>& grid, std::shared_ptr<Cell>& curr, std::stack<std::shared_ptr<Cell>>& mystack) {
    std::shared_ptr<Cell> neigh;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            grid[i][j]->draw();
        }
    }
    curr->visited = true;
    curr->highlight();
    neigh = curr->checkNeighbours(grid);
    
        if (neigh) {
            neigh->visited = true;
            mystack.push(curr);
            removeWalls(curr, neigh);
            curr = neigh;
        }
        else if (!mystack.empty()){
            curr = mystack.top();
            mystack.pop();
        }
}

void mazealgorithm(int width) {
    
    std::vector<std::vector<std::shared_ptr<Cell>>> grid = setup(width, width);
    std::stack<std::shared_ptr<Cell>> mystack;
    std::shared_ptr<Cell> curr = grid[0][0];
    SetTargetFPS(80);
    bool flag = true;
    
    while (flag) {
        BeginDrawing();
        ClearBackground(BLACK);
        drawgrid(grid, curr, mystack);
        EndDrawing();
        
        if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void chooseMisc(int& width, int& height)
{
    SetMousePosition(100, 100);
    Rectangle mazeB{275.0, 100.0, 250, 40};
    Rectangle diffuseB{275.0, 150.0, 250, 40};
    Rectangle controls{275.0, 200.0, 250, 40};
    Rectangle back{275.0, 250.0, 250, 40};
    
    bool flag = true;
    
    while (flag) {
        if (height!=350) {
            height = 350;
            SetWindowSize(width, height);
        }
        
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (GuiButton(mazeB, "Maze Generation")) {
            height = 800;
            SetWindowSize(width, height);
            mazealgorithm(width);
        }
        else if (GuiButton(diffuseB, "Reaction Diffusion")) {
            diffusionChoice(width, height);
        }
        else if (GuiButton(controls, "Controls")) {
            miscControls(width, height);
        }
        else if (GuiButton(back, "Back")) {
            flag = false;
        }
        EndDrawing();
    }
}

void miscControls(int& width, int& height)
{
    bool flag = true;
    Rectangle back{275.0, 250.0, 250,40};
    while (flag) {
        if (height!=350) {
            height = 350;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Delete - Exits out of algorithm.", 20, 100, 20, BLACK);
        DrawText("Reaction Diffusion", 20, 150, 30, BLACK);
        DrawText("Left Click - Adds 'Chemical' to the canvas.", 20, 200, 20, BLACK);
        if (GuiButton(back, "Back")) {
            flag = false;
        }
        
        EndDrawing();
    }
}

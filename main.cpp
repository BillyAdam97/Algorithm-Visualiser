#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include "funcs.hpp"
#include "sortingFuncs.hpp"
#include "mazefuncs.hpp"
#include "searchFuncs.hpp"
#include "diffuseFuncs.hpp"
#include "mstfuncs.hpp"

int main(void)
{
    int width = 800;
    int height = 800;
    
    //Buttons
    Rectangle psaB{(float)((width/2)-200.0), 100.0, 400, 75};
    
    Rectangle caB{(float)((width/2)-200.0), 200.0, 400, 75};
    
    Rectangle searchB{(float)((width/2)-200.0), 300.0, 400, 75};
    
    Rectangle mazeB{(float)((width/2)-200.0), 600.0, 400, 75};
    
    Rectangle linearB{(float)((width/2)-200.0), 400, 400, 75};
    
    Rectangle treeB{(float)((width/2)-200.0), 500.0, 400, 75};
    
    InitWindow(width, height, "Algorithm Visualiser");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (GuiButton(psaB, "Path Finding")) {
            choosePSA(width, height);
        }
        else if (GuiButton(caB, "Cellular Automata")) {
            chooseCA(width, height);
        }
        else if (GuiButton(searchB, "Sorting")) {
            chooseSort(width, height);
        }
        else if (GuiButton(mazeB, "Miscellaneous")) {
            chooseMisc(width, height);
        }
        else if (GuiButton(linearB, "Searching")) {
            chooseSearch(width, height);
        }
        else if (GuiButton(treeB, "Trees")) {
            chooseMST(width, height);
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

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
    int height = 300;
    
    //Buttons
    Rectangle psaB{100.0, 100.0, 250,40};
    Rectangle caB{100.0, 150.0, 250,40};
    
    Rectangle searchB{400.0, 100.0, 250,40};
    
    Rectangle mazeB{100.0, 200.0, 250,40};
    
    Rectangle linearB{400.0, 150.0, 250,40};
    
    Rectangle primsB{400.0, 200.0, 250,40};
    
    InitWindow(width, height, "Algorithm Visualiser");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    
    while (!WindowShouldClose())
    {
        if (height!=300) {
            height=300;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        
        //Options
        DrawText("Pick an Algorithm", 175, 25, 50, BLACK);

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
        else if (GuiButton(primsB, "Mininal Spanning Tree")) {
            chooseMST(width, height);
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

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
    
    //Buttons
    Rectangle astarB{100.0, 100.0, 250,40};
    Rectangle dijkB{100.0, 150.0, 250,40};
    Rectangle golB{100.0, 200.0, 250,40};
    Rectangle bubbleB{400.0, 100.0, 250,40};
    Rectangle quickB{400.0, 150.0, 250,40};
    Rectangle mergeB{400.0, 200.0, 250,40};
    Rectangle mazeB{100.0, 250.0, 250,40};
    Rectangle selectionB{400.0, 250.0, 250,40};
    Rectangle linearB{100.0, 300.0, 250,40};
    Rectangle binaryB{400.0, 300.0, 250,40};
    Rectangle mapgB{100.0, 350.0, 250,40};
    Rectangle diffuseB{400.0, 350.0, 250,40};
    Rectangle primsB{100.0, 400.0, 250,40};
    
    InitWindow(width, width, "Algorithm Visualiser");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        //Options
        DrawText("Pick an Algorithm", 175, 25, 50, BLACK);

        if (GuiButton(astarB, "A Star!")) {
            start_astar(width);
        }
        else if (GuiButton(dijkB, "Dijkstras!")) {
            start_dijkstra(width);
        }
        else if (GuiButton(golB, "Game Of Life!")) {
            start_gol(width);
        }
        else if (GuiButton(bubbleB, "Bubble Sort!")) {
            start_bubble();
        }
        else if (GuiButton(quickB, "Quick Sort!")) {
            start_quicksort();
        }
        else if (GuiButton(mergeB, "Merge Sort!")) {
            start_merge();
        }
        else if (GuiButton(mazeB, "Maze Generator!")) {
            mazealgorithm(width);
        }
        else if (GuiButton(selectionB, "Selection Sort!")) {
            start_selection();
        }
        else if (GuiButton(linearB, "Linear Search!")) {
            startLinear(width);
        }
        else if (GuiButton(binaryB, "Binary Search!")) {
            startBinary(width);
        }
        else if (GuiButton(mapgB, "Map Generator!")) {
            start_MapG(width);
        }
        else if (GuiButton(diffuseB, "Reaction Diffusion!")) {
            start_diffuse(width);
        }
        else if (GuiButton(primsB, "Prims Min Spanning Tree!")) {
            start_prims();
        }
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

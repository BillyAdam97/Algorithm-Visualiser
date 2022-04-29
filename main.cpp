#include "raylib.h"
#include "funcs.hpp"
#include "sortingFuncs.hpp"

int main(void)
{
    int width = 800;
    
    InitWindow(width, width, "Algorithm Visualiser");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        //Options
        DrawText("Pick an Algorithm", 175, 0, 50, BLACK);
        DrawText("Press 1 for A Star!", 150, 100, 45, BLACK);
        DrawText("Press 2 for Dijkstras!", 150, 200, 45, BLACK);
        DrawText("Press 3 for Game of Life!", 150, 300, 45, BLACK);
        DrawText("Press 4 for Bubble Sort!", 150, 400, 45, BLACK);
        DrawText("Press 5 for Quick Sort!", 150, 500, 45, BLACK);
        DrawText("Press 6 for Merge Sort!", 150, 600, 45, BLACK);
        
        EndDrawing();
        
        if (IsKeyPressed(KEY_ONE)) {
            start_astar(width);
        }
        else if (IsKeyPressed(KEY_TWO)) {
            start_dijkstra(width);
        }
        else if (IsKeyPressed(KEY_THREE)) {
            start_gol(width);
        }
        else if (IsKeyPressed(KEY_FOUR)) {
            start_bubble();
        }
        else if (IsKeyPressed(KEY_FIVE)) {
            start_quicksort();
        }
        else if (IsKeyPressed(KEY_SIX)) {
            start_merge();
        }

    }
    
    CloseWindow();
    
    return 0;
}

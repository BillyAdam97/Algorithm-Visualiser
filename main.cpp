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
        DrawText("Press 1 for A Star!", 175, 100, 45, BLACK);
        DrawText("Press 2 for Dijkstras!", 175, 200, 45, BLACK);
        DrawText("Press 3 for Game of Life!", 175, 300, 45, BLACK);
        DrawText("Press 4 for Bubble Sort!", 175, 400, 45, BLACK);
        
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

    }
    
    CloseWindow();
    
    return 0;
}

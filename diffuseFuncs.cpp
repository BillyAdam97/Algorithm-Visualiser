#include "diffuseFuncs.hpp"
#include "funcs.hpp"
#include "raygui.h"

std::vector<std::vector<std::unique_ptr<Pixel>>> make_pixels(int width, int height, int rows)
{
    int gap = width/rows;
    std::vector<std::vector<std::unique_ptr<Pixel>>> grid;
    std::vector<std::unique_ptr<Pixel>> line;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<rows; j++) {
            line.emplace_back(std::make_unique<Pixel>(i,j,gap));
        }
        grid.emplace_back(std::move(line));
        line.clear();
    }
    return grid;
}

float constain(float num, float low, float high)
{
    if (num>high) {
        num = high;
    }
    if (num<low) {
        num = low;
    }
    return num;
}

void drawpixels(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid)
{
    float c;
    for (int i=1; i<grid.size()-1; i++) {
        for (int j=1; j<grid[0].size()-1; j++) {
            c = (grid[i][j]->a-grid[i][j]->b)*255;
            c = constain(c, 0.0, 255.0);
            grid[i][j]->color.r = c;
            grid[i][j]->color.g = c;
            grid[i][j]->color.b = c;
            grid[i][j]->color.a = 255;
            grid[i][j]->draw();
        }
    }
}

float laplaceA(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid, int x, int y)
{
    float sum=0;
    
    sum += grid[x][y]->a * -1;
    sum += grid[x-1][y]->a * 0.2;
    sum += grid[x+1][y]->a * 0.2;
    sum += grid[x][y+1]->a * 0.2;
    sum += grid[x][y-1]->a * 0.2;
    sum += grid[x-1][y-1]->a * 0.05;
    sum += grid[x+1][y+1]->a * 0.05;
    sum += grid[x+1][y-1]->a * 0.05;
    sum += grid[x-1][y+1]->a * 0.05;
    
    return sum;
}

float laplaceB(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid, int x, int y)
{
    float sum=0;
    
    sum += grid[x][y]->b * -1;
    sum += grid[x-1][y]->b * 0.2;
    sum += grid[x+1][y]->b * 0.2;
    sum += grid[x][y+1]->b * 0.2;
    sum += grid[x][y-1]->b * 0.2;
    sum += grid[x-1][y-1]->b * 0.05;
    sum += grid[x+1][y+1]->b * 0.05;
    sum += grid[x+1][y-1]->b * 0.05;
    sum += grid[x-1][y+1]->b * 0.05;
    
    return sum;
}

void diffuse(std::vector<std::vector<std::unique_ptr<Pixel>>>& grid, std::vector<std::vector<std::unique_ptr<Pixel>>>& next, float feed, float k)
{
    
    float dA = 1.0;
    float dB = 0.5;
    //0.055 0.062 coral
    //0.0367 0.0649 mitosis
//    float feed = 0.055;
//    float k = 0.062;
    for (int i=1; i<grid.size()-1; i++) {
        for (int j=1; j<grid[0].size()-1; j++) {
            next[i][j]->a = constain(grid[i][j]->a + dA*laplaceA(grid,i,j)-grid[i][j]->a*grid[i][j]->b*grid[i][j]->b + feed*(1-grid[i][j]->a), 0.0, 1.0);
            next[i][j]->b = constain(grid[i][j]->b + dB*laplaceB(grid,i,j)+grid[i][j]->a*grid[i][j]->b*grid[i][j]->b - (k+feed)*grid[i][j]->b, 0.0, 1.0);
        }
    }
//    grid = next;
    grid.swap(next);
}

void start_diffuse(int width, float feed, float kill) {

    int rows = 200;
    
    std::vector<std::vector<std::unique_ptr<Pixel>>> grid = make_pixels(width,width,rows);
    std::vector<std::vector<std::unique_ptr<Pixel>>> next = make_pixels(width, width, rows);
    Vector2 mouse;
    std::pair<int,int>rowcol;
    SetTargetFPS(120);
    bool flag = true;
    while (flag) {
        BeginDrawing();
        ClearBackground(WHITE);
        drawpixels(grid);
        EndDrawing();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            correct_bound(mouse, width, width);
            rowcol = get_clicked(mouse, rows, width);
            grid[rowcol.second][rowcol.first]->b = 1.0;
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        diffuse(grid, next, feed, kill);
    }
}

void diffusionChoice(int& width, int& height)
{
    Rectangle coral{(float)((width/2)-200.0), 100.0, 400, 75};
    Rectangle mitosis{(float)((width/2)-200.0), 200.0, 400, 75};
    Rectangle test{(float)((width/2)-200.0), 300.0, 400, 75};
    Rectangle back{(float)((width/2)-200.0), 400, 400, 75};
    bool click = false;
    bool flag = true;
    while (flag) {
        
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            click = true;
        }
        
        if (GuiButton(coral, "Coral") && click) {
            start_diffuse(width, 0.055, 0.062);
        }
        else if (GuiButton(mitosis, "Mitosis") && click) {
            start_diffuse(width, 0.0367, 0.0649);
        }
        else if (GuiButton(test, "Coral..ish") && click) {
            //0.02, 0.058
            start_diffuse(width, 0.06100, 0.06264);
        }
        else if (GuiButton(back, "Back") && click) {
            flag = false;
        }
        EndDrawing();
    }
    
}

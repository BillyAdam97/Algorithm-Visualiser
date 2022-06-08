#include "searchFuncs.hpp"
#include "raygui.h"

std::vector<std::shared_ptr<Bar>> makeSorted(int columns, int width, int height)
{
    std::vector<std::shared_ptr<Bar>> alist;
    for (int i=0; i<columns; i++) {
        alist.emplace_back(std::make_shared<Bar>(i,i,width/columns,i*8));
        //rand()%(height-50)+1)
    }
    return alist;
}

void drawSorted(std::vector<std::shared_ptr<Bar>>& alist)
{
    ClearBackground(WHITE);
    for (int i=0; i<alist.size(); i++) {
        alist[i]->draw();
    }
}

int getbar(Vector2 mouse, int columns, int width)
{
    int gap = width/columns;
    int x = mouse.x;
    int col = x/gap;
    return col;
}

void linearSearch(std::vector<std::shared_ptr<Bar>>& alist, std::shared_ptr<Bar>& chosen)
{
    for (int i=0; i<alist.size(); i++) {
        if (alist[i]->height==chosen->height) {
            alist[i]->setSorted();
            return;
        }
        else {
            alist[i]->setCurr();
        }
        BeginDrawing();
        ClearBackground(WHITE);
        drawSorted(alist);
        EndDrawing();
    }
}

void startLinear(int width)
{
    bool flag = true;
    std::vector<std::shared_ptr<Bar>> alist = makeSorted(100, width, width);
    Vector2 click{0.0f, 0.0f};
    int col;
    std::shared_ptr<Bar> cur = alist[0];
    while (flag) {
        
        BeginDrawing();
        ClearBackground(WHITE);
        drawSorted(alist);
        EndDrawing();
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            click = GetMousePosition();
            col = getbar(click, 100, width);
            cur->color = BLACK;
            cur  = alist[col];
            cur->color = PURPLE;
            
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            click = GetMousePosition();
            col = getbar(click, 100, width);
            alist[col]->color = BLACK;
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            linearSearch(alist, cur);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void binarySearch(std::vector<std::shared_ptr<Bar>>& alist, std::shared_ptr<Bar>& chosen)
{
    int low = 0;
    int high = alist.size()-1;
    int mid;
    while (low<=high) {
        mid = low+(high-low)/2;
        alist[mid]->setCurr();
        if (alist[mid]->height == chosen->height) {
            chosen->setSorted();
            return;
        }
        
        if (alist[mid]->height<chosen->height) {
            low = mid+1;
        }
        else {
            high = mid-1;
        }
    }
}

void startBinary(int width)
{
    bool flag = true;
    std::vector<std::shared_ptr<Bar>> alist = makeSorted(100, width, width);
    Vector2 click{0.0f, 0.0f};
    int col;
    std::shared_ptr<Bar> cur = alist[0];
    while (flag) {
        
        BeginDrawing();
        ClearBackground(WHITE);
        drawSorted(alist);
        EndDrawing();
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            click = GetMousePosition();
            col = getbar(click, 100, width);
            cur->color = BLACK;
            cur  = alist[col];
            cur->color = PURPLE;
            
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            click = GetMousePosition();
            col = getbar(click, 100, width);
            alist[col]->color = BLACK;
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            binarySearch(alist, cur);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void chooseSearch(int& width, int& height)
{
    SetMousePosition(100, 100);
    Rectangle linearB{275.0, 100.0, 250, 40};
    Rectangle binaryB{275.0, 150.0, 250, 40};
    Rectangle controls{275.0, 200.0, 250, 40};
    Rectangle back{275.0, 250.0, 250, 40};
    
    bool flag = true;
    
    while (flag) {
        if (height!=350) {
            height=350;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (GuiButton(linearB, "Linear Search")) {
            height = 800;
            SetWindowSize(width, height);
            startLinear(width);
        }
        else if (GuiButton(binaryB, "Binary Search")) {
            height = 800;
            SetWindowSize(width, height);
            startBinary(width);
        }
        else if (GuiButton(controls, "Controls")) {
            searchControls(width, height);
        }
        else if (GuiButton(back, "Back")) {
            flag = false;
        }
        EndDrawing();
    }
}

void searchControls(int& width, int& height)
{
    bool flag = true;
    Rectangle back{275.0, 300.0, 250,40};
    while (flag) {
        if (height!=400) {
            height = 400;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Left Click - Highlights the value to look for.", 20, 100, 20, BLACK);
        DrawText("R - Make a new list.", 20, 150, 20, BLACK);
        DrawText("Delete - Exits out of algorithm.", 20, 200, 20, BLACK);
        DrawText("SpaceBar - Starts the algorithm.", 20, 250, 20, BLACK);
        if (GuiButton(back, "Back")) {
            flag = false;
        }
        
        EndDrawing();
    }
}

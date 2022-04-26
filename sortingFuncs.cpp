#include "sortingFuncs.hpp"

std::vector<std::unique_ptr<Bar>> make_list(int columns, int width, int height) {
    std::vector<std::unique_ptr<Bar>> alist;
    srand((unsigned)time(0));
    for (int i=0; i<columns; i++) {
        alist.emplace_back(std::make_unique<Bar>(i,i,width/columns, rand()%(height-50)+1));
    }
    return alist;
}


void drawBars(std::vector<std::unique_ptr<Bar>>& alist) {
    ClearBackground(WHITE);
    for (int i=0; i<alist.size(); i++) {
        alist[i]->draw();
    }
}

void bubblesort(std::vector<std::unique_ptr<Bar>>& alist) {
    int temp;
    int count = (int)alist.size();
    for (int i=0; i<alist.size(); i++) {
        for (int j=0; j<alist.size()-1; j++) {
            if (alist[j]->height>alist[j+1]->height) {
                alist[j]->setCurr();
                temp = alist[j]->x;
                alist[j]->x = alist[j+1]->x;
                alist[j+1]->x = temp;
                swap(alist[j], alist[j+1]);
                BeginDrawing();
                drawBars(alist);
                EndDrawing();
                alist[j+1]->reset();
            }
            
        }
        count--;
        alist[count]->setSorted();
        
    }
}

void start_bubble() {
    bool flag = true;
    std::vector<std::unique_ptr<Bar>> alist = make_list(50, 800, 800);
    while (flag) {
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            alist = make_list(50, 800, 800);
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            bubblesort(alist);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

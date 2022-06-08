#include "sortingFuncs.hpp"
#include "raygui.h"

std::vector<std::shared_ptr<Bar>> make_list(int columns, int width, int height) {
    std::vector<std::shared_ptr<Bar>> alist;
    srand((unsigned)time(0));
    for (int i=0; i<columns; i++) {
        alist.emplace_back(std::make_shared<Bar>(i,i,width/columns, rand()%(height-50)+1));
    }
    return alist;
}


void drawBars(std::vector<std::shared_ptr<Bar>>& alist) {
    ClearBackground(WHITE);
    for (int i=0; i<alist.size(); i++) {
        alist[i]->draw();
    }
}

void chooseSort(int& width, int& height)
{
    SetMousePosition(100, 100);
    Rectangle bubbleB{275.0, 100.0, 250, 40};
    Rectangle quickB{275.0, 150.0, 250, 40};
    Rectangle mergeB{275.0, 200.0, 250, 40};
    Rectangle selectionB{275.0, 250.0, 250,40};
    Rectangle controls{275.0, 300.0, 250, 40};
    Rectangle back{275.0, 350.0, 250, 40};
    
    bool flag = true;
    
    while (flag) {
        if (height!=450) {
            height=450;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (GuiButton(bubbleB, "Bubble Sort")) {
            height = 800;
            SetWindowSize(width, height);
            start_bubble();
        }
        else if (GuiButton(quickB, "Quick Sort")) {
            height = 800;
            SetWindowSize(width, height);
            start_quicksort();
        }
        else if (GuiButton(mergeB, "Merge Sort")) {
            height = 800;
            SetWindowSize(width, height);
            start_merge();
        }
        else if (GuiButton(selectionB, "Selection Sort")) {
            height = 800;
            SetWindowSize(width, height);
            start_selection();
        }
        else if (GuiButton(controls, "Controls")) {
            sortControls(width, height);
        }
        else if (GuiButton(back, "Back")) {
            flag = false;
        }
        EndDrawing();
    }
}

void sortControls(int& width, int& height)
{
    bool flag = true;
    Rectangle back{275.0, 250.0, 250,40};
    while (flag) {
        if (height!=350) {
            height = 350;
            SetWindowSize(width,height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("R - Make a new list of unsorted values.", 20, 100, 20, BLACK);
        DrawText("Delete - Exits out of algorithm.", 20, 150, 20, BLACK);
        DrawText("SpaceBar - Starts the algorithm.", 20, 200, 20, BLACK);
        if (GuiButton(back, "Back")) {
            flag = false;
        }
        
        EndDrawing();
    }
}

void bubblesort(std::vector<std::shared_ptr<Bar>>& alist) {
    int temp;
    for (int i=0; i<alist.size(); i++) {
        for (int j=0; j<alist.size()-1; j++) {
            if (alist[j]->height>alist[j+1]->height) {
                temp = alist[j]->x;
                alist[j]->x = alist[j+1]->x;
                alist[j+1]->x = temp;
                swap(alist[j], alist[j+1]);
                BeginDrawing();
                drawBars(alist);
                EndDrawing();
            }
            
        }
    }
}

void start_bubble() {
    bool flag = true;
    std::vector<std::shared_ptr<Bar>> alist = make_list(50, 800, 800);
    while (flag) {
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            alist = make_list(50, 800, 800);
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            bubblesort(alist);
            for (int i=0; i<alist.size(); i++) {
                alist[i]->setSorted();
                BeginDrawing();
                drawBars(alist);
                EndDrawing();
            }
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void quicksort(std::vector<std::shared_ptr<Bar>>& alist, int low, int high) {
    int k;
    
    if (low<high) {
        k = partition(alist, low, high);
        quicksort(alist, low, k-1);
        quicksort(alist, k+1, high);
    }
}

int partition(std::vector<std::shared_ptr<Bar>>& alist, int low, int high) {
    int k = alist[high]->height;
    int i = low;
    int temp;
    for (int j=low; j<high; j++) {
        if (alist[j]->height<=k) {
            temp = alist[j]->x;
            alist[j]->x = alist[i]->x;
            alist[i]->x = temp;
            swap(alist[j], alist[i]);
            i++;
            BeginDrawing();
            drawBars(alist);
            EndDrawing();
        }
    }
    temp = alist[i]->x;
    alist[i]->x = alist[high]->x;
    alist[high]->x = temp;
    swap(alist[i], alist[high]);
    
    return i;
}

void start_quicksort() {
    bool flag = true;
    std::vector<std::shared_ptr<Bar>> alist = make_list(100, 800, 800);
    while (flag) {
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            alist = make_list(100, 800, 800);
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            quicksort(alist, 0, alist.size()-1);
            for (int i=0; i<alist.size(); i++) {
                alist[i]->setSorted();
                BeginDrawing();
                drawBars(alist);
                EndDrawing();
            }
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        
    }

}

void merge(std::vector<std::shared_ptr<Bar>>& alist, int begin, int mid, int end) {
    int subonesize = mid-begin+1;
    int subtwosize = end-mid;
    std::vector<std::shared_ptr<Bar>> subone;
    std::vector<std::shared_ptr<Bar>> subtwo;
    for (int i=0; i<subonesize; i++) {
        subone.emplace_back(std::make_shared<Bar>(alist[begin+i]->row,alist[begin+i]->col,alist[begin+i]->width,alist[begin+i]->height));
        //subone[i]=alist[begin+i];
    }
    for (int j=0; j<subtwosize; j++) {
        subtwo.emplace_back(std::make_shared<Bar>(alist[mid+1+j]->row,alist[mid+1+j]->col,alist[mid+1+j]->width,alist[mid+1+j]->height));
    }
    int suboneIndex = 0;
    int subtwoIndex = 0;
    int mergedIndex = begin;
    
    while (suboneIndex<subonesize && subtwoIndex<subtwosize) {
        if (subone[suboneIndex]->height<=subtwo[subtwoIndex]->height) {

            swap(alist[mergedIndex], subone[suboneIndex]);
            alist[mergedIndex]->x = mergedIndex*alist[mergedIndex]->width;

            suboneIndex++;
        }
        else {
            
            swap(alist[mergedIndex], subtwo[subtwoIndex]);
            alist[mergedIndex]->x = mergedIndex*alist[mergedIndex]->width;

            subtwoIndex++;
            
        }
        mergedIndex++;
        BeginDrawing();
        drawBars(alist);
        EndDrawing();

    }
    
    while (suboneIndex<subonesize) {

        swap(alist[mergedIndex], subone[suboneIndex]);
        alist[mergedIndex]->x = mergedIndex*alist[mergedIndex]->width;

        suboneIndex++;
        mergedIndex++;
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
    }
    
    while (subtwoIndex<subtwosize) {

        swap(alist[mergedIndex], subtwo[subtwoIndex]);
        alist[mergedIndex]->x = mergedIndex*alist[mergedIndex]->width;

        subtwoIndex++;
        mergedIndex++;
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
    }
    
    
}

void mergeSort(std::vector<std::shared_ptr<Bar>>& alist, int begin, int end) {
    
    if (begin >= end) {
        return;
    }
    
    int mid = begin + (end-begin)/2;
    mergeSort(alist, begin, mid);
    mergeSort(alist, mid+1, end);
    merge(alist, begin, mid, end);
    
}

void start_merge() {
    bool flag = true;
    std::vector<std::shared_ptr<Bar>> alist = make_list(100, 800, 800);
    while (flag) {
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            alist = make_list(100, 800, 800);
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            mergeSort(alist, 0, alist.size()-1);
            for (int i=0; i<alist.size(); i++) {
                alist[i]->setSorted();
                BeginDrawing();
                drawBars(alist);
                EndDrawing();
            }
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void selectionSort(std::vector<std::shared_ptr<Bar>>& alist)
{
    int n = 0;
    int temp;
    
    for (int i=0; i<alist.size(); i++) {
        n = i;
        for (int j=i+1; j<alist.size(); j++) {
            if (alist[j]->height<alist[n]->height) {
                n=j;
            }
        }
        temp = alist[n]->x;
        alist[n]->x = alist[i]->x;
        alist[i]->x = temp;
        swap(alist[n],alist[i]);
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
    }
}

void start_selection()
{
    std::vector<std::shared_ptr<Bar>> alist = make_list(100, 800, 800);
    bool flag = true;
    
    while (flag) {
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            alist = make_list(100, 800, 800);
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            selectionSort(alist);
            for (int i=0; i<alist.size(); i++) {
                alist[i]->setSorted();
                BeginDrawing();
                drawBars(alist);
                EndDrawing();
            }
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        
    }
}

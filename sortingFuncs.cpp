#include "sortingFuncs.hpp"

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
    std::vector<std::shared_ptr<Bar>> alist = make_list(50, 800, 800);
    while (flag) {
        BeginDrawing();
        drawBars(alist);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            alist = make_list(50, 800, 800);
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
            alist = make_list(50, 800, 800);
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

#include "mstfuncs.hpp"
#include "raygui.h"
#include <iostream>

void drawGraph(std::vector<std::shared_ptr<Node>>& nodes)
{
    Vector2 a;
    Vector2 b;
    for (int i=0; i<nodes.size(); i++) {
        a.x = nodes[i]->row;
        a.y = nodes[i]->col;
        for (int j=0; j<nodes[i]->edges.size(); j++) {
            b.x = nodes[i]->edges[j].first->row;
            b.y = nodes[i]->edges[j].first->col;
            DrawLineEx(a, b, 3.0, nodes[i]->lineColor[nodes[i]->edges[j].first->ind]);
        }
    }
    for (int i=0; i<nodes.size(); i++) {
        nodes[i]->draw();
    }
}

int minKey(std::vector<float>& key, std::vector<bool>& mstSet)
{
    
    float min = INFINITY;
    int min_ind = 0;
    
    for (int i=0; i<key.size(); i++) {
        if (mstSet[i]==false && key[i]<min) {
            min = key[i];
            min_ind = i;
        }
    }
    return min_ind;
    
}

void mst(std::vector<std::shared_ptr<Node>>& nodes, std::vector<float>& key, std::vector<bool>& mstSet) {
    SetTargetFPS(10);
    std::vector<int> parent(nodes.size(),-1);
    key[0] = 0;
    int u;
    nodes[0]->setVisited();
    for (int count=0; count<nodes.size()-1; count++) {
        
        u = minKey(key, mstSet);
        
        mstSet[u] = true;
//        nodes[u]->setVisited();
        
        for (int i=0; i<nodes[u]->edges.size(); i++) {
            if (mstSet[nodes[u]->edges[i].first->ind] == false && nodes[u]->edges[i].second<key[nodes[u]->edges[i].first->ind]) {
                parent[nodes[u]->edges[i].first->ind] = u;
                key[nodes[u]->edges[i].first->ind] = nodes[u]->edges[i].second;
            }
        }
    }
    for (int i=0; i<parent.size(); i++) {
        if (i==0) {
            nodes[i]->setVisited();
        }
        else {
            nodes[i]->setVisited();
            nodes[i]->lineColor[parent[i]] = GREEN;
            nodes[parent[i]]->lineColor[i] = GREEN;
        }
        BeginDrawing();
        ClearBackground(WHITE);
        drawGraph(nodes);
        EndDrawing();
    }
    SetTargetFPS(60);
}

void bfs(std::vector<std::shared_ptr<Node>>& nodes) {
    SetTargetFPS(5);
    std::shared_ptr<Node> temp;
    std::queue<std::shared_ptr<Node>> Q;
    std::vector<int> inQ;
    std::vector<int> parent(nodes.size(),-1);
    Q.push(nodes[0]);
    inQ.emplace_back(0);
    
    while (!Q.empty()) {
        
        temp = Q.front();
        Q.pop();
        temp->setVisited();
        
        for (int i=0; i<temp->edges.size(); i++) {
            if (std::find(inQ.begin(), inQ.end(), temp->edges[i].first->ind)==inQ.end() && !temp->edges[i].first->visited) {
                Q.push(temp->edges[i].first);
                parent[temp->edges[i].first->ind] = temp->ind;
                temp->edges[i].first->setVisited();
            }
        }
        BeginDrawing();
        ClearBackground(WHITE);
        drawGraph(nodes);
        EndDrawing();
    }
    while (!IsKeyPressed(KEY_DELETE)) {
        BeginDrawing();
        ClearBackground(WHITE);
        drawGraph(nodes);
        int k = 100;
        for (int i=1; i<parent.size(); i++) {
            std::string a = std::to_string(parent[i]);
            a+= " ---> ";
            a+= std::to_string(i);
            DrawText(a.c_str(), 500, k, 20, BLACK);
            k+=100;
        }
        EndDrawing();
    }
    
    SetTargetFPS(60);
}

void dfs(std::vector<std::shared_ptr<Node>>& nodes)
{
    SetTargetFPS(5);
    std::shared_ptr<Node> temp;
    std::stack<std::shared_ptr<Node>> stk;
    std::vector<int> instk;
    std::vector<int> parent(nodes.size(),-1);
    stk.push(nodes[0]);
    instk.emplace_back(0);
    
    while (!stk.empty())
    {
        temp = stk.top();
        stk.pop();
        temp->setVisited();
        
        for (int i=temp->edges.size()-1; i>=0; i--) {
            if (std::find(instk.begin(), instk.end(), temp->edges[i].first->ind)==instk.end() && !temp->edges[i].first->visited) {
                stk.push(temp->edges[i].first);
                instk.emplace_back(temp->edges[i].first->ind);
                parent[temp->edges[i].first->ind] = temp->ind;
//                temp->edges[i].first->setVisited();
            }
        }
        BeginDrawing();
        ClearBackground(WHITE);
        drawGraph(nodes);
        EndDrawing();
    }
    while (!IsKeyPressed(KEY_DELETE)) {
        BeginDrawing();
        ClearBackground(WHITE);
        drawGraph(nodes);
        int k = 100;
        for (int i=1; i<parent.size(); i++) {
            std::string a = std::to_string(parent[i]);
            a+= " ---> ";
            a+= std::to_string(i);
            DrawText(a.c_str(), 500, k, 20, BLACK);
            k+=100;
        }
        EndDrawing();
    }
    SetTargetFPS(60);
}

void start_prims()
{
    Node anode(20,20,20, BLUE);
    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Node> temp;
    std::shared_ptr<Node> c1;
    std::shared_ptr<Node> c2;
    std::pair<std::shared_ptr<Node>,float> temppair;
    std::vector<bool> mstSet;
    std::vector<float> key;
    bool loop = true;
    bool flag = false;
    Vector2 mouse;
    
    while (loop) {
        BeginDrawing();
        ClearBackground(WHITE);
        anode.draw();
        drawGraph(nodes);
        EndDrawing();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            if (sqrt((mouse.x-anode.row)*(mouse.x-anode.row) + (mouse.y-anode.col)*(mouse.y-anode.col)) < anode.width) {
                flag = true;
                temp = std::make_shared<Node>(anode.row,anode.col,anode.width,anode.color);
            }
        }
        else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT) && flag) {
            mouse = GetMousePosition();
            temp->x = mouse.x;
            temp->y = mouse.y;
            flag = false;
            temp->character = std::to_string(nodes.size());
            temp->ind = nodes.size();
            nodes.emplace_back(std::move(temp));
            key.emplace_back(INFINITY);
            mstSet.emplace_back(false);
        }
        
        if (flag) {
            mouse = GetMousePosition();
            temp->row = mouse.x;
            temp->col = mouse.y;
            temp->draw();
            
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mouse = GetMousePosition();
            for (int i=0; i<nodes.size(); i++) {
                if (sqrt((mouse.x-nodes[i]->row)*(mouse.x-nodes[i]->row) + (mouse.y-nodes[i]->col)*(mouse.y-nodes[i]->col)) < nodes[i]->width) {
                    if (c1) {
                        c2 = nodes[i];
                        if (*c1==*c2) {
                            c2 = nullptr;
                        }
                        else {
                            c2->setClicked();
                        }
                    }
                    else {
                        c1 = nodes[i];
                        c1->setClicked();
                    }
                }
            }
        }
        //sqrt( std::pow(c2->x-c1->x,2) + std::pow(c2->y-c1->y,2))
        //dis = sqrt( pow((graph.graph[i][j].first->x-graph.adjlist[i]->x),2) + pow((graph.graph[i][j].first->y-graph.adjlist[i]->y),2) );
        if (c1 && c2) {
            temppair = std::make_pair(c2,sqrt( abs(std::pow(c2->row-c1->row,2) + std::pow(c2->col-c1->col,2))) );
            c1->edges.emplace_back(temppair);
            temppair = std::make_pair(c1, sqrt( abs(std::pow(c2->row-c1->row,2) + std::pow(c2->col-c1->col,2))) );
            c2->edges.emplace_back(temppair);
            c1->lineColor[c2->ind] = BLACK;
            c2->lineColor[c1->ind] = BLACK;
            c1->reset();
            c2->reset();
            c1 = nullptr;
            c2 = nullptr;
        }
        
        if (IsKeyPressed(KEY_R)) {
            nodes.clear();
            mstSet.clear();
            key.clear();
            temp = nullptr;
            c1 = nullptr;
            c2 = nullptr;
        }
        
        if (IsKeyPressed(KEY_SPACE)) {
            mst(nodes, key, mstSet);
        }
        
        if (IsKeyPressed(KEY_DELETE)) {
            loop = false;
        }
    }
}

void start_bfs() {
    Node anode(20,20,20, BLUE);
    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Node> temp;
    std::shared_ptr<Node> c1;
    std::shared_ptr<Node> c2;
    std::pair<std::shared_ptr<Node>,float> temppair;
    bool loop = true;
    bool flag = false;
    Vector2 mouse;
    
    while (loop) {
        BeginDrawing();
        ClearBackground(WHITE);
        anode.draw();
        drawGraph(nodes);
        EndDrawing();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            if (sqrt((mouse.x-anode.row)*(mouse.x-anode.row) + (mouse.y-anode.col)*(mouse.y-anode.col)) < anode.width) {
                flag = true;
                temp = std::make_shared<Node>(anode.row,anode.col,anode.width,anode.color);
            }
        }
        else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT) && flag) {
            mouse = GetMousePosition();
            temp->x = mouse.x;
            temp->y = mouse.y;
            flag = false;
            temp->character = std::to_string(nodes.size());
            temp->ind = nodes.size();
            nodes.emplace_back(std::move(temp));
        }
        
        if (flag) {
            mouse = GetMousePosition();
            temp->row = mouse.x;
            temp->col = mouse.y;
            temp->draw();
            
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mouse = GetMousePosition();
            for (int i=0; i<nodes.size(); i++) {
                if (sqrt((mouse.x-nodes[i]->row)*(mouse.x-nodes[i]->row) + (mouse.y-nodes[i]->col)*(mouse.y-nodes[i]->col)) < nodes[i]->width) {
                    if (c1) {
                        c2 = nodes[i];
                        if (*c1==*c2) {
                            c2 = nullptr;
                        }
                        else {
                            c2->setClicked();
                        }
                    }
                    else {
                        c1 = nodes[i];
                        c1->setClicked();
                    }
                }
            }
        }
        //sqrt( std::pow(c2->x-c1->x,2) + std::pow(c2->y-c1->y,2))
        //dis = sqrt( pow((graph.graph[i][j].first->x-graph.adjlist[i]->x),2) + pow((graph.graph[i][j].first->y-graph.adjlist[i]->y),2) );
        if (c1 && c2) {
            temppair = std::make_pair(c2,0);
            c1->edges.emplace_back(temppair);
            temppair = std::make_pair(c1,0);
            c2->edges.emplace_back(temppair);
            c1->lineColor[c2->ind] = BLACK;
            c2->lineColor[c1->ind] = BLACK;
            c1->reset();
            c2->reset();
            c1 = nullptr;
            c2 = nullptr;
        }
        
        if (IsKeyPressed(KEY_R)) {
            nodes.clear();
            temp = nullptr;
            c1 = nullptr;
            c2 = nullptr;
        }
        
        if (IsKeyPressed(KEY_SPACE)) {
            bfs(nodes);
        }
        
        if (IsKeyPressed(KEY_DELETE)) {
            loop = false;
        }
    }
}

void start_dfs() {
    Node anode(20,20,20, BLUE);
    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Node> temp;
    std::shared_ptr<Node> c1;
    std::shared_ptr<Node> c2;
    std::pair<std::shared_ptr<Node>,float> temppair;
    bool loop = true;
    bool flag = false;
    Vector2 mouse;
    
    while (loop) {
        BeginDrawing();
        ClearBackground(WHITE);
        anode.draw();
        drawGraph(nodes);
        EndDrawing();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            if (sqrt((mouse.x-anode.row)*(mouse.x-anode.row) + (mouse.y-anode.col)*(mouse.y-anode.col)) < anode.width) {
                flag = true;
                temp = std::make_shared<Node>(anode.row,anode.col,anode.width,anode.color);
            }
        }
        else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT) && flag) {
            mouse = GetMousePosition();
            temp->x = mouse.x;
            temp->y = mouse.y;
            flag = false;
            temp->character = std::to_string(nodes.size());
            temp->ind = nodes.size();
            nodes.emplace_back(std::move(temp));
        }
        
        if (flag) {
            mouse = GetMousePosition();
            temp->row = mouse.x;
            temp->col = mouse.y;
            temp->draw();
            
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            mouse = GetMousePosition();
            for (int i=0; i<nodes.size(); i++) {
                if (sqrt((mouse.x-nodes[i]->row)*(mouse.x-nodes[i]->row) + (mouse.y-nodes[i]->col)*(mouse.y-nodes[i]->col)) < nodes[i]->width) {
                    if (c1) {
                        c2 = nodes[i];
                        if (*c1==*c2) {
                            c2 = nullptr;
                        }
                        else {
                            c2->setClicked();
                        }
                    }
                    else {
                        c1 = nodes[i];
                        c1->setClicked();
                    }
                }
            }
        }
        //sqrt( std::pow(c2->x-c1->x,2) + std::pow(c2->y-c1->y,2))
        //dis = sqrt( pow((graph.graph[i][j].first->x-graph.adjlist[i]->x),2) + pow((graph.graph[i][j].first->y-graph.adjlist[i]->y),2) );
        if (c1 && c2) {
            temppair = std::make_pair(c2,0);
            c1->edges.emplace_back(temppair);
            temppair = std::make_pair(c1,0);
            c2->edges.emplace_back(temppair);
            c1->lineColor[c2->ind] = BLACK;
            c2->lineColor[c1->ind] = BLACK;
            c1->reset();
            c2->reset();
            c1 = nullptr;
            c2 = nullptr;
        }
        
        if (IsKeyPressed(KEY_R)) {
            nodes.clear();
            temp = nullptr;
            c1 = nullptr;
            c2 = nullptr;
        }
        
        if (IsKeyPressed(KEY_SPACE)) {
            dfs(nodes);
        }
        
        if (IsKeyPressed(KEY_DELETE)) {
            loop = false;
        }
    }
}

void chooseMST(int& width, int& height)
{
    
    Rectangle primsB{(float)((width/2)-200.0), 100.0, 400, 75};
    Rectangle bfsB{(float)((width/2)-200.0), 200.0, 400, 75};
    Rectangle dfsB{(float)((width/2)-200.0), 300.0, 400, 75};
    Rectangle controls{(float)((width/2)-200.0), 400.0, 400, 75};
    Rectangle back{(float)((width/2)-200.0), 500.0, 400, 75};
    
    bool click = false;
    bool flag = true;
    
    while (flag) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            click = true;
        }
        
        if (GuiButton(primsB, "Prims MST") && click) {
            start_prims();
            click = false;
        }
        else if (GuiButton(bfsB, "Breadth First Search")) {
            start_bfs();
            click = false;
        }
        else if (GuiButton(dfsB, "Depth First Search")) {
            start_dfs();
            click = false;
        }
        else if (GuiButton(controls, "Controls") && click) {
            mstControls(width, height);
            click = false;
        }
        else if (GuiButton(back, "Back") && click) {
            flag = false;
        }
        EndDrawing();
    }
}

void mstControls(int& width, int& height)
{
    bool flag = true;
    Rectangle back{275.0, 350.0, 250,40};
    while (flag) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Left Click - Create new nodes by clicking, then drag and dropping in place.", 20, 100, 20, BLACK);
        DrawText("Left Click is also used to connect two node together, click one then the other to create an egde.", 20, 150, 20, BLACK);
        DrawText("R - Clear screen.", 20, 200, 20, BLACK);
        DrawText("Delete - Exits out of algorithm.", 20, 250, 20, BLACK);
        DrawText("SpaceBar - Starts the algorithm.", 20, 300, 20, BLACK);
        if (GuiButton(back, "Back")) {
            flag = false;
        }
        
        EndDrawing();
    }
}

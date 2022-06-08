#include "funcs.hpp"
#include "raygui.h"

//Utility

void correct_bound(Vector2& mouse, int width, int height) {
    if (mouse.y<0) {
        mouse.y=0;
    }
    if (mouse.x<0) {
        mouse.x=0;
    }
    if (mouse.y>=width) {
        mouse.y=width-1;
    }
    if (mouse.x>=width) {
        mouse.x=width-1;
    }
}

double h(std::shared_ptr<Square> a, std::shared_ptr<Square> b)
// Works out the heuristic of two nodes
{
    return abs(a->x-b->x) + abs(a->y-b->y);
}

std::vector<std::vector<std::shared_ptr<Square>>> make_Squares(int rows, int width)
// Creates a n by n grid of pointers to Square instances
{
    std::vector<std::vector<std::shared_ptr<Square>>> grid;
    std::vector<std::shared_ptr<Square>> line;
    int gap = width/rows; //working out the width of each square
    int count = 0; //indexing each square
    for (int i=0; i<rows; i++) {
        for (int j=0; j<rows; j++) {
            line.emplace_back(std::make_shared<Square>(i,j,gap,rows,count));
            count++;
        }
        grid.emplace_back(std::move(line));
    }
    return grid;
}

std::vector<std::vector<std::shared_ptr<Entity>>> make_Entities(int rows, int width)
// Creates a n by n grid of pointers to Square instances
{
    std::vector<std::vector<std::shared_ptr<Entity>>> grid;
    std::vector<std::shared_ptr<Entity>> line;
    int gap = width/rows; //working out the width of each square
    int count = 0; //indexing each square
    for (int i=0; i<rows; i++) {
        for (int j=0; j<rows; j++) {
            line.emplace_back(std::make_shared<Entity>(i,j,gap,gap));
            count++;
        }
        grid.emplace_back(std::move(line));
    }
    return grid;
}

std::vector<std::vector<std::unique_ptr<Tile>>> make_map(int rows, int width, int density, int seed)
{
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;
    std::vector<std::unique_ptr<Tile>> line;
    int gap = width/rows;
    int count = 0;
    int num = 0;
    std::srand(seed);
    for (int i = 0; i<rows; i++) {
        for (int j=0; j<rows; j++) {
            line.emplace_back(std::make_unique<Tile>(i,j,gap));
            num = 1+(rand()%100);
            if (num>=density) {
                line[j]->setLand();
            }
            else {
                line[j]->setWater();
            }
            count++;
        }
        grid.emplace_back(std::move(line));
    }
    return grid;
}

void draw_grid(int rows, int width)
//Draws the grid lines
{
//    Vector2 start;
//    Vector2 end;
    int gap = width/rows;
    for (int i=0; i<rows; i++) {
//        start.x = 0;
//        start.y = i*gap;
//        end.x = width;
//        end.y = i*gap;
        DrawLine(0, (i*gap), width, (i*gap), GRAY);
//        DrawLineEx(start, end, 3.0, BLACK);
//        start.x = i*gap;
//        start.y = 0;
//        end.x = i*gap;
//        end.y = width;
//        DrawLineEx(start, end, 3.0, BLACK);
        DrawLine((i*gap), 0, (i*gap), width, GRAY);
    }
}

void draw(std::vector<std::vector<std::unique_ptr<Tile>>>& grid, int rows, int width)
//Iterates through the grid and calls draw method for each square.
{
    ClearBackground(WHITE);
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            grid[i][j]->draw();
        }
    }
}

void draw(std::vector<std::vector<std::shared_ptr<Square>>>& grid, int rows, int width)
//Iterates through the grid and calls draw method for each square. Then draws the grid.
{
    ClearBackground(WHITE);
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            grid[i][j]->draw();
        }
    }
    draw_grid(rows, width);
    
}

void draw(std::vector<std::vector<std::shared_ptr<Entity>>>& grid, int rows, int width)
//Iterates through the grid and calls draw method for each square. Then draws the grid.
{
    ClearBackground(WHITE);
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            grid[i][j]->draw();
        }
    }
    draw_grid(rows, width);
    
}

std::pair<int,int> get_clicked(Vector2 mousepos, int rows, int width) {
//     Works out which square is clicked.
    int gap = width/rows;
    int y = mousepos.y;
    int x = mousepos.x;
    int row = y/gap;
    int col = x/gap;
    return std::pair<int,int>(row,col);
}

void constructPath(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::unordered_map<int, std::shared_ptr<Square>>& came_from, std::shared_ptr<Square> curr) {
    //iterates through map and draws the shortest path from end -> start.
    while (came_from.count(curr->index)) {
        curr = came_from[curr->index];
        curr->setPath();
        BeginDrawing();
        draw(grid, grid.size(), 800 );
        EndDrawing();
    }
}

void randomWalls(std::vector<std::vector<std::shared_ptr<Square>>>& grid)
{
    int k;
    int p;
    std::srand(time(0));
    for (int i=0; i<100; i++) {
        k = rand()%grid.size();
        p = rand()%grid.size();
        if (grid[k][p]->isStart()==false && grid[k][p]->isEnd()==false) {
            grid[k][p]->setBarrier();
        }
    }
}

//A Star

bool algorithm(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::shared_ptr<Square> start, std::shared_ptr<Square> end) {
    //A star implementation, re factoring needed.
    int count = 0;
    std::tuple<int, int, int, int> temp;
    // Stores the information for the node.
    std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, std::greater<std::tuple<int, int, int, int>>> Q;
    std::unordered_map<int, float> g_score;
    std::unordered_map<int, float> f_score;
    std::unordered_map<int, std::shared_ptr<Square>> came_from;
    std::vector<int> inQ;
    
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            //Set all nodes distance to infinity
            g_score[grid[i][j]->index] = INFINITY;
            f_score[grid[i][j]->index] = INFINITY;
        }
    }
    //Put start node in priority Queue
    Q.push({0, count, start->row, start->col});
    
    //Store index in vector, in order to check if its in the Queue or now.
    inQ.push_back(start->index);
    
    //Set start node distance to 0 and store Heuristic
    g_score[start->index] = 0;
    f_score[start->index] = h(start, end);
    
    std::shared_ptr<Square> curr;
    
    //Execute algorithm until the Queue is empty
    while (!Q.empty()) {
        
        //Pop top off priority queue and store pointer in curr.
        temp = Q.top();
        curr = grid[std::get<2>(temp)][std::get<3>(temp)];
        Q.pop();
        
        //Remove index number from vector to show its not in queue.
        inQ.erase(std::remove(inQ.begin(), inQ.end(), curr->index), inQ.end());
        
        if (*curr == *end) {
            //Draw out the path if the end has been found
            constructPath(grid, came_from, curr);
            end->setEnd();
            start->setStart();
            return true;
        }
        //Iterate through all neighbours of current node.
        for (int i=0; i<curr->neigbours.size(); i++) {
            //set temp score at gscore of current + 1 as +1 in each direction
            int temp_g_score = g_score[curr->index]+1;
            
            if (temp_g_score < g_score[curr->neigbours[i]->index]) {
                //If temp less than neighbours current score then update them
                g_score[curr->neigbours[i]->index] = temp_g_score;
                f_score[curr->neigbours[i]->index] = temp_g_score + h(curr->neigbours[i], end);
                
                if (std::find(inQ.begin(), inQ.end(),curr->neigbours[i]->index) == inQ.end()) {
                    //If the neighbour is not in the queue and not closed then add current to the came from list for the neighbour
                    //push neighbour to queue and set the neighbour to open (Green).
                    if (!curr->neigbours[i]->isClosed()) {
                        came_from[curr->neigbours[i]->index] = curr;
                        count+=1;
                        Q.push({f_score[curr->neigbours[i]->index], count, curr->neigbours[i]->row, curr->neigbours[i]->col});
                        inQ.push_back(curr->neigbours[i]->index);
                        curr->neigbours[i]->setOpen();
                    }
                    
                }
            }
            
        }
        //Once the loop has finished the grid is drawn
        BeginDrawing();
        draw(grid, grid.size(), 800);
        EndDrawing();
        
        if (*curr!=*start) {
            //sets the current node to closed (Red) if its not the start node just to show its been visited.
            curr->setClosed();
        }
    }
    return false;
}

void start_astar(int width) {
    //set up of A star algorithm (setting start and end positions and barriers)
    int rows = 40;
    bool out = false;
    bool in = true;
    std::vector<std::vector<std::shared_ptr<Square>>> grid = make_Squares(rows, width);
    Vector2 mousepos = { 0.0f, 0.0f };
    int row;
    int col;
    bool flag = true;
    bool start = false;
    bool end = false;
    bool started = false;
    std::pair<int,int> startxy;
    std::pair<int,int> endxy;
    std::pair<int,int> rowcol;
    std::shared_ptr<Square> startnode = nullptr;
    std::shared_ptr<Square> endnode = nullptr;
    while (flag) {
        BeginDrawing();
        draw(grid,  rows, width);
        EndDrawing();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows, width);
            row = rowcol.first;
            col = rowcol.second;
            if (!start and !grid[col][row]->isEnd()) {
                startxy.first = row;
                startxy.second = col;
                start=true;
                grid[col][row]->setStart();
                startnode = grid[col][row];
            }
            else if (!end and !grid[col][row]->isStart()) {
                endxy.first = row;
                endxy.second = col;
                end=true;
                grid[col][row]->setEnd();
                endnode = grid[col][row];
            }
            else if (!grid[col][row]->isEnd() && !grid[col][row]->isStart()) {
                grid[col][row]->setBarrier();
            }
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows, width);
            row = rowcol.first;
            col = rowcol.second;
            if (grid[col][row]->isStart()) {
                start = false;
                grid[col][row]->reset();
                startnode = nullptr;
            }
            else if (grid[col][row]->isEnd()) {
                end = false;
                grid[col][row]->reset();
                endnode = nullptr;
            }
            else {
                grid[col][row]->reset();
            }
        }
        if (IsKeyPressed(KEY_SPACE) and start and end) {
            for (int i=0; i<grid.size(); i++) {
                for (int j=0; j<grid[0].size(); j++) {
                    grid[i][j]->updateNeighbours(grid);
                }
            }
            algorithm(grid, startnode, endnode);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        else if (IsKeyPressed(KEY_R)) {
            grid = make_Squares(rows, width);
            startnode = nullptr;
            start = false;
            endnode = nullptr;
            end = false;
        }
        else if (IsKeyPressed(KEY_W)) {
            randomWalls(grid);
        }
        else if (IsKeyPressed(KEY_EQUAL)) {
            if (!out) {
                rows += 40;
                grid = make_Squares(rows, width);
                startnode = nullptr;
                start = false;
                endnode = nullptr;
                end = false;
                out = true;
                in = false;
            }
        }
        else if (IsKeyPressed(KEY_MINUS)) {
            if (!in) {
                rows -= 40;
                grid = make_Squares(rows, width);
                startnode = nullptr;
                start = false;
                endnode = nullptr;
                end = false;
                in = true;
                out = false;
            }
            
        }
    }
            
}


// Dijkstras

bool dijkstras(std::vector<std::vector<std::shared_ptr<Square>>>& grid, std::shared_ptr<Square> start, std::shared_ptr<Square> end) {
    //Dijkstras implementation, re factoring needed.
    std::unordered_map<int, float> distance;
    std::unordered_map<int, std::shared_ptr<Square>> came_from;
    std::priority_queue<std::tuple<int,int,int>, std::vector<std::tuple<int,int,int>>, std::greater<std::tuple<int,int,int>>> pq;
    std::tuple<int, int, int> temp;
    std::vector<int> inQ;
    int dist;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            distance[grid[i][j]->index] = INFINITY;
        }
    }
    distance[start->index] = 0;
    pq.push({0,start->row, start->col});
    inQ.push_back(start->index);
    std::shared_ptr<Square> curr;
    while (!pq.empty()) {
        temp = pq.top();
        curr = grid[std::get<1>(temp)][std::get<2>(temp)];
        pq.pop();
        inQ.erase(std::remove(inQ.begin(), inQ.end(), curr->index), inQ.end());
        if (*curr==*end) {
            constructPath(grid, came_from, curr);
            end->setEnd();
            start->setStart();
            return true;
        }
        
        for (int i=0; i<curr->neigbours.size(); i++) {
            dist = distance[curr->index] + 1;
            if (dist< distance[curr->neigbours[i]->index]) {
                came_from[curr->neigbours[i]->index] = curr;
                distance[curr->neigbours[i]->index] = dist;
                if (std::find(inQ.begin(), inQ.end(),curr->neigbours[i]->index) == inQ.end()) {
                    pq.push({dist, curr->neigbours[i]->row, curr->neigbours[i]->col});
                    curr->neigbours[i]->setOpen();
                }
                
            }
        }
        BeginDrawing();
        draw(grid, grid.size(), 800);
        EndDrawing();
        if (*curr!=*start) {
            curr->setClosed();
        }
    }
    return true;
}

void start_dijkstra(int width) {
    //Set up of Dijkstras (setting start and end positions and barriers)
    bool out = false;
    bool in = true;
    bool flag = true;
    int rows = 40;
    std::vector<std::vector<std::shared_ptr<Square>>> grid = make_Squares(rows, width);
    Vector2 mousepos = { 0.0f, 0.0f };
    int row;
    int col;
    bool start = false;
    bool end = false;
    std::pair<int,int> rowcol;
    std::shared_ptr<Square> startnode = nullptr;
    std::shared_ptr<Square> endnode = nullptr;
    while (flag) {
        BeginDrawing();
        draw(grid, rows, width);
        EndDrawing();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows, width);
            row = rowcol.first;
            col = rowcol.second;
            if (!start && !grid[col][row]->isEnd()) {
                grid[col][row]->setStart();
                start=true;
                startnode = grid[col][row];
            }
            else if (!end && !grid[col][row]->isStart()) {
                grid[col][row]->setEnd();
                end = true;
                endnode = grid[col][row];
            }
            else if (!grid[col][row]->isEnd() && !grid[col][row]->isStart()) {
                grid[col][row]->setBarrier();
            }
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows,width);
            row = rowcol.first;
            col = rowcol.second;
            if (grid[col][row]->isStart()) {
                start = false;
                grid[col][row]->reset();
                startnode = nullptr;
            }
            else if (grid[col][row]->isEnd()) {
                end = false;
                grid[col][row]->reset();
                endnode = nullptr;
            }
            else {
                grid[col][row]->reset();
            }
        }
        if (IsKeyPressed(KEY_SPACE) and start and end) {
            for (int i=0; i<grid.size(); i++) {
                for (int j=0; j<grid[0].size(); j++) {
                    grid[i][j]->updateNeighbours(grid);
                }
            }
            dijkstras(grid, startnode, endnode);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        else if (IsKeyPressed(KEY_R)) {
            grid = make_Squares(rows, width);
            startnode = nullptr;
            start = false;
            endnode = nullptr;
            end = false;
        }
        else if (IsKeyPressed(KEY_W)) {
            randomWalls(grid);
        }
        else if (IsKeyPressed(KEY_EQUAL)) {
            if (!out) {
                rows += 40;
                grid = make_Squares(rows, width);
                startnode = nullptr;
                start = false;
                endnode = nullptr;
                end = false;
                out = true;
                in = false;
            }
        }
        else if (IsKeyPressed(KEY_MINUS)) {
            if (!in) {
                rows -= 40;
                grid = make_Squares(rows, width);
                startnode = nullptr;
                start = false;
                endnode = nullptr;
                end = false;
                in = true;
                out = false;
            }
        }
    }
}

void psaControls(int& width, int& height)
{
    bool flag = true;
    Rectangle back{275.0, 500.0, 250,40};
    while (flag) {
        if (height != 600) {
            height = 600;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Left Click - Places blocks. The first two blocks will be the start (Orange)", 20, 100, 20, BLACK);
        DrawText("and the end (Brown). Once start and end blocks are placed, walls (Black)", 20, 125, 20, BLACK);
        DrawText("are placed instead.", 20, 150, 20, BLACK);
        DrawText("Right Click - Deletes blocks.", 20, 200, 20, BLACK);
        DrawText("R - Makes a brand new grid.", 20, 250, 20, BLACK);
        DrawText("W - Places random wall blocks on the grid.", 20, 300, 20, BLACK);
        DrawText("= - Increase size of grid.", 20, 350, 20, BLACK);
        DrawText("Minus (-) - Decrease size of grid.", 20, 400, 20, BLACK);
        DrawText("SpaceBar - Starts the algorithm.", 20, 450, 20, BLACK);
        
        if (GuiButton(back, "Back")) {
            flag = false;
        }
        
        EndDrawing();
    }
}

void choosePSA(int& width, int& height)
{
    
    SetMousePosition(100, 100);
    Rectangle astarB{275.0, 50.0, 250,40};
    Rectangle dijkB{275.0, 100.0, 250,40};
    Rectangle controls{275.0, 150.0, 250,40};
    Rectangle back{275.0, 200.0, 250,40};
    bool flag = true;
    
    while (flag) {
        if (height != 300) {
            height = 300;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);

        if (GuiButton(astarB, "A* Algorithm")) {
            height = 800;
            SetWindowSize(width, height);
            start_astar(width);
        }
        else if (GuiButton(dijkB, "Dijkstras")) {
            height = 800;
            SetWindowSize(width, height);
            start_dijkstra(width);
        }
        else if (GuiButton(controls, "Controls")) {
            psaControls(width, height);
        }
        else if (GuiButton(back, "Back")) {
            flag = false;
        }
        EndDrawing();
    }
}

void caControls(int& width, int& height)
{
    bool flag = true;
    Rectangle back{275.0, 450.0, 250,40};
    while (flag) {
        if (height != 550) {
            height = 550;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Game of Life and Wolfams", 20, 100, 30, BLACK);
        DrawText("Left Click - Places blocks.", 20, 150, 20, BLACK);
        DrawText("Right Click - Deletes blocks.", 20, 200, 20, BLACK);
        DrawText("R - Makes a brand new grid.", 20, 250, 20, BLACK);
        DrawText("All Algorithms", 20, 350, 20, BLACK);
        DrawText("SpaceBar - Starts the algorithm.", 20, 400, 20, BLACK);
        
        if (GuiButton(back, "Back")) {
            flag = false;
        }
        
        EndDrawing();
    }
}

void chooseCA(int& width, int& height)
{
    SetMousePosition(100, 100);
    Rectangle gol{275.0, 100.0, 250, 40};
    Rectangle wolfamB{275.0, 150.0, 250, 40};
    Rectangle mapGenB{275.0, 200.0, 250, 40};
    Rectangle controls{275.0, 250.0, 250,40};
    Rectangle back{275.0, 300.0, 250, 40};
    
    bool flag = true;
    
    while (flag) {
        if (height != 400) {
            height = 400;
            SetWindowSize(width, height);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (GuiButton(gol, "Game of Life!")) {
            height = 800;
            SetWindowSize(width, height);
            start_gol(width);
        }
        else if (GuiButton(wolfamB, "Wolfam's CA")) {
            height = 800;
            SetWindowSize(width, height);
            choose_rule(width);
        }
        else if (GuiButton(mapGenB, "Map Generation")) {
            height = 800;
            SetWindowSize(width, height);
            start_MapG(width);
        }
        else if (GuiButton(controls, "Controls")) {
            caControls(width, height);
        }
        else if (GuiButton(back, "Back")) {
            flag = false;
        }
        EndDrawing();
    }
}

//Wolfam

void ruleCA(std::vector<std::vector<std::shared_ptr<Entity>>>& grid, int rows, int width, int rule)
{
    SetTargetFPS(20);
    std::vector<bool> temp(grid.size(),0);
    for (int ind = 0; ind<rows-1; ind++) {
        
        BeginDrawing();
        draw(grid, rows, width);
        EndDrawing();
        for (int i=1; i<grid[ind].size()-1; i++) {
            temp[i] = rules(grid[i-1][ind]->isWall(), grid[i][ind]->isWall(), grid[i+1][ind]->isWall(), rule);
        }
        for (int i=0; i<temp.size(); i++) {
            if (temp[i]) {
                grid[i][ind+1]->setWall();
            }
        }
    }
}

bool rules(bool left, bool mid, bool right, int rule)
{
    std::array<bool, 8> ruleset;
    switch(rule) {
        case 30:
            ruleset = {0,0,0,1,1,1,1,0};
            break;
        case 54:
            ruleset = {0,0,1,1,0,1,1,0};
            break;
        case 60:
            ruleset = {0,0,1,1,1,1,0,0};
            break;
        case 62:
            ruleset = {0,0,1,1,1,1,1,0};
            break;
        case 90:
            ruleset = {0,1,0,1,1,0,1,0};
            break;
        case 94:
            ruleset = {0,1,0,1,1,1,1,0};
            break;
        case 102:
            ruleset = {0,1,1,0,0,1,1,0};
            break;
        case 110:
            ruleset = {0,1,1,0,1,1,1,0};
            break;
        case 122:
            ruleset = {0,1,1,1,1,0,1,0};
            break;
        case 126:
            ruleset = {0,1,1,1,1,1,1,0};
            break;
        case 150:
            ruleset = {1,0,0,1,0,1,1,0};
            break;
        case 158:
            ruleset = {1,0,0,1,1,1,1,0};
            break;
        case 182:
            ruleset = {1,0,1,1,0,1,1,0};
            break;
        case 188:
            ruleset = {1,0,1,1,1,1,0,0};
            break;
        case 190:
            ruleset = {1,0,1,1,1,1,1,0};
            break;
        case 220:
            ruleset = {1,1,0,1,1,1,0,0};
            break;
        case 222:
            ruleset = {1,1,0,1,1,1,1,0};
            break;
        case 250:
            ruleset = {1,1,1,1,1,0,1,0};
            break;
    }
    if (left && mid && right) return ruleset[0];
    else if (left && mid) return ruleset[1];
    else if (left && right) return ruleset[2];
    else if (left) return ruleset[3];
    else if (mid && right) return ruleset[4];
    else if (mid) return ruleset[5];
    else if (right) return ruleset[6];
    else return ruleset[7];
}

void start_rule(int width, int rule)
{
    
    int rows = 40;
    std::vector<std::vector<std::shared_ptr<Entity>>> grid = make_Entities(rows, width);
    Vector2 mousepos = { 00.0f, 00.0f };
    int row;
    int col;
    std::pair<int,int> rowcol;
    bool flag = true;
    while (flag) {
        BeginDrawing();
        draw(grid, rows, width);
        EndDrawing();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows, width);
            row = rowcol.first;
            col = rowcol.second;
            if (!grid[col][row]->isWall()) {
                grid[col][row]->setWall();
            }
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows,width);
            row = rowcol.first;
            col = rowcol.second;
            if (grid[col][row]->isWall()) {
                grid[col][row]->reset();
            }
        }
        if (IsKeyPressed(KEY_SPACE)) {
            //gameoflife(grid,rows, width);
            ruleCA(grid, rows, width, rule);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        else if (IsKeyPressed(KEY_R)) {
            grid = make_Entities(rows, width);
        }
    }
}

void choose_rule(int width)
{
    SetMousePosition(width/2-25, width/2);
    bool flag = true;
    Rectangle rule30{100.0, 100.0, 250,40};
    Rectangle rule54{400.0, 100.0, 250,40};
    
    Rectangle rule60{100.0, 150.0, 250,40};
    Rectangle rule62{400.0, 150.0, 250,40};
    
    Rectangle rule90{100.0, 200.0, 250,40};
    Rectangle rule94{400.0, 200.0, 250,40};
    
    Rectangle rule102{100.0, 250.0, 250,40};
    Rectangle rule110{400.0, 250.0, 250,40};
    
    Rectangle rule122{100.0, 300.0, 250,40};
    Rectangle rule126{400.0, 300.0, 250,40};
    
    Rectangle rule150{100.0, 350.0, 250,40};
    Rectangle rule158{400.0, 350.0, 250,40};
    
    Rectangle rule182{100.0, 400.0, 250,40};
    Rectangle rule188{400.0, 400.0, 250,40};
    
    Rectangle rule190{100.0, 450.0, 250,40};
    Rectangle rule220{400.0, 450.0, 250,40};
    
    Rectangle rule222{100.0, 500.0, 250,40};
    Rectangle rule250{400.0, 500.0, 250,40};
    
    while (flag) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (GuiButton(rule30, "Rule 30")) {
            start_rule(width, 30);
        }
        else if (GuiButton(rule54, "Rule 54")) {
            start_rule(width, 54);
        }
        else if (GuiButton(rule60, "Rule 60")) {
            start_rule(width, 60);
        }
        else if (GuiButton(rule62, "Rule 62")) {
            start_rule(width, 62);
        }
        else if (GuiButton(rule90, "Rule 90")) {
            start_rule(width, 90);
        }
        else if (GuiButton(rule94, "Rule 94")) {
            start_rule(width, 94);
        }
        else if (GuiButton(rule102, "Rule 102")) {
            start_rule(width, 102);
        }
        else if (GuiButton(rule110, "Rule 110")) {
            start_rule(width, 110);
        }
        else if (GuiButton(rule122, "Rule 122")) {
            start_rule(width, 122);
        }
        else if (GuiButton(rule126, "Rule 126")) {
            start_rule(width, 126);
        }
        else if (GuiButton(rule150, "Rule 150")) {
            start_rule(width, 150);
        }
        else if (GuiButton(rule158, "Rule 158")) {
            start_rule(width, 158);
        }
        else if (GuiButton(rule182, "Rule 182")) {
            start_rule(width, 182);
        }
        else if (GuiButton(rule188, "Rule 188")) {
            start_rule(width, 188);
        }
        else if (GuiButton(rule190, "Rule 190")) {
            start_rule(width, 190);
        }
        else if (GuiButton(rule220, "Rule 220")) {
            start_rule(width, 220);
        }
        else if (GuiButton(rule222, "Rule 222")) {
            start_rule(width, 222);
        }
        else if (GuiButton(rule250, "Rule 250")) {
            start_rule(width, 250);
        }
        EndDrawing();
        
        if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
    
}

// Game of Life

void gameoflife(std::vector<std::vector<std::shared_ptr<Entity>>>& grid, int rows, int width) {
    //Game of life implementation.
    
    SetTargetFPS(20);
    std::vector<std::vector<bool>> temp(grid.size(),std::vector<bool>(grid[0].size()));
    bool flag = true;
    while (flag) {
        BeginDrawing();
        draw(grid, rows, width);
        EndDrawing();
        for (int j=0; j<grid.size(); j++) {
            for (int k=0; k<grid[0].size(); k++) {
                grid[j][k]->countNeighbours(grid);
                if (grid[j][k]->isWall()) {
                    if (grid[j][k]->wall<2) {
                        temp[j][k] = false;
                    }
                    else if (grid[j][k]->wall==2 || grid[j][k]->wall==3) {
                        temp[j][k] = true;
                    }
                    else {
                        temp[j][k] = false;
                    }
                }
                else {
                    if (grid[j][k]->wall==3) {
                        temp[j][k] = true;
                    }
                }
            }
        }
        for (int i=0; i<temp.size(); i++) {
            for (int j=0; j<temp[0].size(); j++) {
                if (temp[i][j]) {
                    grid[i][j]->setWall();
                }
                else {
                    grid[i][j]->reset();
                }
            }
        }
        if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void start_gol(int width) {
    //Setting up of game of life (setting alive tiles).
    
    int rows = 40;
    std::vector<std::vector<std::shared_ptr<Entity>>> grid = make_Entities(rows, width);
    Vector2 mousepos = { 00.0f, 00.0f };
    int row;
    int col;
    std::pair<int,int> rowcol;
    bool start = false;
    bool flag = true;
    while (flag) {
        BeginDrawing();
        draw(grid, rows, width);
        EndDrawing();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows, width);
            row = rowcol.first;
            col = rowcol.second;
            if (!grid[col][row]->isWall()) {
                grid[col][row]->setWall();
            }
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            mousepos = GetMousePosition();
            correct_bound(mousepos, width, width);
            rowcol = get_clicked(mousepos, rows,width);
            row = rowcol.first;
            col = rowcol.second;
            if (grid[col][row]->isWall()) {
                grid[col][row]->reset();
            }
        }
        if (IsKeyPressed(KEY_SPACE) && !start) {
            gameoflife(grid,rows, width);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
        else if (IsKeyPressed(KEY_R)) {
            grid = make_Entities(rows, width);
        }

    }
}

//MapG

std::vector<std::vector<char>> make_temp(std::vector<std::vector<std::unique_ptr<Tile>>>& grid) {
    
    std::vector<std::vector<char>> temp;
    std::vector<char> line;
    
    for (int i=0; i<grid.size(); i++) {
        for ( int j=0; j<grid[0].size(); j++) {
            if (grid[i][j]->isLand()) {
                line.emplace_back('L');
            }
            else if (grid[i][j]->isWater()){
                line.emplace_back('W');
            }
            else if (grid[i][j]->isDarkLand()) {
                line.emplace_back('D');
            }
            else if (grid[i][j]->isDarkWater()) {
                line.emplace_back('V');
            }
        }
        temp.push_back(line);
    }
    return temp;
}

void start_MapG(int width)
{
    bool flag = true;
    std::vector<std::vector<std::unique_ptr<Tile>>> grid = make_map(100, width, 30, time(0));
    
    while (flag) {
        BeginDrawing();
        ClearBackground(WHITE);
        draw(grid, 100, width);
        EndDrawing();
        
        if (IsKeyPressed(KEY_R)) {
            grid = make_map(100, width, 30, time(0));
        }
        else if (IsKeyPressed(KEY_SPACE)) {
            map_gen(grid, 15);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

void map_gen(std::vector<std::vector<std::unique_ptr<Tile>>>& grid, int count) {
    SetTargetFPS(20);
    std::vector<std::vector<char>> temp;
    for (int i=0; i<count; i++) {
        temp = make_temp(grid);
        for (int j=0; j<grid.size(); j++) {
            for (int k=0; k<grid[0].size(); k++) {
                grid[j][k]->countNeighbours(grid);
                
                if (grid[j][k]->land==8 || grid[j][k]->darkland>4) {
                    temp[j][k] = 'D';
                }
                else if (grid[j][k]->land>4) {
                    temp[j][k] = 'L';
                }
                else if (grid[j][k]->water==8 || grid[j][k]->darkwater>3) {
                    temp[j][k] = 'V';
                }
                else if (grid[j][k]->water>2){
                    temp[j][k] = 'W';
                }
            }
        }
        for (int i=0; i<temp.size(); i++) {
            for (int j=0; j<temp[0].size(); j++) {
                if (temp[i][j]=='L') {
                    grid[i][j]->setLand();
                }
                else if (temp[i][j]=='W') {
                    grid[i][j]->setWater();
                }
                else if (temp[i][j]=='D') {
                    grid[i][j]->setDarkLand();
                }
                else if (temp[i][j]=='V') {
                    grid[i][j]->setDarkWater();
                }
            }
        }
        BeginDrawing();
        draw(grid, grid.size(), 800);
        EndDrawing();
    }
}

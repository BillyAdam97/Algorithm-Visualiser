#include "funcs.hpp"

//Utility

double h(std::shared_ptr<Square> a, std::shared_ptr<Square> b)
// Works out the heuristic of two nodes
{
    return abs(a->x-b->x) + abs(a->y-b->y);
}

std::vector<std::vector<std::shared_ptr<Square>>> make_grid(int rows, int width)
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
        draw(grid, 40, 800);
        EndDrawing();
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
        //Once the loop for has finished the grid is drawn
        BeginDrawing();
        draw(grid, 40, 800);
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
    bool flag = true;
    int rows = 40;
    std::vector<std::vector<std::shared_ptr<Square>>> grid = make_grid(rows, width);
    Vector2 mousepos = { 0.0f, 0.0f };
    int row;
    int col;
    bool start = false;
    std::pair<int,int> startxy;
    bool end = false;
    std::pair<int,int> endxy;
    std::pair<int,int> rowcol;
    bool started = false;
    std::shared_ptr<Square> startnode = nullptr;
    std::shared_ptr<Square> endnode = nullptr;
    while (flag) {
        BeginDrawing();
        draw(grid,  rows, width);
        EndDrawing();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mousepos = GetMousePosition();
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
        if (IsKeyPressed(KEY_SPACE) and !started) {
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
        draw(grid, 40, 800);
        EndDrawing();
        if (*curr!=*start) {
            curr->setClosed();
        }
    }
    return true;
}

void start_dijkstra(int width) {
    //Set up of Dijkstras (setting start and end positions and barriers)
    
    bool flag = true;
    int rows = 40;
    std::vector<std::vector<std::shared_ptr<Square>>> grid = make_grid(rows, width);
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
        if (IsKeyPressed(KEY_SPACE)) {
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
    }
}

// Game of Life

void gameoflife(std::vector<std::vector<std::shared_ptr<Square>>>& grid, int rows, int width) {
    //Game of life implementation.
    
    SetTargetFPS(20);
    std::vector<std::vector<bool>> temp(grid.size(),std::vector<bool>(grid[0].size()));
    bool flag = false;
    while (!flag) {
        BeginDrawing();
        draw(grid, rows, width);
        EndDrawing();
        for (int j=0; j<grid.size(); j++) {
            for (int k=0; k<grid[0].size(); k++) {
                grid[j][k]->countNeighbours(grid);
                if (grid[j][k]->isBarrier()) {
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
                    grid[i][j]->setBarrier();
                }
                else {
                    grid[i][j]->reset();
                }
            }
        }
        if (IsKeyPressed(KEY_DELETE)) {
            flag = true;
        }
    }
}

void start_gol(int width) {
    //Setting up of game of life (setting alive tiles).
    
    int rows = 40;
    std::vector<std::vector<std::shared_ptr<Square>>> grid = make_grid(rows, width);
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
            rowcol = get_clicked(mousepos, rows, width);
            row = rowcol.first;
            col = rowcol.second;
            if (!grid[col][row]->isBarrier()) {
                grid[col][row]->setBarrier();
            }
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            mousepos = GetMousePosition();
            rowcol = get_clicked(mousepos, rows,width);
            row = rowcol.first;
            col = rowcol.second;
            if (grid[col][row]->isBarrier()) {
                grid[col][row]->reset();
            }
        }
        if (IsKeyPressed(KEY_SPACE) && !start) {
            gameoflife(grid,rows, width);
        }
        else if (IsKeyPressed(KEY_DELETE)) {
            flag = false;
        }
    }
}

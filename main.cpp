#include <cstring>
#include "warehouse.h"
#include <stack>
stack<Point> path;
bool grid[11][11];
Point ini, dest;
void initialize()
{
    memset(grid, false, sizeof(grid));
    ini = getRobotPos();
    dest = getItemPos();

    path.push(ini);
    grid[ini.row][ini.col] = true;

}
double calculateHValue(int row, int col, Point dest)
{
    int dx = abs(dest.row - row);
    int dy = abs(dest.col - col);
    double h = dx + dy - (sqrt(2) - 2) * min(dx, dy);
    return h;
}
bool check(Point x)
{
    Point item = dest;
    if (x.row == item.row && x.col == item.col)
    {
        pickItem();
        memset(grid, false, sizeof(grid));
        while (path.size() > 0)
        {
            path.pop();
        }
        ini = item;
        dest = getGoalPos();
        path.push(ini);
        grid[item.row][item.col] = true;
        return true;
    }
    return false;
}
int nextmove(Point curr)
{
    int dist = INT_MAX;
    int t;
    Point s;
    int count = 0;
    ;
    if (isWalkable(-1, -1) && !grid[curr.row - 1][curr.col - 1])
    {
        count++;
        t = calculateHValue(curr.row - 1, curr.col - 1, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row - 1;
            s.col = curr.col - 1;
        }
    }
    if (isWalkable(-1, 0) && !grid[curr.row][curr.col - 1])
    {
        count++;
        t = calculateHValue(curr.row, curr.col - 1, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row;
            s.col = curr.col - 1;
        }
    }
    if (isWalkable(-1, 1) && !grid[curr.row + 1][curr.col - 1])
    {
        count++;
        t = calculateHValue(curr.row + 1, curr.col - 1, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row + 1;
            s.col = curr.col - 1;
        }
    }

    if (isWalkable(0, -1) && !grid[curr.row - 1][curr.col])
    {
        count++;
        t = calculateHValue(curr.row - 1, curr.col, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row - 1;
            s.col = curr.col;
        }
    }

    if (isWalkable(0, 1) && !grid[curr.row + 1][curr.col])
    {
        count++;
        t = calculateHValue(curr.row + 1, curr.col, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row + 1;
            s.col = curr.col;
        }
    }

    if (isWalkable(1, -1) && !grid[curr.row - 1][curr.col + 1])
    {
        count++;
        t = calculateHValue(curr.row - 1, curr.col + 1, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row - 1;
            s.col = curr.col + 1;
        }
    }
    if (isWalkable(1, 0) && !grid[curr.row][curr.col + 1])
    {
        count++;
        t = calculateHValue(curr.row, curr.col + 1, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row;
            s.col = curr.col + 1;
        }
    }
    if (isWalkable(1, 1) && !grid[curr.row + 1][curr.col + 1])
    {
        count++;
        t = calculateHValue(curr.row + 1, curr.col + 1, dest);
        if (t < dist)
        {
            dist = t;
            s.row = curr.row + 1;
            s.col = curr.col + 1;
        }
    }
    if (count > 0)
    {
        moveRobot(s.col - curr.col, s.row - curr.row);
        grid[s.row][s.col] = true;
        path.push(s);
    }
    return count;
}
void solve()
{
    Point prev = path.top();
    if (check(prev))
        return;
    int count = nextmove(prev);
    if (count == 0)
    {
        path.pop();
        moveRobot(path.top().col - prev.col, path.top().row - prev.row);
    }
    
}
int main(int argc, char const *argv[])
{
    // Initalize level
    initMaze(argv[1]);

    initialize();
    cout << "starting\n";
    // Game loop
    while (true)
    {
        // Check reached goal
        if (hasReachedGoal())
        {
            // Hurray!
            cout << "Reached Goal!" << endl;
            break;
        }

        // Solve maze
        solve();
    }

    return 0;
}
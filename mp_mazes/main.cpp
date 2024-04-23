#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze s;
    s.makeMaze(50, 50);
    PNG* maze = s.drawCreativeMazeWithSolution();
    maze->writeToFile("creative.png");
    return 0;
}

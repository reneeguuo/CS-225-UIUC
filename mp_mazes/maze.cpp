#include "maze.h"
#include <sys/time.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

//Note to Self: Convert all similar additions to similar format to reduce confusion

SquareMaze::SquareMaze() {
  height_ = 0;
  width_ = 0;
  dsets = DisjointSets();
  size = 0;
}

void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;
  size = width_ * height_;
  dsets.addelements(size);

  for (int i = 0; i < size; i++) {
    downWalls.push_back(true);
    rightWalls.push_back(true);
  }

  while (dsets.size(0) < size) {

    int x = rand() % width_;
    int y = rand() % height_;

    if (rand() % 2 != 1) {
      if (y != height_ - 1) {
        if (dsets.find(x + y * width_) != dsets.find(x + y * width_ + width_)) {
          setWall(x, y, 1, false);
            dsets.setunion(x + y * width_, x + y * width_ + width_);
        }
      }
    } else {
      if (x != width_ - 1) {
        if (dsets.find(x + y * width_) != dsets.find(x + y * width_ + 1)){
          rightWalls[y * width_ + x] = false;
          dsets.setunion(x + y * width_, x + y * width_ + 1);
        }
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {

  if (dir == 0) { //right
    return rightWalls[x + y * width_] == false;
  } else if (dir == 1) { //down
    return downWalls[x + y * width_] == false;
  } else if (dir == 2) { //left
    return (x != 0) && (rightWalls[x + y * width_ - 1] == false);
  } else if (dir == 3) { //up
    return (y != 0) && (downWalls[x + y * width_ - width_] == false);
  } else {
    return false;
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (dir == 0) {
    rightWalls[x + y * width_] = exists;
  } else if (dir == 1) {
    downWalls[x + y * width_] = exists;
  }
}



vector<int> SquareMaze::solveMaze(){

  int index;

  vector<int> visited;
  vector<int> path;

  visited.push_back(0); //entrance
  path.push_back(0);


  for (int i = 1; i < width_ * height_; i++) {
    visited.push_back(-1);
    path.push_back(0);

  }

  queue<int> q;
  q.push(0);

  int x = 0;
  int y = 0;

  while(!q.empty()) {
    index = q.front();
    x = index % width_; //converting single dimension vector to double dimensional values
    y = index / width_;
    q.pop();

    if (canTravel(x, y, 0)) { // right
      if (visited[index + 1] == -1) { // is right visited
        q.push(index + 1);
        visited[index + 1] = index;
        path[index + 1] = path[index] + 1;
      }
    }

    if (canTravel(x, y, 1)) { // down
      if (visited[index + width_] == -1) { // is down visited
        q.push(index + width_);
        visited[index + width_] = index;
        path[index + width_] = path[index] + 1;
      }
    }

    if (canTravel(x, y, 2)) { // left
      if (visited[index - 1] == -1) { //is left visited
        q.push(index - 1);
        visited[index - 1] = index;
        path[index - 1] = path[index] + 1;
      }
    }

    if (canTravel(x, y, 3)) { // up
      if (visited[index - width_] == -1) { // is up visited
        q.push(index - width_);
        visited[index - width_] = index;
        path[index - width_] = path[index] + 1;
      }
    }
  }


  int range = width_ * (height_ - 1);

  for (int j = 0; j < width_; j++) {
    if (path[width_ * (height_ - 1) + j] > path[range]) {
      range = width_ * (height_ - 1) + j;
    }
  }

  destination = range;
  index = destination;

  vector<int> solvedMaze;

  while (index != 0) {
    if (visited[index] == index - 1) {
      solvedMaze.push_back(0); //right
    } else if (visited[index] == index - width_) {
      solvedMaze.push_back(1); // down
    } else if (visited[index] == index + 1) {
      solvedMaze.push_back(2); // left
    } else if (visited[index] == index + width_) {
      solvedMaze.push_back(3); //up
    }

    index = visited[index];

  }

  reverse(solvedMaze.begin(), solvedMaze.end());
  return solvedMaze;

}



PNG* SquareMaze::drawMaze() const{

  PNG* maze = new PNG(width_ * 10 + 1, height_ * 10 + 1);

  for (int y = 0; y < height_ * 10 + 1; y++) { // left most blacken
    HSLAPixel & pixel = maze->getPixel(0, y);
    pixel.l = 0;
  }
  for (int x = 10; x < width_ * 10 + 1; x++) { // top most blacken with gap for entrance
    HSLAPixel & pixel = maze->getPixel(x, 0);
    pixel.l = 0;
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (rightWalls[x + y * width_]) {
        for (int i = 0; i <= 10; i++) {
          HSLAPixel & pixel = maze->getPixel(10 * x + 10, 10 * y + i);
            pixel.l = 0;
          }
        }
        if (downWalls[x + y * width_]) {
          for (int i = 0; i <= 10; i++) {
            HSLAPixel & pixel = maze->getPixel(10 * x + i, 10 * y + 10);
            pixel.l = 0;
          }
        }
      }
    }
    return maze;
}


PNG* SquareMaze::drawMazeWithSolution(){
  PNG* maze = drawMaze();
  vector<int> solved = solveMaze();
  int x = 5;
  int y = 5;

  int final_x = destination % width_;
  int final_y = destination / height_;

  for (int i = 1; i < 10; i++) {
    HSLAPixel & pixel = maze->getPixel(final_x * 10 + i, (final_y + 1) * 10);
    pixel.l = 1;
  }

  for (size_t i = 0; i < solved.size(); i++) {
    if (solved[i] == 0) {
      for(int j = 0; j <= 10; j++){
        HSLAPixel & pixel = maze->getPixel(x + j, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

      x = x + 10;

    } else if (solved[i] == 1) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & pixel = maze->getPixel(x, y + j);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

        y = y + 10;

    } else if (solved[i] == 2) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & pixel = maze->getPixel(x - j, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

        x = x - 10;

    } else if (solved[i] == 3) {
      for(int j = 0; j <= 10; j++){
        HSLAPixel & pixel = maze->getPixel(x, y - j);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

        y = y - 10;

    }
  }

  return maze;
}

PNG* SquareMaze::drawCreativeMaze(){

  int new_width = width_ * 10 + 1;
  int new_height = height_ * 10 + 1;

  PNG * maze = new PNG(new_width, new_height);

  for (int x = 10; x < new_width; x++) {
    HSLAPixel & pixel = maze->getPixel(x, 0);
    pixel.l = 0;
  }

  for (int y = 0; y < new_height; y++) {
    HSLAPixel & pixel = maze->getPixel(0, y);
    pixel.l = 0;
  }

  for (int x = 0; x < width_ * 0.25; x++) {
    setWall(x, height_ * 0.25, 1, true);
  }

  for (int x = width_ * 0.75; x < width_; x++) {
    setWall(x, height_ * 0.25, 1, true);
  }


  for (int x = 0; x < width_ * 0.25; x++) {
    setWall(x, height_ * 0.75 - 1, 1, true);
  }

  for (int x = width_ * 0.75; x < width_; x++) {
    setWall(x, height_ * 0.75 - 1, 1, true);
  }

  for (int y = height_ * 0.25; y < height_ * 0.75; y++) {
    setWall(width_ * 0.25 - 1, y, 0, true);
  }


  for (int y = height_ * 0.25; y < height_ * 0.75; y++) {
    setWall(width_ * 0.75, y, 0, true);
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (!((y > height_ * 0.25 && y < height_ * 0.75 && x < width_ * 0.25) || (y > height_* 0.25 && y < height_ * 0.75 && x > width_ * 0.75))) {
        if (rightWalls[x + y * width_]) {
          for (int i = 0; i <= 10; i++) {
            HSLAPixel & pixel = maze->getPixel(10 * x + 10, 10 * y + i);
            pixel.h = 0;
            pixel.s = 1;
            pixel.l = 0.5;
            pixel.a = 1;
          }
        }

        if (downWalls[x + y * width_]) {
          for (int i = 0; i <= 10; i++) {
            HSLAPixel & pixel = maze->getPixel(10 * x + i, 10 * y + 10);
            pixel.h = 0;
            pixel.s = 0;
            pixel.l = 0;
            pixel.a = 0;
          }
        }
      }
    }
  }

  return maze;
}

PNG* SquareMaze::drawCreativeMazeWithSolution()
{
  PNG * maze = drawCreativeMaze();
  vector<int> solved = solveMaze();

  int x = 5;
  int y = 5;

  int final_x = destination % width_;
  int final_y = destination / height_;

  for (int i = 1; i < 10; i++) {
    HSLAPixel & pixel = maze->getPixel(final_x * 10 + i, (final_y + 1) * 10);
    pixel.l = 1;
  }

  for (size_t i = 0; i < solved.size(); i++) {
    if (solved[i] == 0) {
      for(int j = 0; j <= 10; j++){
        HSLAPixel & pixel = maze->getPixel(x + j, y);
        pixel.h = 130;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

      x = x + 10;

    } else if (solved[i] == 1) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & pixel = maze->getPixel(x, y + j);
        pixel.h = 130;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

        y = y + 10;

    } else if (solved[i] == 2) {
      for (int j = 0; j <= 10; j++) {
        HSLAPixel & pixel = maze->getPixel(x - j, y);
        pixel.h = 130;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

        x = x - 10;

    } else if (solved[i] == 3) {
      for(int j = 0; j <= 10; j++){
        HSLAPixel & pixel = maze->getPixel(x, y - j);
        pixel.h = 130;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }

        y = y - 10;

    }
  }

  return maze;
}

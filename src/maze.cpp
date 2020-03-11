#include <iostream>
#include <string>
#include "stack.h"
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

enum class Marker {
  Exit = 'X', Entry = 'N', Passage = ' ', Wall = '1', Visited = '.'
};
 
class Cell {
private:
  int x, y;

public:
  Cell(int i, int j): x(i), y(j){}
  bool operator==(const Cell& c){
    return x == c.x && y == c.y;
  }

  friend class Maze;
};

class Maze {
private:
  string* grid;
  unsigned rows, cols;
  cs2420::Stack<Cell> mazeStack;

  void pushVisited(int r, int c){
    if(grid[r][c] == static_cast<char>(Marker::Passage) ||
       grid[r][c] == static_cast<char>(Marker::Exit)){
         mazeStack.push(Cell(r,c));
       }
  }

  Cell findMarker(Marker m){
    for(int r = 0; r < rows; r++){
      for(int c = 0; c < grid[r].size(); c++){
        if(grid[r][c] == static_cast<char>(m)){
          return Cell(r, c);
        }
      }
    }

    return Cell(0,0);
  }

  friend ostream& operator<<(ostream& out, const Maze& maze){
    for(int r = 0; r < maze.rows; r++){
      out << maze.grid[r] << endl;
    }

    return out;
  }
public:
  Maze(string* g, unsigned r): grid(g), rows(r), cols(g[0].size()){}
  void exit(){
    int r, c;

    Cell current = findMarker(Marker::Entry);
    Cell exit = findMarker(Marker::Exit);

    while(!(current == exit)){
      r = current.x;
      c = current.y;

      grid[r][c] = static_cast<char>(Marker::Visited);
      pushVisited(r-1, c);
      pushVisited(r+1, c);
      pushVisited(r, c-1);
      pushVisited(r, c+1);

      if(mazeStack.empty()){
        cout << "Impossible to exit" << endl;
        cout << *this;
        return;
      }else{
        current = mazeStack.pop();
      }
    }

    cout << *this;
    cout << "You are now out of the maze!" << endl;

  }
};

int main(){
  auto start = high_resolution_clock::now();
  string mazeGrid [] = {
    "11111111111",
    "11        1",
    "1 1  1 1 11",
    "X   1111  1",
    "1 1111111 1",
    "1 1 1 1   1",
    "1  1  1  11",
    "111111  111",
    "1  1N1 1  1",
    "1      1111",
    "11111111111"
  };

  Maze maze(mazeGrid, 11u);
  maze.exit();
  auto end = high_resolution_clock::now();

  chrono::duration<double, std::micro> running_time = end - start;

  cout << "Took " << running_time.count() << " micoseconds to run" << endl;


  default_random_engine en;
  en.seed(system_clock::now().time_since_epoch().count());
  uniform_int_distribution dist{1, 6};

  cout << dist(en) << endl;
  cout << dist(en) << endl;
  cout << dist(en) << endl;
  cout << dist(en) << endl;
  cout << dist(en) << endl;
  cout << dist(en) << endl;

  return 0;
}
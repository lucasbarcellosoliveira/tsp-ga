#include <iostream>
using namespace std;

class Point{
       public:
              int x;
              int y;
              int distance(Point p){ //returns the "distance" between two points
                  return abs(x-p.x)+abs(y-p.y);
              }
};

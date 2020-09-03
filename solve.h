#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <list>
#include <set>
#include <emscripten.h>
#ifndef solve_h
#define solve_h

EMSCRIPTEN_KEEPALIVE board readFile(std::string fileName);
EMSCRIPTEN_KEEPALIVE void writeFile(std::string fileName, board& b);
EMSCRIPTEN_KEEPALIVE bool nextTo(board& b, board& known, std::string targ, int x, int y);
EMSCRIPTEN_KEEPALIVE void narrow(board& b, board& known, std::string targ, std::list<coord>& coordsList);
EMSCRIPTEN_KEEPALIVE std::string adjacent(board& b, int size, int x, int y, bool allowWump = false);
EMSCRIPTEN_KEEPALIVE std::list<coord> possibleLocations(board& b, board& known, std::string targ, int x, int y);
EMSCRIPTEN_KEEPALIVE bool getInfo(board& b, board& known, int x, int y, std::list<coord>& wumpLocs, std::list<coord>& goldLocs);
EMSCRIPTEN_KEEPALIVE bool solveable(board& b, board& known, unsigned int& d);
EMSCRIPTEN_KEEPALIVE std::set<board> buildBoards(int SIZE, int PITS, int DIFF);
#endif
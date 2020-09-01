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
#ifndef solve_h
#define solve_h

board readFile(std::string fileName);
void writeFile(std::string fileName, board& b);
bool nextTo(board& b, board& known, std::string targ, int x, int y);
void narrow(board& b, board& known, std::string targ, std::list<coord>& coordsList);
std::string adjacent(board& b, int size, int x, int y, bool allowWump = false);
std::list<coord> possibleLocations(board& b, board& known, std::string targ, int x, int y);
bool getInfo(board& b, board& known, int x, int y, std::list<coord>& wumpLocs, std::list<coord>& goldLocs);
bool solveable(board& b, board& known, uint& d);
std::set<board> buildBoards();
#endif
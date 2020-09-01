//HEADER LEVELMAKE

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#ifndef levelmake_h
#define levelmake_h


typedef std::vector<std::vector<std::string>> board;
typedef std::pair<int, int> coord;

bool inBoard(int x, int y, int size);

void surround(board& in, char c, int x, int y, int size);

void printBoard(board& b, uint size);

board build(int size);

std::vector<board> makeBoards(uint size, uint quantity, uint numPits);


#endif
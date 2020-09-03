//HEADER LEVELMAKE

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <emscripten.h>
#ifndef levelmake_h
#define levelmake_h


typedef std::vector<std::vector<std::string>> board;
typedef std::pair<int, int> coord;

EMSCRIPTEN_KEEPALIVE bool inBoard(int x, int y, int size);

EMSCRIPTEN_KEEPALIVE void surround(board& in, char c, int x, int y, int size);

EMSCRIPTEN_KEEPALIVE void printBoard(board& b, unsigned int size);

EMSCRIPTEN_KEEPALIVE board build(int size);

EMSCRIPTEN_KEEPALIVE std::vector<board> makeBoards(unsigned int size, unsigned int quantity, unsigned int numPits);


#endif
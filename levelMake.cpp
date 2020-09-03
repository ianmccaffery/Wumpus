// level generation
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <emscripten.h>
typedef std::vector<std::vector<std::string>> board;
typedef std::pair<int, int> coord;


EMSCRIPTEN_KEEPALIVE bool inBoard(int x, int y, int size)
{
	return (x >= 0 && x < size && y >= 0 && y < size);
}

EMSCRIPTEN_KEEPALIVE void printBoard(board& b, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		std::cout << "| ";
		for (unsigned int j = 0; j < size; ++j)
		{
			std::cout << b[j][i] << " | "; 
		}
		std::cout << std::endl;
	}
}

EMSCRIPTEN_KEEPALIVE board build(int size)
{
	std::vector<std::string> piece(size, "e");
	std::vector<std::vector<std::string>> x(size, piece);
	return x;
}

EMSCRIPTEN_KEEPALIVE std::vector<board> makeBoards(unsigned int size, unsigned int quantity, unsigned int numPits)
{
	std::vector<board> outVec;
	srand(time(NULL));
	for (unsigned int i = 0; i < quantity; ++i)
	{
		board b = build(size);
		b[0][size-1] = "s"; //temporarily save the start point & surroundings
		b[0][size-2] = "s";
		b[1][size-1] = "s";

		while (true) //find gold position.
		{
			int x = rand()%size;
			int y = rand()%size;
			if (b[x][y] == "e")
			{
				b[x][y] = "g";
				break;
			}
		}
		while (true) //find wumpus position.
		{
			int x = rand()%size;
			int y = rand()%size;
			if (b[x][y] == "e")
			{
				b[x][y] = "w";
				break;
			}
		}

		for (unsigned int i = 0; i < numPits; ++i) //place pits
		{
			while (true)
			{
				int x = rand()%size;
				int y = rand()%size;
				if (b[x][y] == "e")
				{
					b[x][y] = "p";
					break;
				}
			}
		}
		b[0][size-1] = "e"; //revert the start and surrounding points.
		b[0][size-2] = "e";
		b[1][size-1] = "e";
		outVec.push_back(b);
	}
	return outVec;
}
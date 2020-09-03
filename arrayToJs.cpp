#include <math.h>
#include "levelMake.h"
#include "solve.h"
#include <cassert>
#include <emscripten.h>
extern "C" {
	EMSCRIPTEN_KEEPALIVE void fillArray(int EDGELENGTH, int NUMPITS, int DIFFICULTY, int* output_ptr){ 
		std::set<board> grids = buildBoards(4, 2, 1);
		std::set<board>::iterator boardIterator = grids.begin();
		board b = *boardIterator;
		std::vector<int> intBoard;
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			for (unsigned int j = 0; j < b[i].size(); ++j)
			{
				std::string s = b[i][j];
				// std::cout << s;
				if (s == "e") // empty
					intBoard.push_back(0);
				if (s == "p") // pit
					intBoard.push_back(1);
				if (s == "w") // wumpus
					intBoard.push_back(2);
				if (s == "g") //gold
					intBoard.push_back(3);
			}
		}
		std::cout << intBoard.size() << std::endl;
		std::cout << intBoard.size() << std::endl;
				
		for(unsigned int i = 0; i < intBoard.size(); ++i)
		{
			*output_ptr = intBoard[i];
			output_ptr ++;
	    }
	}
}


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>


#include "levelMake.h"
#include "solve.h"
#include "external.h"
#include "button.h"

bool xRayVision = false;
bool mouseButtonDown = false;

uint robotX = 0;
uint robotY = 3;
std::vector<std::vector<sf::RectangleShape>> squares;
std::string hints;

std::vector<Button> initButtons()
{
    std::vector<Button> buttons;
    //Save button:

    
}

void rerun(Button& save, std::set<board>& boards)
{
    save.updateState(false);
    boards = buildBoards();
}

void buildSquares(std::vector<std::vector<sf::RectangleShape>>& squares)
{
    for(uint i = 0; i < 4; ++i)
    {
        std::vector<sf::RectangleShape> line;
        for (uint j = 0; j < 4; ++j)
        {
            sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
            uint x = 20+120* i;
            uint y = 20+120* j;
            square.setFillColor(sf::Color(20, 20, 20, 50));
            square.setPosition(x,y);
            line.push_back(square);
        }
        squares.push_back(line);
    }
}
std::string getHints(int x, int y, const board& b)
{
    bool wumpus = false;
    bool pit = false;
    bool gold = false;
    std::string out;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (inBoard(x+i, y+j, SIZE) && (i != 0 || j != 0) && (i == 0 || j == 0))
            {
                if ((b[x+i][y+j]) == "w")
                    wumpus = true;
                if (b[x+i][y+j] == "p")
                    pit = true;
                if (b[x+i][y+j] == "g")
                    gold = true;
            }
        }
    }
    if (pit)
        out += "There's a breeze in the air\n";
    if (wumpus)
        out += "An awful stench wafts to your nose\n";
    if (gold)
        out += "A glitter is visible in the distance\n";
    if (out.length() == 0)
        out = "";
    return out;
}

void toggleXRay(const board& b, std::vector<std::vector<sf::RectangleShape>>& squares, bool on)
{
    //Blue = robot
    //Yellow = gold
    //Black = pit
    //Green = wumpus
    for (uint i = 0; i < SIZE; ++i)
    {
        for (uint j = 0; j < SIZE; ++j)
        {
            if (on)
            {
                if (b[i][j] == "g")
                    squares[i][j].setFillColor(sf::Color::Yellow);
                if (b[i][j] == "p")
                    squares[i][j].setFillColor(sf::Color::Black);
                if (b[i][j] == "w")
                    squares[i][j].setFillColor(sf::Color::Green);
            }
            else
            {
                squares[i][j].setFillColor(sf::Color(20, 20, 20, 50));
            }
        }
    }
}

bool checkLegal(int x, int y)
{
    return (x < (SIZE) and x >= 0 and y < (SIZE) and y >= 0);
}

void parseInput(sf::Keyboard::Key key, std::vector<std::vector<sf::RectangleShape>>& squares, board& b)
{
    if (key == sf::Keyboard::W)
    {
        if (checkLegal(robotX, robotY-1))
        {
            squares[robotX][robotY].setFillColor(sf::Color(20, 20, 20, 50));
            robotY-=1;
        }
        else
            std::cerr << "not on the board!";
    }
    else if (key == sf::Keyboard::S)
    {
        if (checkLegal(robotX, robotY+1))
        {
            squares[robotX][robotY].setFillColor(sf::Color(20, 20, 20, 50));
            robotY+=1;
        }
        else
            std::cerr << "not on the board!";
    }    
    else if (key == sf::Keyboard::A)
    {
        if (checkLegal(robotX-1, robotY))
        {
            squares[robotX][robotY].setFillColor(sf::Color(20, 20, 20, 50));
            robotX-=1;
        }
        else
            std::cerr << "not on the board!";
    }   
    else if (key == sf::Keyboard::D)
    {
        if (checkLegal(robotX+1, robotY))
        {
            squares[robotX][robotY].setFillColor(sf::Color(20, 20, 20, 50));
            robotX+=1;
        }
        else
            std::cerr << "not on the board!";
    }   
    else if (key = sf::Keyboard::LAlt)
    {
        xRayVision = !xRayVision;
        toggleXRay(b, squares, xRayVision);
    }
}



int main()
{

    sf::Font oswald;
    oswald.loadFromFile("Oswald-Regular.ttf");
    sf::Text hintList;
    hintList.setFont(oswald);
    hintList.setPosition(860,50);
    hintList.setFillColor(sf::Color::Black);
    sf::Text saveText;
    saveText.setString("Click here to save and continue!");
    saveText.setFont(oswald);
    saveText.setPosition(875,675);
    saveText.setFillColor(sf::Color::Black);

    std::set<board> boards = buildBoards();
    std::set<board>::iterator boardIterator = boards.begin();

    sf::Texture save1;
    if (!save1.loadFromFile("unclicked_savebutton.png"))
        std::cerr << "Unable to load image";
    sf::Texture save2;
    if (!save2.loadFromFile("clicked_savebutton.png"))
        std::cerr << "Unable to load image";

    sf::Texture startPage;
    if(!startPage.loadFromFile("start.png", sf::IntRect(0, 0, 1300, 780)))
    {
        std::cerr << "Unable to load starting image.";
    }
    sf::Sprite background;
    background.setTexture(startPage);
    sf::Texture robot;
    if (!robot.loadFromFile("robot.png"))
        std::cerr << "Unable to load image";
    sf::Texture gold;
    if (!gold.loadFromFile("gold.png"))
        std::cerr << "Unable to load image";
    sf::Texture pit;
    if (!pit.loadFromFile("pit.png"))
        std::cerr << "Unable to load image";
    sf::Texture wumpus;
    if (!wumpus.loadFromFile("wumpus.png"))
        std::cerr << "Unable to load image";

    std::vector<std::vector<sf::RectangleShape>> squares;
    buildSquares(squares);
    std::vector<Button> buttons = initButtons();
    std::string s = "Click here to save and continue!";
    sf::Vector2f loc(875, 675);
    Button save(save1, save2, saveText, loc, 20);
    
    sf::RenderWindow window(sf::VideoMode(1300, 780), "Wumpus World");

    while (window.isOpen())
    {
        board b = *boardIterator;
        hintList.setString(getHints(robotX, robotY, b));
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                //window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                //key-press
                case sf::Event::KeyPressed:
                    parseInput(event.key.code, squares, b);
                case sf::Event::MouseButtonPressed:
                    if(save.click(sf::Mouse::getPosition(window), true))
                    {
                        rerun(save, boards);
                        boardIterator = boards.begin();
                    }
                default:
                    break;
            }
        }
        window.clear(sf::Color::White);
        window.draw(background);
        squares[robotX][robotY].setFillColor(sf::Color::Blue);
        for (uint i =0; i < SIZE; ++i)
        {
            for (uint j = 0; j < SIZE; ++j)
            {
                window.draw(squares[i][j]);
            }
        }
        // window.draw(save.getSprite());
        window.draw(save.getSprite());
        window.draw(save.getText());
        window.draw(hintList);
        window.display();
    }

    return 0;
}
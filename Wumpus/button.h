//Button Header File
#ifndef button_h
#define button_h
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <SFML/Graphics.hpp>

class Button{
public:
	Button (sf::Texture& origTexture, sf::Texture& clickedTexture, sf::Text text, sf::Vector2f loc, uint size);
	bool click(sf::Vector2i point, bool clickType);
	void updateState(bool state);
	void setText(std::string s);
	bool getState();
	sf::Sprite getSprite();
	sf::Text getText();
private:
	sf::Sprite currentSpr;
	sf::Text text;
	sf::Texture origTexture;
	sf::Texture clickedTexture;
	bool state;
};
#endif
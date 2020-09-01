//Button Main Class File
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "button.h"	


Button::Button(sf::Texture& origTexture, sf::Texture& clickedTexture, sf::Text text, sf::Vector2f loc, uint size)
{
	this->origTexture = origTexture;
	this->clickedTexture = clickedTexture;
	this->state = false;
	this->text = text;
	this->currentSpr.setTexture(origTexture);
	this->currentSpr.setPosition(loc);
}


void Button::updateState(bool which)
{
	state = which;
	if (state)
	{
		currentSpr.setTexture(clickedTexture);
	}
	else
		currentSpr.setTexture(origTexture);
}

bool Button::click(sf::Vector2i point, bool clickType)
{
	if (currentSpr.getGlobalBounds().contains(point.x, point.y)) 
	{
        this->updateState(clickType);
        return true;
	}
}


void Button::setText(std::string s)
{
	text.setString(s);
}

bool Button::getState()
{
	return state;
}

sf::Sprite Button::getSprite()
{
	return currentSpr;
}

sf::Text Button::getText()
{
	return text;	
}
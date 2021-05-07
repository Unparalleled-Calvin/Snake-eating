#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 1400;//640;
	static const int Height = 840;//480;
    static const int grid = 20;
	static std::shared_ptr<Screen> Screen;
    
    void setGridlines();
	void drawGridlines();
	void drawbackground(sf::RenderWindow &window_);
	int Gridlines_color = 0;
	int background_color = 4;
private:
	sf::RenderWindow window_;
	std::vector<sf::RectangleShape> Gridlines;
	static const sf::Time TimePerFrame;
};
}


#endif
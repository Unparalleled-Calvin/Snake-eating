#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};//枚举方向

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window_);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;

	unsigned getSize() const;

private:
	void move();
	void Newmove();
	void grow(int addition);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	float movex = 0;
	float movey = -20.0;

	bool hitSelf_;

	sf::Vector2f position_;
	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;
    
	static const int InitialSize;

};
}

#endif
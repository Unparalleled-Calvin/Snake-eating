#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0));
    int getAddition(){return addition;};
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;

private:
	sf::CircleShape shape_;
    int addition;
	static const float Radius;
};
}

#endif
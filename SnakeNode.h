#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>
#include <vector>
namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), int index = 0);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const float Height;

	int index_;
	void initTex();
private:
	sf::Sprite sprite_;
	sf::Vector2f position_;
	std::vector<sf::Texture> tex;
};
}

#endif
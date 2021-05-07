#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "SnakeNode.h"
using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 20.f;


SnakeNode::SnakeNode(sf::Vector2f position, int index)
: position_(position), index_(index)
{
	sf::Texture ntex;
	ntex.loadFromFile("Pictures\\20\\"+std::to_string(index_==0?0:(index_-1)%6+1)+".png");
	tex.push_back(ntex);
	sprite_.setTexture(tex[0]);//我也不明白为什么必须将Texture存入作为属性的vector中，Texture才能得以保存
	sprite_.setPosition(position);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	sprite_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	sprite_.setPosition(position_);
}//结点的move

sf::FloatRect SnakeNode::getBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}
#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include <random>
using namespace sfSnake;
const float Fruit::Radius = 5.f;


Fruit::Fruit(sf::Vector2f position)
{
    static std::default_random_engine random(time(NULL));
	static std::uniform_int_distribution<int> TYPE(0,3);
	addition = TYPE(random);
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	switch(addition){
		case 0:
		    if(TYPE(random)%2){
				shape_.setFillColor(sf::Color::Black);
			}
			else{
				shape_.setFillColor(sf::Color(96,56,17));//褐色
			}
			break;
		case 1:
			shape_.setFillColor(sf::Color::Green);
			break;
		case 2:
		    shape_.setFillColor(sf::Color::Blue);
			break;
		case 3:
		    shape_.setFillColor(sf::Color::Red);
			break; 
	}
}//构造函数

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}
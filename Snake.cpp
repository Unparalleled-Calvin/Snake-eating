#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

#include <iostream>

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();
	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)), i));
	}
}

void Snake::handleInput(sf::RenderWindow& window_)
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		int vectorx = sf::Mouse::getPosition(window_).x - nodes_[0].getPosition().x;
		int vectory = sf::Mouse::getPosition(window_).y - nodes_[0].getPosition().y;//获得运动方向向量
		int nodex = nodes_[0].getPosition().x - nodes_[2].getPosition().x;
		int nodey = nodes_[0].getPosition().y - nodes_[2].getPosition().y;//获得蛇头处的方向向量
		//由于此时node_[0]与node_[1]为同一位置，所以第二个位置的结点是node_[2]
		double cos_ = (vectorx*nodex+vectory*nodey)/sqrt(vectorx*vectorx + vectory*vectory)/sqrt(nodex*nodex + nodey*nodey);
		//cos_是运动方向与蛇身方向夹角的余弦值，运动时视觉上必须满足夹角小于135°
		if(cos_ > cos(acos(-1.0)*135/180)){
			if(abs(vectorx) > abs(vectory)){
				this->movex = vectorx*SnakeNode::Width/abs(vectorx);
				this->movey = vectory*SnakeNode::Width/abs(vectorx);
			}
			else{
				this->movex = vectorx*SnakeNode::Width/abs(vectory);
				this->movey = vectory*SnakeNode::Width/abs(vectory);
			}
		}
	}
	nodes_[0].move(this->movex,this->movey);
	//通过引入movex和movey两个属性记录每次运动的偏移值，当夹角大于135°时沿用上一次的偏移量
	checkSelfCollisions();
}

void Snake::update(sf::Time delta)
{
	//move();
	checkEdgeCollisions();
	//checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin())/*<-类型推导*/ toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;//如果头部位置和水果位置有重叠，那么水果位置即将被抹去
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();//播放
		grow(toRemove->getAddition());
		fruits.erase(toRemove);
	}
}

void Snake::grow(int addition){
    for(;addition>0;addition--){
		nodes_.push_back(SnakeNode(nodes_[nodes_.size() - 1].getPosition(),nodes_.size()));
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}//穿墙

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_){
		node.render(window);
	}
		
}
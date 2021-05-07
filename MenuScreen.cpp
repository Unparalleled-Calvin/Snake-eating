#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit"
		"\n\nPress [1] or [2] or [3] to change gridline-color"
		"\n\nPress [0] to close gridline-color"
		"\n\nPress [4] or [5] or [6] to change background-color");//设置指引文本
	text_.setColor(sf::Color(205,190,112));
	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(sf::Color(244,164,96));//SandyBrown色
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);//设置游戏介绍文本

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
	    snakeTextBounds.top + snakeTextBounds.height / 2);//这是对象所有坐标变化的中心点
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);//设置对象中心点的位置
	//设置文本的放置位置
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//更换这里的Space等按键就可以实现用其他按键控制
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());//asSeconds返回秒数，意思是每过1s，旋转1度

		if (static_cast<int>(snakeText_.getRotation()) == 10)//只让他旋转10度
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}//设置SNAKE旋转

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);//将元素绘制到窗口上去
}
#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);//设置帧率0.1s为一帧

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}//这段是为了让用户在没有按Esc的情况下也能安全退出

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);//重写虚函数的使用
}

void Game::render()
{
	drawbackground(window_);
	drawGridlines();
	int new_Gridlines_color = Gridlines_color;
	int new_background_color = background_color;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
		new_Gridlines_color = 1;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
		new_Gridlines_color = 2;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
		new_Gridlines_color = 3;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
		new_Gridlines_color = 0;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
		new_background_color = 4;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
		new_background_color = 5;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
		new_background_color = 6;
	}
	if(new_Gridlines_color!=Gridlines_color){
		Gridlines_color = new_Gridlines_color;
		setGridlines();
	}
	if(new_background_color!=background_color){
		background_color = new_background_color;
	}
	Game::Screen->render(window_);
	window_.display();
}

void Game::setGridlines(){
	Gridlines.clear();
	sf::Color linecolor;
	switch(Gridlines_color){
		case 1:
        linecolor = sf::Color(0,134,139);//绿松石色
		break;
		case 2:
        linecolor = sf::Color(154,205,50);//橄榄色
		break;
		case 3:
        linecolor = sf::Color(205,92,92);//印第安红
		break;
		case 0:
        linecolor = sf::Color::Transparent;//透明
		break;
	}
	for(int i=0;i<Width/grid;i++){
        sf::RectangleShape yline;
		yline.setSize(sf::Vector2f(1,Height));
		yline.setFillColor(linecolor);//设置颜色
		yline.setPosition(sf::Vector2f(i*grid,0));
        Gridlines.push_back(yline);
	}
	for(int i=0;i<Height/grid;i++){
        sf::RectangleShape xline;
		xline.setSize(sf::Vector2f(Width,1));
		xline.setFillColor(linecolor);//设置颜色
		xline.setPosition(sf::Vector2f(0,i*grid));
        Gridlines.push_back(xline);
	}
}

void Game::drawbackground(sf::RenderWindow &window_){
	switch(background_color){
		case 4:
		window_.clear(sf::Color(255,255,240));//象牙色
		break;
		case 5:
		window_.clear(sf::Color(205,145,158));//粉色
		break;
		case 6:
		window_.clear(sf::Color(139,131,120));//古董白
		break;
	}
}

void Game::drawGridlines(){
	for(auto &eachline:Gridlines){
		window_.draw(eachline);
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	setGridlines();
	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();//restart:归零时钟并返回逝去的时间
		timeSinceLastUpdate += delta;
		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);//如果距离上一次更新时间超过一帧时间，那么就立刻更新，传入的参数是1帧的时间
		}

		render();
	}
}
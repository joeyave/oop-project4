#pragma once
#include <SFML/Graphics.hpp>




inline void mouse_move(sf::Shape* body, sf::RenderWindow& wnd)
{
	if (body)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mouse_position;
			mouse_position.x = sf::Mouse::getPosition(wnd).x;
			mouse_position.y = sf::Mouse::getPosition(wnd).y;
			body->setPosition(mouse_position.x, mouse_position.y);
		}
	}
}

inline void collision_deformation(sf::Shape* shp1, sf::Shape* shp2)
{
	if (shp1->getGlobalBounds().intersects(shp2->getGlobalBounds()))
	{
		shp2->setScale(1.5f, 1.5f);
	}
}
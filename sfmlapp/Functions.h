#pragma once
#include <SFML/Graphics.hpp>

inline void window_boud_move(sf::Shape& body, sf::RenderWindow& wnd)
{
	if (body.getPosition().x < 0)
	{
		body.setPosition(sf::Vector2f(wnd.getSize().x, body.getPosition().y));
	}
	if (body.getPosition().x > wnd.getSize().x)
	{
		body.setPosition(sf::Vector2f(0.0f, body.getPosition().y));
	}
	if (body.getPosition().y > wnd.getSize().y)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, 0.0f));
	}
	if (body.getPosition().y < 0)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, wnd.getSize().y));
	}
}

inline void change_agregator_color(sf::Shape* shapes[4], sf::Color c)
{
	for (int i = 0; i < 4; i++)
	{
		if (shapes[i])
		{
			shapes[i]->setFillColor(c);
		}
	}
}

inline void keyboard_move(sf::Shape* body, sf::RenderWindow& wnd)
{
	if (body)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			body->move(-1.5f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			body->move(1.5f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			body->move(0.0f, -1.5f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			body->move(0.0f, 1.5f);
		}
	}
}

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

inline void make_invisible(sf::Shape* body, sf::RenderWindow& wnd)
{
	static sf::Color temp;
	if (body)
	{
		if (body->getFillColor() != sf::Color::Transparent)
		{
			temp = body->getFillColor();
			body->setFillColor(sf::Color::Transparent);
		}
		else
		{
			body->setFillColor(temp);
		}
	}
}

inline sf::Shape* select_shape(sf::Shape* shapes[], sf::RenderWindow& wnd)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(wnd).x;
	mouse_position.y = sf::Mouse::getPosition(wnd).y;

	for (int i = 0; i < 4; i++)
	{
		if (shapes[i] && shapes[i]->getGlobalBounds().contains(mouse_position))
		{
			return shapes[i];
		}
	}
	return nullptr;
}

inline void collision_deformation(sf::Shape* shp1, sf::Shape* shp2)
{
	if (shp1->getGlobalBounds().intersects(shp2->getGlobalBounds()))
	{
		shp2->setScale(1.5f, 1.5f);
	}
}
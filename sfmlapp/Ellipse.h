#pragma once
//#include <SFML/Graphics.hpp>
#include "Shape.h"

class Ellipse : public sf::Shape
{
public:
	Ellipse()
	{
		setToDefault();
		update();
	}
	
	Ellipse(const sf::Vector2f& rds)
	{
		radius = rds;
		update();
	}

	void setToDefault()
	{
		setRadius(sf::Vector2f(150.0f, 100.0f));
		setScale(1.0f, 1.0f);
		setFillColor(sf::Color::Yellow);
		setPosition(200, 1000);
		setOrigin(20, 200);
		update();
	}

	void setRadius(const sf::Vector2f& rds)
	{
		radius = rds;
		update();
	}

	const sf::Vector2f& getRadius() const
	{
		return radius;
	}

	std::size_t getPointCount() const override
	{
		return 30;
	}

	sf::Vector2f getPoint(std::size_t index) const override
	{
		static const float pi = 3.141592654f;

		const float angle = index * 2 * pi / getPointCount() - pi / 2;
		const float x = std::cos(angle) * radius.x;
		const float y = std::sin(angle) * radius.y;

		return {radius.x + x, radius.y + y};
	}

private:
	sf::Vector2f radius;
};


#pragma once
#include <SFML/Graphics.hpp>

class Ellipse : public sf::Shape
{
public:
	Ellipse(const sf::Vector2f& rds = sf::Vector2f(0.f, 0.f))
	{
		radius = rds;
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

	virtual std::size_t getPointCount() const
	{
		return 30;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / getPointCount() - pi / 2;
		float x = std::cos(angle) * radius.x;
		float y = std::sin(angle) * radius.y;

		return {radius.x + x, radius.y + y};
	}

private:
	sf::Vector2f radius;
};


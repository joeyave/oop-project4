#pragma once
#include "Rectangle.h"

class Line : public Rectangle
{
public:
	Line()
	{
		Line::setToDefault();
		update();
	}

	void setToDefault() override
	{
		setSize(sf::Vector2f(250.0f, 10.0f));
		setScale(1.0f, 1.0f);
		setFillColor(sf::Color::Cyan);
		setPosition(1700, 100);
		setOrigin(150 / 2, 2 / 2);
		update();
	}
};


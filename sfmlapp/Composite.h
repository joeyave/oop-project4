#pragma once
//#include "Graphics.hpp"
#include "Shape.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Composite : public sf::Shape
{
public:
	Composite()
	{
		update();
	}

	Composite(sf::Shape* shp)
	{
		add_shape(shp);
		update();
	}

	void add_shape(sf::Shape* shp)
	{
		shapes.push_back(shp);
		update();
	}

	virtual std::size_t getPointCount() const
	{
		for (auto& shape : shapes)
			return shape->getPointCount();
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		for (auto& shape : shapes)
			return shape->getPoint(index);
	}

	void setFillColor(const sf::Color& color)
	{
		for (auto& shape : shapes)
			shape->setFillColor(color);
	}

	const sf::Color& getFillColor() const
	{
		return shapes[0]->getFillColor();
	}

	void move(float offsetX, float offsetY) override
	{
		for (auto& shape : shapes)
			shape->move(offsetX, offsetY);
	}

	void move(const sf::Vector2f& offset) override
	{
		for (auto& shape : shapes)
			shape->move(offset);
	}

	void boundMoveActivate(sf::RenderWindow& wnd) override
	{
		for (auto& shape : shapes)
		{
			if (shape->getPosition().x < 0)
			{
				shape->setPosition(sf::Vector2f(wnd.getSize().x, shape->getPosition().y));
			}
			if (shape->getPosition().x > wnd.getSize().x)
			{
				shape->setPosition(sf::Vector2f(0.0f, shape->getPosition().y));
			}
			if (shape->getPosition().y > wnd.getSize().y)
			{
				shape->setPosition(sf::Vector2f(shape->getPosition().x, 0.0f));
			}
			if (shape->getPosition().y < 0)
			{
				shape->setPosition(sf::Vector2f(shape->getPosition().x, wnd.getSize().y));
			}
		}
	}

	const sf::Vector2f& getPosition() const override
	{
		return shapes[0]->getPosition();
	}

	bool intersectsWith(sf::Shape* shp, sf::RenderWindow& wnd) override
	{
		for(auto& shape : shapes)
		{
			if (shape->intersectsWith(shp, wnd))
				return true;
		}
		return false;
	}
	
	std::vector<sf::Shape*>* get_shapes()
	{
		return &shapes;
	}

	void setAlpha(sf::Uint8 index)
	{
		std::vector<sf::Color> colors;

		for (auto& shape : shapes)
			colors.push_back(shape->getFillColor());

		for (auto& color : colors)
			color.a = index;

		for (auto& shape : shapes)
		{
			shape->setFillColor(colors.back());
			colors.pop_back();
		}
	}

	sf::Uint8 containsTransparent()
	{
		for (auto& shape : shapes)
		{
			if (shape->getFillColor().a == 0)
				return true;
		}
		return false;
	}
	
	//sf::FloatRect getGlobalBounds() const
	//{
	//	std::vector<sf::FloatRect> vglobal_bounds;
	//	
	//	for (auto& shape : shapes)
	//	{
	//		vglobal_bounds.push_back(shape->getTransform().transformRect(getLocalBounds()));
	//	}
	//	
	//}

	bool selectedWithMouse(sf::RenderWindow& wnd) override
	{
		for(auto& shape : shapes)
		{
			if (shape->selectedWithMouse(wnd))
				return true;
		}

		return false;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		for (auto& shape : shapes)
		{
			if (shape)
				target.draw(*shape);
		}
	}

	std::vector<sf::Shape*> shapes;
};

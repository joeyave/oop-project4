#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <ostream>


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

	/// \li getPointCount must return the number of points of the shape
	/// \li getPoint must return the points of the shape


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

	void move(float offsetX, float offsetY)
	{
		for (auto& shape : shapes)
			shape->move(offsetX, offsetY);
	}

	void move(const sf::Vector2f& offset)
	{
		for (auto& shape : shapes)
			shape->move(offset);
	}

	const sf::Vector2f& getPosition() const
	{
		return shapes[0]->getPosition();
	}

	std::vector<sf::Shape*>* get_shapes()
	{
		return &shapes;
	}
	
private:
	std::vector<sf::Shape*> shapes;
};
#pragma once

// My Shape.
#include "Drawable.h"
#include "Transformable.h"

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace sf
{
	class SFML_GRAPHICS_API Shape : public Drawable, public Transformable
	{
	public:
		virtual ~Shape();
		void setTexture(const Texture* texture, bool resetRect = false);
		void setTextureRect(const IntRect& rect);
		virtual void setFillColor(const Color& color);
		void setOutlineColor(const Color& color);
		void setOutlineThickness(float thickness);
		const Texture* getTexture() const;
		const IntRect& getTextureRect() const;
		virtual const Color& getFillColor() const;
		const Color& getOutlineColor() const;
		float getOutlineThickness() const;
		virtual std::size_t getPointCount() const;
		virtual Vector2f getPoint(std::size_t index) const;

		virtual bool selectedWithMouse(sf::RenderWindow& wnd)
		{
			sf::Vector2f mouse_position;
			mouse_position.x = sf::Mouse::getPosition(wnd).x;
			mouse_position.y = sf::Mouse::getPosition(wnd).y;

			if (getGlobalBounds().contains(mouse_position))
				return true;

			return false;
		}

		virtual void boundMoveActivate(sf::RenderWindow& wnd)
		{
			if (getPosition().x < 0)
			{
				setPosition(sf::Vector2f(wnd.getSize().x, getPosition().y));
			}
			if (getPosition().x > wnd.getSize().x)
			{
				setPosition(sf::Vector2f(0.0f, getPosition().y));
			}
			if (getPosition().y > wnd.getSize().y)
			{
				setPosition(sf::Vector2f(getPosition().x, 0.0f));
			}
			if (getPosition().y < 0)
			{
				setPosition(sf::Vector2f(getPosition().x, wnd.getSize().y));
			}
		}

		virtual bool intersectsWith(sf::Shape* shp, sf::RenderWindow& wnd)
		{
			if (getGlobalBounds().intersects(shp->getGlobalBounds()))
				return true;
			return false;
		}

		virtual void setAlpha(const sf::Uint8 index)
		{
			Color color = getFillColor();
			color.a = index;
			setFillColor(color);
		}

		FloatRect getLocalBounds() const;
		virtual FloatRect getGlobalBounds() const;

	protected:
		Shape();
		void update();

	private:
		virtual void draw(RenderTarget& target, RenderStates states) const;
		void updateFillColors();
		void updateTexCoords();
		void updateOutline();
		void updateOutlineColors();

		const Texture* m_texture;
		IntRect        m_textureRect;
		Color          m_fillColor;
		Color          m_outlineColor;
		float          m_outlineThickness;
		VertexArray    m_vertices;
		VertexArray    m_outlineVertices;
		FloatRect      m_insideBounds;
		FloatRect      m_bounds;
	};

}

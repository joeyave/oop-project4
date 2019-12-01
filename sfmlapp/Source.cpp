
#include <iostream>
#include <vector>
#include <algorithm>

#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Composite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Line.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Lab 4!",
		sf::Style::Close | sf::Style::Titlebar);

	//My shapes.
	Rectangle my_rect;
	Line my_line;
	Circle my_circle;
	Ellipse my_ellipse;

	Composite container;

	// Shapes array.
	std::vector<sf::Shape*> vshapes;

	sf::Shape* shapes[4];
	for (auto& shape : shapes)
	{
		shape = nullptr;
	}

	// Pointer to the activated shape.
	sf::Shape* current_shape = nullptr;

	bool show_tail_switch = false;
	bool transparecy_switch = false;
	int color_switch = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Set current shape. Press MLK.
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mouse_position;
				mouse_position.x = sf::Mouse::getPosition(window).x;
				mouse_position.y = sf::Mouse::getPosition(window).y;

				for (auto& shape : vshapes)
				{
					if (shape->selectedWithMouse(window))
					{
						{
							std::cout << "single shape selected" << std::endl;
							current_shape = shape;
							break;
						}
					}
					else
					{
						std::cout << "nothing is selected" << std::endl;
						current_shape = nullptr;
					}
				}
			}

			// Visualize of remove shapes.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				if (!std::count(vshapes.begin(), vshapes.end(), &my_rect))
				{
					vshapes.push_back(&my_rect);
				}
				else
				{
					vshapes.erase(std::remove(vshapes.begin(),
						vshapes.end(), &my_rect), vshapes.end());
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				if (!std::count(vshapes.begin(), vshapes.end(), &my_line))
				{
					vshapes.push_back(&my_line);
				}
				else
				{
					vshapes.erase(std::remove(vshapes.begin(),
						vshapes.end(), &my_line), vshapes.end());
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				if (!std::count(vshapes.begin(), vshapes.end(), &my_ellipse))
				{
					vshapes.push_back(&my_ellipse);
				}
				else
				{
					vshapes.erase(std::remove(vshapes.begin(),
						vshapes.end(), &my_ellipse), vshapes.end());
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
			{
				if (!std::count(vshapes.begin(), vshapes.end(), &my_circle))
				{
					vshapes.push_back(&my_circle);
				}
				else
				{
					vshapes.erase(std::remove(vshapes.begin(),
						vshapes.end(), &my_circle), vshapes.end());
				}
			}

			// Restore shape to default settings.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				if (current_shape == dynamic_cast<sf::Shape*>(&my_rect))
				{
					my_rect.setToDefault();
				}
				if (current_shape == dynamic_cast<sf::Shape*>(&my_line))
				{
					my_line.setToDefault();
				}
				if (current_shape == dynamic_cast<sf::Shape*>(&my_ellipse))
				{
					my_ellipse.setToDefault();
				}
				if (current_shape == dynamic_cast<sf::Shape*>(&my_circle))
				{
					my_circle.setToDefault();
				}
			}

			// Change colour.
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			{
				sf::Color color = current_shape->getFillColor();

				switch (color_switch)
				{
				case 1:
					current_shape->setFillColor(sf::Color::White);
					container.setFillColor(sf::Color::White);
					color_switch++;
					break;
				case 2:
					current_shape->setFillColor(sf::Color::Blue);
					container.setFillColor(sf::Color::Blue);
					color_switch++;
					break;
				case 3:
					current_shape->setFillColor(sf::Color::Cyan);
					container.setFillColor(sf::Color::Cyan);
					color_switch++;
					break;
				case 4:
					current_shape->setFillColor(sf::Color::Green);
					container.setFillColor(sf::Color::Green);
					color_switch++;
					break;
				case 5:
					current_shape->setFillColor(sf::Color::Magenta);
					container.setFillColor(sf::Color::Magenta);
					color_switch++;
					break;
				default:
					color_switch = 1;
					current_shape->setFillColor(color);
					container.setFillColor(color);
					color_switch++;
					break;
				}
			}

			// Make invisible.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
			{
				if (current_shape)
					if (!transparecy_switch)
					{
						if (std::count(container.get_shapes()->begin(),
							container.get_shapes()->end(), current_shape))
						{
							container.setAlpha(0);
						}
						else
						{
							sf::Color color = current_shape->getFillColor();
							color.a = 0;
							current_shape->setFillColor(color);
						}

						transparecy_switch = true;
					}
					else
					{
						if (std::count(container.get_shapes()->begin(),
							container.get_shapes()->end(), current_shape))
						{
							// make container visible
							container.setAlpha(255);

						}
						else
						{
							sf::Color color = current_shape->getFillColor();
							color.a = 255;
							current_shape->setFillColor(color);
						}
						transparecy_switch = false;
					}
			}

			// Show tail when move.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
			{
				if (show_tail_switch == false)
					show_tail_switch = true;
				else
					show_tail_switch = false;
			}

			// Add shape to the container.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				// If container doesn't contain selected shape
				if (!std::count(container.get_shapes()->begin(),
					container.get_shapes()->end(),
					current_shape) && dynamic_cast<Composite*>(current_shape) != &container)
				{
					// add shape to the container.
					container.get_shapes()->push_back(current_shape);
					std::cout << "Shape added to the container!" << std::endl;

					// If shapes container doesn't contain container
					if (!std::count(vshapes.begin(), vshapes.end(), &container))
					{
						// add container to the shapes vector.
						vshapes.push_back(&container);
						std::cout << "container added to the shapes vector" << std::endl;
					}

					// Remove shape from the shapes vector.
					vshapes.erase(std::remove(vshapes.begin(),
						vshapes.end(), current_shape), vshapes.end());
					std::cout << "shape removed from the shapes vector" << std::endl;
				}
				else
				{
					// Remove and clean container. Push it's elements to the shapes vector.
					//if (!container.get_shapes()->empty())
					//	while (sf::Shape* s = container.get_shapes()->back())
					//	{
					//		vshapes.push_back(s);
					//		container.get_shapes()->pop_back();
					//	}

					for (auto& shape : *container.get_shapes())
					{
						vshapes.push_back(shape);
					}
					container.get_shapes()->clear();
					
					vshapes.erase(std::remove(vshapes.begin(),
						vshapes.end(), &container), vshapes.end());
					std::cout << "container removed from the shapes vector" << std::endl;

					//// Remove selected shape from the container.
					//container.get_shapes()->erase(std::remove(container.get_shapes()->begin(),
					//	container.get_shapes()->end(), current_shape), container.get_shapes()->end());
					//std::cout << "Shape removed from the container, added to the shapes vector" << std::endl;

					//// Add selected shape to the shapes vector.
					//vshapes.push_back(current_shape);

					//if (container.get_shapes()->empty())
					//{
					//	vshapes.erase(std::remove(vshapes.begin(),
					//		vshapes.end(), &container), vshapes.end());
					//	std::cout << "container removed from the shapes vector" << std::endl;
					//}
				}
			}
		}

		// Enable keyboard move for current shape.
		if (current_shape)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				current_shape->move(-1.5f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				current_shape->move(1.5f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				current_shape->move(0.0f, -1.5f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				current_shape->move(0.0f, 1.5f);
			}
		}

		// Keep moving after reaching window's bound.
		for (auto& shape : shapes)
		{
			if (shape)
			{
				if (shape->getPosition().x < 0)
				{
					shape->setPosition(sf::Vector2f(window.getSize().x, shape->getPosition().y));
				}
				if (shape->getPosition().x > window.getSize().x)
				{
					shape->setPosition(sf::Vector2f(0.0f, shape->getPosition().y));
				}
				if (shape->getPosition().y > window.getSize().y)
				{
					shape->setPosition(sf::Vector2f(shape->getPosition().x, 0.0f));
				}
				if (shape->getPosition().y < 0)
				{
					shape->setPosition(sf::Vector2f(shape->getPosition().x, window.getSize().y));
				}
			}
		}

		for (auto& shape : shapes)
		{
			if (current_shape && shape && current_shape != shape &&
				current_shape->getGlobalBounds().intersects(shape->getGlobalBounds()))
			{
				shape->setScale(1.5f, 1.5f);
			}
		}

		// Move to the clicked point.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (current_shape)
			{
				sf::Vector2f total_movement(sf::Mouse::getPosition((window)).x - current_shape->getPosition().x,
					sf::Mouse::getPosition((window)).y - current_shape->getPosition().y);
				current_shape->move(total_movement * (1.0f / 60.0f));
			}

			//else if (container.get_shapes()->capacity() != 0)
			//{
			//	sf::Vector2f total_movement(sf::Mouse::getPosition((window)).x - container.getPosition().x,
			//		sf::Mouse::getPosition((window)).y - container.getPosition().y);
			//	container.move(total_movement * (1.0f / 60.0f));
			//}
		}

		if (show_tail_switch == false)
			window.clear();

		for (auto& shape : vshapes)
			window.draw(*shape);

		window.display();
	}

	return 0;
}

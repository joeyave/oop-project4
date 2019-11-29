#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Rectangle.h"
#include "Circle.h"
#include "Functions.h"
#include "Ellipse.h"
#include "Composite.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Lab 4!",
		sf::Style::Close | sf::Style::Titlebar);

	//My shapes.
	Rectangle my_rect;
	Rectangle my_line;
	Circle my_circle;
	Ellipse my_ellipse;

	// Shapes array.
	sf::Shape* shapes[4];
	for (auto& shape : shapes)
	{
		shape = nullptr;
	}

	Composite container;


	// Pointer to the activated shape.
	sf::Shape* curr_shape = nullptr;

	// Show or hide tail.
	bool show_tail = false;

	// For switching color.
	int color_switch = 1;
	int transparecy_switch = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Visualize of remove shapes.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				if (shapes[0] == nullptr)
				{
					my_rect.setSize(sf::Vector2f(100, 100));
					my_rect.setFillColor(sf::Color::Blue);
					my_rect.setPosition(150, 150);
					my_rect.setOrigin(100 / 2, 100 / 2);
					shapes[0] = &my_rect;
				}
				else
				{
					shapes[0] = nullptr;
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				if (shapes[1] == nullptr)
				{
					my_line.setSize(sf::Vector2f(250.0f, 10.0f));
					my_line.setFillColor(sf::Color::Cyan);
					my_line.setPosition(1700, 100);
					my_line.setOrigin(150 / 2, 2 / 2);
					shapes[1] = &my_line;
				}
				else
					shapes[1] = nullptr;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				if (shapes[2] == nullptr)
				{
					my_ellipse.setRadius(sf::Vector2f(150.0f, 100.0f));
					my_ellipse.setFillColor(sf::Color::Yellow);
					my_ellipse.setPosition(200, 1000);
					my_ellipse.setOrigin(20, 200);
					shapes[2] = &my_ellipse;
				}
				else
					shapes[2] = nullptr;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
			{
				if (shapes[3] == nullptr)
				{
					my_circle.setRadius(200.0f);
					my_circle.setFillColor(sf::Color::Magenta);
					my_circle.setPosition(1700, 760);
					my_circle.setOrigin(200, 200);
					shapes[3] = &my_circle;
				}
				else
					shapes[3] = nullptr;
			}

			// Restore shape to default settings.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				if ((curr_shape == dynamic_cast<sf::Shape*>(&my_rect)))
				{
					my_rect.setSize(sf::Vector2f(100, 100));
					my_rect.setScale(1.0f, 1.0f);
					my_rect.setFillColor(sf::Color::Blue);
					my_rect.setPosition(150, 150);
					my_rect.setOrigin(100 / 2, 100 / 2);
				}
				if ((curr_shape == dynamic_cast<sf::Shape*>(&my_line)))
				{
					my_line.setSize(sf::Vector2f(250.0f, 10.0f));
					my_line.setScale(1.0f, 1.0f);
					my_line.setFillColor(sf::Color::Cyan);
					my_line.setPosition(1700, 100);
					my_line.setOrigin(150 / 2, 2 / 2);
				}
				if ((curr_shape == dynamic_cast<sf::Shape*>(&my_ellipse)))
				{
					my_ellipse.setRadius(sf::Vector2f(150.0f, 100.0f));
					my_ellipse.setScale(1.0f, 1.0f);
					my_ellipse.setFillColor(sf::Color::Yellow);
					my_ellipse.setPosition(200, 1000);
					my_ellipse.setOrigin(20, 200);
				}
				if ((curr_shape == dynamic_cast<sf::Shape*>(&my_circle)))
				{
					my_circle.setRadius(200.0f);
					my_circle.setScale(1.0f, 1.0f);
					my_circle.setFillColor(sf::Color::Magenta);
					my_circle.setPosition(1700, 760);
					my_circle.setOrigin(200, 200);
				}
			}

			// Change colour.
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			{
				switch (color_switch)
				{
				case 1:
					curr_shape->setFillColor(sf::Color::White);
					container.setFillColor(sf::Color::White);
					color_switch++;
					break;
				case 2:
					curr_shape->setFillColor(sf::Color::Blue);
					container.setFillColor(sf::Color::Blue);
					color_switch++;
					break;
				case 3:
					curr_shape->setFillColor(sf::Color::Cyan);
					container.setFillColor(sf::Color::Cyan);
					color_switch++;
					break;
				case 4:
					curr_shape->setFillColor(sf::Color::Green);
					container.setFillColor(sf::Color::Green);
					color_switch++;
					break;
				case 5:
					curr_shape->setFillColor(sf::Color::Magenta);
					container.setFillColor(sf::Color::Magenta);
					color_switch++;
					break;
				default:
					color_switch = 1;
					curr_shape->setFillColor(sf::Color::Red);
					container.setFillColor(sf::Color::Red);
					color_switch++;
					break;
				}
			}

			// Make invisible.
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				static sf::Color temp;

				curr_shape = select_shape(shapes, window);

				if (container.get_shapes()->capacity() > 0)
				{
					if (container.getFillColor() != sf::Color::Transparent)
					{
						temp = container.getFillColor();
						container.setFillColor(sf::Color::Transparent);
					}
					else
					{
						container.setFillColor(temp);
					}
				}
				else
					if (curr_shape)
						make_invisible(*curr_shape, window);
			}

			// Show tail when move.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
			{
				if (show_tail == false)
					show_tail = true;
				else
					show_tail = false;
			}

			// Add shape to the container.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				if (!std::count(container.get_shapes()->begin(),
					container.get_shapes()->end(),
					curr_shape))
				{
					container.get_shapes()->push_back(curr_shape);
					std::cout << "Shape added!" << std::endl;
				}
				else
				{
					container.get_shapes()->erase(std::remove(container.get_shapes()->begin(),
						container.get_shapes()->end(), curr_shape), container.get_shapes()->end());
					std::cout << "Shape removed" << std::endl;
				}
			}

		}

		// Set current shape. Press MLK.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			curr_shape = select_shape(shapes, window);

		// Enable keyboard move for current shape.
		if (curr_shape)
			keyboard_move(*curr_shape, window);

		// Enable keyboard move for the container.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			container.move(-1.5f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			container.move(1.5f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			container.move(0.0f, -1.5f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			container.move(0.0f, 1.5f);
		}

		// Keep moving after reaching window's bound.
		for (auto& shape : shapes)
		{
			if (shape)
				window_boud_move(*shape, window);
		}

		// Deformate when collide.
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == i || !shapes[i] || !shapes[j])
					continue;
				collision_deformation(shapes[i], shapes[j]);
			}
		}

		// Move to the clicked point.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (curr_shape)
			{
				sf::Vector2f total_movement(sf::Mouse::getPosition((window)).x - curr_shape->getPosition().x,
					sf::Mouse::getPosition((window)).y - curr_shape->getPosition().y);
				curr_shape->move(total_movement * (1.0f / 60.0f));
			}

			else if (container.get_shapes()->capacity() != 0)
			{
				sf::Vector2f total_movement(sf::Mouse::getPosition((window)).x - container.getPosition().x,
					sf::Mouse::getPosition((window)).y - container.getPosition().y);
				container.move(total_movement * (1.0f / 60.0f));
			}
		}

		if (show_tail == false)
			window.clear();

		// Draw here:
		for (int i = 0; i < 4; i++)
		{
			if (shapes[i])
				window.draw(*shapes[i]);
		}

		window.display();
	}

	return 0;
}

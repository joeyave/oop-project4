#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rectangle.h"
#include "Circle.h"
#include "Functions.h"
#include "Ellipse.h"
#include "Container.h"

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

	// Pointer to the activated shape.
	sf::Shape* curr_shape = nullptr;

	// Show or hide tail.
	bool show_tail = false;

	bool is_aggregate = false;

	// For switching color.
	int color_switch = 1;

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
					if (!is_aggregate)
						curr_shape->setFillColor(sf::Color::White);
					else
						change_agregator_color(shapes, sf::Color::White);
					color_switch++;
					break;
				case 2:
					if (!is_aggregate)
						curr_shape->setFillColor(sf::Color::Green);
					else
						change_agregator_color(shapes, sf::Color::Green);
					color_switch++;
					break;
				case 3:
					if (!is_aggregate)
						curr_shape->setFillColor(sf::Color::Red);
					else
						change_agregator_color(shapes, sf::Color::Red);
					color_switch++;
					break;
				case 4:
					if (!is_aggregate)
						curr_shape->setFillColor(sf::Color::Magenta);
					else
						change_agregator_color(shapes, sf::Color::Magenta);
					color_switch++;
					break;
				case 5:
					if (!is_aggregate)
						curr_shape->setFillColor(sf::Color::Cyan);
					else
						change_agregator_color(shapes, sf::Color::Cyan);
					color_switch++;
					break;
				default:
					color_switch = 1;
					if (!is_aggregate)
						curr_shape->setFillColor(sf::Color::White);
					else
						change_agregator_color(shapes, sf::Color::White);
					color_switch++;
					break;
				}
			}

			// Make invisible.
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				if (!is_aggregate)
				{
					curr_shape = select_shape(shapes, window);
					make_invisible(curr_shape, window);
				}
				else
				{
					for (auto& shape :shapes)
					{
						make_invisible(shape, window);
					}
				}
			}

			// Show tail when move.
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
			{
				if (show_tail == false)
					show_tail = true;
				else
					show_tail = false;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				if (!is_aggregate)
					is_aggregate = true;
				else
					is_aggregate = false;
			}
		}


		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		//{
		//	for (auto& shape : shapes)
		//		shape->move(-1.5f, 0.0f);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		//{
		//	for (auto& shape : shapes)
		//		shape->move(1.5f, 0.0f);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		//{
		//	for (auto& shape : shapes)
		//		shape->move(0.0f, -1.5f);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		//{
		//	for (auto& shape : shapes)
		//		shape->move(0.0f, 1.5f);
		//}


		// Set current shape. Press MLK.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			curr_shape = select_shape(shapes, window);

		// Enable keyboard move for current shape.
		if (is_aggregate)
		{
			for (auto& shape : shapes)
			{
				keyboard_move(shape, window);
			}
		}
		else
			keyboard_move(curr_shape, window);

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
			if (curr_shape && !!is_aggregate)
			{
				sf::Vector2f total_movement(sf::Mouse::getPosition((window)).x - curr_shape->getPosition().x,
					sf::Mouse::getPosition((window)).y - curr_shape->getPosition().y);
				curr_shape->move(total_movement * (1.0f / 60.0f));
			}
			else
			{
				for (auto& shape : shapes)
				{
					if (shape)
					{
						sf::Vector2f total_movement(sf::Mouse::getPosition((window)).x - shape->getPosition().x,
							sf::Mouse::getPosition((window)).y - shape->getPosition().y);
						shape->move(total_movement * (1.0f / 60.0f));
					}
				}
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

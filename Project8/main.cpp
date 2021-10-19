#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
sf::Vector2f intersects(sf::VertexArray& ray, sf::VertexArray& wall) {
	const float x1 = wall[0].position.x;
	const float y1 = wall[0].position.y;
	const float x2 = wall[1].position.x;
	const float y2 = wall[1].position.y;

	const float x3 = ray[0].position.x;
	const float y3 = ray[0].position.y;
	const float x4 = ray[1].position.x;
	const float y4 = ray[1].position.y;

	const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// wall and ray are parallel
	if (den == 0) {
		return { -10, -10 };
	}
	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t > 0 && t < 1 && u > 0) {
		sf::Vector2f intersection_dot;
		intersection_dot.x = x1 + t * (x2 - x1);
		intersection_dot.y = y1 + t * (y2 - y1);
		return intersection_dot;
	}
	else
		return { -10, -10 };
}
void set_ray_direction(sf::VertexArray& ray) {
	ray[1].position.x = sf::Mouse::getPosition().x;
	ray[1].position.y = sf::Mouse::getPosition().y;
}
int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "Ray casting");

	sf::VertexArray wall(sf::Lines, 2);
	wall[0].position = sf::Vector2f(250, 50);
	wall[1].position = sf::Vector2f(250, 300);

	sf::VertexArray ray(sf::Lines, 2);
	ray[0].position = sf::Vector2f(100, 100);
	ray[1].position = sf::Vector2f(200, 200);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// create circle_shape for visualization a dot of intersection
		sf::CircleShape dot_of_intersection;
		dot_of_intersection.setRadius(5.f);
		dot_of_intersection.setFillColor(sf::Color::Red);
		set_ray_direction(ray);
		sf::Vector2f intersection_dot = intersects(ray, wall);
		dot_of_intersection.setPosition(intersection_dot);
		dot_of_intersection.setPosition(dot_of_intersection.getPosition().x - dot_of_intersection.getRadius(), dot_of_intersection.getPosition().y - dot_of_intersection.getRadius());

		window.clear();
		window.draw(dot_of_intersection);
		window.draw(ray);
		window.draw(wall);
		window.display();
	}
}
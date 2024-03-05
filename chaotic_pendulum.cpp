
#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159f; // Pi
const float g = 0.001f; // Gravitational acceleration
const float timeScale = 0.05f;

const float m1 = 100; // Mass of the first ball
const float m2 = 5; // Mass of the second ball
const float r1 = 200; // Length of first pendulum
const float r2 = 100; // Length of Second pendulum
float a1 = PI / 2; // Starting angle of the first pendulum
float a2 = PI; // Starting angle of the second pendulum
float a1_v = 0; // Angular velocity of the first pendulum
float a2_v = 0; // Angular velocity of the second pendulum
float a1_a = 0; // Angular acceleration of the first pendulum
float a2_a = 0; // Angular acceleration of second pendulum

std::vector<sf::Vector2f> path1; 
std::vector<sf::Vector2f> path2; 
const int pathLength = 200; 

void update() {
    float num1, num2, num3, num4, den;

    num1 = -g * (2 * m1 + m2) * sin(a1);
    num2 = -m2 * g * sin(a1 - 2 * a2);
    num3 = -2 * sin(a1 - a2) * m2;
    num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2);
    den = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
    a1_a = (num1 + num2 + num3 * num4) / den;

    num1 = 2 * sin(a1 - a2);
    num2 = (a1_v * a1_v * r1 * (m1 + m2));
    num3 = g * (m1 + m2) * cos(a1);
    num4 = a2_v * a2_v * r2 * m2 * cos(a1 - a2);
    den = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
    a2_a = (num1 * (num2 + num3 + num4)) / den;

    a1_v += a1_a * timeScale;
    a2_v += a2_a * timeScale;
    a1 += a1_v * timeScale;
    a2 += a2_v * timeScale;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Kaotik Çift Sarkaç");
    window.setFramerateLimit(0);

    sf::Vector2f pivot(400, 400); 
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        update();

        sf::Vector2f firstPendulumPos = pivot + sf::Vector2f(r1 * sin(a1), r1 * cos(a1));
        sf::Vector2f secondPendulumPos = firstPendulumPos + sf::Vector2f(r2 * sin(a2), r2 * cos(a2));

        path1.push_back(firstPendulumPos);
        path2.push_back(secondPendulumPos);
        if (path1.size() > pathLength) path1.erase(path1.begin());
        if (path2.size() > pathLength) path2.erase(path2.begin());

        // Drawings
        sf::VertexArray lines(sf::LinesStrip, 3);
        lines[0].position = pivot;
        lines[1].position = firstPendulumPos;
        lines[2].position = secondPendulumPos;
        lines[0].color = sf::Color::White;
        lines[1].color = sf::Color::White;
        lines[2].color = sf::Color::White;

        sf::CircleShape bob1(10.f);
        bob1.setPosition(firstPendulumPos - sf::Vector2f(10.f, 10.f));
        bob1.setFillColor(sf::Color::Red);

        sf::CircleShape bob2(10.f);
        bob2.setPosition(secondPendulumPos - sf::Vector2f(10.f, 10.f));
        bob2.setFillColor(sf::Color::Green);

        window.clear();

        for (size_t i = 0; i < path1.size(); ++i) {
            sf::CircleShape point(2);
            point.setPosition(path1[i]);
            point.setFillColor(sf::Color(255, 0, 0, i * 255 / path1.size())); 
            window.draw(point);
        }
        for (size_t i = 0; i < path2.size(); ++i) {
            sf::CircleShape point(2);
            point.setPosition(path2[i]);
            point.setFillColor(sf::Color(0, 255, 0, i * 255 / path2.size())); 
            window.draw(point);
        }

        window.draw(lines);
        window.draw(bob1);
        window.draw(bob2);
        window.display();

    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include<iostream>
#include "SoundPool.cpp"


float distance(sf::Vector2f a, sf::Vector2f b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
    
int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Delay ile Yarýçapý Artan Top");
    window.setFramerateLimit(60);
    SoundPool soundPool;


    sf::SoundBuffer buffer;
    buffer.loadFromFile("bounce.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);


    sf::CircleShape circle(250.f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(4.f);
    circle.setOutlineColor(sf::Color::White);
    circle.setPosition(250.f, 250.f);

    sf::CircleShape ball(5.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(385.f, 285.f);

    float velocityX = 5.f, velocityY = 5.f;
    float gravity = 0.f;
    float bounceFactor = -1.f;
    bool isMoving = false;
    sf::Clock clock; 
    float delaySeconds = 0.0; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                isMoving = true; 
            }
        }

        if (isMoving) {
            velocityY += gravity;
            ball.move(velocityX, velocityY);
        }

        sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
        sf::Vector2f ballCenter = ball.getPosition() + sf::Vector2f(ball.getRadius(), ball.getRadius());

        float dist = distance(ballCenter, circleCenter);

        if (dist > (circle.getRadius() - ball.getRadius())) {
            if (isMoving) {
                soundPool.play(buffer);
                float deltaX = ballCenter.x - circleCenter.x;
                float deltaY = ballCenter.y - circleCenter.y;
                float angle = atan2(deltaY, deltaX)+0.15;
                float speed = sqrt(velocityX * velocityX + velocityY * velocityY) * bounceFactor;
                velocityX = cos(angle) * speed;
                velocityY = sin(angle) * speed;
                
                if (clock.getElapsedTime().asSeconds() > delaySeconds) {
                    ball.setRadius(ball.getRadius()+3.f);
                    ball.setPosition(ball.getPosition().x - 3.f, ball.getPosition().y - 3.f);
                    if (ball.getRadius() >= circle.getRadius()) {

                        isMoving = false;
                        ball.setPosition(248.f, 149.f);
                        
                    }
                    clock.restart();
                }
            }

        }
        else {
            if (clock.getElapsedTime().asSeconds() > delaySeconds) {
                clock.restart(); 
            }
        }

        window.clear();
        window.draw(circle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
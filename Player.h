#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include <math.h>

#include <iostream>
using namespace std;


class Player
{
    public:
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f Position);
        virtual ~Player();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

            sf::Vector2f GetPosition();

            void setSpeed(float _speed);

            void setBodyPosition(float x, float y);

            sf::RectangleShape getBody();

            void CheckActivePlatform(Platform &platform);
            void RectCheckCollision(Platform &platform);

    private:
        sf::RectangleShape body;
        Animation animation;
        unsigned int row;
        float speed, def_Speed;
        bool faceRight;
        bool hitTheFloor;
        sf::Vector2f velocity;
        float jumpHeight;
        sf::Vector2f collisionDirection;
};


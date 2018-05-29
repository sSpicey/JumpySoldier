#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include <math.h>
#include <iostream>
#include "Projectile.h"

#include <vector>

using namespace std;


class Player
{
    private:
        Animation animation;
        Projectile projectile;
        vector<Projectile> vectProj;

    public:
        //ctor dtor
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Texture* projTexture);
        virtual ~Player();

        //sets
        void setSpeed(float _speed);
        void setBodyPosition(float x, float y);

        //gets
        sf::RectangleShape getBody();
        sf::Vector2f GetPosition();
        bool getFaceRight();

        //interacoes com o ambiente
        //do personagem
        void CheckActivePlatform(Platform &platform);
        void StaticCheckCollision(Platform &platform);
        void MovableCheckCollision(Platform &platform, float mass);
        //do tiro
        void Projectile_CheckCollision(sf::RectangleShape target);
        void Projectile_CheckCollision_Damage(sf::RectangleShape target, float &damage);


        //Atualizacao e grafico personagem
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);


        //Atualizacao e grafico tiro
        void Projectile_Update(float deltaTime);
        void Projectile_Draw(sf::RenderWindow& window);

    public:
        float damage;

    private:
        unsigned int i;
        sf::RectangleShape body;
        unsigned int row;
        float speed;
        bool faceRight;
        bool hitTheFloor;
        sf::Vector2f velocity;
        float jumpHeight;

        //CD == cooldown
        float shootCD;
        float jumpCD;

        //sem uso
        float def_Speed;
        sf::Vector2f collisionDirection;
        sf::Vector2f projVelocity;
};


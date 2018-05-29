#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

#include "Animation.h"

class Projectile
{
    private:
        Animation animation;

    public:
        //ctor dtor
        Projectile(sf::Texture* projTexture);
        virtual ~Projectile();

        //sets
        void setSpeed(float _speed);
        void setBodyPosition(sf::Vector2f playerPos, bool faceRight);
        void setFaceRight(bool faceRight);
        void addVelocity(sf::Vector2f velocity);

        //gets
        sf::Vector2f GetPosition();
        sf::RectangleShape getBody();

        //interacoes com o ambiente
        void CheckCollision(sf::RectangleShape target);
        void CheckCollision_Damage(sf::RectangleShape target, float &damage);

        //Atualizacao e grafico tiro
        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

        //usados em Projectile.cpp e Player.cpp
        bool collision;
        float duration;
        float totalTime;

        //SEM USO
        //void setVelocityY(float y);

    private:
        sf::RectangleShape body;
        float speed;
        bool faceRight;
        sf::Vector2f velocity;
        sf::Vector2f iniPosition;

        //sem uso
        float def_Speed;
};

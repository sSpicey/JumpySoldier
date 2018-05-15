#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

using namespace std;

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    float def_Speed = 500.0f;

    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/Player_tex.png");

    sf::Texture groundTexture;
    groundTexture.loadFromFile("textures/ground.png");

    sf::Texture bushTexture;
    bushTexture.loadFromFile("textures/bush.png");

    sf::Texture floorTexture;
    floorTexture.loadFromFile("textures/floor.png");

    Player player(&playerTexture, sf::Vector2u(3, 4), 0.1f, def_Speed);

    Platform ground(&groundTexture, sf::Vector2f(576.0f, 156.0f), sf::Vector2f(1020.0f, 0.0f));
    Platform ground2(&groundTexture, sf::Vector2f(576.0f, 156.0f), sf::Vector2f(1596.0f, 156.0f));
    Platform ground3(&groundTexture, sf::Vector2f(576.0f, 156.0f), sf::Vector2f(444.0f, -156.0f));
    Platform bush(&bushTexture, sf::Vector2f(468.0f, 140.0f), sf::Vector2f(500.0f, 10.0f));
    Platform floor(&floorTexture, sf::Vector2f(576.0f, 36.0f), sf::Vector2f(1020.0f, -95.0f));


    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        player.Update(deltaTime);
        view.setCenter(player.GetPosition());
        player.RectCheckCollision(ground);
        player.RectCheckCollision(ground2);
        player.RectCheckCollision(ground3);

        player.CheckActivePlatform(ground);
        player.CheckActivePlatform(ground2);
        player.CheckActivePlatform(ground3);

        cout << "Plataforma ground " << ground.get_isActivePlatform() << endl;

        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        floor.Draw(window);
        player.Draw(window);
        ground.Draw(window);
        ground2.Draw(window);
        ground3.Draw(window);
        bush.Draw(window);


        window.display();
    }

    return 0;
}

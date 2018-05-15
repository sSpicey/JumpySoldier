#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
    public:
        Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
        virtual ~Platform();

        void Draw(sf::RenderWindow& window);

        sf::RectangleShape getBody()
        {
            return body;
        }

        bool get_isActivePlatform();
        void set_isActivePlatform(bool activePlatform);

    private:
        sf::RectangleShape body;
        bool isActivePlatform;
};

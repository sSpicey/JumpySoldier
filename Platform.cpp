#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
    isActivePlatform = false;
}

Platform::~Platform()
{
    //dtor
}

void Platform::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

bool Platform::get_isActivePlatform()
{
    return isActivePlatform;
}

void Platform::set_isActivePlatform(bool activePlatform)
{
    isActivePlatform = activePlatform;
}

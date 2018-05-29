#include "Player.h"

static const float sCD = 0.25f;
static const float jCD = 0.5f;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Texture* projTexture):
        animation(texture, imageCount, switchTime), projectile(projTexture)
{
        this->speed = speed;
        row = 0;
        faceRight = true;
        setBodyPosition(400.0f, -400.0f);

        shootCD = sCD;
        jumpCD = jCD;

        texture->setSmooth(true);
        body.setSize(sf::Vector2f(100.0f, 150.0f));
        body.setOrigin(body.getSize()/2.0f);
        body.setTexture(texture);

        damage = 0.0f;
}

Player::~Player()
{
    //dtor
}

void Player::Update(float deltaTime)
{
    velocity.x = 0.0f;
    jumpHeight = 180.0f;
    shootCD += deltaTime;
    jumpCD += deltaTime;

    //GRAVIDADE
    velocity.y += 981.0f * deltaTime;

    //MOVIMENTO
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += speed;
    }

    //PULO
    if (jumpCD >= jCD)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hitTheFloor == true)
        {
            velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
            hitTheFloor = false;
            jumpCD = 0.0f;
        }
    }

    //TIRO
    if (shootCD >= sCD)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            vectProj.push_back(projectile);
            vectProj[vectProj.size() - 1].addVelocity(velocity);
            shootCD = 0.0f;
            vectProj[vectProj.size() - 1].setFaceRight(getFaceRight());
            vectProj[vectProj.size() - 1].setBodyPosition(body.getPosition(), getFaceRight());
        }
    }

    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].totalTime += deltaTime;

        if(vectProj[i].totalTime >= vectProj[i].duration)
        {
            vectProj.erase (vectProj.begin()+i);
            cout << vectProj.size() << endl;
        }
    }

    if(hitTheFloor == true)
    {
        velocity.y = 0.0;
    }

    if(velocity.x == 0.0f)
    {
        row = 1;
    }

    else
    {
        row = 2;

        if(velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else
        {
            faceRight = false;
        }
    }

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::Vector2f Player::GetPosition()
{
    return body.getPosition();
}

void Player::setSpeed(float _speed)
{
    speed = _speed;
}

void Player::setBodyPosition(float x, float y)
{
    body.setPosition(x, y);
}

sf::RectangleShape Player::getBody()
{
    return body;
}

void Player::CheckActivePlatform(Platform &platform)
{
    if(body.getPosition().x > platform.getBody().getPosition().x + (platform.getBody().getSize().x / 2)  ||  body.getPosition().x < platform.getBody().getPosition().x - (platform.getBody().getSize().x / 2))
        platform.set_isActivePlatform(false);

    else
        platform.set_isActivePlatform(true);

    if(platform.get_isActivePlatform() == true)
    {
        if((body.getPosition().y - (platform.getBody().getPosition().y + platform.getBody().getSize().y / 2) < -250.0f))
        hitTheFloor = false;
    }
}

void Player::StaticCheckCollision(Platform &platform)
{
    if(body.getGlobalBounds().intersects(platform.getBody().getGlobalBounds()))
    {
        if(body.getPosition().y > platform.getBody().getPosition().y + platform.getBody().getSize().y / 2)
        {
            body.move(0.0, 1.0);
            velocity.y = 0.0f;
        }

        else
        if(body.getPosition().y < platform.getBody().getPosition().y - platform.getBody().getSize().y / 2)
        {
            body.move(0.0, - 1.0);
            //velocity.y = 0.0f;
            hitTheFloor = true;
        }

        else
        if(body.getPosition().x < platform.getBody().getPosition().x - platform.getBody().getSize().x / 2)
        {
            body.move(- 1.0, 0.0);
            velocity.x = 0.0f;
        }

        else
        if(body.getPosition().x > platform.getBody().getPosition().x + platform.getBody().getSize().x / 2)
        {
            body.move(1.0, 0.0);
            velocity.x = 0.0f;
        }
    }
}

void Player::Projectile_CheckCollision(sf::RectangleShape target)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].CheckCollision(target);

        if(vectProj[i].collision == true)
        {
            vectProj.erase (vectProj.begin()+i);
            vectProj.shrink_to_fit();
        }
    }
}

void Player::Projectile_CheckCollision_Damage(sf::RectangleShape target, float &damage)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].CheckCollision_Damage(target, damage);

        if(vectProj[i].collision == true)
        {
            vectProj.erase (vectProj.begin()+i);
            vectProj.shrink_to_fit();
        }
    }
}

void Player::Projectile_Update(float deltaTime)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].Update(deltaTime);
    }
}

void Player::Projectile_Draw(sf::RenderWindow& window)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].Draw(window);
    }
}

bool Player::getFaceRight()
{
    return faceRight;
}

void Player::MovableCheckCollision(Platform &platform, float mass)
{
    if(abs(mass) > 10.0)
        mass = 10.0f;

    if(body.getGlobalBounds().intersects(platform.getBody().getGlobalBounds()))
    {

        if(body.getPosition().y > platform.getBody().getPosition().y + platform.getBody().getSize().y / 2)
        {
            body.move(0.0, 1.0);
            velocity.y = 0.0f;
        }

        else
        if(body.getPosition().y < platform.getBody().getPosition().y - platform.getBody().getSize().y / 2)
        {
            body.move(0.0, - 1.0);
            velocity.y = 0.0f;
            hitTheFloor = true;
        }

        else
        if(body.getPosition().x < platform.getBody().getPosition().x - platform.getBody().getSize().x / 2)
        {
            body.move(- 1.0, 0.0);
            platform.bodyMove(10.0 - abs(mass) , 0.0f);
            velocity.x = 0.0f;
        }

        else
        if(body.getPosition().x > platform.getBody().getPosition().x + platform.getBody().getSize().x / 2)
        {
            body.move(1.0, 0.0);
            platform.bodyMove(-(10.0 - abs(mass)) , 0.0f);
            velocity.x = 0.0f;
        }
    }
}

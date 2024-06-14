#pragma once
#include <SFML/Graphics.hpp>

class LCollisionBase
{
protected:
    std::shared_ptr<sf::Shape> CollisionShape = nullptr;

public:
    virtual ~LCollisionBase() = default;
    virtual bool CheckCollision(const std::shared_ptr<LCollisionBase>& other) const = 0;

    void SetPosition(const sf::Vector2f& position) const
    {
        CollisionShape->setPosition(position);
    }

    void SetRotation(float rotation) const
    {
        CollisionShape->setRotation(rotation);
    }

    void SetScale(const sf::Vector2f& scale) const
    {
        CollisionShape->setScale(scale);
    }

    sf::FloatRect GetBounds() const
    {
        return CollisionShape->getGlobalBounds();
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(*CollisionShape);
    }
};

class LBoxCollisionComponent : public LCollisionBase
{
public:
    LBoxCollisionComponent(const sf::Vector2f& size)
    {
        CollisionShape = std::make_shared<sf::RectangleShape>(size);
        CollisionShape->setFillColor(sf::Color::Transparent);
        CollisionShape->setOutlineThickness(2);
        CollisionShape->setOutlineColor(sf::Color::Red);
    }

    bool CheckCollision(const std::shared_ptr<LCollisionBase>& other) const override
    {
        return CollisionShape->getGlobalBounds().intersects(other->GetBounds());
    }
};

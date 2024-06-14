#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../../LSpawnableObject.h"
#include "../../LazyWidgets/LazyEnvoyDeclaraction.h"
#include "../Collision/LCollisionBase.h"

class LTrashCan : public LSpawnableObject
{
    sf::Sprite TrashCanBounds;
    sf::Texture TrashCan_Texture;

public:
    LazyEnvoy OnTrashCollected;
public:
    LTrashCan();
    ~LTrashCan() override = default;

    void SetPosition(const sf::Vector2f& NewPosition) override;
    
    sf::Vector2f GetPosition() const override { return TrashCanBounds.getPosition(); }

    void SetRotation(const float& Rotation) override;

    void SetScale(const sf::Vector2f& scale) override;

    void Update(float Delta_Time) override;
    
    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    void OnCollisionBeginOverlap(const std::shared_ptr<LCollisionBase>& Other) override;
};

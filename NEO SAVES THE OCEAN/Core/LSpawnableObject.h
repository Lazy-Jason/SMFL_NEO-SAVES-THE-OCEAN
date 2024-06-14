#pragma once
#include "LObject.h"
#include "Primitive/Collision/LCollisionBase.h"

class LSpawnableObject : public LObject
{
    std::shared_ptr<LCollisionBase> CollisionComponent;
    std::shared_ptr<LCollisionBase> OverlappedComponent;

public:
    LSpawnableObject();
    ~LSpawnableObject() override = default;

    const std::shared_ptr<LCollisionBase>& GetCollisionComponent() const { return CollisionComponent; }

    void SetCollisionComponent(const std::shared_ptr<LCollisionBase>& NewComponent);
    void Update(float Delta_Time) override;

    void SetPosition(const sf::Vector2f& NewPosition) override;
    void SetRotation(const float& Rotation) override;
    void SetScale(const sf::Vector2f& Scale) override;
    virtual void OnCollisionBeginOverlap(const std::shared_ptr<LCollisionBase>& Other);
    virtual void OnCollisionEndOverlap(const std::shared_ptr<LCollisionBase>& Other);
    void ReclaimOverlap();
};

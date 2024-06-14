#include "LSpawnableObject.h"

#include <memory>

LSpawnableObject::LSpawnableObject()
= default;

void LSpawnableObject::SetCollisionComponent( const std::shared_ptr<LCollisionBase>& NewComponent )
{
    CollisionComponent = NewComponent;
}

void LSpawnableObject::Update(float Delta_Time)
{
    LObject::Update(Delta_Time);
}

void LSpawnableObject::SetPosition(const sf::Vector2f& NewPosition)
{
    if(CollisionComponent != nullptr) CollisionComponent->SetPosition(NewPosition);
}

void LSpawnableObject::SetRotation(const float& Rotation)
{
    if(CollisionComponent != nullptr) CollisionComponent->SetRotation(Rotation);
}

void LSpawnableObject::SetScale(const sf::Vector2f& Scale)
{
    if(CollisionComponent != nullptr) CollisionComponent->SetScale(Scale);
}

void LSpawnableObject::OnCollisionBeginOverlap(const std::shared_ptr<LCollisionBase>& Other)
{
    if(Other == nullptr || Other == OverlappedComponent) return;
    OverlappedComponent = Other;
}

void LSpawnableObject::OnCollisionEndOverlap(const std::shared_ptr<LCollisionBase>& Other)
{
    OverlappedComponent.reset();
}

void LSpawnableObject::ReclaimOverlap()
{
    if(OverlappedComponent == nullptr) return;

    OnCollisionEndOverlap(OverlappedComponent);
}

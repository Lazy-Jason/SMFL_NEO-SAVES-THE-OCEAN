#include "LSpawnableObject.h"

#include <memory>

#include "FunctionLibrary/LCoreStatic.h"

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

void LSpawnableObject::EvaluateOverlap( const std::shared_ptr<LCollisionBase>& Other )
{
    if(Other == OverlappedComponent) return;
    OverlappedComponent = Other;
    
    OnCollisionBeginOverlap(OverlappedComponent);
}

void LSpawnableObject::OnCollisionBeginOverlap(const std::shared_ptr<LCollisionBase>& Other)
{}

void LSpawnableObject::OnCollisionEndOverlap(const std::shared_ptr<LCollisionBase>& Other)
{
    OverlappedComponent.reset();
}

void LSpawnableObject::ReclaimOverlap()
{
    if(OverlappedComponent == nullptr) return;

    OnCollisionEndOverlap(OverlappedComponent);
}

bool LSpawnableObject::Destroy()
{
    // Use shared_from_this() to create a shared_ptr from 'this' pointer
    auto sharedThis = shared_from_this();
    
    if (!LCoreStatic::DestroyObject(sharedThis)) return false;
    OnDestroy.AlertEnvoys();
    
    return true;
}

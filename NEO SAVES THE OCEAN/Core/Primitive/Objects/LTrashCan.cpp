#include "LTrashCan.h"
#include "..\Collision.h"
#include "../../FunctionLibrary/LCoreStatic.h"
#include "../../Player/LPlayableCharacterBase.h"

LTrashCan::LTrashCan()
{
    if(Collision::CreateTextureAndBitmask(TrashCan_Texture, TEXTURE_PATH "Trash Bottle.png"))
    {
        TrashCanBounds.setTexture(TrashCan_Texture, true);
    }
    SetCollisionComponent(std::make_shared<LBoxCollisionComponent>(sf::Vector2f(TrashCanBounds.getGlobalBounds().width, TrashCanBounds.getGlobalBounds().height)));
}

void LTrashCan::SetPosition(const sf::Vector2f& NewPosition)
{
    LSpawnableObject::SetPosition(NewPosition);
    TrashCanBounds.setPosition(NewPosition);
}

void LTrashCan::SetRotation(const float& Rotation)
{
    LSpawnableObject::SetRotation(Rotation);
    TrashCanBounds.setRotation(Rotation);
}

void LTrashCan::SetScale(const sf::Vector2f& scale)
{
    LSpawnableObject::SetScale(scale);
    TrashCanBounds.setScale(scale);
}

void LTrashCan::Update(float Delta_Time)
{
    LSpawnableObject::Update(Delta_Time);
}

void LTrashCan::DrawToWindow(sf::RenderWindow& Render_Window)
{
    Render_Window.draw(TrashCanBounds);
    if(GetCollisionComponent() != nullptr) GetCollisionComponent()->Draw(Render_Window);
}

void LTrashCan::OnCollisionBeginOverlap(const std::shared_ptr<LCollisionBase>& Other)
{
    // do we have a valid player and do the collision component belong to the player.?
    if(LCoreStatic::GetPlayerCharacter().lock() == nullptr || LCoreStatic::GetPlayerCharacter().lock()->GetCollisionComponent() != Other) return;
    printf("Overlap begin \n");
    
    OnTrashCollected.AlertEnvoys();
    Destroy();
}

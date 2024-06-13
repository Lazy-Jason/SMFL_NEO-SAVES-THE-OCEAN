#include "LPlayableCharacterBase.h"

LPlayableCharacterBase::LPlayableCharacterBase()
{
    if(PlayerTexture.loadFromFile(TEXTURE_PATH "Neo Character.png"))
    {
        PlayerBounds.setTexture(PlayerTexture, true);
    }
    CurrentHealth = Attribute.MaxHealth;
    CurrentBoost = Attribute.MaxBoost;
}

void LPlayableCharacterBase::OnMouseButtonAction(const sf::Mouse::Button MouseAction)
{
    LObject::OnMouseButtonAction(MouseAction);
}

void LPlayableCharacterBase::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    LObject::OnMouseButtonMove(Render_Window);
}

void LPlayableCharacterBase::SetPosition(const sf::Vector2f& NewPosition)
{
    PlayerBounds.setPosition(NewPosition);
}

void LPlayableCharacterBase::SetRotation(const float& Rotation)
{
    PlayerBounds.setRotation(Rotation);
}

void LPlayableCharacterBase::SetScale(const sf::Vector2f& scale)
{
    PlayerBounds.setScale(scale);
}

void LPlayableCharacterBase::Update(const float Delta_Time)
{
    if (InputAxis.x == 0 && InputAxis.y == 0) return;

    // Calculate the desired movement
    const sf::Vector2f desiredMovement = InputAxis * Speed * Delta_Time;

    // Apply the movement
    PlayerBounds.move(desiredMovement);
}

void LPlayableCharacterBase::DrawToWindow(sf::RenderWindow& Render_Window)
{
    Render_Window.draw(PlayerBounds);
}

void LPlayableCharacterBase::AddMovementAxis(const float x, const float y)
{
    InputAxis.x = std::clamp<float>(InputAxis.x += x, -1, 1);
    InputAxis.y = std::clamp<float>(InputAxis.y += y, -1, 1);
}

void LPlayableCharacterBase::AddBoost(float Amount)
{
    CurrentBoost = std::clamp<float>(CurrentBoost + Amount, 0, Attribute.MaxBoost);
    OnBoostAdded.AlertEnvoys();
}

void LPlayableCharacterBase::RemoveBoost(float Amount)
{
    CurrentBoost = std::clamp<float>(CurrentBoost - Amount, 0, Attribute.MaxBoost);
    OnBoostRemoved.AlertEnvoys();
}

void LPlayableCharacterBase::StartRemovingBoostByRate()
{
    if(!bCanRemoveBoost) return;

    RemoveBoost(BoostDecrement_Rate);
    if(CurrentBoost <= 0)
    {
        bCanRemoveBoost = false;
        return;
    }
    StartRemovingBoostByRate();
}

void LPlayableCharacterBase::OnKeyPressed( const sf::Keyboard::Key InputKey )
{
    switch (InputKey)
    {
    case sf::Keyboard::W:
        InputAxis.y = -1.0f;
        break;
    case sf::Keyboard::A:
        InputAxis.x = -1.0f;
        break;
    case sf::Keyboard::S:
        InputAxis.y = 1.0f;
        break;
    case sf::Keyboard::D:
        InputAxis.x = 1.0f;
        break;
    case sf::Keyboard::LShift:
        StartRemovingBoostByRate();
        break;
    default:
        break;
    }
}

void LPlayableCharacterBase::OnKeyReleased( const sf::Keyboard::Key InputKey )
{
    switch (InputKey)
    {
    case sf::Keyboard::W:
        InputAxis.y = 0.0f;
        break;
    case sf::Keyboard::A:
        InputAxis.x = 0.0f;
        break;
    case sf::Keyboard::S:
        InputAxis.y = 0.0f;
        break;
    case sf::Keyboard::D:
        InputAxis.x = 0.0f;
        break;
    case sf::Keyboard::LShift:
        bCanRemoveBoost = false;
        break;
    default:
        break;
    }
}

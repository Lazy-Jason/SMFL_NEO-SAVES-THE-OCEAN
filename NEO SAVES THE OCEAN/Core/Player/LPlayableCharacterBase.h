#pragma once
#include "../LObject.h"
#include "../LazyWidgets/LazyEnvoyDeclaraction.h"

struct PlayerAttribute
{
    int MaxHealth = 3;
    float MaxBoost = 100.0f;
};

class LPlayableCharacterBase : public LObject
{
    sf::Sprite PlayerBounds;
    sf::Texture PlayerTexture;

    PlayerAttribute Attribute;
    float Speed = 220.0f;
    float Speed_Boost = 620.0f;
    int CurrentHealth;
    float CurrentBoost;
    
    sf::Vector2f InputAxis = {0, 0};
    bool bCanRemoveBoost = false;
    float BoostDecrement_Rate = 1.0;

public:
    LazyEnvoy OnBoostAdded;
    LazyEnvoy OnBoostRemoved;

public:
    LPlayableCharacterBase();
    ~LPlayableCharacterBase() override = default;

    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;

    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;

    sf::FloatRect GetGlobalBounds() const { return PlayerBounds.getGlobalBounds(); }

    void SetPosition(const sf::Vector2f& NewPosition) override;

    sf::Vector2f GetPosition() const override { return PlayerBounds.getPosition(); }

    void SetRotation(const float& Rotation) override;

    void SetScale(const sf::Vector2f& scale) override;

    void Update(float Delta_Time) override;

    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    void AddMovementAxis(float x, float y);

    void AddBoost( float Amount );
    
    void RemoveBoost( float Amount );

    void StartRemovingBoostByRate();
    
    void OnKeyPressed(sf::Keyboard::Key InputKey) override;

    void OnKeyReleased(sf::Keyboard::Key InputKey) override;
    
    float GetBoostRatio() const { return CurrentBoost / Attribute.MaxBoost; }
};

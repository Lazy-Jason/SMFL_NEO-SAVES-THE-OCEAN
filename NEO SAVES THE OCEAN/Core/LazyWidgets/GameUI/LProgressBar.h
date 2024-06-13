#pragma once
#include "../../LObject.h"

class LProgressBar : public LObject
{
    sf::RectangleShape Progress_Bound;
    sf::RectangleShape ProgressFill;
    sf::RectangleShape ProgressBackground;

    sf::Color ProgressFill_Color = sf::Color::White;
    sf::Color ProgressBackground_Color = sf::Color::Transparent;

    sf::Vector2f ProgressBound_Size = {0, 0};

    float Percent = 0;
public:
    LProgressBar( sf::Vector2f Size = {50, 10}, sf::Color ProgressFill_Color = sf::Color::White, sf::Color ProgressBackground_Color = sf::Color::Black );
    ~LProgressBar() override = default;

    void DrawToWindow( sf::RenderWindow& Render_Window ) override;
    void SetPosition( const sf::Vector2f& NewPosition ) override;
    
    void SetPercent( const float& New_Percent );
    float GetPercent() const { return Percent; }
    
    void SetFillColor(const sf::Color& Color);
    sf::Color GetFillColor() const { return ProgressFill_Color; }

    void SetBackgroundColor(const sf::Color& Color);
    sf::Color GetBackgroundColor() const { return ProgressBackground_Color; }

    void SetSize(const sf::Vector2f& Size);
    sf::Vector2f GetProgressBound_Size() const { return ProgressBound_Size; }
private:
    void UpdateFill();
    void UpdateFillPosition();
};

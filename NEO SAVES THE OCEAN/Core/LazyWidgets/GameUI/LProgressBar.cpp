#include "LProgressBar.h"

LProgressBar::LProgressBar(sf::Vector2f Size, sf::Color ProgressFill_Color, sf::Color ProgressBackground_Color)
{
    this->ProgressBound_Size = Size;
    this->ProgressFill_Color = ProgressFill_Color;
    this->ProgressBackground_Color = ProgressBackground_Color;

    SetFillColor(this->ProgressFill_Color);
    SetBackgroundColor(this->ProgressBackground_Color);
    SetSize(ProgressBound_Size);
    Progress_Bound.setFillColor(sf::Color::Transparent);
    SetPercent(0);
}

void LProgressBar::DrawToWindow(sf::RenderWindow& Render_Window)
{
    Render_Window.draw(Progress_Bound);
    Render_Window.draw(ProgressBackground);
    Render_Window.draw(ProgressFill);
}

void LProgressBar::SetPosition( const sf::Vector2f& NewPosition )
{
    Progress_Bound.setPosition(NewPosition);
    UpdateFillPosition();
}

void LProgressBar::SetPercent(const float& New_Percent)
{
    Percent = std::clamp(New_Percent, 0.0f, 1.0f);
    UpdateFill();
}

void LProgressBar::SetFillColor(const sf::Color& Color)
{
    ProgressFill.setFillColor(Color);
}

void LProgressBar::SetBackgroundColor(const sf::Color& Color)
{
    ProgressBackground.setFillColor(Color);
}

void LProgressBar::SetSize(const sf::Vector2f& Size)
{
    Progress_Bound.setSize(Size);
}

void LProgressBar::UpdateFill()
{
    const sf::Vector2f BoundSize = Progress_Bound.getSize();
    const sf::Vector2f FillSize = {BoundSize.x * Percent, BoundSize.y};

    ProgressFill.setSize(FillSize);
    ProgressBackground.setSize({BoundSize.x - FillSize.x, BoundSize.y});

    UpdateFillPosition();
}

void LProgressBar::UpdateFillPosition()
{
    ProgressFill.setPosition(Progress_Bound.getPosition());
    const sf::Vector2f FillSize = {Progress_Bound.getSize().x * Percent, Progress_Bound.getSize().y};
    ProgressBackground.setPosition({Progress_Bound.getPosition().x + FillSize.x, Progress_Bound.getPosition().y});
}

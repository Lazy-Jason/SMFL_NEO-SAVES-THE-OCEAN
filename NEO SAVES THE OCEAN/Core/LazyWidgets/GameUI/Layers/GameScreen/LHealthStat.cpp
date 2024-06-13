#include "LHealthStat.h"

LHealthStat::LHealthStat()
{
    if (!HealthTexture.loadFromFile(TEXTURE_PATH "Heart.png")) return;
    InitHealthShape();
    SetHealthShapesTextures(&HealthTexture);
    HeathTextBlock.setFont(GetDefaultFont());
    HeathTextBlock.setString(HealthText_Content);
    HeathTextBlock.setCharacterSize(25);

    
    // Calculate the total width required for all health shapes
    const float totalWidth = (HealthTexture.getSize().x + HeathTextBlock.getScale().x) * HealthAmount + Horizontal_Spacing * (HealthAmount - 1);

    // Set the size of the StatBounds rectangle
    StatBounds.setSize(sf::Vector2f(totalWidth, HealthTexture.getSize().y + Vertical_Spacing));
    StatBounds.setFillColor(sf::Color::Transparent);

    // Position the health shapes inside the StatBounds rectangle
    CalculateHealthStatPosition();
}

void LHealthStat::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    LObject::OnMouseButtonAction(MouseAction);
}

void LHealthStat::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    LObject::OnMouseButtonMove(Render_Window);
}

void LHealthStat::DrawToWindow(sf::RenderWindow& Render_Window)
{
    Render_Window.draw(StatBounds);
    Render_Window.draw(HeathTextBlock);
    
    for (const std::unique_ptr<sf::RectangleShape>& element : HeathShapes)
    {
        Render_Window.draw(*element);
    }
}

void LHealthStat::InitHealthShape()
{
    for (int i = 0; i < HealthAmount; ++i)
    {
        sf::RectangleShape local = sf::RectangleShape({static_cast<float>(HealthShapeSize.x), static_cast<float>(HealthShapeSize.y)});
        HeathShapes.push_back(std::make_unique<sf::RectangleShape>(local));
    }
}

void LHealthStat::SetHealthShapesTextures(const sf::Texture* Texture) const
{
    if(HeathShapes.empty()) return;

    for (const std::unique_ptr<sf::RectangleShape>& element : HeathShapes)
    {
        element->setTexture(Texture);
    }
}

void LHealthStat::SetPosition(const sf::Vector2f& NewPosition)
{
    StatBounds.setPosition(NewPosition);
    CalculateHealthStatPosition();
}

void LHealthStat::CalculateHealthStatPosition()
{
    float currentX = StatBounds.getPosition().x;
    const float currentY = StatBounds.getPosition().y;
    
    HeathTextBlock.setPosition(currentX, currentY);
    for (const std::unique_ptr<sf::RectangleShape>& element : HeathShapes)
    {
        currentX += (HealthTexture.getSize().x - HeathTextBlock.getScale().x) + Horizontal_Spacing;
        element->setPosition(currentX, currentY);
    }
}

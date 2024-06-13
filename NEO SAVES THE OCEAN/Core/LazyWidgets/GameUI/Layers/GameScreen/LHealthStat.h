#pragma once
#include "../../../../LObject.h"

class LHealthStat : public LObject
{
    sf::Text HeathTextBlock;
    std::string HealthText_Content = "HP";
    std::vector<std::unique_ptr<sf::RectangleShape>> HeathShapes;
    sf::Vector2i HealthShapeSize = {72, 50};
    sf::Texture HealthTexture;
    
    sf::RectangleShape StatBounds;
    int HealthAmount = 3;

    float Horizontal_Spacing = 0.0f;
    float Vertical_Spacing = 0.0f;
public:
    LHealthStat();
    ~LHealthStat() override = default;
    
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;

    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;

    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    void InitHealthShape();

    void SetHealthShapesTextures( const sf::Texture* Texture ) const;

    void SetPosition(const sf::Vector2f& NewPosition) override;

    void CalculateHealthStatPosition();
};

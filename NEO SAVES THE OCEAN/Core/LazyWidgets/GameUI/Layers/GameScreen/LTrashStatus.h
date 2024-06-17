#pragma once
#include "../../../../LObject.h"

class LTrashStatus : public LObject
{
    sf::Text TitleTextBlock;
    sf::Text TrashValue_TextBlock;
    sf::Font ValueFont;
    std::string TitleText_Content = "Trash Collected";
    sf::Sprite TrashIcon;
    sf::Texture TrashIcon_Texture;
    
    sf::RectangleShape Status_BoundsShapes;
    sf::Texture HealthTexture;
    
    float HorizontalPadding = 10.0f;
    float VerticalPadding = 10.0f;
    
    float VerticalSpacing = 10.0f;

public:
    LTrashStatus();
    ~LTrashStatus() override = default;

    void SetPosition(const sf::Vector2f& NewPosition) override;

    void SetRotation(const float& Rotation) override;

    void SetScale(const sf::Vector2f& Scale) override;

    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    void UpdateTrashCount( const int& Current, const int& Max );

    sf::Vector2f GetSize() const { return Status_BoundsShapes.getSize(); }

private:
    void UpdateVerticalStacking();
};

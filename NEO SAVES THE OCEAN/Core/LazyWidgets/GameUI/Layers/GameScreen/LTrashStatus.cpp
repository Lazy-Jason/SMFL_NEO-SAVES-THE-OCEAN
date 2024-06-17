#include "LTrashStatus.h"

#include "../../../../Primitive/Collision.h"

LTrashStatus::LTrashStatus() : Status_BoundsShapes(sf::Vector2f())
{
    TitleTextBlock.setFont(GetDefaultFont());
    TitleTextBlock.setString(TitleText_Content);
    TitleTextBlock.setCharacterSize(22);
    
    TrashValue_TextBlock.setCharacterSize(30);
    TrashValue_TextBlock.setStyle( sf::Text::Bold );
    if(ValueFont.loadFromFile(FONT_PATH "Dela_Gothic_One\\DelaGothicOne-Regular.ttf"))
    {
        TrashValue_TextBlock.setFont(ValueFont);
    }
    if(Collision::CreateTextureAndBitmask(TrashIcon_Texture, TEXTURE_PATH "Trash Bottle.png"))
    {
        TrashIcon.setTexture(TrashIcon_Texture);
        TrashIcon.setScale(0.5f,0.5f);
        TrashIcon.setRotation(25);
    }
    UpdateVerticalStacking();
}

void LTrashStatus::SetPosition(const sf::Vector2f& NewPosition)
{
    Status_BoundsShapes.setPosition(NewPosition);
    UpdateVerticalStacking();
}

void LTrashStatus::SetRotation(const float& Rotation)
{
    TitleTextBlock.setRotation(Rotation);
    TrashValue_TextBlock.setRotation(Rotation);
}

void LTrashStatus::SetScale(const sf::Vector2f& Scale)
{
    TitleTextBlock.setScale(Scale);
    TrashValue_TextBlock.setScale(Scale);
}

void LTrashStatus::DrawToWindow(sf::RenderWindow& Render_Window)
{
    Render_Window.draw(TrashIcon);
    Render_Window.draw(TitleTextBlock);
    Render_Window.draw(TrashValue_TextBlock);
}

void LTrashStatus::UpdateTrashCount(const int& Current, const int& Max)
{
    const std::string Trash_Value = std::to_string(Current) + " / " + std::to_string(Max);
    TrashValue_TextBlock.setString(Trash_Value);
    UpdateVerticalStacking(); // Update stacking when text changes
}

void LTrashStatus::UpdateVerticalStacking()
{
    // Get global bounds for both text blocks
    const sf::FloatRect titleBounds = TitleTextBlock.getGlobalBounds();
    const sf::FloatRect trashBounds = TrashValue_TextBlock.getGlobalBounds();

    // Calculate the maximum width and total height
    const float maxWidth = std::max(titleBounds.width, trashBounds.width);
    const float totalHeight = titleBounds.height + VerticalSpacing + trashBounds.height;

    // Update the bounding shape size
    Status_BoundsShapes.setSize(sf::Vector2f(maxWidth + 2 * HorizontalPadding, totalHeight + 2 * VerticalPadding));

    // Position the bounding shape
    const sf::Vector2f boundsPosition = Status_BoundsShapes.getPosition();
    Status_BoundsShapes.setPosition(boundsPosition);

    // Center the title text block horizontally
    TitleTextBlock.setPosition(boundsPosition.x + HorizontalPadding + (maxWidth - titleBounds.width) / 2.0f, boundsPosition.y + VerticalPadding);

    // Position the trash value text block below the title
    TrashValue_TextBlock.setPosition
    (
        boundsPosition.x + VerticalPadding + titleBounds.height + VerticalSpacing,
        boundsPosition.y + VerticalPadding + titleBounds.height + VerticalSpacing
    );
    TrashIcon.setPosition
    (
        boundsPosition.x,
        boundsPosition.y + VerticalPadding + titleBounds.height + VerticalSpacing
    );
}

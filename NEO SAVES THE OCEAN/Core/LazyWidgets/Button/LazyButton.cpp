#include "LazyButton.h"

LazyButton::LazyButton() = default;

LazyButton::LazyButton(const std::string& DisplayText, sf::Vector2f Size, int CharacterSize, sf::Color BackgroundColor,
                       sf::Color TextColor, const sf::Font& NewFont, sf::Color Hover_Background_Color, sf::Color Hover_Text_Color)
{
    // Set button properties
    SetButtonSize(Size);
    this->Hover_Background_Color = Hover_Background_Color;
    this->Hover_Text_Color = Hover_Text_Color;
    this->Idle_Background_Color = BackgroundColor;
    this->Idle_Text_Color = TextColor;
    SetButtonColor(BackgroundColor);
    SetButtonText(DisplayText);
    SetButtonTextColor(TextColor);
    SetButtonCharacterSize(CharacterSize);

    if (!NewFont.getInfo().family.empty())
    {
        SetDefaultFont(NewFont);
    }
    SetButtonFont(GetDefaultFont());
}

LazyButton::~LazyButton() = default;

void LazyButton::SetButtonPosition(sf::Vector2f NewPosition)
{
    // Calculate the position of the button text based on the button's position and size
    float X_postion = (NewPosition.x + (ButtonBounds.getLocalBounds().width / 2)) - (ButtonTextBlock.getLocalBounds().width / 2);
    float Y_postion = (NewPosition.y + (ButtonBounds.getLocalBounds().height / 2)) - (ButtonTextBlock.getLocalBounds().height / 2);

    ButtonTextBlock.setPosition({ X_postion, Y_postion });

    // Set the position of the button
    ButtonBounds.setPosition(NewPosition);
}

void LazyButton::SetButtonSize(sf::Vector2f Size)
{
    // Set button size
    ButtonBounds.setSize(Size);
}

void LazyButton::SetButtonColor(sf::Color BackgroundColor)
{
    // Set button background color
    ButtonBounds.setFillColor(BackgroundColor);
}

void LazyButton::SetButtonText(const std::string& string)
{
    // Set button text
    ButtonTextBlock.setString(string);
}

void LazyButton::SetButtonTextColor(sf::Color color)
{
    // Set button text color
    ButtonTextBlock.setFillColor(color);
}

void LazyButton::SetButtonCharacterSize(int character_size)
{
    // Set button text character size
    ButtonTextBlock.setCharacterSize(character_size);
}

void LazyButton::DrawToWindow(sf::RenderWindow& Render_Window)
{
    // Draw the button and its text to the render window
    Render_Window.draw(ButtonBounds);
    Render_Window.draw(ButtonTextBlock);
}

bool LazyButton::IsMouseButtonOver(sf::RenderWindow& Render_Window) const
{
    // Get the mouse position relative to the window
    const sf::Vector2i pixelPos = sf::Mouse::getPosition(Render_Window);

    // Convert the pixel position to world coordinates
    const sf::Vector2f worldPos = Render_Window.mapPixelToCoords(pixelPos, Render_Window.getView());

    // Get the button's global bounds
    const sf::FloatRect bounds = ButtonBounds.getGlobalBounds();

    // Check if the mouse position is within the button's bounds
    if (bounds.contains(worldPos))
    {
        // Mouse is over the button
        return true;
    }

    // Mouse is not over the button
    return false;
}

void LazyButton::OnMouseEnter()
{
    // Call the base class OnMouseEnter function
    LObject::OnMouseEnter();

    // Call the OnHoverEnvoy if it's set
    if (OnHoverEnvoy) OnHoverEnvoy();

    // Update the button's appearance to the hover state
    SetButtonColor(Hover_Background_Color);
    SetButtonTextColor(Hover_Text_Color);
}

void LazyButton::OnMouseLeave()
{
    // Call the base class OnMouseLeave function
    LObject::OnMouseLeave();

    // Call the OnUnhoverEnvoy if it's set
    if (OnUnhoverEnvoy) OnUnhoverEnvoy();

    // Update the button's appearance to the idle state
    SetButtonColor(Idle_Background_Color);
    SetButtonTextColor(Idle_Text_Color);
}

void LazyButton::OnMouseClick()
{
    // Call the base class OnMouseClick function
    LObject::OnMouseClick();

    // Call the OnClickEnvoy if it's set
    if (OnClickEnvoy) OnClickEnvoy();
}

void LazyButton::OnMouseRelease()
{
    // Call the base class OnMouseRelease function
    LObject::OnMouseRelease();

    // Call the OnReleasedEnvoy if it's set
    if (OnReleasedEnvoy) OnReleasedEnvoy();
}

void LazyButton::SetButtonFont(const sf::Font& NewFont)
{
    // Set button font
    ButtonTextBlock.setFont(NewFont);
}
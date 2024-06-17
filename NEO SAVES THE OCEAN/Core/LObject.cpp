#include "LObject.h"

// Default constructor implementation
LObject::LObject()
{
    // Load default font if custom font is not provided
    if (!Default_Font.loadFromFile(FONT_PATH "Hind_Guntur\\HindGuntur-Medium.ttf"))
    {
        printf("Font failed to load \n");
    }
}

// Destructor implementation
LObject::~LObject() = default;

void LObject::OnMouseClick()
{}

void LObject::OnMouseRelease()
{}

void LObject::OnMouseEnter()
{}

void LObject::OnMouseLeave()
{}

void LObject::OnKeyPressed(sf::Keyboard::Key InputKey)
{}

void LObject::OnKeyReleased(sf::Keyboard::Key InputKey)
{}

void LObject::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    switch (MouseAction)
    {
    case sf::Mouse::Left:
        if(b_IsClicked || !b_IsHovered) return;

        OnMouseClick();
        b_IsClicked = true;
        break;
    case sf::Mouse::Right:
        if(!b_IsClicked || !b_IsHovered) return;

        OnMouseRelease();
        b_IsClicked = false;
        break;
    default:
        printf("Mouse Action Button Was %d", MouseAction);
        break;
    }
}

void LObject::SetPosition(const sf::Vector2f& NewPosition)
{}

void LObject::SetDefaultFont(const sf::Font& NewFont)
{
    Default_Font = NewFont;
}

void LObject::SetRotation( const float& Rotation )
{}

void LObject::SetScale( const sf::Vector2f& Scale )
{}

// DrawToWindow function implementation
void LObject::DrawToWindow(sf::RenderWindow& Render_Window)
{
    // The function body is intentionally empty as this is a virtual function
    // meant to be overridden by derived classes.
    // Add specific drawing logic in derived classes.
}

void LObject::Update(float Delta_Time)
{}

void LObject::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    if (IsMouseButtonOver(Render_Window))
    {
        // Check if not already hovered
        if (!b_IsHovered)
        {
            // Call OnMouseEnter only if not hovered
            OnMouseEnter();
            b_IsHovered = true;
        }
    }
    else
    {
        // Check if already hovered
        if (b_IsHovered) 
        {
            // Call OnMouseLeave only if already hovered
            OnMouseLeave();
            b_IsHovered = false;
        }
    }
}

#include "GMenu.h"

#include "../Core/GEngine.h"

GMenu::GMenu() : LObject()
{}

GMenu::~GMenu() = default;

void GMenu::SetBackgroundTexture(const sf::Texture& NewTexture, sf::Uint8 Opacity)
{
    Background_Sprite.setTexture(NewTexture);
    Overlay_Sprite.setTexture(NewTexture);
    Overlay_Sprite.setColor({OverlayColor.r, OverlayColor.g, OverlayColor.b, Opacity});
    ScaleBackgroundSprite();
}

void GMenu::ScaleBackgroundSprite()
{
    // Get the size of the game window
    const sf::Vector2u windowSize = {1920, 1080};
    // Check if the window size and background sprite dimensions are valid
    if (windowSize.x > 0 && windowSize.y > 0 && Background_Sprite.getGlobalBounds().width > 0 && Background_Sprite.getGlobalBounds().height > 0)
    {
        // Calculate the scaling factors
        float XScale = static_cast<float>(windowSize.x) / Background_Sprite.getGlobalBounds().width;
        float YScale = static_cast<float>(windowSize.y) / Background_Sprite.getGlobalBounds().height;

        // Apply the scaling factors to the background sprite
        Background_Sprite.setScale({XScale, YScale});
        Overlay_Sprite.setScale({XScale, YScale});
    }
    else
    {
        // Print an error message if dimensions are invalid
        std::cerr << "Error: Invalid window size or background sprite dimensions." << "\n";
    }
}

void GMenu::DrawToWindow(sf::RenderWindow& Render_Window)
{
    LObject::DrawToWindow(Render_Window);
    if (Background_Sprite.getTexture() == nullptr) return;
    Render_Window.draw(Background_Sprite);
    Render_Window.draw(Overlay_Sprite);
}

void GMenu::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    LObject::OnMouseButtonMove(Render_Window);
}

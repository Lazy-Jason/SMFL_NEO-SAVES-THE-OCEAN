#pragma once

#include <SFML/Graphics.hpp>
#include "../Core/LObject.h"

/**
 * @brief GMenu class represents a graphical menu.
 */
class GMenu : public LObject
{
protected:
    sf::Texture Background_Texture;
    sf::Sprite Background_Sprite;
    sf::Sprite Overlay_Sprite;
    sf::Color OverlayColor = {sf::Uint8(3),sf::Uint8(4),sf::Uint8(15),sf::Uint8( 0 )};

   public:
    // Constructor / Destructor
    GMenu(); /**< Default constructor. */
    ~GMenu() override; /**< Destructor. */

    /**
     * @brief Sets the background texture of the menu.
     * @param NewTexture The new texture to set as the background.
     * @param Opacity The overlay opacity, from 0 to 255.
     */
    void SetBackgroundTexture( const sf::Texture& NewTexture, sf::Uint8 Opacity = 0 );

    /**
     * @brief Scales the background sprite to fit the window.
     */
    void ScaleBackgroundSprite();

    /**
     * @brief Gets the background texture of the menu.
     * @return A pointer to the background texture.
     */
    const sf::Texture* GetBackgroundTexture() const { return Background_Sprite.getTexture(); }

    /**
     * @brief Sets the background texture of the menu.
     * @param NewTexture The new texture to set as the background.
     */
    void SetBackGroundTexture(const sf::Texture& NewTexture) { Background_Sprite.setTexture(NewTexture); }

    /**
     * @brief Handles mouse button movement on the menu.
     * @param Render_Window The render window where the mouse event occurred.
     */
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
 
    void DrawToWindow(sf::RenderWindow& Render_Window) override;
};

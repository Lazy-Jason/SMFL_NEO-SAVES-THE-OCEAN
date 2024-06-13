#pragma once
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "FunctionLibrary/LCoreStatic.h"


#define TEXTURE_PATH "C:\\\\Users\\\\hunti\\\\OneDrive\\\\Documents\\\\Cpp Projects\\\\NEO SAVES THE OCEAN\\\\Textures\\\\"
#define FONT_PATH "C:\\\\Users\\\\hunti\\\\OneDrive\\\\Documents\\\\Cpp Projects\\\\NEO SAVES THE OCEAN\\\\Fonts\\\\"

/**
 * @brief The base class for all drawable objects in the application.
 *        Provides functionality for handling mouse events and drawing to a render window.
 */
class LObject
{
    ///< Flag indicating whether the object is currently being hovered over by the mouse.
    bool b_IsHovered = false;
    ///< Flag indicating whether the object has been clicked.
    bool b_IsClicked = false;
    ///< The default font.
    sf::Font Default_Font;
protected:
 using CallbackFunction = std::function<void()>;
public:
    /**
     * @brief Default constructor of the LObject class.
     */
    LObject();

    /**
     * @brief Virtual destructor of the LObject class.
     */
    virtual ~LObject();

    /**
     * @brief Draws the object to the specified SFML render window.
     * @param Render_Window The SFML render window to draw the object to.
     */
    virtual void DrawToWindow(sf::RenderWindow& Render_Window);

    virtual void Update(float Delta_Time);

    /**
     * @brief Handles mouse movement events for the object.
     * Invoked whenever the mouse moves over or away from the object.
     * @param Render_Window The SFML render window being used.
     */
    virtual void OnMouseButtonMove(sf::RenderWindow& Render_Window);

    /**
     * @brief Handles mouse click events for the object.
     * Invoked when the object is clicked by the mouse.
     */
    virtual void OnMouseClick();

    /**
    * @brief Handles mouse release events for the object.
    * Invoked when the object is released by the mouse.
    */
    virtual void OnMouseRelease();

    /**
     * @brief Handles mouse enter events for the object.
     * Invoked when the mouse enters the area occupied by the object.
     */
    virtual void OnMouseEnter();

    /**
     * @brief Handles mouse leave events for the object.
     * Invoked when the mouse leaves the area occupied by the object.
     */
    virtual void OnMouseLeave();

    /**
     * @brief Checks if the mouse is currently over the object.
     * Override this method in derived classes to implement custom mouse-over behavior.
     * @param Render_Window The SFML render window being used.
     * @return True if the mouse is over the object, false otherwise.
     */
    virtual bool IsMouseButtonOver(sf::RenderWindow& Render_Window) const { return false; }

    virtual void OnKeyPressed( sf::Keyboard::Key InputKey );
 
    virtual void OnKeyReleased( sf::Keyboard::Key InputKey );
 
    virtual void OnMouseButtonAction( sf::Mouse::Button MouseAction );

    virtual void SetPosition( const sf::Vector2f& NewPosition );
 
    virtual sf::Vector2f GetPosition() const { return {}; }
 
    virtual void SetRotation( const float& Rotation );
 
    virtual void SetScale( const sf::Vector2f& Scale );

    sf::Font& GetDefaultFont() { return Default_Font; }
 
    /**
    * @brief Sets the font of the button text.
    * @param NewFont The new font to set.
    */
    void SetDefaultFont(const sf::Font& NewFont);
};
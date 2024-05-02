#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "../../LObject.h"

/**
 * @brief Represents a lazy button with customizable properties.
 */
class LazyButton : public LObject
{
    using CallbackFunction = std::function<void()>;

public:
    ///< The hover color state of the background.
    sf::Color Hover_Background_Color;
    ///< The hover color state of the text.
    sf::Color Hover_Text_Color;
    ///< The idle color state of the background.
    sf::Color Idle_Background_Color;
    ///< The idle color state of the text.
    sf::Color Idle_Text_Color;

    ///< Callback function for the button click event.
    CallbackFunction OnClickEnvoy;
    ///< Callback function for the button release event.
    CallbackFunction OnReleasedEnvoy;
    ///< Callback function for the button hover event.
    CallbackFunction OnHoverEnvoy;
    ///< Callback function for the button unhover event.
    CallbackFunction OnUnhoverEnvoy;

private:
    ///< The shape representing the button.
    sf::RectangleShape ButtonBounds;
    ///< The text displayed on the button.
    sf::Text ButtonTextBlock;

public:
    LazyButton();
 
    /**
     * @brief Constructs a LazyButton object with the specified parameters.
     *
     * @param DisplayText The text to display on the button.
     * @param Size The size of the button.
     * @param CharacterSize The size of the text characters (default is 12).
     * @param BackgroundColor The background color of the button.
     * @param TextColor The color of the text on the button.
     * @param NewFont The font to use for the button text.
     * @param Hover_Background_Color The hover background color.
     * @param Hover_Text_Color The hover text color.
     */
    LazyButton(const std::string& DisplayText, sf::Vector2f Size, int CharacterSize,
    sf::Color BackgroundColor = sf::Color::Transparent,
    sf::Color TextColor = sf::Color::White, const sf::Font& NewFont = sf::Font(),
    sf::Color Hover_Background_Color = sf::Color::Transparent,
    sf::Color Hover_Text_Color = sf::Color::White);

    /**
     * @brief Destroys the LazyButton object.
     */
    ~LazyButton() override;

    /**
     * @brief Sets the position of the button.
     * @param NewPosition The new position of the button.
     */
    void SetButtonPosition(sf::Vector2f NewPosition);

    /**
     * @brief Sets the font of the button text.
     * @param NewFont The new font to set.
     */
    void SetButtonFont(const sf::Font& NewFont);

    /**
     * @brief Sets the size of the button.
     * @param size The new size of the button.
     */
    void SetButtonSize(sf::Vector2f size);

    /**
     * @brief Sets the background color of the button.
     * @param color The new background color.
     */
    void SetButtonColor(sf::Color color);

    /**
     * @brief Sets the text to display on the button.
     * @param string The new text to display.
     */
    void SetButtonText(const std::string& string);

    /**
     * @brief Sets the color of the text on the button.
     * @param color The new text color.
     */
    void SetButtonTextColor(sf::Color color);

    /**
     * @brief Sets the size of the characters in the button text.
     * @param character_size The new character size.
     */
    void SetButtonCharacterSize(int character_size);

    sf::Vector2f GetButtonSize() const { return ButtonBounds.getSize(); }
    sf::FloatRect GetButtonLocalBounds() const { return ButtonBounds.getLocalBounds(); }
    sf::FloatRect GetButtonGlobalBounds() const { return ButtonBounds.getGlobalBounds(); }
 
    void DrawToWindow(sf::RenderWindow& Render_Window) override;
    bool IsMouseButtonOver(sf::RenderWindow& Render_Window) const override;

protected:
    void OnMouseEnter() override;
    void OnMouseLeave() override;
    void OnMouseClick() override;
    void OnMouseRelease() override;
};
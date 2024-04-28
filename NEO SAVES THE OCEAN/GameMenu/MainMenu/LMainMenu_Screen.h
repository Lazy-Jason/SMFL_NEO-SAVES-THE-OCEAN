#pragma once

#include "../GMenu.h"
#include "../../Core/LazyWidgets/Button/LazyButton.h"

/**
 * @brief Represents the main menu screen of the application.
 */
class LMainMenu_Screen : public GMenu
{
    // Decoration
    sf::Font ButtonFont; ///< Font used for the buttons.
    float SpaceBetween_Buttons = 60.0f; ///< Spacing between the buttons.
    sf::Vector2f MenuButton_Position = {100.0f, 500.0f}; ///< Position of the menu buttons.
    sf::Vector2f MenuButton_Size = {200.0f, 50.0f}; ///< Size of the menu buttons.

    // Definition of menu buttons to be constructed.
    LazyButton Play_Button; //< Play button.
    LazyButton Options_Button; ///< Options button.
    LazyButton Credits_Button; ///< Credits button.
    LazyButton Exit_Button; ///< Exit button.

public:
    CallbackFunction OnPlay_ButtonReleasedEnvoy; ///< Callback function for the Play button release event.
    CallbackFunction OnOptions_ButtonReleasedEnvoy; ///< Callback function for the Options button release event.
    CallbackFunction OnCredit_ButtonReleasedEnvoy; ///< Callback function for the Credits button release event.
    CallbackFunction OnExit_ButtonReleasedEnvoy; ///< Callback function for the Exit button release event.

public:
    /**
     * @brief Constructs the LMainMenu_Screen object.
     */
    LMainMenu_Screen();

    /**
     * @brief Destroys the LMainMenu_Screen object.
     */
    ~LMainMenu_Screen() override;

    /**
     * @brief Handles the mouse button move event.
     * @param Render_Window The render window.
     */
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;

    /**
     * @brief Handles the mouse click event.
     */
    void OnMouseClick() override;

    /**
     * @brief Handles the mouse release event.
     */
    void OnMouseRelease() override;

    /**
     * @brief Draws the main menu screen to the provided render window.
     * @param Render_Window The render window.
     */
    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    /**
     * @brief Checks if the mouse button is over any of the menu buttons.
     * @param Render_Window The render window.
     * @return True if the mouse button is over a menu button, false otherwise.
     */
    bool IsMouseButtonOver(sf::RenderWindow& Render_Window) const override;
};
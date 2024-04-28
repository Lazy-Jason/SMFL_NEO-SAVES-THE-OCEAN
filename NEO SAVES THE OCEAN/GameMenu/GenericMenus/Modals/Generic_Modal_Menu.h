// Generic_Modal_Menu.h
#pragma once
#include "../../../Core/LObject.h"
#include "../../../Core/LazyWidgets/Button/LazyButton.h"

/**
 * @brief Represents a generic modal menu with customizable properties.
 */
class Generic_Modal_Menu : public LObject
{

public:
 CallbackFunction OnYes_Button_Released;
 CallbackFunction OnNo_Button_Released;
private:
    const float TitleMargin = 50.0f;
    sf::Vector2f BoundSize = {1920, 1080};
    sf::Vector2f ModalSize = {1000, 400};
    float Button_SpaceBetween = 200.0f;  ///< The spacing between the Yes and No buttons.
    float Button_YOffSet = 20.0f;       ///< The vertical offset of the buttons from the bottom of the modal.
    sf::RectangleShape ModalBounds;     ///< The shape representing the modal bounds.
    sf::RectangleShape ModalShape;  
    sf::Text TitleTextBlock;            ///< The text block for the modal title.
    sf::Text MessageTextBlock;          ///< The text block for the modal message.
    LazyButton YesButton;               ///< The Yes button.
    LazyButton NoButton;                ///< The No button.

    int FontSize = 20;

public:
    /**
     * @brief Constructs an empty Generic_Modal_Menu object.
     */
    Generic_Modal_Menu();

    /**
     * @brief Constructs a Generic_Modal_Menu object with the specified properties.
     * @param Title The title text of the modal (default is "Default Title").
     * @param Message The message text of the modal (default is "Default Message").
     * @param BackgroudColor The background color of the modal (default is semi-transparent black).
     */
    Generic_Modal_Menu(const std::string& Title = "Default Title",
                       const std::string& Message = "Default Message",
                       sf::Color BackgroudColor = sf::Color(sf::Uint8( 3 ),sf::Uint8( 4 ),sf::Uint8( 15 ),sf::Uint8( 255 )));

    /**
     * @brief Destroys the Generic_Modal_Menu object.
     */
    ~Generic_Modal_Menu() override = default;

    /**
     * @brief Draws the modal menu to the provided render window.
     * @param Render_Window The render window.
     */
    void DrawToWindow(sf::RenderWindow& Render_Window) override;
    bool IsMouseButtonOver(sf::RenderWindow& Render_Window) const override;
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;

    void CalculateObjectPositions(const sf::RenderWindow& Render_Window);
    void SetTitle(const std::string& NewTitle ) { TitleTextBlock.setString(NewTitle); }
    void SetMessage(const std::string& NewMessage ) { MessageTextBlock.setString(NewMessage); }
};
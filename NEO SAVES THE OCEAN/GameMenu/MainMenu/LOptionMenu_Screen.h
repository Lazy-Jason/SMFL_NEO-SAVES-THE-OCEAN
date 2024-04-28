#pragma once
#include "../GMenu.h"
#include "../../Core/LazyWidgets/Button/LazyButton.h"

class LOptionMenu_Screen : public GMenu
{
    sf::Text OptionsTextBlock;
    LazyButton ReturnButton;
public:
    CallbackFunction OnReturn_Button_Released;
public:
    LOptionMenu_Screen();
    ~LOptionMenu_Screen() override = default;
    void DrawToWindow(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
};

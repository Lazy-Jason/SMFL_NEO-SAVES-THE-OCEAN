#pragma once
#include "../GMenu.h"
#include "../../Core/LazyWidgets/Button/LazyButton.h"

class LCreditMenu_Screen : public GMenu
{
    sf::Text CreditTextBlock;
    LazyButton ReturnButton;
public:
    CallbackFunction OnReturn_Button_Released;
public:
    LCreditMenu_Screen();
    ~LCreditMenu_Screen() override = default;
    void DrawToWindow(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
};

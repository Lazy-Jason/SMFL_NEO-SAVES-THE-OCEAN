#include "LCreditMenu_Screen.h"

LCreditMenu_Screen::LCreditMenu_Screen():
ReturnButton("Return", {200, 50}, 20, sf::Color::Transparent, sf::Color::White, GetDefaultFont(), sf::Color::Red, sf::Color::White)
{
    if(Background_Texture.loadFromFile(TEXTURE_PATH "Underwater background.png"))
    {
        SetBackgroundTexture(Background_Texture, 160);
    }
    CreditTextBlock.setString("Created with C++ / Sfml\n PROGRAMMER: Job Omondiale");
    CreditTextBlock.setStyle(sf::Text::Italic);
    CreditTextBlock.setOrigin(0.5,0.5);
    CreditTextBlock.setFont(GetDefaultFont());
    CreditTextBlock.setCharacterSize(25);
    ReturnButton.SetButtonPosition({100, 1000});
    ReturnButton.OnReleasedEnvoy = [this] {if(OnReturn_Button_Released) OnReturn_Button_Released();};
}

void LCreditMenu_Screen::DrawToWindow(sf::RenderWindow& Render_Window)
{
    GMenu::DrawToWindow(Render_Window);
    ReturnButton.DrawToWindow(Render_Window);
    Render_Window.draw(CreditTextBlock);
    CreditTextBlock.setPosition(Render_Window.getView().getCenter() - CreditTextBlock.getLocalBounds().getSize() / 2.f);
}

void LCreditMenu_Screen::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    ReturnButton.OnMouseButtonAction(MouseAction);
}

void LCreditMenu_Screen::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    ReturnButton.OnMouseButtonMove(Render_Window);
}

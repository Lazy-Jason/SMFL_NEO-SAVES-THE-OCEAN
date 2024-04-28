#include "LOptionMenu_Screen.h"

LOptionMenu_Screen::LOptionMenu_Screen():
ReturnButton("Return", {200, 50}, 20, sf::Color::Transparent, sf::Color::White, GetDefaultFont(), sf::Color::Red, sf::Color::White)
{
    if(Background_Texture.loadFromFile(TEXTURE_PATH "Underwater background.png"))
    {
        SetBackgroundTexture(Background_Texture, 160);
    }
    OptionsTextBlock.setString("This is the options page");
    OptionsTextBlock.setFont(GetDefaultFont());
    OptionsTextBlock.setCharacterSize(20);
    ReturnButton.SetButtonPosition({100, 1000});
    ReturnButton.OnReleasedEnvoy = [this] {if(OnReturn_Button_Released) OnReturn_Button_Released();};
}

void LOptionMenu_Screen::DrawToWindow(sf::RenderWindow& Render_Window)
{
    GMenu::DrawToWindow(Render_Window);
    ReturnButton.DrawToWindow(Render_Window);
    Render_Window.draw(OptionsTextBlock);
    OptionsTextBlock.setPosition(Render_Window.getView().getCenter() - OptionsTextBlock.getLocalBounds().getSize() / 2.f);
}

void LOptionMenu_Screen::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    ReturnButton.OnMouseButtonAction(MouseAction);
}

void LOptionMenu_Screen::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    ReturnButton.OnMouseButtonMove(Render_Window);
}


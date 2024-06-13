#include "LMainMenu_Level.h"
#include "../../../GameMenu/MainMenu/LMenu_Hud.h"

void LMainMenu_Level::Init()
{
    MainMenu_HUD = std::make_unique<LMenu_Hud>();
}

void LMainMenu_Level::Update(float Delta_Time)
{}

void LMainMenu_Level::Render(sf::RenderWindow& window)
{
    if(MainMenu_HUD == nullptr) return;

    // draw to window
    MainMenu_HUD->DrawToWindow(window);
}

void LMainMenu_Level::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    if(MainMenu_HUD == nullptr) return;

    // on mouse move
    MainMenu_HUD->OnMouseButtonMove(Render_Window);
}

void LMainMenu_Level::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    if(MainMenu_HUD == nullptr) return;

    // on mouse action
    MainMenu_HUD->OnMouseButtonAction(MouseAction);
}

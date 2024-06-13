// LMainMenu_Screen.cpp

#include "LMainMenu_Screen.h"

LMainMenu_Screen::LMainMenu_Screen():
    Play_Button("Play", MenuButton_Size, 20, sf::Color::Transparent, sf::Color::White, ButtonFont, sf::Color::Red, sf::Color::White), // Initialize Play button
    Options_Button("Options", MenuButton_Size, 20, sf::Color::Transparent, sf::Color::White, ButtonFont, sf::Color::Red, sf::Color::White), // Initialize Options button
    Credits_Button("Credits", MenuButton_Size, 20, sf::Color::Transparent, sf::Color::White, ButtonFont, sf::Color::Red, sf::Color::White), // Initialize Credits button
    Exit_Button("Exit", MenuButton_Size, 20, sf::Color::Transparent, sf::Color::White, ButtonFont, sf::Color::Red, sf::Color::White) // Initialize Exit button
{
    if(Background_Texture.loadFromFile(TEXTURE_PATH "Saving the ocean title background.png"))
    {
        SetBackgroundTexture(Background_Texture);
    }
    Play_Button.SetButtonPosition( MenuButton_Position );
    Options_Button.SetButtonPosition( {MenuButton_Position.x, MenuButton_Position.y + SpaceBetween_Buttons} );
    Credits_Button.SetButtonPosition( {MenuButton_Position.x, MenuButton_Position.y + 2 * SpaceBetween_Buttons} );
    Exit_Button.SetButtonPosition( {MenuButton_Position.x, MenuButton_Position.y + 3 * SpaceBetween_Buttons} );
    
    // Bind the member function pointer to the Button's OnClick envoy
    Play_Button.OnReleasedEnvoy = [this] { if(OnPlay_ButtonReleasedEnvoy) OnPlay_ButtonReleasedEnvoy(); };
    Options_Button.OnReleasedEnvoy = [this] { if(OnOptions_ButtonReleasedEnvoy) OnOptions_ButtonReleasedEnvoy(); };
    Credits_Button.OnReleasedEnvoy = [this] { if(OnCredit_ButtonReleasedEnvoy) OnCredit_ButtonReleasedEnvoy(); };
    Exit_Button.OnReleasedEnvoy = [this] { if(OnExit_ButtonReleasedEnvoy) OnExit_ButtonReleasedEnvoy(); };
}

LMainMenu_Screen::~LMainMenu_Screen() = default;

void LMainMenu_Screen::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    GMenu::OnMouseButtonMove(Render_Window);
    Play_Button.OnMouseButtonMove(Render_Window);
    Options_Button.OnMouseButtonMove(Render_Window);
    Credits_Button.OnMouseButtonMove(Render_Window);
    Exit_Button.OnMouseButtonMove(Render_Window);
}

void LMainMenu_Screen::OnMouseClick()
{
    GMenu::OnMouseClick();
    Play_Button.OnMouseButtonAction(sf::Mouse::Left);
    Options_Button.OnMouseButtonAction(sf::Mouse::Left);
    Credits_Button.OnMouseButtonAction(sf::Mouse::Left);
    Exit_Button.OnMouseButtonAction(sf::Mouse::Left);
}

void LMainMenu_Screen::OnMouseRelease()
{
    GMenu::OnMouseRelease();
    Play_Button.OnMouseButtonAction(sf::Mouse::Right);
    /*Options_Button.OnMouseButtonAction(sf::Mouse::Right);
    Credits_Button.OnMouseButtonAction(sf::Mouse::Right);
    Exit_Button.OnMouseButtonAction(sf::Mouse::Right);*/
}

void LMainMenu_Screen::DrawToWindow(sf::RenderWindow& Render_Window)
{
    GMenu::DrawToWindow(Render_Window);
    
    // Draw menu buttons
    Play_Button.DrawToWindow(Render_Window);
    Options_Button.DrawToWindow(Render_Window);
    Credits_Button.DrawToWindow(Render_Window);
    Exit_Button.DrawToWindow(Render_Window);
}

bool LMainMenu_Screen::IsMouseButtonOver(sf::RenderWindow& Render_Window) const
{
    // bad way of doing it
    return true;
}

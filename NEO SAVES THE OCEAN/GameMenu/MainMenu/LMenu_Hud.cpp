#include "LMenu_Hud.h"
#include <iostream>
#include <functional>

LMenu_Hud::LMenu_Hud():
ExitModalMenu("Exit Game", "Are you sure you want to quit?")
{
    Main_Menu_Screen.OnPlay_ButtonReleasedEnvoy = [this] { SetActiveWindowByIndex(0); };
    Main_Menu_Screen.OnOptions_ButtonReleasedEnvoy = [this] { SetActiveWindowByIndex(1); };
    Main_Menu_Screen.OnCredit_ButtonReleasedEnvoy = [this] { SetActiveWindowByIndex(2); };
    Main_Menu_Screen.OnExit_ButtonReleasedEnvoy = [this] { bIsConfirmingExit = true; };

    Options_Menu_Screen.OnReturn_Button_Released = [this] { SetActiveWindowByIndex(0); };
    Credit_Menu_Screen.OnReturn_Button_Released = [this] { SetActiveWindowByIndex(0); };
    
    ExitModalMenu.OnYes_Button_Released = [this] { if(GameWindowREF) GameWindowREF->close(); };
    ExitModalMenu.OnNo_Button_Released = [this] { bIsConfirmingExit = false; };
}

LMenu_Hud::~LMenu_Hud() = default;

LObject* LMenu_Hud::GetActiveMenu()
{
    return GetMenuByIndex(MenuIndex);
}

LObject* LMenu_Hud::GetMenuByIndex(int Index)
{
    switch (Index)
    {
        case 0:
            return &Main_Menu_Screen;
        case 1:
            return &Options_Menu_Screen;
        case 2:
            return &Credit_Menu_Screen;
        default:
            std::cout << "Out Of Range Index: Index Stops At 2 \n";
    }
}

void LMenu_Hud::SetActiveWindowByIndex(int Index)
{
    if(Index == MenuIndex) return;
    
    MenuIndex = std::clamp( MenuIndex = Index, 0, 2);
}

void LMenu_Hud::DrawToWindow(sf::RenderWindow& Render_Window)
{
    GameWindowREF = &Render_Window;
    GetActiveMenu()->DrawToWindow(Render_Window);
    if(bIsConfirmingExit)
    {
        ExitModalMenu.DrawToWindow(Render_Window);
    }
}

void LMenu_Hud::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    if(bIsConfirmingExit)
    {
        ExitModalMenu.OnMouseButtonMove(Render_Window);
        return;
    }
    GetActiveMenu()->OnMouseButtonMove(Render_Window);
}

void LMenu_Hud::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    if(bIsConfirmingExit)
    {
        ExitModalMenu.OnMouseButtonAction(MouseAction);
        return;
    }
    GetActiveMenu()->OnMouseButtonAction(MouseAction);
}

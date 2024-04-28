#pragma once
#include "LCreditMenu_Screen.h"
#include "LMainMenu_Screen.h"
#include "LOptionMenu_Screen.h"
#include "../../Core/LObject.h"
#include "../GenericMenus/Modals/Generic_Modal_Menu.h"

class LMenu_Hud : public LObject
{
    sf::RenderWindow* GameWindowREF;
    int MenuIndex = 0;
    bool bIsConfirmingExit = false;
public:
    LMainMenu_Screen Main_Menu_Screen;
    LOptionMenu_Screen Options_Menu_Screen;
    LCreditMenu_Screen Credit_Menu_Screen;
    Generic_Modal_Menu ExitModalMenu;

protected:
public:
    LMenu_Hud();
    ~LMenu_Hud() override;
    LObject* GetActiveMenu();
    LObject* GetMenuByIndex( int Index );

    void SetActiveWindowByIndex( int Index );
    void DrawToWindow(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;
};

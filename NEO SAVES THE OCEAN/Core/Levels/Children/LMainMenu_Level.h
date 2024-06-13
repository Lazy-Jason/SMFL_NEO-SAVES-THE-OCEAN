#pragma once
#include "../LLevel.h"

class LMenu_Hud;

class LMainMenu_Level : public LLevel
{
    std::unique_ptr<LMenu_Hud> MainMenu_HUD = nullptr;
public:
    LMainMenu_Level() = default;
    ~LMainMenu_Level() override = default;
    
    void Init() override;
    void Update(float Delta_Time) override;
    void Render(sf::RenderWindow& window) override;
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;
};

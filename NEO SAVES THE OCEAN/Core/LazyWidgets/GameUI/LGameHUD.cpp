#include "LGameHUD.h"
#include "Layers/GameScreen/LGameScreen_Layer.h"

LGameHUD::LGameHUD() : GameScreen( std::make_unique<LGameScreen_Layer>() )
{}

void LGameHUD::Update(float Delta_Time)
{
    GameScreen->Update(Delta_Time);
}

void LGameHUD::DrawToWindow(sf::RenderWindow& Render_Window)
{
    GameScreen->DrawToWindow(Render_Window);
}

void LGameHUD::SetBoostPercent(const float& Percent) const
{
    GameScreen->SetBoostPercent(Percent);
}

void LGameHUD::SetTrashCollectedAmount(const int& CurrentValue, const int& Max_Value)
{
    GameScreen->SetTrashCollectedAmount(CurrentValue, Max_Value);
}

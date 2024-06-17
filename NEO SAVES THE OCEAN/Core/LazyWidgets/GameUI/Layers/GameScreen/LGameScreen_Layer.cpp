#include "LGameScreen_Layer.h"
#include "LHealthStat.h"
#include "LTrashStatus.h"
#include "../../LProgressBar.h"

LGameScreen_Layer::LGameScreen_Layer() : Health_StatWidget(std::make_unique<LHealthStat>()),
Boost_StatWidget(std::make_unique<LProgressBar>(sf::Vector2f(300, 20), sf::Color::Cyan, sf::Color(1, 1, 1, 150))),
Trash_StatusWidget(std::make_unique<LTrashStatus>())
{
    if(Health_StatWidget != nullptr) Health_StatWidget->SetPosition({50, 50});
    if(Boost_StatWidget != nullptr) Boost_StatWidget->SetPosition({50, 130});
    if(Trash_StatusWidget != nullptr) Trash_StatusWidget->SetPosition({ 960 - Trash_StatusWidget->GetSize().x, 970 });
}

void LGameScreen_Layer::Update(float Delta_Time)
{
    if(Health_StatWidget != nullptr) Health_StatWidget->Update(Delta_Time);
    if(Boost_StatWidget != nullptr) Boost_StatWidget->Update(Delta_Time);
}

void LGameScreen_Layer::DrawToWindow(sf::RenderWindow& Render_Window)
{
    if(Health_StatWidget != nullptr) Health_StatWidget->DrawToWindow(Render_Window);
    if(Boost_StatWidget != nullptr) Boost_StatWidget->DrawToWindow(Render_Window);
    if(Trash_StatusWidget != nullptr) Trash_StatusWidget->DrawToWindow(Render_Window);
}

void LGameScreen_Layer::SetHealth(int Health)
{
    return;
    /*if(Health_StatWidget != nullptr) Health_StatWidget->Set;*/
}

void LGameScreen_Layer::SetBoostPercent(float Percent) const
{
    if(Boost_StatWidget != nullptr) Boost_StatWidget->SetPercent(Percent);
}

void LGameScreen_Layer::SetTrashCollectedAmount(int Current_value, int Max_value) const
{
    if(Trash_StatusWidget != nullptr) Trash_StatusWidget->UpdateTrashCount(Current_value, Max_value);
}

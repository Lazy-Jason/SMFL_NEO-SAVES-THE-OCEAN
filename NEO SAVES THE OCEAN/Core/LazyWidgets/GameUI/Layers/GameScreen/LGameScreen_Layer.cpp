#include "LGameScreen_Layer.h"
#include "LHealthStat.h"
#include "../../LProgressBar.h"

LGameScreen_Layer::LGameScreen_Layer() : Health_StatWidget(std::make_unique<LHealthStat>()),
Boost_StatWidget(std::make_unique<LProgressBar>(sf::Vector2f(300, 20), sf::Color::Cyan, sf::Color(1, 1, 1, 50)))
{
    if(Health_StatWidget != nullptr) Health_StatWidget->SetPosition({50, 50});
    if(Boost_StatWidget != nullptr) Boost_StatWidget->SetPosition({50, 130});
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

#pragma once
#include "../../../../LObject.h"

class LProgressBar;
class LHealthStat;

class LGameScreen_Layer : LObject
{
    std::unique_ptr<LHealthStat> Health_StatWidget = nullptr;
    std::unique_ptr<LProgressBar> Boost_StatWidget = nullptr;

public:
    LGameScreen_Layer();
    ~LGameScreen_Layer() override = default;
    void Update(float Delta_Time) override;
    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    void SetHealth(int Health);
    void SetBoostPercent(float Percent) const;
};

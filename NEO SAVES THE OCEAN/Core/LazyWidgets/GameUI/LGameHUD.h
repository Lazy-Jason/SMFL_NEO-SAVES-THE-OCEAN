#pragma once
#include "../../LObject.h"

class LGameScreen_Layer;

class LGameHUD : public LObject
{
    std::unique_ptr<LGameScreen_Layer> GameScreen = nullptr;
public:
    LGameHUD();
    ~LGameHUD() override = default;

    void Update(float Delta_Time) override;
    void DrawToWindow(sf::RenderWindow& Render_Window) override;

    void SetBoostPercent( const float& Percent ) const;
    void SetTrashCollectedAmount( const int& CurrentValue, const int& Max_Value );
};

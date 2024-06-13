#pragma once
#include "LGame_LevelBase.h"

class LFirstGame_Level : public LGame_LevelBase
{
public:
    LFirstGame_Level() = default;
    ~LFirstGame_Level() override = default;

    void Init() override;

    void DrawToWindow(sf::RenderWindow& Render_Window) override;
};

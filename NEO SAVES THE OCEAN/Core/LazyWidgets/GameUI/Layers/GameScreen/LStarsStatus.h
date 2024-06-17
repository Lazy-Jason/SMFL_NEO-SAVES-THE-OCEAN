#pragma once
#include "../../../../LObject.h"

class LStarsStatus : public LObject
{
public:
    LStarsStatus() = default;
    ~LStarsStatus() override = default;

    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;

    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;

    void DrawToWindow(sf::RenderWindow& Render_Window) override;
    
};

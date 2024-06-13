#pragma once
#include "../LObject.h"

class LLevel : public LObject
{
public:
    LLevel() = default;
    ~LLevel() override = default;
    
    virtual void Init() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
};

#pragma once
#include "../LLevel.h"
#include "../../LazyWidgets/GameUI/LGameHUD.h"

class LPlayableCharacterBase;

struct GameLevel_Data
{
    /**
     * \brief 
     */
    int Trash_Required = 10;
    
    int Trash_Spawn = 20;

    int Enemies_Spawn = 10;
};

class LGame_LevelBase : public LLevel
{
    std::unique_ptr<LGameHUD> GameHUD_Container = nullptr;
    GameLevel_Data GameLevelInformation;

    std::shared_ptr<LPlayableCharacterBase> PlayerCharacter = nullptr;
    sf::Sprite Background;
    sf::Texture Background_Texture;
    sf::RectangleShape FinishLine_Shape;
    sf::Texture FinishLine_Texture;
    sf::Vector2f LevelBound = {3220.0f, 1280.0f};
    sf::View CameraView;

public:
    LGame_LevelBase();
    void Init() override;
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;
    void OnKeyPressed(sf::Keyboard::Key InputKey) override;
    void OnKeyReleased(sf::Keyboard::Key InputKey) override;
    void Update(float Delta_Time) override;
    void Render(sf::RenderWindow& window) override;

protected:
    void UpdateBoostUI() const;
};

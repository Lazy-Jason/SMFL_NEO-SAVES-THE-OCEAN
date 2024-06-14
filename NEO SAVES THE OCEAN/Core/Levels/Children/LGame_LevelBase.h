#pragma once
#include "../LLevel.h"
#include "../../LazyWidgets/GameUI/LGameHUD.h"

class LTrashCan;
class LPlayableCharacterBase;

struct GameLevel_Data
{
    int Trash_Required = 10;
    int Trash_Spawn = 20;
    int Enemies_Spawn = 10;
    sf::Vector2f LevelBound = { 4500.0f, 1880.0f };
    float MinDistanceFromEdge = 250.0f;
    float ObjectSpawnThreshold = 400.0f;
};

class LGame_LevelBase : public LLevel
{
    std::unique_ptr<LGameHUD> GameHUD_Container = nullptr;
    GameLevel_Data GameLevelInformation;
    std::vector<std::shared_ptr<LTrashCan>> AllTrashCan;

    std::shared_ptr<LPlayableCharacterBase> PlayerCharacter = nullptr;
    sf::Sprite Background;
    sf::Texture Background_Texture;
    sf::RectangleShape FinishLine_Shape;
    sf::Texture FinishLine_Texture;
    sf::View CameraView;

public:
    LGame_LevelBase();
    void Init() override;
    void InitTrash();
    void InitEnemies();
    void OnMouseButtonMove(sf::RenderWindow& Render_Window) override;
    void OnMouseButtonAction(sf::Mouse::Button MouseAction) override;
    void OnKeyPressed(sf::Keyboard::Key InputKey) override;
    void OnKeyReleased(sf::Keyboard::Key InputKey) override;
    void HandleCollisionCheck() const;
    void HandleCameraAndPlayerPosition();
    void Update(float Delta_Time) override;
    void Render(sf::RenderWindow& window) override;
    sf::Vector2f& GetRandomLocationInWorldBounds() const;
    const std::shared_ptr<LPlayableCharacterBase>& GetPlayerCharacter() const { return PlayerCharacter; }

protected:
    void UpdateBoostUI() const;
};

#include "LGame_LevelBase.h"
#include "../../Player/LPlayableCharacterBase.h"
#include "../../Primitive/LCollisionBase.h"

LGame_LevelBase::LGame_LevelBase()
{
    CameraView.setSize(1920, 1080);
    FinishLine_Shape.setSize(sf::Vector2f(300.0f, LevelBound.y + 50.0f));
}

void LGame_LevelBase::Init()
{
    GameHUD_Container = std::make_unique<LGameHUD>();

    LObjectSpawnParameter PlayerSpawnParam;
    PlayerSpawnParam.Location = {100, 900};

    PlayerCharacter = LCoreStatic::SpawnLObject<LPlayableCharacterBase>(PlayerSpawnParam);
    PlayerCharacter->OnBoostAdded.AddEnvoy([this]() { UpdateBoostUI(); });
    PlayerCharacter->OnBoostRemoved.AddEnvoy([this]() { UpdateBoostUI(); });
    if(Collision::CreateTextureAndBitmask(Background_Texture, TEXTURE_PATH "Underwater background.png"))
    {
        Background.setTexture(Background_Texture);
    }
    if(Collision::CreateTextureAndBitmask(FinishLine_Texture, TEXTURE_PATH "Finish Line.jpg"))
    {
        FinishLine_Shape.setTexture(&FinishLine_Texture);
        FinishLine_Shape.setPosition(LevelBound.x - FinishLine_Shape.getSize().x, 0);
    }
    Background.setScale(sf::Vector2f(2, 10));
}

void LGame_LevelBase::OnMouseButtonMove(sf::RenderWindow& Render_Window)
{
    LLevel::OnMouseButtonMove(Render_Window);
}

void LGame_LevelBase::OnMouseButtonAction(sf::Mouse::Button MouseAction)
{
    LLevel::OnMouseButtonAction(MouseAction);
}

void LGame_LevelBase::OnKeyPressed(sf::Keyboard::Key InputKey)
{
    if(GameHUD_Container != nullptr) GameHUD_Container->OnKeyPressed(InputKey);
    if(PlayerCharacter != nullptr) PlayerCharacter->OnKeyPressed(InputKey);
}

void LGame_LevelBase::OnKeyReleased(sf::Keyboard::Key InputKey)
{
    if(GameHUD_Container != nullptr) GameHUD_Container->OnKeyReleased(InputKey);
    if(PlayerCharacter != nullptr) PlayerCharacter->OnKeyReleased(InputKey);
}

void LGame_LevelBase::Update(float Delta_Time)
{
    if (PlayerCharacter != nullptr) PlayerCharacter->Update(Delta_Time);
    if (GameHUD_Container != nullptr) GameHUD_Container->Update(Delta_Time);

    // Update the camera view based on the player's position
    const sf::Vector2f playerPosition = PlayerCharacter->GetPosition();
    sf::Vector2f desiredViewCenter = playerPosition;

    // Clamp the desired view center within the level bounds
    desiredViewCenter.x = std::max(desiredViewCenter.x, CameraView.getSize().x / 2.0f);
    desiredViewCenter.x = std::min(desiredViewCenter.x, LevelBound.x - CameraView.getSize().x / 2.0f);
    desiredViewCenter.y = std::max(desiredViewCenter.y, CameraView.getSize().y / 2.0f);
    desiredViewCenter.y = std::min(desiredViewCenter.y, LevelBound.y - CameraView.getSize().y / 2.0f);

    // Set the camera view's center to the clamped desired view center
    CameraView.setCenter(desiredViewCenter);

    // Get the player's sprite dimensions
    const sf::Vector2f playerSize = sf::Vector2f(PlayerCharacter->GetGlobalBounds().width, PlayerCharacter->GetGlobalBounds().height);

    // Clamp the player's position within the level bounds, considering their sprite size
    sf::Vector2f clampedPlayerPosition = PlayerCharacter->GetPosition();
    clampedPlayerPosition.x = std::max(clampedPlayerPosition.x, 0.0f);
    clampedPlayerPosition.x = std::min(clampedPlayerPosition.x, LevelBound.x - playerSize.x);
    clampedPlayerPosition.y = std::max(clampedPlayerPosition.y, 0.0f);
    clampedPlayerPosition.y = std::min(clampedPlayerPosition.y, LevelBound.y - playerSize.y);

    // Update the player's position with the clamped position
    PlayerCharacter->SetPosition(clampedPlayerPosition);
}

void LGame_LevelBase::Render(sf::RenderWindow& window)
{
    window.setView(CameraView);
    window.draw(Background);
    window.draw(FinishLine_Shape);
    if(PlayerCharacter != nullptr) PlayerCharacter->DrawToWindow(window);

    window.setView(window.getDefaultView());
    if(GameHUD_Container != nullptr) GameHUD_Container->DrawToWindow(window);
}

void LGame_LevelBase::UpdateBoostUI() const
{
    if(PlayerCharacter == nullptr) return;

    GameHUD_Container->SetBoostPercent(PlayerCharacter->GetBoostRatio());
}

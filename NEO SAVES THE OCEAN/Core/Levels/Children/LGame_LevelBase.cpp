#include "LGame_LevelBase.h"
#include "../../FunctionLibrary/LCoreStatic.h"
#include "../../Player/LPlayableCharacterBase.h"
#include "../../Primitive/Objects/LTrashCan.h"
#include "..\..\Primitive\Collision.h"

LGame_LevelBase::LGame_LevelBase()
{
    CameraView.setSize(1920, 1080);
    FinishLine_Shape.setSize(sf::Vector2f(300.0f, GameLevelInformation.LevelBound.y + 50.0f));
}

void LGame_LevelBase::Init()
{
    GameHUD_Container = std::make_unique<LGameHUD>();

    LObjectSpawnParameter PlayerSpawnParam;
    PlayerSpawnParam.Location = {100, 900};

    PlayerCharacter = LCoreStatic::SpawnLObject<LPlayableCharacterBase>(PlayerSpawnParam);

    // Register the callbacks
    if ( PlayerCharacter.lock() != nullptr ) // Lock the weak_ptr to get a shared_ptr
    {
        PlayerCharacter.lock()->OnBoostAdded.AddEnvoy([this]() { UpdateBoostUI(); });
        PlayerCharacter.lock()->OnBoostRemoved.AddEnvoy([this]() { UpdateBoostUI(); });
    }

    UpdateBoostUI();
    if(Collision::CreateTextureAndBitmask(Background_Texture, TEXTURE_PATH "Underwater background.png"))
    {
        Background.setTexture(Background_Texture);
    }
    if(Collision::CreateTextureAndBitmask(FinishLine_Texture, TEXTURE_PATH "Finish Line.jpg"))
    {
        FinishLine_Shape.setTexture(&FinishLine_Texture);
        FinishLine_Shape.setPosition(GameLevelInformation.LevelBound.x - FinishLine_Shape.getSize().x, 0);
    }
    Background.setScale(sf::Vector2f(2, 10));

    InitTrash();
    InitEnemies();
    UpdateTrashCollectionUI();
}

void LGame_LevelBase::InitTrash()
{
    for (int i = 0; i < GameLevelInformation.Trash_Spawn; ++i)
    {
        LObjectSpawnParameter Spawn_Parameter;
        Spawn_Parameter.Location = GetRandomLocationInWorldBounds();
        std::shared_ptr<LTrashCan> New_TrashCan = LCoreStatic::SpawnLObject<LTrashCan>(Spawn_Parameter);
        New_TrashCan->OnTrashCollected.AddEnvoy([this]() { UpdateTrashCollection(); });
        AllTrashCan.push_back(New_TrashCan);
    }
}

void LGame_LevelBase::InitEnemies()
{
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
    if( PlayerCharacter.lock() ) PlayerCharacter.lock()->OnKeyPressed(InputKey);
}

void LGame_LevelBase::OnKeyReleased(sf::Keyboard::Key InputKey)
{
    if(GameHUD_Container != nullptr) GameHUD_Container->OnKeyReleased(InputKey);
    if( PlayerCharacter.lock() ) PlayerCharacter.lock()->OnKeyReleased(InputKey);
}

void LGame_LevelBase::HandleCollisionCheck()
{
    RemoveTrash();
    for (const auto& element : AllTrashCan)
    {
        if(element.lock()->GetCollisionComponent()->CheckCollision(PlayerCharacter.lock()->GetCollisionComponent()))
        {
            element.lock()->EvaluateOverlap(PlayerCharacter.lock()->GetCollisionComponent());
        }
        else
        {
            element.lock()->ReclaimOverlap();
        }
    }
}

void LGame_LevelBase::HandleCameraAndPlayerPosition()
{
    if( PlayerCharacter.lock() == nullptr ) return;
    
    // Update the camera view based on the player's position
    const sf::Vector2f playerPosition = PlayerCharacter.lock()->GetPosition();
    sf::Vector2f desiredViewCenter = playerPosition;

    // Clamp the desired view center within the level bounds
    desiredViewCenter.x = std::max(desiredViewCenter.x, CameraView.getSize().x / 2.0f);
    desiredViewCenter.x = std::min(desiredViewCenter.x, GameLevelInformation.LevelBound.x - CameraView.getSize().x / 2.0f);
    desiredViewCenter.y = std::max(desiredViewCenter.y, CameraView.getSize().y / 2.0f);
    desiredViewCenter.y = std::min(desiredViewCenter.y, GameLevelInformation.LevelBound.y - CameraView.getSize().y / 2.0f);

    // Set the camera view's center to the clamped desired view center
    CameraView.setCenter(desiredViewCenter);

    // Get the player's sprite dimensions
    const sf::Vector2f playerSize = sf::Vector2f(PlayerCharacter.lock()->GetGlobalBounds().width, PlayerCharacter.lock()->GetGlobalBounds().height);

    // Clamp the player's position within the level bounds, considering their sprite size
    sf::Vector2f clampedPlayerPosition = PlayerCharacter.lock()->GetPosition();
    clampedPlayerPosition.x = std::max(clampedPlayerPosition.x, 0.0f);
    clampedPlayerPosition.x = std::min(clampedPlayerPosition.x, GameLevelInformation.LevelBound.x - playerSize.x);
    clampedPlayerPosition.y = std::max(clampedPlayerPosition.y, 0.0f);
    clampedPlayerPosition.y = std::min(clampedPlayerPosition.y, GameLevelInformation.LevelBound.y - playerSize.y);

    // Update the player's position with the clamped position
    PlayerCharacter.lock()->SetPosition(clampedPlayerPosition);
}

void LGame_LevelBase::Update(float Delta_Time)
{
    if( PlayerCharacter.lock() ) PlayerCharacter.lock()->Update(Delta_Time);
    if(GameHUD_Container != nullptr) GameHUD_Container->Update(Delta_Time);

    HandleCollisionCheck();
    HandleCameraAndPlayerPosition();
}

void LGame_LevelBase::Render(sf::RenderWindow& window)
{
    window.setView(CameraView);
    window.draw(Background);
    window.draw(FinishLine_Shape);
    for (const auto& element : AllTrashCan)
    {
        if( element.lock() != nullptr ) element.lock()->DrawToWindow(window);
    }
    if( PlayerCharacter.lock() ) PlayerCharacter.lock()->DrawToWindow(window);

    // UI Render
    window.setView(window.getDefaultView());
    if(GameHUD_Container != nullptr) GameHUD_Container->DrawToWindow(window);
}

sf::Vector2f& LGame_LevelBase::GetRandomLocationInWorldBounds() const
{
    static sf::Vector2f NewLocation;

    if (AllTrashCan.empty())
    {
        // If no objects are present, generate a random location within the level bounds
        const float randomX = static_cast<float>(std::rand()) / RAND_MAX * (GameLevelInformation.LevelBound.x - 2 * GameLevelInformation.MinDistanceFromEdge) + GameLevelInformation.MinDistanceFromEdge;
        const float randomY = static_cast<float>(std::rand()) / RAND_MAX * (GameLevelInformation.LevelBound.y - 2 * GameLevelInformation.MinDistanceFromEdge) + GameLevelInformation.MinDistanceFromEdge;
        NewLocation = sf::Vector2f(randomX, randomY);
        return NewLocation;
    }

    bool validLocation = false;
    while (!validLocation)
    {
        // Generate a random location within the level bounds
        const float randomX = static_cast<float>(std::rand()) / RAND_MAX * (GameLevelInformation.LevelBound.x - 2 * GameLevelInformation.MinDistanceFromEdge) + GameLevelInformation.MinDistanceFromEdge;
        const float randomY = static_cast<float>(std::rand()) / RAND_MAX * (GameLevelInformation.LevelBound.y - 2 * GameLevelInformation.MinDistanceFromEdge) + GameLevelInformation.MinDistanceFromEdge;
        NewLocation = sf::Vector2f(randomX, randomY);

        // Check if the new location is at least the specified distance away from existing objects
        validLocation = true;
        for (const auto& trashCan : AllTrashCan)
        {
            if(!trashCan.lock()) break;
            const float distance = std::sqrt(std::pow(NewLocation.x - trashCan.lock()->GetPosition().x, 2) + std::pow(NewLocation.y - trashCan.lock()->GetPosition().y, 2));
            if (distance < GameLevelInformation.ObjectSpawnThreshold)
            {
                validLocation = false;
                break;
            }
        }
    }

    return NewLocation;
}

void LGame_LevelBase::UpdateTrashCollection()
{
    if( PlayerCharacter.lock() == nullptr ) return;

    PlayerCharacter.lock()->AddBoost(GameLevelInformation.BoostPerTrash_Collected);
    GameLevelInformation.Trash_Collected ++;
    UpdateTrashCollectionUI();
}

void LGame_LevelBase::UpdateTrashCollectionUI() const
{
    GameHUD_Container->SetTrashCollectedAmount
    (GameLevelInformation.Trash_Collected, GameLevelInformation.Trash_Required);
}

void LGame_LevelBase::RemoveTrash()
{
    // Remove all null weak_ptr instances from AllTrashCan
    std::erase_if
    (
        AllTrashCan,
        [](const std::weak_ptr<LTrashCan>& weakPtr)
        {
            return weakPtr.expired();
        }
    );
}

void LGame_LevelBase::UpdateBoostUI() const
{
    if( PlayerCharacter.lock() == nullptr ) return;

    GameHUD_Container->SetBoostPercent(PlayerCharacter.lock()->GetBoostRatio());
}

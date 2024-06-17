#include "LCoreStatic.h"
#include "../Levels/Children/LGame_LevelBase.h"

std::weak_ptr<LPlayableCharacterBase> LCoreStatic::GetPlayerCharacter()
{
    GEngine* Instance;
    if ((Instance = &GEngine::GetInstance()) == nullptr) return {};

    const LGame_LevelBase* GameLevelBase = dynamic_cast<LGame_LevelBase*>(Instance->GetActiveLevel().get());
    if (GameLevelBase == nullptr) return {};

    return GameLevelBase->GetPlayerCharacter();
}

bool LCoreStatic::DestroyObject( std::shared_ptr<LSpawnableObject>& ObjectToDestroy )
{
    GEngine* Instance;
    if ((Instance = &GEngine::GetInstance()) == nullptr) return false;

    return Instance->GetActiveLevel()->DestroyObject(ObjectToDestroy);
}

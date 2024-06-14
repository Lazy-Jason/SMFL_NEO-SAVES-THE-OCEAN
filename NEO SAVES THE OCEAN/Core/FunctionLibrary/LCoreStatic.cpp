#include "LCoreStatic.h"
#include "../Levels/Children/LGame_LevelBase.h"

std::shared_ptr<LPlayableCharacterBase> LCoreStatic::GetPlayerCharacter()
{
    GEngine* Instance;
    if ((Instance = &GEngine::GetInstance()) == nullptr) return nullptr;

    const LGame_LevelBase* GameLevelBase = dynamic_cast<LGame_LevelBase*>(Instance->GetActiveLevel().get());
    if (GameLevelBase == nullptr) return nullptr;

    return GameLevelBase->GetPlayerCharacter();
}

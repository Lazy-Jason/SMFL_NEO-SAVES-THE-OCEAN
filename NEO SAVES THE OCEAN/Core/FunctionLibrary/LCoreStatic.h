#pragma once
#include <SFML/Graphics.hpp>
#include "../Levels/LLevel.h"
#include "../GEngine.h"


class LPlayableCharacterBase;
class LObject;

struct LObjectSpawnParameter
{
    sf::Vector2f Location {0, 0};
    float Rotation = 0;
    sf::Vector2f Scale = {1, 1};
};

class LCoreStatic
{
public:
    /**
     * \brief Spawns a new LObject instance at the specified location with the given rotation and scale.
     *
     * This function creates a new instance of the LObject class and initializes its position, rotation, and scale
     * based on the provided spawn parameters. The function returns a shared pointer to the newly created LObject
     * instance.
     *
     * \param Spawn_Parameter A struct containing the spawn parameters for the new LObject instance.
     *                         The struct includes the following members:
     *                         - Location: A 2D vector representing the position where the LObject should be spawned.
     *                         - Rotation: A float value representing the rotation angle of the LObject in degrees.
     *                         - Scale: A 2D vector representing the scale factors for the LObject along the x and y axes.
     *
     * \return A shared pointer to the newly created LObject instance, or nullptr if the engine instance is not available.
     */
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<LObject, T>>>
    static std::shared_ptr<T> SpawnLObject(const LObjectSpawnParameter& Spawn_Parameter);
    
    /**
    * \brief Retrieves the player character from the current active game level.
    * 
    * This function accesses the current active level from the game engine instance
    * and attempts to dynamically cast it to an `LGame_LevelBase` object. If successful,
    * it retrieves and returns the player character from the game level. If the cast
    * fails or if the game engine instance or active level is null, it returns nullptr.
    * 
    * \return A shared pointer to the player character if the active level is an instance
    *         of `LGame_LevelBase`, otherwise nullptr.
    */
    static std::weak_ptr<LPlayableCharacterBase> GetPlayerCharacter();

    /**
     * \brief Destroys the specified object.
     * \param ObjectToDestroy The object to destroy.
     * \return True if the object was successfully destroyed, false otherwise.
     */
    static bool DestroyObject( std::shared_ptr<LSpawnableObject>& ObjectToDestroy );
};

template <typename T, typename>
std::shared_ptr<T> LCoreStatic::SpawnLObject(const LObjectSpawnParameter& Spawn_Parameter)
{
    GEngine* Instance;
    if(( Instance = &GEngine::GetInstance()) == nullptr ) return nullptr;

    if(Instance->GetActiveLevel() == nullptr) return nullptr;

    return Instance->GetActiveLevel()->SpawnObjectAtLocation<T>(Spawn_Parameter.Location, Spawn_Parameter.Rotation, Spawn_Parameter.Scale);
}
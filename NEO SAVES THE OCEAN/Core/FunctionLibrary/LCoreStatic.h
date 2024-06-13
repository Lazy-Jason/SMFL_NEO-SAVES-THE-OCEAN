#pragma once
#include <SFML/Graphics.hpp>
#include "../GEngine.h"
#include <iostream>

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
};

template <typename T, typename>
std::shared_ptr<T> LCoreStatic::SpawnLObject(const LObjectSpawnParameter& Spawn_Parameter)
{
    GEngine* Instance;
    if ((Instance = &GEngine::GetInstance()) == nullptr) return nullptr;

    return Instance->SpawnObjectAtLocation<T>(Spawn_Parameter.Location, Spawn_Parameter.Rotation, Spawn_Parameter.Scale);
}
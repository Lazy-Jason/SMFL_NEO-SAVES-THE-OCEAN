#pragma once
#include "../LObject.h"

class LSpawnableObject;

/**
 * \class LLevel
 * \brief Represents a game level and manages spawnable objects within the level.
 */
class LLevel : public LObject
{
    // Using shared_ptr for multiple ownership and automatic memory management
    std::vector<std::shared_ptr<LSpawnableObject>> Spawned_Objects;
public:
    LLevel() = default;
    ~LLevel() override = default;
    
    /**
     * \brief Initializes the level. Must be overridden by derived classes.
     */
    virtual void Init() = 0;

    /**
     * \brief Renders the level. Must be overridden by derived classes.
     * \param window The window to render the level to.
     */
    virtual void Render(sf::RenderWindow& window) = 0;
    
    /**
     * \brief Spawns an object of type T at the specified location, rotation, and scale.
     * \tparam T The type of object to spawn, must be derived from LObject.
     * \param Location The location to spawn the object at.
     * \param Rotation The rotation to apply to the spawned object.
     * \param Scale The scale to apply to the spawned object.
     * \return A shared pointer to the spawned object.
     */
    template <typename T>
    std::shared_ptr<T> SpawnObjectAtLocation(const sf::Vector2f Location, const float Rotation, const sf::Vector2f Scale);

    /**
     * \brief Destroys the specified object from the level.
     * \param ObjectToDestroy The object to destroy.
     * \return True if the object was successfully destroyed, false otherwise.
     */
    bool DestroyObject( std::shared_ptr<LSpawnableObject>& ObjectToDestroy );
};

template <typename T>
std::shared_ptr<T> LLevel::SpawnObjectAtLocation(const sf::Vector2f Location, const float Rotation, const sf::Vector2f Scale)
{
    static_assert(std::is_base_of_v<LSpawnableObject, T>, "T must be derived from LSpawnableObject");

    const std::shared_ptr<T> NewObject = std::make_shared<T>();

    NewObject->SetPosition(Location);
    NewObject->SetRotation(Rotation);
    NewObject->SetScale(Scale);

    Spawned_Objects.push_back(NewObject);
    return NewObject;
}
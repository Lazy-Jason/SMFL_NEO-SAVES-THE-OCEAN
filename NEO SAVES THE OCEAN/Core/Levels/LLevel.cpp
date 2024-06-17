#include "LLevel.h"
#include "../LSpawnableObject.h"

bool LLevel::DestroyObject( std::shared_ptr<LSpawnableObject>& ObjectToDestroy )
{
    if (Spawned_Objects.empty()) return false;

    // Find and remove the object from the Spawned_Objects vector
    const auto it = std::remove_if(Spawned_Objects.begin(), Spawned_Objects.end(),
    [&ObjectToDestroy](const std::shared_ptr<LSpawnableObject>& element)
    {
        return element == ObjectToDestroy;
    });
    
    ObjectToDestroy.reset();

    if (it == Spawned_Objects.end()) return false; // Object not found

    // Erase the nullified shared pointers from the vector
    Spawned_Objects.erase(it, Spawned_Objects.end());
    return true;
}

#include "LazyEnvoyDeclaraction.h"

void LazyEnvoy::AddEnvoy(const std::function<void()>& CallbackFunction)
{
    AllEnvoys.push_back(CallbackFunction);
}

void LazyEnvoy::RemoveEnvoy(const std::function<void()>& CallbackFunction)
{
    const auto it = std::remove_if(AllEnvoys.begin(), AllEnvoys.end(),
   [&CallbackFunction](const std::function<void()>& func)
   {
       // Compare the target of the functions
       return CallbackFunction.target_type() == func.target_type() &&
           CallbackFunction.target<void()>() == func.target<void()>();
   });
    AllEnvoys.erase(it, AllEnvoys.end());
}

bool LazyEnvoy::ClearEnvoy() const
{
    return AllEnvoys.empty();
}

void LazyEnvoy::AlertEnvoys() const
{
    for (const auto& element : AllEnvoys)
    {
        element();
    }
}

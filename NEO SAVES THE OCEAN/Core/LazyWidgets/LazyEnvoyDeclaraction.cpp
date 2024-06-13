#include "LazyEnvoyDeclaraction.h"

void LazyEnvoy::AddEnvoy(const std::function<void()>& CallbackFunction)
{
    AllEnvoys.push_back(CallbackFunction);
}

void LazyEnvoy::RemoveEnvoy(const std::function<void()>& CallbackFunction)
{
    std::erase(AllEnvoys, CallbackFunction);
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

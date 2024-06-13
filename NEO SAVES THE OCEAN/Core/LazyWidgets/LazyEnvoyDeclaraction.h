#pragma once
#include <vector>
#include <functional>

class LazyEnvoy
{
    using CallbackFunction = std::function<void()>;
    std::vector<CallbackFunction> AllEnvoys;

public:
    void AddEnvoy(const std::function<void()>& CallbackFunction );
    void RemoveEnvoy(const std::function<void()>& CallbackFunction );
    bool ClearEnvoy() const;

    void AlertEnvoys() const;
};

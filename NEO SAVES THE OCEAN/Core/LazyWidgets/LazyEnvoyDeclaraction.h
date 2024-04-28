#pragma once
#include <vector>
#include <functional>
#include <iostream>

// The Envoy declaration macro
#define DECLARE_ENVOY(EnvoyName, FunctionSignature) \
LazyEnvoyDeclaration<FunctionSignature> EnvoyName##Envoy;

// A helper type to store member function pointers of any class
template<typename T>
struct MemberFunctionCallback
{
    T* object;
    // Instead of a template for function, use std::function
    std::function<void()> function;

    MemberFunctionCallback(T* obj, const std::function<void()>& func) : object(obj), function(func) {}
};

class LazyEnvoyDeclarationBase
{
public:
    virtual void AlertEnvoys() = 0;
};

template<typename Function>
class LazyEnvoyDeclaration : public LazyEnvoyDeclarationBase
{
public:
    template<class UserClass>
    void BindEnvoy(UserClass* object, Function function)
    {
        callbacks_.emplace_back(object, function);
    }

    void AlertEnvoys() override
    {
        for (auto& callback : callbacks_)
        {
            // Call the function directly without std::invoke
            callback.function();
        }
    }

private:
    std::vector<MemberFunctionCallback<void>> callbacks_;
};
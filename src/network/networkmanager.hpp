#pragma once
#include "uuid/uuid.hpp"
namespace Network
{
    class BaseNetworkManager
    {
    private:
        UUID uuid;
    public:
        BaseNetworkManager() : uuid() {}
        BaseNetworkManager(const UUID& uuid) : uuid(uuid) {}
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual ~BaseNetworkManager() = default;
    };
}
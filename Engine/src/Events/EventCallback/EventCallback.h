#pragma once

#include "ccpch.h"
#include "Events/SysEvent.h"

namespace Cannis {
    class IEventCallback {
    private:
        virtual void Call(SysEvent& e) = 0;

    public:
        IEventCallback() = default;
        virtual ~IEventCallback() = default;

        void Execute(SysEvent& e) {
            Call(e);
        }
    };

    template <typename TOwner, typename TEvent>
    class SysEventCallback : public IEventCallback {
    private:
        typedef void (TOwner::* CallbackFunction)(TEvent&);

        TOwner* ownerInstance;
        CallbackFunction callbackFunction;

        virtual void Call(SysEvent& e) override {
            std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
        }

    public:
        SysEventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
            this->ownerInstance = ownerInstance;
            this->callbackFunction = callbackFunction;
        }

        virtual ~SysEventCallback() override = default;
    };
}
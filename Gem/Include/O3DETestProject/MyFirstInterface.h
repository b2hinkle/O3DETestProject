
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace O3DETestProject
{
    class MyFirstRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(O3DETestProject::MyFirstRequests, "{41B99F26-E6F9-40B5-B0CB-27DC502A6175}");

        // Put your public request methods here.

        virtual void DoSomething() = 0; // This new line was added
        
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using MyFirstRequestBus = AZ::EBus<MyFirstRequests>;

} // namespace O3DETestProject

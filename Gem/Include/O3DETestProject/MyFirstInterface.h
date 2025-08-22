
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace O3DETestProject
{
    class MyFirstRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(O3DETestProject::MyFirstRequests, "{62A1327E-9A50-420D-AC50-F5411CF5C93E}");

        // Put your public request methods here.

        virtual void DoFlash() = 0;  // this new line was added
        
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using MyFirstRequestBus = AZ::EBus<MyFirstRequests>;

} // namespace O3DETestProject

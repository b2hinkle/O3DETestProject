
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace O3DETestProject
{
    class MaterialColorFlashRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(O3DETestProject::MaterialColorFlashRequests, "{62A1327E-9A50-420D-AC50-F5411CF5C93E}");

        // Put your public request methods here.

        virtual void DoFlash() = 0;  // this new line was added
        
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using MaterialColorFlashRequestBus = AZ::EBus<MaterialColorFlashRequests>;

} // namespace O3DETestProject


#pragma once

#include <AzCore/Component/Component.h>

#include <O3DETestProject/O3DETestProjectBus.h>

namespace O3DETestProject
{
    class O3DETestProjectSystemComponent
        : public AZ::Component
        , protected O3DETestProjectRequestBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(O3DETestProjectSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        O3DETestProjectSystemComponent();
        ~O3DETestProjectSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // O3DETestProjectRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}


#include <AzCore/Serialization/SerializeContext.h>

#include "O3DETestProjectSystemComponent.h"

#include <O3DETestProject/O3DETestProjectTypeIds.h>

namespace O3DETestProject
{
    AZ_COMPONENT_IMPL(O3DETestProjectSystemComponent, "O3DETestProjectSystemComponent",
        O3DETestProjectSystemComponentTypeId);

    void O3DETestProjectSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<O3DETestProjectSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void O3DETestProjectSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("O3DETestProjectService"));
    }

    void O3DETestProjectSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("O3DETestProjectService"));
    }

    void O3DETestProjectSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void O3DETestProjectSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    O3DETestProjectSystemComponent::O3DETestProjectSystemComponent()
    {
        if (O3DETestProjectInterface::Get() == nullptr)
        {
            O3DETestProjectInterface::Register(this);
        }
    }

    O3DETestProjectSystemComponent::~O3DETestProjectSystemComponent()
    {
        if (O3DETestProjectInterface::Get() == this)
        {
            O3DETestProjectInterface::Unregister(this);
        }
    }

    void O3DETestProjectSystemComponent::Init()
    {
    }

    void O3DETestProjectSystemComponent::Activate()
    {
        O3DETestProjectRequestBus::Handler::BusConnect();
    }

    void O3DETestProjectSystemComponent::Deactivate()
    {
        O3DETestProjectRequestBus::Handler::BusDisconnect();
    }
}


#include "MyFirstComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace O3DETestProject
{
    AZ_COMPONENT_IMPL(MyFirstComponent, "MyFirstComponent", "{FA322119-225E-449B-8C07-93F89C46C1FA}");

    void MyFirstComponent::Activate()
    {
        MyFirstRequestBus::Handler::BusConnect(GetEntityId());
    }

    void MyFirstComponent::Deactivate()
    {
        MyFirstRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void MyFirstComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MyFirstComponent, AZ::Component>()
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<MyFirstComponent>("MyFirstComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<MyFirstComponent>("MyFirst Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "O3DETestProject Gem Group")
                ;
        }
    }

    void MyFirstComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MyFirstComponentService"));
    }

    void MyFirstComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
    }

    void MyFirstComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MyFirstComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
} // namespace O3DETestProject

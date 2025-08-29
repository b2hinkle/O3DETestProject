
#include "MaterialColorFlashComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

#include <AtomLyIntegration/CommonFeatures/Material/MaterialComponentBus.h>

namespace O3DETestProject
{
    AZ_COMPONENT_IMPL(MaterialColorFlashComponent, "MaterialColorFlashComponent", "{FA322119-225E-449B-8C07-93F89C46C1FA}");

    void MaterialColorFlashComponent::Activate()
    {
        MaterialColorFlashRequestBus::Handler::BusConnect(GetEntityId());

        if (m_activateImmediately)
        {
            DoFlash();
        }
    }

    void MaterialColorFlashComponent::Deactivate()
    {
        MaterialColorFlashRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void MaterialColorFlashComponent::OnTick(float deltaTime, AZ::ScriptTimePoint)
    {
        using MaterialBus = AZ::Render::MaterialComponentRequestBus;

        float ratioBeforeTicking = 0.0f;
        if (m_durationMilliseconds > 0.0f) // avoid divide by zero 
        {
            ratioBeforeTicking = m_tickTimeRemaining / m_durationMilliseconds;
        }

        m_tickTimeRemaining = m_tickTimeRemaining - deltaTime;

        AZ_Warning("IDK", false, "%f", m_tickTimeRemaining);
    

#if 0
        if (ratioBeforeTicking > 0.0f)
        {
            AZ::Color finalColor = m_color.Lerp(AZ::Color::CreateFromRgba(0, 0, 0, 255), ratioBeforeTicking);
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.intensity", AZStd::any(m_intensity));
        }
        else
        {
            // we are done, so disconnect from the tick bus and set the material back to normal
            m_tickTimeRemaining = 0.0f;
            AZ::TickBus::Handler::BusDisconnect();
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId,"emissive.enable", m_initialEmissiveEnabled);
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId,"emissive.intensity", m_initialEmissiveIntensity);
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId,"emissive.color", m_initialEmissiveColor);
        }
#else

        MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.enable", AZStd::any(true));
        MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.intensity", AZStd::any(10.f));
        MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.color", AZStd::any(AZ::Color::CreateFromRgba(255, 255, 255, 255)));

#endif
    }

    void MaterialColorFlashComponent::DoFlash()
    {
        if (!AZ::TickBus::Handler::BusIsConnected())
        {
            // we are not already ticking, so connect to the tick bus to start getting OnTick()
            AZ::TickBus::Handler::BusConnect();
            // Capture the prior properties before we start.
            using MaterialBus = AZ::Render::MaterialComponentRequestBus; // this is a convenient way to avoid typing this constantly.
            AZ_Assert(m_initialEmissiveEnabled.empty(), ".");
            MaterialBus::EventResult(m_initialEmissiveEnabled, GetEntityId(), &MaterialBus::Events::GetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.enable");
            AZ_Assert(!m_initialEmissiveEnabled.empty(), ".");
            MaterialBus::EventResult(m_initialEmissiveIntensity, GetEntityId(), &MaterialBus::Events::GetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.intensity");
            MaterialBus::EventResult(m_initialEmissiveColor, GetEntityId(), &MaterialBus::Events::GetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.color");

            // Only the Intensity animates over time, so set them all up here:
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.enable", AZStd::any(true));
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.intensity", AZStd::any(m_intensity));
            MaterialBus::Event(GetEntityId(), &MaterialBus::Events::SetPropertyValue, AZ::Render::DefaultMaterialAssignmentId, "emissive.color", AZStd::any(m_color));
        }

        m_tickTimeRemaining = m_durationMilliseconds;
    }

    void MaterialColorFlashComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MaterialColorFlashComponent, AZ::Component>()
                ->Version(1)

                ->Field("Color", &MaterialColorFlashComponent::m_color)
                ->Field("Intensity", &MaterialColorFlashComponent::m_intensity)
                ->Field("DurationMS", &MaterialColorFlashComponent::m_durationMilliseconds)
                ->Field("ActivateImmediately", &MaterialColorFlashComponent::m_activateImmediately)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<MaterialColorFlashComponent>("MaterialColorFlashComponent", "When this is triggered, flashes the emissive material property")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                        ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))

                    ->DataElement(AZ::Edit::UIHandlers::Color, &MaterialColorFlashComponent::m_color, "Color", "What color to apply to the material property")
                    ->DataElement(AZ::Edit::UIHandlers::SpinBox, &MaterialColorFlashComponent::m_durationMilliseconds, "Duration (ms)", "How long the effect fades out over.")
                        ->Attribute(AZ::Edit::Attributes::Min, 50.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 10000.0f)
                        ->Attribute(AZ::Edit::Attributes::Step, 50.0f)
                        ->Attribute(AZ::Edit::Attributes::Suffix, "ms")
                    ->DataElement(AZ::Edit::UIHandlers::SpinBox, &MaterialColorFlashComponent::m_intensity, "Intensity", "Light emissive intensity")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.1f)
                        ->Attribute(AZ::Edit::Attributes::Max, 100.0f)
                        ->Attribute(AZ::Edit::Attributes::Step, 0.25f)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &MaterialColorFlashComponent::m_activateImmediately, "Immediately Activate on start", "If checked, it will start on activate")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<MaterialColorFlashComponent>("MaterialColorFlash Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "O3DETestProject Gem Group")
                ;
        }
    }

    void MaterialColorFlashComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MaterialColorFlashComponentService"));
    }

    void MaterialColorFlashComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
    }

    void MaterialColorFlashComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("MaterialProviderService"));
    }

    void MaterialColorFlashComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
} // namespace O3DETestProject


#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "O3DETestProjectSystemComponent.h"
#include "MyFirstComponent.h"
#include "MaterialColorFlashComponent.h"

#include <O3DETestProject/O3DETestProjectTypeIds.h>

namespace O3DETestProject
{
    class O3DETestProjectModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(O3DETestProjectModule, O3DETestProjectModuleTypeId, AZ::Module);
        AZ_CLASS_ALLOCATOR(O3DETestProjectModule, AZ::SystemAllocator);

        O3DETestProjectModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                O3DETestProjectSystemComponent::CreateDescriptor(),

                MyFirstComponent::CreateDescriptor(),
                MaterialColorFlashComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<O3DETestProjectSystemComponent>(),
            };
        }
    };
}// namespace O3DETestProject

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), O3DETestProject::O3DETestProjectModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_O3DETestProject, O3DETestProject::O3DETestProjectModule)
#endif


#pragma once

#include <O3DETestProject/O3DETestProjectTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace O3DETestProject
{
    class O3DETestProjectRequests
    {
    public:
        AZ_RTTI(O3DETestProjectRequests, O3DETestProjectRequestsTypeId);
        virtual ~O3DETestProjectRequests() = default;
        // Put your public methods here
    };

    class O3DETestProjectBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using O3DETestProjectRequestBus = AZ::EBus<O3DETestProjectRequests, O3DETestProjectBusTraits>;
    using O3DETestProjectInterface = AZ::Interface<O3DETestProjectRequests>;

} // namespace O3DETestProject

#ifndef SERVICES_WI_FI_NETWORK_HPP
#define SERVICES_WI_FI_NETWORK_HPP

#include "hal/interfaces/MacAddress.hpp"
#include "infra/timer/Timer.hpp"
#include "infra/util/BoundedString.hpp"
#include "infra/util/Observer.hpp"
#include "services/network/Address.hpp"

namespace services
{
    struct WiFiSecurity
    {
        enum class SecurityMode : int8_t
        {
            unknown = -1,
            open = 0,
            wpa2MixedPsk = 1,
            wpa3Psk = 2
        };

        WiFiSecurity() = default;
        WiFiSecurity(const WiFiSecurity& other, infra::BoundedConstString key);

        bool operator==(const WiFiSecurity& other) const;
        bool operator!=(const WiFiSecurity& other) const;

        static WiFiSecurity Wpa2Security(infra::BoundedConstString key);
        static WiFiSecurity Wpa3Security(infra::BoundedConstString key);

        infra::BoundedConstString ToString() const;

        SecurityMode securityMode = SecurityMode::open;

        static const std::size_t minimumSecurityKeySize = 8;
        static const std::size_t securityKeySize = 64;
        infra::BoundedString::WithStorage<securityKeySize> key;
    };

    const uint8_t MaxSsidSize{ 32 };
    using SsidString = infra::BoundedString::WithStorage<MaxSsidSize>;

    struct IPAddresses
    {
        services::IPAddress address;
        services::IPAddress netmask;
        services::IPAddress gateway;

        bool operator==(const IPAddresses& other) const;
        bool operator!=(const IPAddresses& other) const;
    };

    struct IpConfig
    {
        bool useDhcp;
        IPAddresses addresses;

        bool operator==(const IpConfig& other) const;
        bool operator!=(const IpConfig& other) const;
    };

    enum class WiFiJoiningStatus
    {
        noError,
        unknownError,
        timeout,
        authenticationError,
        networkNotFound
    };

    class WiFiNetwork;

    class WiFiNetworkStationObserver
        : public infra::SingleObserver<WiFiNetworkStationObserver, WiFiNetwork>
    {
    public:
        using infra::SingleObserver<WiFiNetworkStationObserver, WiFiNetwork>::SingleObserver;

        virtual void LinkDown() = 0;
        virtual void LinkUp() = 0;
        virtual void IpAddressChanged() = 0;
    };

    class WiFiNetworkAccessPointObserver
        : public infra::SingleObserver<WiFiNetworkAccessPointObserver, WiFiNetwork>
    {
    public:
        using infra::SingleObserver<WiFiNetworkAccessPointObserver, WiFiNetwork>::SingleObserver;

        virtual void HasClientAssociations() = 0;
        virtual void HasNoClientAssociations() = 0;
    };

    class WiFiNetworkAccessPointResultObserver
        : public infra::SingleObserver<WiFiNetworkAccessPointResultObserver, WiFiNetwork>
    {
    public:
        using infra::SingleObserver<WiFiNetworkAccessPointResultObserver, WiFiNetwork>::SingleObserver;

        virtual void AccessPointCreated() = 0;
        virtual void AccessPointFailed() = 0;
    };

    class WiFiNetworkJoinResultObserver
        : public infra::SingleObserver<WiFiNetworkJoinResultObserver, WiFiNetwork>
    {
    public:
        using infra::SingleObserver<WiFiNetworkJoinResultObserver, WiFiNetwork>::SingleObserver;

        virtual void JoinedNetwork() = 0;
        virtual void JoinNetworkFailed(WiFiJoiningStatus error) = 0;
    };

    class WiFiNetwork
        : public infra::Subject<WiFiNetworkStationObserver>
        , public infra::Subject<WiFiNetworkAccessPointObserver>
        , public infra::Subject<WiFiNetworkJoinResultObserver>
        , public infra::Subject<WiFiNetworkAccessPointResultObserver>
    {
    public:
        virtual void StartAccessPoint(infra::BoundedConstString ssid, const WiFiSecurity& security, uint8_t channel, services::IPAddresses ipSettings) = 0;
        virtual void JoinNetwork(infra::BoundedConstString ssid, const WiFiSecurity& security, const IpConfig& ipConfig) = 0;
        virtual void JoinNetwork(infra::BoundedConstString ssid, hal::MacAddress bssid, uint8_t channel, const WiFiSecurity& security, const IpConfig& ipConfig) = 0;
        virtual void Stop() = 0;

        virtual bool GetRssi(int32_t& rssiOut) const = 0;
        virtual hal::MacAddress GetMacAddress() const = 0;
        virtual IpConfig GetIpConfig() const = 0;

        virtual bool HasAssociatedClients() const = 0;
    };

    class WiFiNetworkScanner;

    class WiFiNetworkScanNetworkForDetailsResultObserver
        : public infra::SingleObserver<WiFiNetworkScanNetworkForDetailsResultObserver, WiFiNetworkScanner>
    {
    public:
        using infra::SingleObserver<WiFiNetworkScanNetworkForDetailsResultObserver, WiFiNetworkScanner>::SingleObserver;

        virtual void NetworkDetailsAvailable(const hal::MacAddress& bssid, uint8_t channel, const WiFiSecurity& security) = 0;
        virtual void NetworkDetailsUnavailable() = 0;
    };

    class WiFiNetworkScanNetworksResultObserver
        : public infra::SingleObserver<WiFiNetworkScanNetworksResultObserver, WiFiNetworkScanner>
    {
    public:
        using infra::SingleObserver<WiFiNetworkScanNetworksResultObserver, WiFiNetworkScanner>::SingleObserver;

        virtual void NetworksFound(infra::BoundedConstString ssid, int32_t signalStrength, const WiFiSecurity& security) = 0;
    };

    class WiFiNetworkScanner
        : public infra::Subject<WiFiNetworkScanNetworkForDetailsResultObserver>
        , public infra::Subject<WiFiNetworkScanNetworksResultObserver>
    {
    public:
        virtual void ScanForNetworkDetails(infra::BoundedConstString ssid, WiFiNetworkScanNetworkForDetailsResultObserver& observer) = 0;
        virtual void ScanNetworks(int32_t numOfProbesPerChannel, infra::Optional<infra::Duration> waitTimePerChannelActive, WiFiNetworkScanNetworksResultObserver& observer) = 0;
    };

    class NetworkPing;

    class NetworkPingResultsObserver
        : public infra::SingleObserver<NetworkPingResultsObserver, NetworkPing>
    {
    public:
        using infra::SingleObserver<NetworkPingResultsObserver, NetworkPing>::SingleObserver;

        virtual void PingSuccess() = 0;
        virtual void PingFailed() = 0;
    };

    class NetworkPing
        : public infra::Subject<NetworkPingResultsObserver>
    {
    public:
        virtual void PingGateway(infra::Duration timeout) = 0;
    };
}

#endif

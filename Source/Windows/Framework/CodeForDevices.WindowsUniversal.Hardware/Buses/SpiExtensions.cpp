#include "pch.h"
#include "SpiExtensions.h"

using namespace winrt;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Devices::Spi;

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
    Windows::Devices::Spi::SpiDevice SpiExtensions::Connect(int32_t busNumber, int32_t chipSelectLine, Windows::Devices::Spi::SpiMode const& mode, int32_t dataBitLength, int32_t clockFrequency, Windows::Devices::Spi::SpiSharingMode const& sharingMode)
    {
        // Validate
        if (busNumber < 0) throw hresult_invalid_argument(L"busNumber");
        if (chipSelectLine < 0) throw hresult_invalid_argument(L"chipSelectLine");

        // Query bus information
        auto query = SpiDevice::GetDeviceSelector();
        auto busInformation = DeviceInformation::FindAllAsync(query).get();
        if (busInformation.Size() < 1)
            throw hresult_invalid_argument(L"busNumber");

        // Configure connection
        auto id = busInformation.GetAt(busNumber).Id();
        auto settings = SpiConnectionSettings(chipSelectLine);
        settings.Mode(mode);
        settings.DataBitLength(dataBitLength);
        settings.ClockFrequency(clockFrequency);
        settings.SharingMode(sharingMode);

        // Connect to device and return (null when failed)
        auto device = SpiDevice::FromIdAsync(id, settings).get();

        // Return device.
        return device;
    }
}

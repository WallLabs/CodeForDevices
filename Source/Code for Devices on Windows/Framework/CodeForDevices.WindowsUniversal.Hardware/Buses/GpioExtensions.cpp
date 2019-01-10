#include "pch.h"
#include "GpioExtensions.h"

using namespace winrt::Windows::Devices::Gpio;

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
    GpioPin GpioExtensions::Connect(uint32_t busNumber, uint32_t pinNumber, GpioPinDriveMode const& driveMode, GpioSharingMode const& sharingMode)
    {
        // Validate
        if (busNumber < 0) throw hresult_invalid_argument(L"busNumber");
        if (pinNumber < 0) throw hresult_invalid_argument(L"pinNumber");

        // Get controller (return null when doesn't exist)
        // TODO: support multiple controllers (after lightning)
        if (busNumber >= 1)
            throw hresult_invalid_argument(L"busNumber");
        auto controller = GpioController::GetDefaultAsync().get();

        // Connect to device (return null when doesn't exist)
        auto pin = controller.OpenPin(pinNumber, sharingMode);
        if (pin == nullptr)
        {
            // Not found.
            return nullptr;
        }

        // Configure pin when necessary.
        if (pin.GetDriveMode() != driveMode)
        {
            // Only set when different.
            pin.SetDriveMode(driveMode);
        }

        // Return pin.
        return pin;
    }
}
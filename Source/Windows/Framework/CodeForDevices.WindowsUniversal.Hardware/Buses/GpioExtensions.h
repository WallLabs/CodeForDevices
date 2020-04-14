#pragma once

#include "Generated Files/GpioExtensions.g.h"

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
    /// <summary>
    /// Extensions for work with GPIO devices.
    /// </summary>
    struct GpioExtensions
    {
        GpioExtensions() = delete;	// Abstract class

        /// <summary>
        /// Connects to a GPIO pin if it exists.
        /// </summary>
        /// <param name="busNumber">Bus controller number, zero based.</param>
        /// <param name="pinNumber">Pin number.</param>
        /// <param name="driveMode">Drive mode.</param>
        /// <param name="sharingMode">Sharing mode.</param>
        /// <returns>Pin when controller and device exist, otherwise null.</returns>
        static Windows::Devices::Gpio::GpioPin Connect(int32_t busNumber, int32_t pinNumber, Windows::Devices::Gpio::GpioPinDriveMode const& driveMode, Windows::Devices::Gpio::GpioSharingMode const& sharingMode);
    };
}

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::factory_implementation
{
    struct GpioExtensions : GpioExtensionsT<GpioExtensions, implementation::GpioExtensions>
    {
    };
}

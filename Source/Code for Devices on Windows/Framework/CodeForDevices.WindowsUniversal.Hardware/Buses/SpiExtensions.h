#pragma once

#include "CodeForDevices.WindowsUniversal.Hardware.Buses.SpiExtensions.g.h"

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
    /// <summary>
    /// Extensions for work with SPI devices.
    /// </summary>
    struct SpiExtensions
    {
    private:

        SpiExtensions() = delete; // Abstract class

    public:

        /// <summary>
        /// Connects to an SPI device if it exists.
        /// </summary>
        /// <param name="busNumber">Bus controller number, zero based.</param>
        /// <param name="chipSelectLine">Slave Chip Select Line.</param>
        /// <param name="mode">Communication mode, i.e. clock polarity.</param>
        /// <param name="dataBitLength">Data length in bits.</param>
        /// <param name="clockFrequency">Frequency in Hz.</param>
        /// <returns>Device when the bus controller and device exist, otherwise null.</returns>
        static Windows::Devices::Spi::SpiDevice Connect(uint32_t busNumber, uint32_t chipSelectLine, Windows::Devices::Spi::SpiMode const& mode, uint32_t dataBitLength, uint32_t clockFrequency, Windows::Devices::Spi::SpiSharingMode const& sharingMode);
    };
}

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::factory_implementation
{
    struct SpiExtensions : SpiExtensionsT<SpiExtensions, implementation::SpiExtensions>
    {
    };
}

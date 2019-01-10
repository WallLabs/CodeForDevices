#pragma once

#include "CodeForDevices.WindowsUniversal.Hardware.Buses.GpioSwdPort.g.h"

using namespace std;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Devices::Gpio;

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
    /// <summary>
    /// ARM SW-DP (Serial Wire Debug Port) bus/protocol implementation over two GPIO pins (SWD_IO and SWD_CLK).
    /// </summary>
    /// <see href="https://github.com/emlid/blackmagic/blob/feat/pi2/src/platforms/pi2/swdptap.c" />
    /// <see href="https://github.com/disk91/PySWD/blob/master/RpiGPIO.py#L195" />
    struct GpioSwdPort : GpioSwdPortT<GpioSwdPort>
    {
    private:

#pragma region Private Fields

        /// <summary>
        /// GPIO pin connected to SWD-CLK.
        /// </summary>
        GpioPin _clockPin = nullptr;

        /// <summary>
        /// GPIO pin of connected to SWD-IO.
        /// </summary>
        GpioPin _ioPin = nullptr;

#pragma endregion

#pragma region Private Mehods

        /// <summary>
        /// Sends a clock cycle on the SWD_CLK pin (high then low).
        /// </summary>
        void Clock();

        /// <summary>
        /// Changes the SWD_IO pin direction if necessary.
        /// </summary>
        void Turn(bool drive);

        /// <summary>
        /// Reads a single bit.
        /// The SWD_IO pin level is read as the value then the SWD_CLK pin is cycled.
        /// </summary>
        bool ReadBit();

        /// <summary>
        /// Reads a sequence of up to 32 bits.
        /// For each bit the SWD_IO pin level is read as the value then the SWD_CLK pin is cycled.
        /// </summary>
        uint32 ReadBits(uint8 count);

        /// <summary>
        /// Reads a sequence of up to 32 bits and checks the parity.
        /// For each bit the SWD_IO pin level is read as the value then the SWD_CLK pin is cycled.
        /// Additionally a final parity bit is read and compared against the calculated parity whilst reading the data bits.
        /// </summary>
        /// <returns>
        /// Data read and true when the parity matches the data, or false when it is corrupt.
        /// </returns>
        bool ReadBitsWithParity(uint32 *readData, uint8 count);

        /// <summary>
        /// Sends a single bit.
        /// The SWD_IO pin is set according to the value then the SWD_CLK pin is cycled.
        /// </summary>
        void WriteBit(bool writeData);

        /// <summary>
        /// Sends a sequence of up to 32 bits.
        /// For each bit the SWD_IO pin is set according to the value then the SWD_CLK pin is cycled.
        /// </summary>
        void WriteBits(uint32 writeData, uint8 count);

        /// <summary>
        /// Sends a sequence of up to 32 bits and a parity bit.
        /// For each bit the SWD_IO pin is set according to the value then the SWD_CLK pin is cycled.
        /// Additionally a final parity bit is written, calculated whilst writing the data bits.
        /// </summary>
        void WriteBitsWithParity(uint32 writeData, uint8 count);

#pragma endregion

    public:

#pragma region Lifetime

        GpioSwdPort() = delete;

        /// <summary>
        /// Creates an instance using the specified GPIO pins.
        /// </summary>
        GpioSwdPort(uint32_t busNumber, uint32_t clockPinNumber, uint32_t ioPinNumber);

        /// <summary>
        /// Frees resources owned by this instance.
        /// </summary>
        virtual ~GpioSwdPort();

#pragma endregion

#pragma region IO

        /// <summary>
        /// Sends a reset sequence.
        /// Sets the SWD_IO pin high then cycles the SWD_CLK pin 50 times,
        /// then lowers the SWD_IO pin and performs another two SWD_CLK "idle" cycles.
        /// </summary>
        void Reset();

        /// <summary>
        /// Reads one byte from the SWD port.
        /// </summary>
        uint8_t ReadByte();

        /// <summary>
        /// Reads multiple bytes from the SWD port.
        /// </summary>
        IVector<uint8_t> ReadBytes();

        /// <summary>
        /// Writes one byte from the SWD port.
        /// </summary>
        void WriteByte(uint8_t writeData);

        /// <summary>
        /// Writes multiple bytes from the SWD port.
        /// </summary>
        void WriteBytes(IVectorView<uint8_t> const& writeData);

#pragma endregion
    };
}
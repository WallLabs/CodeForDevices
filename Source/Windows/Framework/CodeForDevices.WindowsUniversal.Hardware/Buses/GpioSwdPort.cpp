#include "pch.h"
#include "GpioSwdPort.h"

using namespace std;
using namespace winrt::Windows::Devices::Gpio;

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
#pragma region Lifetime

    GpioSwdPort::GpioSwdPort(int32_t busNumber, int32_t clockPinNumber, int32_t ioPinNumber)
    {
        // Validate
        if (busNumber < 0) throw hresult_invalid_argument(L"busNumber");
        if (clockPinNumber < 0) throw hresult_invalid_argument(L"clockPinNumber");
        if (ioPinNumber < 0) throw hresult_invalid_argument(L"ioPinNumber");

        // Get controller (return null when doesn't exist)
        // TODO: support multiple controllers (after lightning)
        if (busNumber >= 1)
            throw hresult_invalid_argument(L"busNumber");
        auto controller = GpioController::GetDefaultAsync().get();

        // Open clock pin
        _clockPin = controller.OpenPin(clockPinNumber, GpioSharingMode::Exclusive);
        if (_clockPin == nullptr) throw new hresult_out_of_bounds(L"clockPinNumber");
        if (_clockPin.GetDriveMode() != GpioPinDriveMode::Output)
            _clockPin.SetDriveMode(GpioPinDriveMode::Output);

        // Open IO pin
        _ioPin = controller.OpenPin(ioPinNumber, GpioSharingMode::Exclusive);
        if (_ioPin == nullptr) throw new hresult_out_of_bounds(L"ioPinNumber");
        if (_ioPin.GetDriveMode() != GpioPinDriveMode::Output)
            _ioPin.SetDriveMode(GpioPinDriveMode::Output);
    }

    GpioSwdPort::~GpioSwdPort()
    {
        // Free resources
        if (_ioPin != nullptr)
            _ioPin.Close();
        if (_clockPin != nullptr)
            _clockPin.Close();
    }

#pragma endregion

#pragma region Private Methods

    void GpioSwdPort::Clock()
    {
        // Clock high
        _clockPin.Write(GpioPinValue::High);

        // Clock low
        _clockPin.Write(GpioPinValue::Low);
    }

    void GpioSwdPort::Turn(bool drive)
    {
        // Get current drive mode
        auto current = _ioPin.GetDriveMode();

        // Do nothing when same
        auto requested = drive ? GpioPinDriveMode::Output : GpioPinDriveMode::Input;
        if (current == requested)
            return;

        // Change direction
        if (!drive) Clock();				// Clock cycle before when changing to read mode
        _ioPin.SetDriveMode(requested);
        if (drive) Clock();					// Clock cycle afterwards when changing to wire mode
    }

    bool GpioSwdPort::ReadBit()
    {
        // Read IO pin level as value
        bool value = _ioPin.Read() == GpioPinValue::High;

        // Cycle clock to complete transaction
        Clock();

        // Return result
        return value;
    }

    uint32 GpioSwdPort::ReadBits(uint8 count)
    {
        // Read all bits
        uint32 result = 0, bit = 1;
        while (count-- > 0)
        {
            // Read bit and store in result when set
            if (ReadBit()) result |= bit;

            // Next bit...
            bit <<= 1;
        }

        // Return result
        return result;
    }

    bool GpioSwdPort::ReadBitsWithParity(uint32* readData, uint8 count)
    {
        // Read all data bits
        uint32 result = 0, bit = 1;
        byte parity = byte(0);
        while (count-- > 0)
        {
            // Read bit, store in result and add parity when set
            if (ReadBit())
            {
                result |= bit;
                parity ^= byte(1);
            }

            // Next bit...
            bit <<= 1;
        }

        // Read parity bit
        bool parityBit = ReadBit();
        bool valid = parityBit && (parity > byte(0));

        // Return result
        *readData = result;
        return valid;
    }

    void GpioSwdPort::WriteBit(bool value)
    {
        // Write IO pin level as value
        auto level = value ? GpioPinValue::High : GpioPinValue::Low;
        _ioPin.Write(level);

        // Cycle clock to complete transaction
        Clock();
    }

    void GpioSwdPort::WriteBits(uint32 value, uint8 count)
    {
        // Write all bits
        while (count-- > 0)
        {
            // Get bit value
            bool bit = (value & 1) != 0;

            // Write bit
            WriteBit(bit);

            // Next bit
            value >>= 1;
        }
    }

    void GpioSwdPort::WriteBitsWithParity(uint32 value, uint8 count)
    {
        // Read all data bits
        byte parity = byte(0);
        while (count-- > 0)
        {
            // Get bit value
            bool bit = (value & 1) > 0;

            // Write bit
            WriteBit(bit);

            // Add parity
            parity ^= byte(bit ? 1 : 0);

            // Next bit
            value >>= 1;
        }

        // Write parity bit
        bool parityBit = (parity & byte(1)) > byte(0);
        WriteBit(parityBit);
    }

#pragma endregion

#pragma region IO

    void GpioSwdPort::Reset()
    {
        // Set write mode
        Turn(true);

        // Set IO pin high
        _ioPin.Write(GpioPinValue::High);

        // Send 50 clock cycles
        for (int count = 0; count < 50; count++)
            Clock();

        // Send 2 idle cycles (with IO pin low)
        _ioPin.Write(GpioPinValue::Low);
        Clock();
        Clock();
    }

    /// <summary>
    /// Reads one byte from the SWD port.
    /// </summary>
    uint8_t GpioSwdPort::ReadByte()
    {
        throw hresult_not_implemented();
    }

    /// <summary>
    /// Reads multiple bytes from the SWD port.
    /// </summary>
    com_array<uint8_t> GpioSwdPort::ReadBytes()
    {
        throw hresult_not_implemented();
    }

    /// <summary>
    /// Writes one byte from the SWD port.
    /// </summary>
    void GpioSwdPort::WriteByte(uint8_t writeData)
    {
        writeData++;	// Avoid code analysis warning=error
        throw hresult_not_implemented();
    }

    /// <summary>
    /// Writes multiple bytes from the SWD port.
    /// </summary>
    void GpioSwdPort::WriteBytes(array_view<uint8_t const> writeData)
    {
        writeData.size();	// Avoid code analysis warning=error
        throw hresult_not_implemented();
    }

#pragma endregion
}

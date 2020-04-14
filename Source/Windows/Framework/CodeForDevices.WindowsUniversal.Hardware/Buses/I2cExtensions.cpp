#include "pch.h"
#include "I2cExtensions.h"

using namespace winrt;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Devices::I2c;

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
#pragma region Connect

    Windows::Devices::I2c::I2cDevice I2cExtensions::Connect(int32_t busNumber, int32_t address, Windows::Devices::I2c::I2cBusSpeed const& speed, Windows::Devices::I2c::I2cSharingMode const& sharingMode)
    {
        // Validate
        if (busNumber < 0) throw hresult_invalid_argument(L"busNumber");
        if (address < 0 || address > 0x7f) throw hresult_invalid_argument(L"address");

        // Query bus information
        auto query = I2cDevice::GetDeviceSelector();
        auto busInformation = DeviceInformation::FindAllAsync(query).get();
        if (busInformation.Size() < 1)
            throw hresult_invalid_argument(L"busNumber");

        // Configure connection
        auto id = busInformation.GetAt(busNumber).Id();
        auto settings = I2cConnectionSettings(address);
        settings.BusSpeed(speed);
        settings.SharingMode(sharingMode);

        // Connect to device and return (null when failed)
        auto device = I2cDevice::FromIdAsync(id, settings).get();

        // Return connected device
        return device;
    }

#pragma endregion

#pragma region Read

    uint8_t I2cExtensions::ReadByte(Windows::Devices::I2c::I2cDevice const& device)
    {
        // Call overloaded method and return result
        return ReadBytes(device, 1)[0];
    }

    com_array<uint8_t> I2cExtensions::ReadBytes(Windows::Devices::I2c::I2cDevice const& device, int32_t size)
    {
        // Create buffer
        auto readBuffer = std::vector<uint8_t>(size, 0);

        // Call extended device method
        device.Read(readBuffer);

        // Return buffer
        return com_array<uint8_t>(move(readBuffer));
    }

    uint8_t I2cExtensions::WriteReadByte(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData)
    {
        // Cast argument to correct type
        auto writeBuffer = array_view<uint8_t const>({ writeData });

        // Call overloaded method
        return WriteReadBytes(device, writeBuffer, 1)[0];
    }

    uint8_t I2cExtensions::WriteReadByte(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> writeData)
    {
        // Call overloaded method
        auto readBuffer = WriteReadBytes(device, writeData, 1);

        // Return first uint8_t in buffer
        return readBuffer[0];
    }

    com_array<uint8_t> I2cExtensions::WriteReadBytes(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData, int32_t size)
    {
        // Cast data to correct type
        auto writeBuffer = array_view<uint8_t const>({ writeData });

        // Call overloaded method
        return WriteReadBytes(device, writeBuffer, size);
    }

    com_array<uint8_t> I2cExtensions::WriteReadBytes(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> writeData, int32_t size)
    {
        // Create buffers
        auto readBuffer = std::vector<uint8_t>(size);
        size_t writeSize = writeData.size();
        auto writeBuffer = std::vector<uint8_t>(writeSize);
        std::memmove(writeBuffer.data(), &writeData, writeSize);

        // Call extended device method
        device.WriteRead(writeBuffer, readBuffer);

        // Return buffer
        return com_array<uint8_t>(std::move(readBuffer));
    }

    bool I2cExtensions::WriteReadBit(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData, uint8_t mask)
    {
        // Cast data to correct type
        auto writeBuffer = array_view<uint8_t const>({ writeData });

        // Call overloaded method and return result
        return WriteReadBit(device, writeBuffer, mask);
    }

    bool I2cExtensions::WriteReadBit(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> writeData, uint8_t mask)
    {
        // Read byte
        auto readByte = WriteReadByte(device, writeData);

        // Apply mask and return true when set
        return (readByte & mask) != 0;
    }

#pragma endregion

#pragma region Write

    void I2cExtensions::WriteByte(Windows::Devices::I2c::I2cDevice const& device, uint8_t data)
    {
        // Cast data to correct type
        auto writeBuffer = std::vector<uint8_t>({ data });

        // Call extended device function
        device.Write(writeBuffer);
    }

    /// <summary>
    /// Writes one or more data uint8_ts.
    /// </summary>
    /// <param name="device">Device to use.</param>
    /// <param name="data">Data to write.</param>
    void I2cExtensions::WriteBytes(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> data)
    {
        // Call extended device function
        device.Write(data);
    }

    /// <summary>
    /// Joins two uint8_t values then writes them.
    /// </summary>
    /// <param name="device">Device to use.</param>
    /// <param name="data1">First part of data to write.</param>
    /// <param name="data2">Second part of data to write.</param>
    void I2cExtensions::WriteJoinByte(Windows::Devices::I2c::I2cDevice const& device, uint8_t data1, uint8_t data2)
    {
        // Create buffer
        auto writeBuffer = std::vector<uint8_t>({ data1, data2 });

        // Call extended device method
        device.Write(writeBuffer);
    }

    /// <summary>
    /// Joins two uint8_t values then writes them.
    /// </summary>
    /// <param name="device">Device to use.</param>
    /// <param name="data1">First part of data to write.</param>
    /// <param name="data2">Second part of data to write.</param>
    void I2cExtensions::WriteJoinByte(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> data1, uint8_t data2)
    {
        // Cast data to correct type
        auto data2Array = array_view<uint8_t const>({ data2 });

        // Call overloaded method
        WriteJoinBytes(device, data1, data2Array);
    }

    /// <summary>
    /// Joins two uint8_t values then writes them.
    /// </summary>
    /// <param name="device">Device to use.</param>
    /// <param name="data1">First part of data to write.</param>
    /// <param name="data2">Second part of data to write.</param>
    void I2cExtensions::WriteJoinBytes(Windows::Devices::I2c::I2cDevice const& device, uint8_t data1, array_view<uint8_t const> data2)
    {
        // Cast data to correct type
        auto data1Array = array_view<uint8_t const>({ data1 });

        // Call overloaded method
        WriteJoinBytes(device, data1Array, data2);
    }

    /// <summary>
    /// Joins two uint8_t values then writes them.
    /// </summary>
    /// <param name="device">Device to use.</param>
    /// <param name="data1">First part of data to write.</param>
    /// <param name="data2">Second part of data to write.</param>
    void I2cExtensions::WriteJoinBytes(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> data1, array_view<uint8_t const> data2)
    {
        // Join buffers
        size_t addressLength = data1.size();
        size_t dataLength = data2.size();
        size_t bufferSize = addressLength + dataLength;
        auto buffer = std::vector<uint8_t>(bufferSize);
        std::memmove(buffer.data(), &data1, addressLength);
        std::memmove(buffer.data() + addressLength, &data2, dataLength);

        // Call extended device method
        device.Write(buffer);
    }

    /// <summary>
    /// Sets or clears one or more bits.
    /// </summary>
    /// <param name="device">Device to use.</param>
    /// <param name="writeData">Data to write.</param>
    /// <param name="mask">
    /// Mask of the bit to set or clear according to value.
    /// Supports setting or clearing multiple bits.
    /// </param>
    /// <param name="value">Value of the bits, i.e. set or clear.</param>
    /// <returns>Value written.</returns>
    /// <remarks>
    /// Commonly used to set register flags.
    /// Reads the current uint8_t value, merges the positive or negative bit mask according to value,
    /// then writes the modified uint8_t back.
    /// </remarks>
    uint8_t I2cExtensions::WriteReadWriteBit(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData, uint8_t mask, bool value)
    {
        // Read existing uint8_t
        auto oldByte = WriteReadByte(device, writeData);

        // Merge bit (set or clear bit accordingly)
        auto newByte = value ? (uint8_t)(oldByte | mask) : (uint8_t)(oldByte & ~mask);

        // Write new uint8_t
        WriteJoinByte(device, writeData, newByte);

        // Return the value written
        return newByte;
    }

#pragma endregion
}

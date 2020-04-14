#pragma once

#include "Generated Files/I2cExtensions.g.h"

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::implementation
{
    /// <summary>
    /// Extensions for work with I2C devices.
    /// </summary>
    struct I2cExtensions
    {
        I2cExtensions() = delete;	// Abstract class

#pragma region Constants

        /// <summary>
        /// Maximum transfer size for I2C requests on Windows IoT or Raspberry Pi 2.
        /// This is a confirmed soft limitation by Microsoft, it should be 64K.
        /// </summary>
        /// <seealso href="https://social.msdn.microsoft.com/Forums/en-US/e938900f-b732-41dc-95f6-058a39dac31d/i2c-transfer-limit-of-16384-bytes-on-raspberry-pi-2?forum=WindowsIoT"/>
        static int32_t MaximumTransferSize();

#pragma endregion

#pragma region Connect

        /// <summary>
        /// Connects to an I2C device if it exists.
        /// </summary>
        /// <param name="busNumber">Bus controller number, zero based.</param>
        /// <param name="address">7-bit I2C slave address (8 bit addresses must be shifted down to exclude the read/write bit).</param>
        /// <param name="speed">Bus speed.</param>
        /// <param name="sharingMode">Sharing mode.</param>
        /// <returns>Device when the bus controller and device exist, otherwise null.</returns>
        static Windows::Devices::I2c::I2cDevice Connect(int32_t busNumber, int32_t address, Windows::Devices::I2c::I2cBusSpeed const& speed, Windows::Devices::I2c::I2cSharingMode const& sharingMode);

#pragma endregion

#pragma region Read

        /// <summary>
        /// Reads one data byte.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <returns>Read data byte.</returns>
        static uint8_t ReadByte(Windows::Devices::I2c::I2cDevice const& device);

        /// <summary>
        /// Reads one or more data bytes.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="size">Amount of data to read.</param>
        /// <returns>Read data bytes.</returns>
        static com_array<uint8_t> ReadBytes(Windows::Devices::I2c::I2cDevice const& device, int32_t size);

        /// <summary>
        /// Writes data then reads a single byte result.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="writeData">Data to write.</param>
        /// <returns>Read data byte.</returns>
        static uint8_t WriteReadByte(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData);

        /// <summary>
        /// Writes data then reads a single byte result.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="writeData">Data to write.</param>
        /// <returns>Read data byte.</returns>
        static uint8_t WriteReadByte(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> writeData);

        /// <summary>
        /// Writes data then reads a single byte result.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="writeData">Data to write.</param>
        /// <param name="size">Amount of data to read.</param>
        /// <returns>Read data bytes.</returns>
        static com_array<uint8_t> WriteReadBytes(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData, int32_t size);

        /// <summary>
        /// Writes data then reads one or more bytes.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="writeData">Data to write.</param>
        /// <param name="size">Amount of data to read.</param>
        /// <returns>Read data bytes.</returns>
        static com_array<uint8_t> WriteReadBytes(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> writeData, int32_t size);

        /// <summary>
        /// Writes data, reads a byte result then tests on or more bits.
        /// </summary>
        /// <remarks>
        /// Commonly used to test register flags.
        /// </remarks>
        /// <param name="device">Device to use.</param>
        /// <param name="writeData">Data to write.</param>
        /// <param name="mask">Index of the bit to read, zero based.</param>
        /// <returns>True when the result was positive (any bits in the mask were set).</returns>
        static bool WriteReadBit(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData, uint8_t mask);

        /// <summary>
        /// Writes data, reads a byte result then tests on or more bits.
        /// </summary>
        /// <remarks>
        /// Commonly used to test register flags.
        /// </remarks>
        /// <param name="device">Device to use.</param>
        /// <param name="writeData">Data to write.</param>
        /// <param name="mask">Index of the bit to read, zero based.</param>
        /// <returns>True when the result was positive (any bits in the mask were set).</returns>
        static bool WriteReadBit(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> writeData, uint8_t mask);

#pragma endregion

#pragma region Write

        /// <summary>
        /// Writes one data byte.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="data">Data to write.</param>
        static void WriteByte(Windows::Devices::I2c::I2cDevice const& device, uint8_t data);

        /// <summary>
        /// Writes one or more data bytes.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="data">Data to write.</param>
        static void WriteBytes(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> data);

        /// <summary>
        /// Joins two byte values then writes them.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="data1">First part of data to write.</param>
        /// <param name="data2">Second part of data to write.</param>
        static void WriteJoinByte(Windows::Devices::I2c::I2cDevice const& device, uint8_t data1, uint8_t data2);

        /// <summary>
        /// Joins two byte values then writes them.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="data1">First part of data to write.</param>
        /// <param name="data2">Second part of data to write.</param>
        static void WriteJoinByte(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> data1, uint8_t data2);

        /// <summary>
        /// Joins two byte values then writes them.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="data1">First part of data to write.</param>
        /// <param name="data2">Second part of data to write.</param>
        static void WriteJoinBytes(Windows::Devices::I2c::I2cDevice const& device, uint8_t data1, array_view<uint8_t const> data2);

        /// <summary>
        /// Joins two byte values then writes them.
        /// </summary>
        /// <param name="device">Device to use.</param>
        /// <param name="data1">First part of data to write.</param>
        /// <param name="data2">Second part of data to write.</param>
        static void WriteJoinBytes(Windows::Devices::I2c::I2cDevice const& device, array_view<uint8_t const> data1, array_view<uint8_t const> data2);

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
        /// Reads the current byte value, merges the positive or negative bit mask according to value,
        /// then writes the modified byte back.
        /// </remarks>
        static uint8_t WriteReadWriteBit(Windows::Devices::I2c::I2cDevice const& device, uint8_t writeData, uint8_t mask, bool value);

#pragma endregion
    };
}

namespace winrt::CodeForDevices::WindowsUniversal::Hardware::Buses::factory_implementation
{
    struct I2cExtensions : I2cExtensionsT<I2cExtensions, implementation::I2cExtensions>
    {
    };
}

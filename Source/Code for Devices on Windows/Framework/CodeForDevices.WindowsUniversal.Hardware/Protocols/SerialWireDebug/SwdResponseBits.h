#pragma once

#include "pch.h"

namespace CodeForDevices
{
    namespace Windows
    {
        namespace Hardware
        {
            namespace Protocols
            {
                namespace SerialWireDebug
                {
                    /// <summary>
                    /// ARM Serial Wire Debug (SWD) protocol acknowledgment response bits.
                    /// </summary>
                    [winrt::Flags]
                    public enum class SwdResponseBits : byte
                    {
                        /// <summary>
                        /// Okay.
                        /// </summary>
                        Ok = 0x01,

                        /// <summary>
                        /// Wait.
                        /// </summary>
                        Wait = 0x02,

                        /// <summary>
                        /// Fault.
                        /// </summary>
                        Fault = 0x04
                    };
                }
            }
        }
    }
}
#pragma once

// Ensure C++/WinRT Windows Runtime library is linked.
#pragma comment(lib, "windowsapp")

// ----------------------------------------------------------------------------
// Disable Visual Studio Code Analysis warnings for external include files
#include <CodeAnalysis\Warnings.h>
#pragma warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
// ----------------------------------------------------------------------------

// CRT headers
#define _CRT_SECURE_DEPRECATE_MEMORY
#include <tchar.h>

// STL headers
#include <cstddef>
//#include <stdio.h>
//#include <iostream>
#include <memory>
//#include <sstream>

// C++/WinRT headers
#include "winrt\base.h"
#include "winrt\Windows.Foundation.h"
#include "winrt\Windows.Foundation.Collections.h"
#include "winrt\Windows.Foundation.Metadata.h"
#include "winrt\Windows.Devices.h"
#include "winrt\Windows.Devices.Enumeration.h"
#include "winrt\Windows.Devices.Gpio.h"
#include "winrt\Windows.Devices.I2c.h"
#include "winrt\Windows.Devices.Spi.h"

// ----------------------------------------------------------------------------
// Resume Visual Studio Code Analysis warnings after external includes
#pragma warning(pop)
#undef _CRT_SECURE_NO_WARNINGS
// ----------------------------------------------------------------------------
//
//// Globally used STL namespaces.
//using namespace std;
//
//// Globally used C++/WinRT namespaces.
//using namespace winrt;
//using namespace Windows::Foundation;
//using namespace Windows::Foundation::Collections;
//using namespace Windows::Foundation::Metadata;
//using namespace Windows::Devices::Enumeration;
//using namespace Windows::Devices::I2c;
//using namespace Windows::Devices::Spi;
//using namespace Windows::Devices::Gpio;

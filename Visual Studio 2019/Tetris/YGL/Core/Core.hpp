#pragma once

#pragma warning(disable:4584)

#include <Windows.h>
#include <wrl/client.h>
#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>
#include <dsound.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dsound.lib")


using namespace D2D1;
using namespace Microsoft::WRL;
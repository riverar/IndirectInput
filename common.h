#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "inc/dinput.h"

typedef HRESULT(WINAPI *DirectInputCreateAFn)(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA *ppDI, LPUNKNOWN punkOuter);
typedef HRESULT(WINAPI *DirectInputCreateWFn)(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTW *ppDI, LPUNKNOWN punkOuter);
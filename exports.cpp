#include "common.h"
#include "indirectinput.h"

#pragma warning(disable: 4104) // warning LNK4104: export of symbol 'xxx' should be PRIVATE

static DirectInputCreateAFn g_DirectInputCreateA = nullptr;
static DirectInputCreateWFn g_DirectInputCreateW = nullptr;
static IndirectInput* g_IndirectInput = nullptr;
static HMODULE g_DirectInputModule = nullptr;

void InitializeIfNeeded()
{
    if (!g_DirectInputModule)
    {
        wchar_t directInputPath[MAX_PATH] = LR"(%SystemRoot%\System32\DINPUT.DLL)";
        ExpandEnvironmentStringsW(directInputPath, directInputPath, MAX_PATH);

        g_DirectInputModule = LoadLibraryW(directInputPath);
        if (g_DirectInputModule)
        {
            g_DirectInputCreateA = reinterpret_cast<DirectInputCreateAFn>(GetProcAddress(g_DirectInputModule, "DirectInputCreateA"));
            g_DirectInputCreateW = reinterpret_cast<DirectInputCreateWFn>(GetProcAddress(g_DirectInputModule, "DirectInputCreateW"));
        }
    }
}

HRESULT WINAPI WrappedDirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA *ppDI, LPUNKNOWN punkOuter)
{
    InitializeIfNeeded();
    auto hr = g_DirectInputCreateA(hinst, dwVersion, ppDI, punkOuter);
    if (SUCCEEDED(hr))
    {
        g_IndirectInput = new IndirectInput(*ppDI);
        *ppDI = g_IndirectInput;
    }
    return hr;
}

HRESULT WINAPI WrappedDirectInputCreateW(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTW *ppDI, LPUNKNOWN punkOuter)
{
    InitializeIfNeeded();
    return g_DirectInputCreateW(hinst, dwVersion, ppDI, punkOuter);
}

HRESULT WrappedDllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    return E_FAIL;
}

HRESULT WrappedDllCanUnloadNow()
{
    return S_FALSE;
}

HRESULT WrappedDllRegisterServer()
{
    return S_OK;
}

HRESULT WrappedDllUnregisterServer()
{
    return S_OK;
}
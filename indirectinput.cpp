#include "common.h"
#include "indirectinput.h"

IndirectInput::IndirectInput(LPDIRECTINPUTA directInput)
{
    _directInput = directInput;
}

HRESULT __stdcall IndirectInput::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    return _directInput->QueryInterface(riid, ppvObj);
}

ULONG __stdcall IndirectInput::AddRef()
{
    return _directInput->AddRef();
}

ULONG __stdcall IndirectInput::Release()
{
    return _directInput->Release();
}

HRESULT __stdcall IndirectInput::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICEA * lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
    return _directInput->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
}

HRESULT __stdcall IndirectInput::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    //
    // To workaround a Windows 10 platform bug that causes a crash when a DEVCLASS_DEVICE
    // is encountered (https://aka.ms/AA3931c), we fall back to the EnumDevices behavior
    // circa 1996 [DirectInput 3.0 API (September 11, 1996, v1.0, DINPUT3E.DOC)]
    //

    HRESULT hr = _directInput->EnumDevices(DIDEVTYPE_KEYBOARD, lpCallback, pvRef, dwFlags);
    if (SUCCEEDED(hr))
    {
        hr = _directInput->EnumDevices(DIDEVTYPE_MOUSE, lpCallback, pvRef, dwFlags);
    }
    if (SUCCEEDED(hr))
    {
        hr = _directInput->EnumDevices(DIDEVTYPE_JOYSTICK, lpCallback, pvRef, dwFlags);
    }
    return hr;
}

HRESULT __stdcall IndirectInput::GetDeviceStatus(REFGUID rguid)
{
    return _directInput->GetDeviceStatus(rguid);
}

HRESULT __stdcall IndirectInput::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
    return _directInput->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT __stdcall IndirectInput::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
    return _directInput->Initialize(hinst, dwVersion);
}

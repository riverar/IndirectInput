#pragma once

class IndirectInput : public IDirectInputA
{
public:
    IndirectInput(LPDIRECTINPUTA original);

    // Inherited via IDirectInputA
    virtual HRESULT __stdcall QueryInterface(REFIID riid, LPVOID * ppvObj) override;
    virtual ULONG __stdcall AddRef(void) override;
    virtual ULONG __stdcall Release(void) override;
    virtual HRESULT __stdcall CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICEA * lplpDirectInputDevice, LPUNKNOWN pUnkOuter) override;
    virtual HRESULT __stdcall EnumDevices(DWORD, LPDIENUMDEVICESCALLBACKA, LPVOID, DWORD) override;
    virtual HRESULT __stdcall GetDeviceStatus(REFGUID) override;
    virtual HRESULT __stdcall RunControlPanel(HWND, DWORD) override;
    virtual HRESULT __stdcall Initialize(HINSTANCE, DWORD) override;

private:
    LPDIRECTINPUTA _directInput;
};

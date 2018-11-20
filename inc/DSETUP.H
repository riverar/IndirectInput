/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dsetup.h
 *  Content:    DirectXSetup, error codes and flags
 ***************************************************************************/

#ifndef __DSETUP_H__
#define __DSETUP_H__

#ifdef _WIN32
#define COM_NO_WINDOWS_H
#include <objbase.h>
#else
#define GUID   void
#define LPGUID LPVOID
#define LPWSTR LPSTR
#define INT    int
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Setup Error Codes
//
#define DSETUPERR_BADWINDOWSVERSION     -1
#define DSETUPERR_SOURCEFILENOTFOUND    -2
#define DSETUPERR_BADSOURCESIZE         -3
#define DSETUPERR_BADSOURCETIME         -4
#define DSETUPERR_NOCOPY                -5
#define DSETUPERR_OUTOFDISKSPACE        -6
#define DSETUPERR_CANTFINDINF           -7
#define DSETUPERR_CANTFINDDIR           -8
#define DSETUPERR_INTERNAL              -9
//#define DSETUPERR_NTWITHNO3D          -10  // obsolete, see docs
#define DSETUPERR_UNKNOWNOS             -11
#define DSETUPERR_USERHITCANCEL         -12
#define DSETUPERR_NOTPREINSTALLEDONNT   -13


//
// String Constants
//
#define MAX_INFLINE             (16*1024)
#define MAX_DESCRIPTION         256

//
// DSETUP Flags
//
#define DSETUP_DDRAW            0x00000001      /* install DirectDraw           */
#define DSETUP_DSOUND           0x00000002      /* install DirectSound          */
#define DSETUP_DPLAY            0x00000004      /* install DirectPlay           */
#define DSETUP_DDRAWDRV         0x00000008      /* install DirectDraw Drivers   */
#define DSETUP_DSOUNDDRV        0x00000010      /* install DirectSound Drivers  */
#define DSETUP_DPLAYSP          0x00000020      /* install DirectPlay Providers */
#define DSETUP_DVIDEO           0x00000040      /* install DirectVideo          */

#define DSETUP_D3D              0x00000200      /* install Direct3D                                                     */
//
// This flag is obsolete.
// For NT, we now return either 0 for pre installed or
// DSETUPERR_NOTPREINSTALLEDONNT which implies this version of DirectX
// is not installed on this machine.
//
//#define DSETUP_REQUIRESD3D    0x00000400 | DSETUP_D3D /* install Direct3D, pop up dialog box on NT, if no D3D present         */
#define DSETUP_DINPUT           0x00000800      /* install DirectInput                                                     */
#define DSETUP_DIRECTXSETUP     0x00001000      /* install DirectXSetup DLL's   */
#define DSETUP_PROMPTFORDRIVERS 0x10000000      /* prompt when replacing display/audio drivers  */
#define DSETUP_RESTOREDRIVERS   0x20000000      /* restore display/audio drivers  */


#define DSETUP_DIRECTX          (DSETUP_D3D | DSETUP_DDRAW | DSETUP_DSOUND | \
                                 DSETUP_DPLAY | DSETUP_DINPUT | \
                                 DSETUP_DDRAWDRV | DSETUP_DSOUNDDRV | \
                                 DSETUP_DPLAYSP)


//
// Data Structures
//
#ifndef UNICODE_ONLY
typedef struct _DIRECTXREGISTERAPPA {
    DWORD    dwSize;
    DWORD    dwFlags;
    LPSTR    lpszApplicationName;
    LPGUID   lpGUID;
    LPSTR    lpszFilename;
    LPSTR    lpszCommandLine;
    LPSTR    lpszPath;
    LPSTR    lpszCurrentDirectory;
} DIRECTXREGISTERAPPA, *PDIRECTXREGISTERAPPA, *LPDIRECTXREGISTERAPPA;
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
typedef struct _DIRECTXREGISTERAPPW {
    DWORD    dwSize;
    DWORD    dwFlags;
    LPWSTR   lpszApplicationName;
    LPGUID   lpGUID;
    LPWSTR   lpszFilename;
    LPWSTR   lpszCommandLine;
    LPWSTR   lpszPath;
    LPWSTR   lpszCurrentDirectory;
} DIRECTXREGISTERAPPW, *PDIRECTXREGISTERAPPW, *LPDIRECTXREGISTERAPPW;
#endif //!ANSI_ONLY
#ifdef UNICODE
typedef DIRECTXREGISTERAPPW DIRECTXREGISTERAPP;
typedef PDIRECTXREGISTERAPPW PDIRECTXREGISTERAPP;
typedef LPDIRECTXREGISTERAPPW LPDIRECTXREGISTERAPP;
#else
typedef DIRECTXREGISTERAPPA DIRECTXREGISTERAPP;
typedef PDIRECTXREGISTERAPPA PDIRECTXREGISTERAPP;
typedef LPDIRECTXREGISTERAPPA LPDIRECTXREGISTERAPP;
#endif // UNICODE


//
// API
//
#ifndef UNICODE_ONLY
INT
WINAPI
DirectXSetupA(
    HWND  hWnd,
    LPSTR lpszRootPath,
    DWORD dwFlags
    );
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
INT
WINAPI
DirectXSetupW(
    HWND   hWnd,
    LPWSTR lpszRootPath,
    DWORD  dwFlags
    );
#endif //!ANSI_ONLY
#ifdef UNICODE
#define DirectXSetup  DirectXSetupW
#else
#define DirectXSetup  DirectXSetupA
#endif // !UNICODE

#ifndef UNICODE_ONLY
INT
WINAPI
DirectXDeviceDriverSetupA(
    HWND  hWnd,
    LPSTR lpszDriverClass,
    LPSTR lpszINFPath,
    LPSTR lpszDriverPath,
    DWORD dwFlags
    );
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
INT
WINAPI
DirectXDeviceDriverSetupW(
    HWND   hWnd,
    LPWSTR lpszDriverClass,
    LPWSTR lpszINFPath,
    LPWSTR lpszDriverPath,
    DWORD  dwFlags
    );
#endif //!ANSI_ONLY
#ifdef UNICODE
#define DirectXDeviceDriverSetup  DirectXDeviceDriverSetupW
#else
#define DirectXDeviceDriverSetup  DirectXDeviceDriverSetupA
#endif // !UNICODE

#ifndef UNICODE_ONLY
INT
WINAPI
DirectXRegisterApplicationA(
    HWND                  hWnd,
    LPDIRECTXREGISTERAPPA lpDXRegApp
    );
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
INT
WINAPI
DirectXRegisterApplicationW(
    HWND                  hWnd,
    LPDIRECTXREGISTERAPPW lpDXRegApp
    );
#endif //!ANSI_ONLY
#ifdef UNICODE
#define DirectXRegisterApplication  DirectXRegisterApplicationW
#else
#define DirectXRegisterApplication  DirectXRegisterApplicationA
#endif // !UNICODE

INT
WINAPI
DirectXSetupIsJapan( void );

INT
WINAPI
DirectXSetupIsJapanNec( void );


//
// Function Pointers
//
#ifdef UNICODE
typedef INT (WINAPI * LPDIRECTXSETUP)(HWND, LPWSTR, DWORD);
typedef INT (WINAPI * LPDIRECTXDEVICEDRIVERSETUP)(HWND, LPWSTR, LPSTR, LPSTR, DWORD);
typedef INT (WINAPI * LPDIRECTXREGISTERAPPLICATION)(HWND, LPDIRECTXREGISTERAPPW);
#else
typedef INT (WINAPI * LPDIRECTXSETUP)(HWND, LPSTR, DWORD);
typedef INT (WINAPI * LPDIRECTXDEVICEDRIVERSETUP)(HWND, LPSTR, LPSTR, LPSTR, DWORD);
typedef INT (WINAPI * LPDIRECTXREGISTERAPPLICATION)(HWND, LPDIRECTXREGISTERAPPA);
#endif // UNICODE

typedef INT (WINAPI * LPDIRECTXSETUPISJAPAN)(VOID);
typedef INT (WINAPI * LPDIRECTXSETUPISJAPANNEC)(VOID);


#ifdef __cplusplus
};
#endif

#endif

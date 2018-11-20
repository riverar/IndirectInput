/*==========================================================================;
 *
 *  Copyright (C) 1996 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dplobby.h
 *  Content:    DirectPlayLobby include file
 ***************************************************************************/
#ifndef __DPLOBBY_INCLUDED__
#define __DPLOBBY_INCLUDED__

#include "dplay.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * GUIDS used by DirectPlay objects
 */

/* {AF465C71-9588-11cf-A020-00AA006157AC} */
DEFINE_GUID(IID_IDirectPlayLobby, 0xaf465c71, 0x9588, 0x11cf, 0xa0, 0x20, 0x0, 0xaa, 0x0, 0x61, 0x57, 0xac);
/* {26C66A70-B367-11cf-A024-00AA006157AC} */
DEFINE_GUID(IID_IDirectPlayLobbyA, 0x26c66a70, 0xb367, 0x11cf, 0xa0, 0x24, 0x0, 0xaa, 0x0, 0x61, 0x57, 0xac);



/****************************************************************************
 *
 * IDirectPlayLobby Structures
 *
 * Various structures used to invoke DirectPlayLobby.
 *
 ****************************************************************************/

typedef struct IDirectPlayLobby     FAR *LPDIRECTPLAYLOBBY;
typedef struct IDirectPlayLobby     FAR *LPDIRECTPLAYLOBBYA;
typedef struct IDirectPlayLobby     IDirectPlayLobbyA;


/*
 * DPLCONNECTION
 * Used to hold all in the informaion needed to connect
 * an application to a session or create a session
 */
typedef struct DPLCONNECTION
{
    DWORD               dwSize;             // Size of this structure
    DWORD               dwFlags;            // Flags specific to this structure
    LPDPSESSIONDESC2    lpSessionDesc;      // Pointer to session desc to use on connect
    LPDPNAME            lpPlayerName;       // Pointer to Player name structure
    GUID                guidSP;             // GUID of the DPlay SP to use
    LPVOID              lpAddress;          // Address for service provider
    DWORD               dwAddressSize;      // Size of address data
} DPLCONNECTION, FAR *LPDPLCONNECTION;

/*
 * LPCDPLCONNECTION
 * A constant pointer to DPLCONNECTION
 */
typedef const DPLCONNECTION FAR *LPCDPLCONNECTION;

/*
 * This application should create a new session as
 * described by the DPSESIONDESC structure
 */
#define DPLCONNECTION_CREATESESSION         DPOPEN_CREATE

/*
 * This application should join the session described by 
 * the DPSESIONDESC structure with the lpAddress data
 */
#define DPLCONNECTION_JOINSESSION           DPOPEN_JOIN


/*
 * DPLAPPINFO
 * Used to hold information about a registered DirectPlay
 * application
 */
typedef struct DPLAPPINFO
{
    DWORD       dwSize;             // Size of this structure
    GUID        guidApplication;    // GUID of the Application
    union
    {
        LPSTR   lpszAppNameA;       // Pointer to the Application Name
        LPWSTR  lpszAppName;
    };

} DPLAPPINFO, FAR *LPDPLAPPINFO;

/*
 * LPCDPLAPPINFO
 * A constant pointer to DPLAPPINFO
 */
typedef const DPLAPPINFO FAR *LPCDPLAPPINFO;

/****************************************************************************
 *
 * Enumeration Method Callback Prototypes
 *
 ****************************************************************************/

/*
 * Callback for EnumAddress()
 */
typedef BOOL (FAR PASCAL *LPDPENUMADDRESSCALLBACK)(
    REFGUID         guidDataType,
    DWORD           dwDataSize,
    LPCVOID         lpData,
    LPVOID          lpContext);

/*
 * Callback for EnumAddressTypes()
 */
typedef BOOL (FAR PASCAL *LPDPLENUMADDRESSTYPESCALLBACK)(
    REFGUID         guidDataType,
    LPVOID          lpContext,
    DWORD           dwFlags);

/*
 * Callback for EnumLocalApplications()
 */
typedef BOOL (FAR PASCAL * LPDPLENUMLOCALAPPLICATIONSCALLBACK)(
    LPCDPLAPPINFO   lpAppInfo,
    LPVOID          lpContext,
    DWORD           dwFlags);


/****************************************************************************
 *
 * DirectPlayLobby API Prototypes
 *
 ****************************************************************************/
#ifdef UNICODE
#define DirectPlayLobbyCreate   DirectPlayLobbyCreateW
#else
#define DirectPlayLobbyCreate   DirectPlayLobbyCreateA
#endif /* UNICODE */

extern HRESULT WINAPI DirectPlayLobbyCreateW(LPGUID, LPDIRECTPLAYLOBBY *, IUnknown *, LPVOID, DWORD );
extern HRESULT WINAPI DirectPlayLobbyCreateA(LPGUID, LPDIRECTPLAYLOBBYA *, IUnknown *, LPVOID, DWORD );


/****************************************************************************
 *
 * IDirectPlayLobby (and IDirectPlayLobbyA) Interface
 *
 ****************************************************************************/
#undef INTERFACE
#define INTERFACE IDirectPlayLobby
DECLARE_INTERFACE_( IDirectPlayLobby, IUnknown )
{
    /*  IUnknown Methods        */
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    /*  IDirectPlayLobby Methods        */
    STDMETHOD(Connect)              (THIS_ DWORD, LPDIRECTPLAY2 *, IUnknown FAR *) PURE;
    STDMETHOD(CreateAddress)        (THIS_ REFGUID, REFGUID, LPCVOID, DWORD, LPVOID, LPDWORD) PURE;
    STDMETHOD(EnumAddress)          (THIS_ LPDPENUMADDRESSCALLBACK, LPCVOID, DWORD, LPVOID) PURE;
    STDMETHOD(EnumAddressTypes)     (THIS_ LPDPLENUMADDRESSTYPESCALLBACK, REFGUID, LPVOID, DWORD) PURE;
    STDMETHOD(EnumLocalApplications)(THIS_ LPDPLENUMLOCALAPPLICATIONSCALLBACK, LPVOID, DWORD) PURE;
    STDMETHOD(GetConnectionSettings)(THIS_ DWORD, LPVOID, LPDWORD) PURE;
    STDMETHOD(ReceiveLobbyMessage)  (THIS_ DWORD, DWORD, LPDWORD, LPVOID, LPDWORD) PURE;
    STDMETHOD(RunApplication)       (THIS_ DWORD, LPDWORD, LPDPLCONNECTION, HANDLE) PURE;
    STDMETHOD(SendLobbyMessage)     (THIS_ DWORD, DWORD, LPVOID, DWORD) PURE;
    STDMETHOD(SetConnectionSettings)(THIS_ DWORD, DWORD, LPDPLCONNECTION) PURE;
    STDMETHOD(SetLobbyMessageEvent) (THIS_ DWORD, DWORD, HANDLE) PURE;

};

/****************************************************************************
 *
 * IDirectPlayLobby interface macros
 *
 ****************************************************************************/

#if !defined(__cplusplus) || defined(CINTERFACE)

#define IDirectPlayLobby_QueryInterface(p,a,b)              (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectPlayLobby_AddRef(p)                          (p)->lpVtbl->AddRef(p)
#define IDirectPlayLobby_Release(p)                         (p)->lpVtbl->Release(p)
#define IDirectPlayLobby_Connect(p,a,b,c)                   (p)->lpVtbl->Connect(p,a,b,c)
#define IDirectPlayLobby_CreateAddress(p,a,b,c,d,e,f)       (p)->lpVtbl->CreateAddress(p,a,b,c,d,e,f)
#define IDirectPlayLobby_EnumAddress(p,a,b,c,d)             (p)->lpVtbl->EnumAddress(p,a,b,c,d)
#define IDirectPlayLobby_EnumAddressTypes(p,a,b,c,d)        (p)->lpVtbl->EnumAddressTypes(p,a,b,c,d)
#define IDirectPlayLobby_EnumLocalApplications(p,a,b,c)     (p)->lpVtbl->EnumLocalApplications(p,a,b,c)
#define IDirectPlayLobby_GetConnectionSettings(p,a,b,c)     (p)->lpVtbl->GetConnectionSettings(p,a,b,c)
#define IDirectPlayLobby_ReceiveLobbyMessage(p,a,b,c,d,e)   (p)->lpVtbl->ReceiveLobbyMessage(p,a,b,c,d,e)
#define IDirectPlayLobby_RunApplication(p,a,b,c,d)          (p)->lpVtbl->RunApplication(p,a,b,c,d)
#define IDirectPlayLobby_SendLobbyMessage(p,a,b,c,d)        (p)->lpVtbl->SendLobbyMessage(p,a,b,c,d)
#define IDirectPlayLobby_SetConnectionSettings(p,a,b,c)         (p)->lpVtbl->SetConnectionSettings(p,a,b,c)
#define IDirectPlayLobby_SetLobbyMessageEvent(p,a,b,c)      (p)->lpVtbl->SetLobbyMessageEvent(p,a,b,c)

#else /* C++ */

#define IDirectPlayLobby_QueryInterface(p,a,b)              (p)->QueryInterface(a,b)
#define IDirectPlayLobby_AddRef(p)                          (p)->AddRef()
#define IDirectPlayLobby_Release(p)                         (p)->Release()
#define IDirectPlayLobby_Connect(p,a,b,c)                   (p)->Connect(a,b,c)
#define IDirectPlayLobby_CreateAddress(p,a,b,c,d,e,f)       (p)->CreateAddress(a,b,c,d,e,f)
#define IDirectPlayLobby_EnumAddress(p,a,b,c,d)             (p)->EnumAddress(a,b,c,d)
#define IDirectPlayLobby_EnumAddressTypes(p,a,b,c,d)        (p)->EnumAddressTypes(a,b,c,d)
#define IDirectPlayLobby_EnumLocalApplications(p,a,b,c)     (p)->EnumLocalApplications(a,b,c)
#define IDirectPlayLobby_GetConnectionSettings(p,a,b,c)     (p)->GetConnectionSettings(a,b,c)
#define IDirectPlayLobby_ReceiveLobbyMessage(p,a,b,c,d,e)   (p)->ReceiveLobbyMessage(a,b,c,d,e)
#define IDirectPlayLobby_RunApplication(p,a,b,c,d)          (p)->RunApplication(a,b,c,d)
#define IDirectPlayLobby_SendLobbyMessage(p,a,b,c,d)        (p)->SendLobbyMessage(a,b,c,d)
#define IDirectPlayLobby_SetConnectionSettings(p,a,b,c)         (p)->SetConnectionSettings(a,b,c)
#define IDirectPlayLobby_SetLobbyMessageEvent(p,a,b,c)      (p)->SetLobbyMessageEvent(a,b,c)

#endif

/****************************************************************************
 *
 * DirectPlayLobby Flags
 *
 ****************************************************************************/

/*
 *      This flag is a message flag used by GetApplicationData.  It can be
 *      returned in the dwMessageFlags parameter to indicate a message from
 *      the system.
 */
#define DPLAD_SYSTEM                    0x00000001


/****************************************************************************
 *
 * DirectPlayLobby system messages and message data structures
 *
 * All system message have a dwMessageFlags value of DPLAD_SYSTEM returned
 * from a call to GetApplicationData.  
 *
 ****************************************************************************/

/*
 * DPLMSG_GENERIC
 * Generic message structure used to identify the message type.
 */
typedef struct DPLMSG_GENERIC
{
    DWORD       dwType;         // Message type
} DPLMSG_GENERIC, FAR *LPDPLMSG_GENERIC;


/******************************************
 *
 *      Sytem message dwType values
 *
 *****************************************/

/*
 *  The application has read the connection settings.
 *  It is now O.K. for the lobby client to release
 *  its IDirectPlayLobby interface.
 */
#define DPLSYS_CONNECTIONSETTINGSREAD   0x00000001

/*
 *  The application's call to DirectPlayConnect failed
 */
#define DPLSYS_DPLAYCONNECTFAILED       0x00000002

/*
 *  The application has created a DirectPlay session.
 */
#define DPLSYS_DPLAYCONNECTSUCCEEDED    0x00000003

/*
 *  The application has terminated.
 */
#define DPLSYS_APPTERMINATED            0x00000004


/****************************************************************************
 *
 * DirectPlay Address ID's
 *
 ****************************************************************************/

/* DirectPlay Address
 *
 * A DirectPlay address consists of multiple chunks of data, each tagged
 * with a GUID signifying the type of data in the chunk. The chunk also
 * has a length so that unknown chunk types can be skipped.
 *
 * The EnumAddress() function is used to parse these address data chunks.
 * The address data is passed to the SPInit method in the lpAddress field
 * and the size is passed in the dwAddressSize field. These parameters are
 * then passed to EnumAddress() to enumerate the tags.
 */

/*
 * DPADDRESS
 *
 * Header for block of address data elements
 */
typedef struct _DPADDRESS
{
    GUID                guidDataType;
    DWORD               dwDataSize;
} DPADDRESS;

typedef DPADDRESS FAR* LPDPADDRESS;

 /*
 * DPAID_ServiceProvider
 *
 * Chunk is a GUID describing the service provider that created the chunk.
 * All addresses must contain this chunk.
 */

// {07D916C0-E0AF-11cf-9C4E-00A0C905425E}
DEFINE_GUID(DPAID_ServiceProvider, 
0x7d916c0, 0xe0af, 0x11cf, 0x9c, 0x4e, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

/*
 * DPAID_Phone
 *
 * Chunk is a string containing a phone number (i.e. "1-800-555-1212")
 */

// {78EC89A0-E0AF-11cf-9C4E-00A0C905425E}
DEFINE_GUID(DPAID_Phone, 
0x78ec89a0, 0xe0af, 0x11cf, 0x9c, 0x4e, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

/*
 * DPAID_Inet
 *
 * Chunk is a string containing a TCP/IP host name or an IP address
 *(i.e. "dplay.microsoft.com" or "137.55.100.173")
 */

// {C4A54DA0-E0AF-11cf-9C4E-00A0C905425E}
DEFINE_GUID(DPAID_INet, 
0xc4a54da0, 0xe0af, 0x11cf, 0x9c, 0x4e, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

/*
 * DPCOMPORTADDRESS
 *
 * Used to specify com port settings. The constants that define baud rate,
 * stop bits and parity are defined in WINBASE.H. The constants for flow
 * control are given below.
 */

#define DPCPA_NOFLOW        0           // no flow control
#define DPCPA_XONXOFFFLOW   1           // software flow control
#define DPCPA_RTSFLOW       2           // hardware flow control with RTS
#define DPCPA_DTRFLOW       3           // hardware flow control with DTR
#define DPCPA_RTSDTRFLOW    4           // hardware flow control with RTS and DTR

typedef struct _DPCOMPORTADDRESS
{
    DWORD   dwComPort;                  // COM port to use (1-4)
    DWORD   dwBaudRate;                 // baud rate (100-256k)
    DWORD   dwStopBits;                 // no. stop bits (1-2)
    DWORD   dwParity;                   // parity (none, odd, even, mark)
    DWORD   dwFlowControl;              // flow control (none, xon/xoff, rts, dtr)
} DPCOMPORTADDRESS;

typedef DPCOMPORTADDRESS FAR* LPDPCOMPORTADDRESS;

/*
 * DPAID_ComPort
 *
 * Chunk contains a DPCOMPORTADDRESS structure defining the serial port.
 */

// {F2F0CE00-E0AF-11cf-9C4E-00A0C905425E}
DEFINE_GUID(DPAID_ComPort, 
0xf2f0ce00, 0xe0af, 0x11cf, 0x9c, 0x4e, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __DPLOBBY_INCLUDED__ */

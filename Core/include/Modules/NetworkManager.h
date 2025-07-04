#pragma once

#include "Core.h"

// todo add multithreading

#pragma region typedefs

#define NETWORK_MANAGER_MAX_RESPONSE_DATA_LENGTH 8192
#define NETWORK_MANAGER_MAX_REQUEST_DATA_LENGTH 8192

/// @brief Enum representing the response codes for network requests.
typedef enum NetworkResponseCode
{
    NetworkResponseCode_Kolpa = -1,
    NetworkResponseCode_Ok = 0,
    NetworkResponseCode_UnsupportedProtocol,     /* 1 */
    NetworkResponseCode_FailedInit,              /* 2 */
    NetworkResponseCode_UrlMalformat,            /* 3 */
    NetworkResponseCode_NotBuiltIn,              /* 4 - [was obsoleted in August 2007 for
                                                           7.17.0, reused in April 2011 for 7.21.5] */
    NetworkResponseCode_CouldNotResolveProxy,    /* 5 */
    NetworkResponseCode_CouldNotResolveHost,     /* 6 */
    NetworkResponseCode_CouldNotConnect,         /* 7 */
    NetworkResponseCode_WeirdServerReply,        /* 8 */
    NetworkResponseCode_RemoteAccessDenied,      /* 9 - a service was denied by the server
                                                           due to lack of access - when login fails
                                                           this is not returned. */
    NetworkResponseCode_FTPAcceptFailed,         /* 10 - [was obsoleted in April 2006 for
                                                           7.15.4, reused in Dec 2011 for 7.24.0] */
    NetworkResponseCode_FTPWeirdPassReply,       /* 11 */
    NetworkResponseCode_FTPAcceptTimeout,        /* 12 - timeout occurred accepting server
                                                           [was obsoleted in August 2007 for 7.17.0,
                                                           reused in Dec 2011 for 7.24.0] */
    NetworkResponseCode_FTPWeirdPasvReply,       /* 13 */
    NetworkResponseCode_FTPWeird227Format,       /* 14 */
    NetworkResponseCode_FTPCanNotGetHost,        /* 15 */
    NetworkResponseCode_HTTP2,                   /* 16 - A problem in the http2 framing layer.
                                                         [was obsoleted in August 2007 for 7.17.0,
                                                         reused in July 2014 for 7.38.0] */
    NetworkResponseCode_FTPCouldNotSetType,      /* 17 */
    NetworkResponseCode_PartialFile,             /* 18 */
    NetworkResponseCode_FTPCouldNotRetrFile,     /* 19 */
    NetworkResponseCode_Obsolete20,              /* 20 - NOT USED */
    NetworkResponseCode_QuoteError,              /* 21 - quote command failure */
    NetworkResponseCode_HTTPReturnedError,       /* 22 */
    NetworkResponseCode_WriteError,              /* 23 */
    NetworkResponseCode_Obsolete24,              /* 24 - NOT USED */
    NetworkResponseCode_UploadFailed,            /* 25 - failed upload "command" */
    NetworkResponseCode_ReadError,               /* 26 - could not open/read from file */
    NetworkResponseCode_OutOfMemory,             /* 27 */
    NetworkResponseCode_OperationTimedOut,       /* 28 - the timeout time was reached */
    NetworkResponseCode_Obsolete29,              /* 29 - NOT USED */
    NetworkResponseCode_FTPPortFailed,           /* 30 - FTP PORT operation failed */
    NetworkResponseCode_FTPCouldNotUseRest,      /* 31 - the REST command failed */
    NetworkResponseCode_Obsolete32,              /* 32 - NOT USED */
    NetworkResponseCode_RangeError,              /* 33 - RANGE "command" did not work */
    NetworkResponseCode_Obsolete34,              /* 34 */
    NetworkResponseCode_SSLConnectError,         /* 35 - wrong when connecting with SSL */
    NetworkResponseCode_BadDownloadResume,       /* 36 - could not resume download */
    NetworkResponseCode_FileCouldNotReadFile,    /* 37 */
    NetworkResponseCode_LDAPCanNotBind,          /* 38 */
    NetworkResponseCode_LDAPSearchFailed,        /* 39 */
    NetworkResponseCode_Obsolete40,              /* 40 - NOT USED */
    NetworkResponseCode_Obsolete41,              /* 41 - NOT USED starting with 7.53.0 */
    NetworkResponseCode_AbortedByCallback,       /* 42 */
    NetworkResponseCode_BadFunctionArgument,     /* 43 */
    NetworkResponseCode_Obsolete44,              /* 44 - NOT USED */
    NetworkResponseCode_InterfaceFailed,         /* 45 - CURLOPT_INTERFACE failed */
    NetworkResponseCode_Obsolete46,              /* 46 - NOT USED */
    NetworkResponseCode_TooManyRedirects,        /* 47 - catch endless re-direct loops */
    NetworkResponseCode_UnknownOption,           /* 48 - User specified an unknown option */
    NetworkResponseCode_SetoptOptionSyntax,      /* 49 - Malformed setopt option */
    NetworkResponseCode_Obsolete50,              /* 50 - NOT USED */
    NetworkResponseCode_Obsolete51,              /* 51 - NOT USED */
    NetworkResponseCode_GotNothing,              /* 52 - when this is a specific error */
    NetworkResponseCode_SSLEngineNotFound,       /* 53 - SSL crypto engine not found */
    NetworkResponseCode_SSLEngineSetFailed,      /* 54 - can not set SSL crypto engine as
                                                           default */
    NetworkResponseCode_SendError,               /* 55 - failed sending network data */
    NetworkResponseCode_ReceiveError,            /* 56 - failure in receiving network data */
    NetworkResponseCode_Obsolete57,              /* 57 - NOT IN USE */
    NetworkResponseCode_SSLCertificateProblem,   /* 58 - problem with the local certificate */
    NetworkResponseCode_SSLCipher,               /* 59 - could not use specified cipher */
    NetworkResponseCode_PeerFailedVerification,  /* 60 - peer's certificate or fingerprint
                                                         was not verified fine */
    NetworkResponseCode_BadContentEncoding,      /* 61 - Unrecognized/bad encoding */
    NetworkResponseCode_Obsolete62,              /* 62 - NOT IN USE since 7.82.0 */
    NetworkResponseCode_FileSizeExceeded,        /* 63 - Maximum file size exceeded */
    NetworkResponseCode_UseSSLFailed,            /* 64 - Requested FTP SSL level failed */
    NetworkResponseCode_SendFailRewind,          /* 65 - Sending the data requires a rewind
                                                         that failed */
    NetworkResponseCode_SSLEngineInitFailed,     /* 66 - failed to initialise ENGINE */
    NetworkResponseCode_LoginDenied,             /* 67 - user, password or similar was not
                                                         accepted and we failed to login */
    NetworkResponseCode_TFTPNotFound,            /* 68 - file not found on server */
    NetworkResponseCode_TFTPPerm,                /* 69 - permission problem on server */
    NetworkResponseCode_RemoteDiskFull,          /* 70 - out of disk space on server */
    NetworkResponseCode_TFTPIllegal,             /* 71 - Illegal TFTP operation */
    NetworkResponseCode_TFTPUnknownId,           /* 72 - Unknown transfer ID */
    NetworkResponseCode_RemoteFileExists,        /* 73 - File already exists */
    NetworkResponseCode_TFTPNoSuchUser,          /* 74 - No such user */
    NetworkResponseCode_Obsolete75,              /* 75 - NOT IN USE since 7.82.0 */
    NetworkResponseCode_Obsolete76,              /* 76 - NOT IN USE since 7.82.0 */
    NetworkResponseCode_SSLCACERTBadFile,        /* 77 - could not load CACERT file, missing
                                                         or wrong format */
    NetworkResponseCode_RemoteFileNotFound,      /* 78 - remote file not found */
    NetworkResponseCode_SSH,                     /* 79 - error from the SSH layer, somewhat
                                                         generic so the error message will be of
                                                         interest when this has happened */
    NetworkResponseCode_SSLShutdownFailed,       /* 80 - Failed to shut down the SSL
                                                             connection */
    NetworkResponseCode_Again,                   /* 81 - socket is not ready for send/recv,
                                                         wait till it is ready and try again (Added
                                                         in 7.18.2) */
    NetworkResponseCode_SSLCrlBadFile,           /* 82 - could not load CRL file, missing or
                                                         wrong format (Added in 7.19.0) */
    NetworkResponseCode_SSLIssuerError,          /* 83 - Issuer check failed.  (Added in
                                                         7.19.0) */
    NetworkResponseCode_FTPPretFailed,           /* 84 - a PRET command failed */
    NetworkResponseCode_RTSPCSeqError,           /* 85 - mismatch of RTSP CSeq numbers */
    NetworkResponseCode_RTSPSessionError,        /* 86 - mismatch of RTSP Session Ids */
    NetworkResponseCode_FTPBadFileList,          /* 87 - unable to parse FTP file list */
    NetworkResponseCode_ChunkFailed,             /* 88 - chunk callback reported error */
    NetworkResponseCode_NoConnectionAvailable,   /* 89 - No connection available, the
                                                         session will be queued */
    NetworkResponseCode_SSLPinnedPubKeyNotMatch, /* 90 - specified pinned public key did not
                                                         match */
    NetworkResponseCode_SSLInvalidCertStatus,    /* 91 - invalid certificate status */
    NetworkResponseCode_HTTP2Stream,             /* 92 - stream error in HTTP/2 framing layer
                                                  */
    NetworkResponseCode_RecursiveApiCall,        /* 93 - an api function was called from
                                                         inside a callback */
    NetworkResponseCode_AuthError,               /* 94 - an authentication function returned an
                                                         error */
    NetworkResponseCode_HTTP3,                   /* 95 - An HTTP/3 layer problem */
    NetworkResponseCode_QUICConnectionError,     /* 96 - QUIC connection error */
    NetworkResponseCode_Proxy,                   /* 97 - proxy handshake error */
    NetworkResponseCode_SSLClientCert,           /* 98 - client-side certificate required */
    NetworkResponseCode_UnrecoverablePoll,       /* 99 - poll/select returned fatal error */
    NetworkResponseCode_TooLarge,                /* 100 - a value/data met its maximum */
    NetworkResponseCode_ECHRequired,             /* 101 - ECH tried but failed */
    NetworkResponseCode_Last,                    /* never use! */
    NetworkResponseCode_Reserved115 = 115,       /* 115-126 - used in tests */
    NetworkResponseCode_Reserved116 = 116,
    NetworkResponseCode_Reserved117 = 117,
    NetworkResponseCode_Reserved118 = 118,
    NetworkResponseCode_Reserved119 = 119,
    NetworkResponseCode_Reserved120 = 120,
    NetworkResponseCode_Reserved121 = 121,
    NetworkResponseCode_Reserved122 = 122,
    NetworkResponseCode_Reserved123 = 123,
    NetworkResponseCode_Reserved124 = 124,
    NetworkResponseCode_Reserved125 = 125,
    NetworkResponseCode_Reserved126 = 126
} NetworkResponseCode;

/// @brief Enum representing the type of network request.
typedef enum NetworkRequestType
{
    NetworkRequestType_GET,
    NetworkRequestType_POST,
    NetworkRequestType_PUT,
    NetworkRequestType_DELETE,
    NetworkRequestType_PATCH
} NetworkRequestType;

/// @brief Holds the request data for a network request. Can be used for all types of requests.
typedef struct NetworkRequest NetworkRequest;

/// @brief Holds the response from a network request.
typedef struct NetworkResponse
{
    char body[NETWORK_MANAGER_MAX_RESPONSE_DATA_LENGTH];
    NetworkResponseCode code;
} NetworkResponse;

/// @brief Callback function type for handling network responses.
typedef void (*NetworkResponseCallback)(const NetworkResponse *response);

#pragma endregion

///@brief Initializes the Network Manager. Should not be used by app.
void NetworkManager_Initialize();

///@brief Terminates the Network Manager. Should not be used by app.
void NetworkManager_Terminate();

/// @brief Creates a network request to use with the Network Manager.
/// @param type The type of the network request.
/// @param url The URL for the request.
/// @param data The data to send with the request.
/// @param dataSize The size of the data to send.
/// @param singleUse If true, the request will be destroyed after use.
/// @return A pointer to the created NetworkRequest.
NetworkRequest *NetworkRequest_Create(NetworkRequestType type, string url, void *data, size_t dataSize, bool singleUse);

///@brief Performs a network request.
///@param request The network request to perform.
///@param callback The callback function to handle the response.
void NetworkManager_Request(NetworkRequest *request, NetworkResponseCallback callback);

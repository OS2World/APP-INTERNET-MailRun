/* global.h */

#define INCL_WIN
#define INCL_DOS
#define INCL_REXXSAA

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <process.h>
/* #include <types.h>
#include <netinet\in.h>
#include <sys\socket.h>
#include <netdb.h> */
#include <rexxsaa.h>

#define ID_SUSPENDTIMER 12300

BOOL SOUNDS;
INT pgmData[30];
HWND hwndPopup;
CHAR mmsg[260];


CHAR passWord[CCHMAXPATH];
CHAR userName[CCHMAXPATH];
CHAR mailServer[CCHMAXPATH];
CHAR waveFile[CCHMAXPATH];
CHAR mProg[CCHMAXPATH];
CHAR mProgArgs[CCHMAXPATH];
extern VOID _Optlink suspendChk();
extern VOID queryMRSet(HWND hwndDlg);
extern VOID saveMRSet(HWND hwndDlg);
extern VOID menuChoice(HWND hwndDlg, HWND hwndFrame, HWND hwndPopup, ULONG msg, MPARAM mp1, MPARAM mp2);
ULONG (* APIENTRY pmciSendString)   (PSZ      pszCommandBuf,
                                 PSZ      pszReturnString,
                                 USHORT   wReturnLength,
                                 HWND     hwndCallBack,
                                 USHORT   usUserParm );
ULONG (* APIENTRY pmciGetErrorString)(ULONG   ulError,
                                 PSZ     pszBuffer,
                                 USHORT  usLength);
                                 
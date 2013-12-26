/* XTRA.H */

#define INCL_WIN
#define INCL_DOS
// #define INCL_REXXSAA
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <process.h>
#include <types.h>
#include <netinet\in.h>
#include <sys\socket.h>
#include <netdb.h> 
#include <sys\ioctl.h>
#include <net\if.h>
#include <net\route.h>
#include <net\if.h>
#include <net\if_arp.h>

// #include <rexxsaa.h>
#include <os2me.h>
#include <mailrun.rch>
#include <direct.h>
#include <sys\stat.h>



#define BSTACK     61440
#define bsize         4096
#define RECNUM      500
#define MAXTRIES    100

// PVOID rbuf;
// CHAR *rbuf;
extern CHAR mmsg[260];
extern BOOL SOUNDS;
HWND hwndTbar;
HWND hwndSMenu;
HWND hwndMin;
HWND hwndMax;
HWND hwndMinmax;
extern CHAR passWord[];
extern CHAR userName[];
extern CHAR mailServer[];
extern CHAR waveFile[];
extern CHAR mProg[];
extern CHAR mProgArgs[];
INT STOPME;
extern INT pgmData[30];
HINI hini;
ULONG rSize;
BOOL PAUSEAC;
BOOL PAUSESP;
// extern CHAR INIFILE[];
CHAR rcbuf[bsize];

typedef struct SSData
   {
   CHAR title[260];
   CHAR str[260];
   }SSD;
typedef SSD FAR *PFSSD;

typedef struct CData
   {
   HWND hwndF;
   HWND hwndDlg;
   CHAR dTopFold[260];
   CHAR ftitle[260];
   INT interval;
   }CBD;
typedef CBD FAR *PFCBD;

typedef struct MData
   {
   HWND hwndDlg;
   CHAR str[bsize];
   }MBD;
typedef MBD FAR *PFMBD;

typedef struct INETData
   {
   CHAR INDATE[80];
   // CHAR INTIME[80];
   CHAR INSUBJECT[1024];
   CHAR INSIZE[80];
   CHAR INFROM[1024];
   }INETD;
typedef INETD FAR *PFINETD;

INETD pvdat[RECNUM];
INETD netchatdat;

CBD chkdat1;
CBD chkdat2;
CBD chkdat3;
CBD chkdat4;
INT mailthread;
INT mailthread2;
INT suspendthread;
INT mthread;
BOOL PREVIEWBUSY;
HPOINTER      oldMPointer;
HPOINTER      newMPointer;
PFNWP oldProc1;
PFNWP oldProc2;
PFNWP oldProc3;
PFNWP oldProc4;
PFNWP oldProc5;
PFNWP oldProc6;
PFNWP oldProc7;
PFNWP oldProc8;
PFNWP oldProc9;
PFNWP oldProc10;
PFNWP oldProc11;
PFNWP oldProc12;
PFNWP oldProc13;
CHAR receivebufA[bsize];
CHAR baseDLName[260];
CHAR dloadname[260];
PFNWP oldWinProc;
PFNWP moldWinProc;
PFNWP voldWinProc;
INT FLOATME;
BOOL GOTHAIL;
CHAR netChatArg[260];
CHAR fqNCPath[260];



MRESULT EXPENTRY saveFileProc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY NewTxtProc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY VNewTxtProc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 );
extern ULONG (* APIENTRY pmciSendString)   (PSZ      pszCommandBuf,
                                 PSZ      pszReturnString,
                                 USHORT   wReturnLength,
                                 HWND     hwndCallBack,
                                 USHORT   usUserParm );
extern ULONG (* APIENTRY pmciGetErrorString)(ULONG   ulError,
                                 PSZ     pszBuffer,
                                 USHORT  usLength);ULONG (* APIENTRY pmciSendString) (PSZ      pszCommandBuf,
                                                     PSZ      pszReturnString,
                                                     USHORT   wReturnLength,
                                                     HWND     hwndCallBack,
                                                     USHORT   usUserParm );
INT msgBoxOKCANCEL(HWND hwndDlg, CHAR *title, CHAR *msg);
VOID msgOKBox(HWND hwnd, CHAR *title, CHAR *message);
INT existFile(CHAR *fl);
INT chkValidPath(CHAR *dstr);
INT getStr1(CHAR *tmp, CHAR *dStr);
INT getStr2(INT cz, CHAR *tmp, CHAR *dStr);
VOID dloadM(CHAR *dStr);
VOID dload(INT num, CHAR *dStr);
VOID _Optlink dloadV(PVOID viewdat);
INT playWavFile(CHAR *fname, INT volnum);
VOID queryMRSet(HWND hwndDlg);
VOID saveMRSet(HWND hwndDlg);
VOID _Optlink startMPreview(PVOID hwnd);
VOID _Optlink startMProg(PVOID hwnd);
VOID _Optlink suspendChk(PVOID hwnd);
VOID _Optlink checkForMail(PVOID chkmaildat);
VOID _Optlink checkForMailNow(PVOID chkmaildat);
VOID _Optlink previewMail(PVOID chkmaildat);
VOID _Optlink deleteMail(PVOID deletemaildat);
VOID _Optlink deleteAllMail(PVOID deletemaildat);
VOID _Optlink downloadMail(PVOID downloadmaildat);
VOID _Optlink downloadALLMail(PVOID downloadmaildat);
VOID _Optlink downloadMailV(PVOID downloadmaildat);
// VOID msgOK(CHAR *title, CHAR *message);
VOID debugMsgCH(CHAR ch, CHAR *varName);
VOID debugMsgStr(CHAR *str, CHAR *varName);
VOID debugMsgULong(ULONG num, CHAR *varName);
VOID debugMsgLong(LONG num, CHAR *varName);
VOID debugMsgInt(INT num, CHAR *varName);
VOID debugWriteStr(CHAR *title, CHAR *str);
VOID dbgWriteStr(CHAR *titleStr, CHAR *dStr);
VOID dbgWriteStr2(CHAR *titleStr, CHAR *dStr);
VOID _Optlink debugWriteStrTHREAD(PVOID strdat);
VOID MRnotify(HWND hwndDlg, INT mode, CHAR *msg);
VOID menuChoice(HWND hwndDlg, HWND hwndFrame, HWND hwndPopup, ULONG msg, MPARAM mp1, MPARAM mp2);
void strdelc(char *s, char c);
int strndel(char *s, int n);
char * strinsert(char *s, char insert);
VOID startMailProg(VOID);
VOID callPgm(PSZ PgmName, PSZ PgmInputs, SHORT PgmType,
	         ULONG swapStuff, PSZ startDir,  PSZ title );
VOID saveheaderData(INT indx, CHAR *buf);
VOID savesizeData(INT indx, CHAR *buf);
VOID zeroData(VOID);
VOID SetPtrDefault (VOID);
VOID SetPtrWait (VOID);
VOID subcpview(HWND hwndDlg);
VOID unsubcpview(HWND hwndDlg);
MRESULT EXPENTRY PREVIEWDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
// BOOL saveheaderDataToFile(INT curn, INT maxn, CHAR *buf);
BOOL saveheaderDataToFile(CHAR *buf);
BOOL isNCActive(VOID);
BOOL callPgmDSS(PSZ PgmName, PSZ PgmInputs, UINT PgmType, ULONG SSFStuff, PSZ startDir,  PSZ title );





/* xtra.c  */

#define TCPV40HDRS

#include <xtra.h>
#include <xtrarc.h>
#include <notify1.h>
#include <viewmr.h>
#include <about.h>
#include <settings.h>
#include <preview.h>
#include <ncset.h>




VOID msgOKBox(HWND hwnd, CHAR *title, CHAR *message)
{
WinMessageBox(HWND_DESKTOP,
                     hwnd,
                     message,
                     title,
                     0,
                     MB_OK | MB_ICONEXCLAMATION );
}


MRESULT EXPENTRY NewTxtProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 )
{
PFNWP moldWinProc;

moldWinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CONTEXTMENU :
      {
      WinSendMsg(WinQueryWindow(hwndWnd, QW_OWNER), WM_CONTEXTMENU, 0, 0);
      }
      break;

   default :
      break;
   }
return( *moldWinProc ) (hwndWnd, ulMsg, mp1, mp2);
}




MRESULT EXPENTRY VNewTxtProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 )
{
PFNWP voldWinProc;

voldWinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CONTEXTMENU :
      {
      WinSendMsg(WinQueryWindow(hwndWnd, QW_OWNER), WM_CONTEXTMENU, 0, 0);
      }
      break;

   default :
      break;
   }
return( *voldWinProc ) (hwndWnd, ulMsg, mp1, mp2);
}



MRESULT EXPENTRY saveFileProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 )
{
PFNWP oldWinProc;
HAB habA;
PCHAR pchStr;
LONG len;

oldWinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_BEGINDRAG :
      {
      PDRAGINFO pdrginfo ;
      DRAGITEM drgitem, *pdrgitem ;
      DRAGIMAGE drgimage ;
      HWND hwndTarget;
      CHAR szFullPathName[260] ;
      CHAR szFullDocName[260] ;
      CHAR cwd[260];
      CHAR fileName[] = "TEMP.TXT";
      HPOINTER  standard;
      FILE *handd;

      strcpy(szFullPathName, "");
      strcpy(szFullDocName, "");
      _getcwd(cwd, 260);
      if( cwd != NULL )
         {
         strcpy(szFullDocName, cwd);
         strcpy(szFullPathName, cwd);
         if( szFullDocName[strlen(szFullDocName)-1] != '\\' )
            {
	 strcat(szFullDocName, "\\");
	 }
         }
      strcat(szFullDocName, fileName);

      standard = WinLoadPointer(HWND_DESKTOP, 0L, 256);
      
      WinQueryDlgItemText(WinQueryWindow(hwndWnd, QW_PARENT),
		               1000,
		               sizeof(receivebufA), receivebufA);

      handd = fopen( szFullDocName, "w+b" );
      fwrite(&receivebufA, strlen(receivebufA), 1, handd);
      fclose(handd);

      pdrginfo = DrgAllocDraginfo( 1L) ;
      pdrginfo -> hwndSource = hwndWnd;

      drgitem.hwndItem = hwndWnd;
      drgitem.ulItemID = 100L ;
      drgitem.hstrType = DrgAddStrHandle( DRT_TEXT) ;
      drgitem.hstrRMF = DrgAddStrHandle( "(DRM_OS2FILE)x(DRF_TEXT,DRF_UNKNOWN)" ) ;
      drgitem.hstrContainerName = DrgAddStrHandle(szFullPathName) ;
      drgitem.hstrSourceName = DrgAddStrHandle(fileName) ;
      drgitem.hstrTargetName = NULLHANDLE ;
      drgitem.cxOffset = 0 ;
      drgitem.cyOffset = 0 ;
      drgitem.fsControl = DC_REMOVEABLEMEDIA ;
      drgitem.fsSupportedOps = DO_COPYABLE;

      pdrgitem = (PDRAGITEM)( pdrginfo + 1) ;

      if( !DrgSetDragitem( pdrginfo, &drgitem, sizeof( DRAGITEM), 0L))
	WinAlarm( HWND_DESKTOP, WA_ERROR) ;


      drgimage.cb = sizeof( DRAGIMAGE) ;
      drgimage.cptl = 0 ;
      drgimage.hImage = standard;
      drgimage.sizlStretch.cx = 0L ;
      drgimage.sizlStretch.cy = 0L ;
      drgimage.fl = DRG_ICON ;
      drgimage.cxOffset = 0 ;
      drgimage.cyOffset = 0 ;
      hwndTarget = DrgDrag(hwndWnd,
			     pdrginfo,
			     &drgimage,
			     1L,
			     VK_ENDDRAG,
			     NULL) ;
      }
      break;

   default :
      break;
   }
return( *oldWinProc ) (hwndWnd, ulMsg, mp1, mp2);
}



INT existFile(CHAR *fl)
{
FILEFINDBUF3 findbuf;
HDIR hDir = HDIR_CREATE;
ULONG usSearchCount = 1;
// BOOL HASFOLD;
// ULONG ulStyle;


if(DosFindFirst(fl, &hDir,
                   FILE_NORMAL | FILE_ARCHIVED | FILE_SYSTEM | FILE_READONLY | FILE_HIDDEN,
                   (PVOID)&findbuf, sizeof(findbuf), &usSearchCount, FIL_STANDARD) != 0 )
   {
   DosFindClose(hDir);
   return(0);
   }
else
   {
   DosFindClose(hDir);
   return(1);   
   }
}

INT chkValidPath(CHAR *dstr)
{
CHAR dest[260];

if( strlen(dstr) > 260 )
   return(0);
strcpy(dest, dstr);
if( dest[strlen(dest)-1] == '\\' )
   dest[strlen(dest)-1] = '\0';
if( WinQueryObject(dest) == NULLHANDLE )
   return(0);
else
   return(1);
}


VOID debugWriteStr(CHAR *title, CHAR *str)
{
static SSD ssdat;   

strcpy(ssdat.title, title);
strcpy(ssdat.str, str);

_beginthread(debugWriteStrTHREAD, NULL, 8192, (PVOID)&ssdat);
}


VOID debugWriteStrTHREAD(PVOID strdat)
{
CHAR titleStr[260];
CHAR dStr[260];
CHAR newLine[] = "\n";
CHAR space[] = "     ";
FILE *han;


strcpy(titleStr, ((PFSSD)strdat)->title);
strcpy(dStr, ((PFSSD)strdat)->str);

han = fopen("H:\\Desktop\\DebugMsg.DOC", "b" );

fseek(han, 0L, SEEK_END);
fwrite(newLine, strlen(newLine), 1, han);
fwrite(newLine, strlen(newLine), 1, han);

fwrite(titleStr, strlen(titleStr), 1, han);

fwrite(space, strlen(space), 1, han);

fwrite(dStr, strlen(dStr), 1, han);

fwrite(newLine, strlen(newLine), 1, han);

fclose(han);

_endthread();
}




VOID dbgWriteStr(CHAR *titleStr, CHAR *dStr)
{
CHAR newLine[] = "\n";
FILE *han;
CHAR space[] = "     ";


han = fopen("H:\\Desktop\\DbugWS.DOC", "ab" );

fseek(han, 0L, SEEK_END);
fwrite(newLine, strlen(newLine), 1, han);
fwrite(newLine, strlen(newLine), 1, han);

fwrite(titleStr, strlen(titleStr), 1, han);

fwrite(space, strlen(space), 1, han);

fwrite(dStr, strlen(dStr), 1, han);

fwrite(newLine, strlen(newLine), 1, han);

fclose(han);
}




/*
VOID dbgWriteStr(CHAR *titleStr, CHAR *dStr)
{
CHAR newLine[] = "\n";
FILE *han;
CHAR space[] = "     ";
INT cz;


han = fopen("H:\\Desktop\\DbugWS.DOC", "ab" );

fwrite(newLine, strlen(newLine), 1, han);
fwrite(newLine, strlen(newLine), 1, han);

fwrite(titleStr, strlen(titleStr), 1, han);

fwrite(newLine, strlen(newLine), 1, han);

cz = 0;

do
   {
   fwrite(dStr+cz, sizeof(CHAR), 1, han);
   cz++;   
   }
while( (cz < bsize-3) && (dStr[cz] != '\0') );

// fwrite("\0", sizeof(CHAR), 1, han);
    
// fwrite(dStr, sizeof(dStr), 1, han);

// fwrite(newLine, strlen(newLine), 1, han);

fclose(han);
}
*/


VOID dbgWriteStr2(CHAR *titleStr, CHAR *dStr)
{
CHAR newLine[] = "\n";
FILE *han;
CHAR space[] = "     ";
INT cz;


han = fopen("H:\\Desktop\\DbugWS.DOC", "ab" );

cz = 0;
do
   {
   fwrite(dStr+cz, sizeof(CHAR), 1, han);
   cz++;   
   }
while( (cz < bsize-3) && (dStr[cz] != '\0') );

fwrite("\0", sizeof(CHAR), 1, han);
    
fwrite(newLine, strlen(newLine), 1, han);

fwrite(newLine, strlen(newLine), 1, han);

fclose(han);
}



VOID SetPtrDefault (VOID)
{
   if (!WinQuerySysValue (HWND_DESKTOP, SV_MOUSEPRESENT))
      WinShowPointer (HWND_DESKTOP, FALSE);

   WinSetPointer (HWND_DESKTOP,
      WinQuerySysPointer (HWND_DESKTOP, SPTR_ARROW, 0));
}


VOID SetPtrWait (VOID)
{
   WinSetPointer (HWND_DESKTOP,
      WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT, 0));

   if (!WinQuerySysValue (HWND_DESKTOP, SV_MOUSEPRESENT))
      WinShowPointer (HWND_DESKTOP, TRUE);
}


VOID zeroData(VOID)
{
INT cj;

for( cj=0;cj<RECNUM;cj++ )
   {
   pvdat[cj].INDATE[0] = '\0';
   pvdat[cj].INFROM[0] = '\0';
   pvdat[cj].INSIZE[0] = '\0';
   pvdat[cj].INSUBJECT[0] = '\0';
   }
}




VOID suspendChk(PVOID hwnd)
{
HAB habT;
HMQ hmqT;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

DosSleep(pgmData[12]*1000*60);
pgmData[11] = 0;
saveMRSet((HWND)hwnd);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}





VOID saveMRSet(HWND hwndDlg)
{
PrfWriteProfileData(hini, "MailRun", "WINPOS", 
                    &pgmData, sizeof(pgmData));
PrfWriteProfileString(hini, "MAILRUN",
                      "MAILSERVER", mailServer);
PrfWriteProfileString(hini, "MAILRUN",
                      "USERNAME", userName);
PrfWriteProfileString(hini, "MAILRUN",
                      "MPW", passWord);
PrfWriteProfileString(hini, "MAILRUN",
                      "Wave", waveFile);
PrfWriteProfileString(hini, "MAILRUN",
                      "mprog", mProg);
PrfWriteProfileString(hini, "MAILRUN",
                      "mprogargs", mProgArgs);
PrfWriteProfileString(hini, "MAILRUN",
                      "dloadname", dloadname);
PrfWriteProfileString(hini, "MAILRUN",
                      "FQNCPATH", fqNCPath);
}





VOID queryMRSet(HWND hwndDlg)
{
CHAR INIFILE[] = "MAILRUN.INI";

if ( (hini = PrfOpenProfile(WinQueryAnchorBlock(hwndDlg) , INIFILE)) != NULLHANDLE )
   {
   PrfQueryProfileSize(hini, "MailRun", "WINPOS", &rSize);
   if ( rSize == (sizeof(pgmData)) )
      {
      PrfQueryProfileData(hini, "MailRun", "WINPOS", &pgmData, &rSize);
      PrfQueryProfileString(hini, "MAILRUN", "MAILSERVER",
                            "", mailServer, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "USERNAME",
                            "", userName, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "MPW",
                            "", passWord, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "Wave",
                            "", waveFile, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "mprog",
                            "", mProg, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "mprogargs",
                            "", mProgArgs, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "dloadname",
                            "", dloadname, CCHMAXPATH );
      PrfQueryProfileString(hini, "MAILRUN", "FQNCPATH",
                            "", fqNCPath, CCHMAXPATH );
      }
   else
      {
      strcpy(mailServer, "");
      strcpy(userName, "");
      strcpy(passWord, "");
      strcpy(waveFile, "");
      strcpy(dloadname, "");
      strcpy(fqNCPath, "");
      strcpy(mProg, "");
      strcpy(mProgArgs, "");
      pgmData[0] = 50;
      pgmData[1] = 50;
      pgmData[2] = 300;
      pgmData[3] = 85;
      pgmData[4] = 60;
      pgmData[5] = 0;
      pgmData[6] = 0;
      pgmData[7] = 1;
      pgmData[8] = 1;
      pgmData[9] = 0;     /* autofade enable/disable */
      pgmData[10] = 6;  /* autofade default value */
      pgmData[11] = 0;    /* suspend enable/disable */
      pgmData[12] = 10;   /* suspend default value */
      pgmData[13] = 0;   /* Beep  on not. with dialog */
      pgmData[14] = 0;   /* Start program on not. */
      pgmData[15] = 0;   /* Start Preview screen on not. */
      pgmData[16] = 50;   /* DownLoad line limit */
      pgmData[17] = 1;   /* start mail preview on preview opening */
      pgmData[18] = 0;   /* Float to top */
      pgmData[19] = 0;   /* Filter NetChat Messages */
      pgmData[20] = 0;   /* 0 = Notify 1 = start NetChat automatically */
      }
   }   
else
   {
   strcpy(mailServer, "");
   strcpy(userName, "");
   strcpy(passWord, "");
   strcpy(waveFile, "");
   strcpy(dloadname, "");
   strcpy(fqNCPath, "");
   strcpy(mProg, "");
   strcpy(mProgArgs, "");
   pgmData[0] = 50;
   pgmData[1] = 50;
   pgmData[2] = 300;
   pgmData[3] = 85;
   pgmData[4] = 60;
   pgmData[5] = 0;
   pgmData[6] = 0;
   pgmData[7] = 1;
   pgmData[8] = 1;
   pgmData[9] = 0;     /* autofade enable/disable */
   pgmData[10] = 6;  /* autofade default value */
   pgmData[11] = 0;    /* suspend enable/disable */
   pgmData[12] = 10;   /* suspend default value */
   pgmData[13] = 0;   /* Beep  on not. with dialog */
   pgmData[14] = 0;   /* Start program on not. */
   pgmData[15] = 0;   /* Start Preview screen on not. */
   pgmData[16] = 50;   /* DownLoad line limit */
   pgmData[17] = 1;   /* start mail preview on preview opening */
   pgmData[18] = 0;   /* Float to top */
   pgmData[19] = 0;   /* Filter NetChat Messages */
   pgmData[20] = 0;   /* 0 = Notify 1 = start NetChat automatically */
   }
}




VOID checkForMail(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
CHAR mailserverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
CHAR mrreport[260];
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
INT dontblock, cnts;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

STOPME = 0;
hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;

WinEnableControl(hwndDlg, 1003, TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg, 1000), FALSE);

do
   {
   GOTHAIL = FALSE;
   queryMRSet(hwndDlg);
   if( strlen(mailServer) > 0 && strlen(userName) > 0 && strlen(passWord) > 0 )
      {
      WinSetWindowText(WinWindowFromID(hwndDlg, 1005), mailServer);
      strcpy(serverbuf, mailServer);
      strcpy(userbuf, "USER ");
      strcat(userbuf, userName);
      strcat(userbuf, termn);
      strcpy(passwordbuf, "PASS ");
      strcat(passwordbuf, passWord);
      strcat(passwordbuf, termn);
      strcpy(statbuf, "STAT");
      strcat(statbuf, termn);
      }
   else
      {
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }   

   while( PAUSEAC || PAUSESP )
      {
      DosSleep(500);
      };
   
   WinSetDlgItemText(hwndDlg, 1003, "Checking for mail");

   sock_init();

   sock = socket(AF_INET, SOCK_STREAM, 0);

   if (sock < 0)
      {
      WinSetDlgItemText(hwndDlg, 1003, "Can't open socket!");
      soclose(sock);   
      }
   else
      {
      // msgOK("Got this far!", "LINE : 407");
      hp = gethostbyname(serverbuf);
      if (!hp) 
         {
         WinSetDlgItemText(hwndDlg, 1003, "Can't get host name!");
         soclose(sock);   
         } 
      else 
         {
         memset(&server, 0, sizeof(server));
         bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
         server.sin_port = htons(mailreceiveport);
         server.sin_family = AF_INET;
         
         if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
            {
            WinSetDlgItemText(hwndDlg, 1003, "Can't connect to port!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            }
         else 
            {
            dontblock = 1;
            ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
            memset(&receivebuf, 0, sizeof(receivebuf));

            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebuf, bsize, 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   
                     
            // rval = recv(sock, receivebuf, bsize, 0); 
            
            if (rval <= 0)
               {
               WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }

         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            {
            CHAR er[260];
         
      
            socks[0] = sock;
            select(socks, 1, 0, 0, 2000);
         
            memset(&receivebuf, 0, sizeof(receivebuf));
            rv = send(sock, userbuf, strlen(userbuf), 0);
            
            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebuf, bsize, 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   
                     
            if (rval <= 0)
               {
               WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }        

         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            send(sock, passwordbuf, strlen(passwordbuf), 0);
            
            // rval = recv(sock, receivebuf, bsize, 0); 

            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebuf, bsize, 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   

            if (rval <= 0)
               {
               WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            if( strnicmp(receivebuf, "+OK", 3) != 0 )
               {
               WinSetDlgItemText(hwndDlg, 1003, "Busy or locked!");
               }
            }
         
         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            send(sock, statbuf, strlen(statbuf), 0);
            
            // rval = recv(sock, receivebuf, bsize, 0); 

            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebuf, bsize, 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   

            if (rval <= 0)
               {
               WinSetDlgItemText(hwndDlg, 1003, "STAT error!");
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }
         }
      // send(sock, quitbuf, strlen(quitbuf), 0);
      // soclose(sock);   
      }
      
   if( strlen(receivebuf) > 2 && strnicmp(receivebuf, "+OK", 3) == 0 )
      { 
      strcpy(mrreport, "MR : ");
      strndel(receivebuf, 4);
      if( receivebuf[0] == '0' )
         strcat(mrreport, "NO messages");
      else
         {  
         BOOL retd;
         INT delnum;
         
         
         if( pgmData[19] )
            {
            CHAR topc[260];
            CHAR report[20];
            CHAR numm[20];
            INT numlines, nmsg, fx, fz;
            
            
            fx = 0;
            report[0] = '\0';
            do
               {
               report[fx] = receivebuf[fx];
               fx++;
               }
            while (receivebuf[fx] != ' ' && receivebuf[fx] != '\0' );
            report[fx] = '\0';   
            
            nmsg = atoi (&report[0]);
            
            for( fz=0;fz<nmsg;fz++ )
               {
               INT lnum, newlnum, totrec;
            
               itoa(fz+1,numm,10);
               strcpy(topc, "TOP ");
               strcat(topc, numm);
               strcat(topc, " 0");
               strcat(topc, termn);
            
               memset(&rcbuf, 0, sizeof(rcbuf));
               memset(&receivebufA, 0, sizeof(receivebufA));
               send(sock, topc, strlen(topc), 0);
            
               lnum = 0;
               totrec = 0;
               do
                  {
                  newlnum = lnum;

                  cnts = 0;
                  do
                     {
                     if( cnts > 0 )
                        DosSleep(100);
                     rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                     cnts++;
                     }
                  while(rval <= 0 && cnts < MAXTRIES);   

                  // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  
                  if( rval == SOCEWOULDBLOCK )
                     DosBeep(100, 50);
                  lnum = getStr2(newlnum, rcbuf, receivebufA);
                  }
               while( lnum != -1 ); 
               
               if( !GOTHAIL )
                  {
                  zeroData();
                  retd = saveheaderDataToFile(rcbuf);
                  }
               else
                  retd = FALSE;
                     
               if( retd )
                  GOTHAIL = TRUE;
               }
               
            if( GOTHAIL )
               {
               if( pgmData[20] == 0 )
                  {
                  DosBeep(1200, 50);
                  DosBeep(1800, 100);
                  DosBeep(2000, 200);
                  DosBeep(1800, 150);
                  DosBeep(1200, 50);
                  }
               if( pgmData[20] == 1 )
                  {
                  CHAR fqfn[260];
                  
                  
                  strcpy(fqfn, fqNCPath);
                  if( fqfn[strlen(fqfn)-1] != '\\' )
                     strcat(fqfn, "\\");
                  strcat(fqfn, "NETCHAT.EXE");
                  if( !isNCActive() )
                     callPgm(fqfn, netChatArg, PROG_PM,  SWP_ACTIVATE, fqNCPath, NULL);
                  else
                     {
                     DosBeep(1200, 50);
                     DosBeep(1800, 100);
                     DosBeep(2000, 200);
                     DosBeep(1800, 150);
                     DosBeep(1200, 50);
                     }   
                  }
               }
            }
         for( ig=5,ih=0;ih<strlen(receivebuf);ig++,ih++ )
            {
            mrreport[ig] = receivebuf[ih];
            if( receivebuf[ih+1] == ' ' )
               {
               mrreport[ig+1] = '\0';    
               strcat(mrreport, " message(s)"); 
               ih = strlen(receivebuf) + 1;
               }
            }
         }
         
      WinSetDlgItemText(hwndDlg, 1003, mrreport);
      
      if( pgmData[7] == 0 )
         {
         MRnotify(hwndDlg, pgmData[8], mrreport);
         }
      if( pgmData[7] == 1 )
         {   
         if( strlen(mrreport) > 6 )
            {     
            if( strncmp(mrreport, "MR : ", 5) == 0 && strncmp(mrreport, "MR : NO", 7) != 0 )
               {
               if( pgmData[14] ) 
                  startMailProg();
               MRnotify(hwndDlg, pgmData[8], mrreport);
               if( pgmData[15] ) 
                  {
                  USHORT usReturn;
                  HWND hNewFrame;
                  
                  send(sock, quitbuf, strlen(quitbuf), 0);
                  soclose(sock);   
                  hNewFrame = OpenPREVIEW(hwndDlg, 0);
                  usReturn = (USHORT) WinProcessDlg(hNewFrame);
                  }
               }
            }
         }
      }         
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   DosSleep(pgmData[4]*1000);
   memset(&receivebuf, 0, sizeof(receivebuf));
   }
while( !STOPME );

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID checkForMailNow(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
CHAR mailserverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
CHAR mrreport[260];
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
INT dontblock, cnts;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;

WinQueryPresParam(WinWindowFromID(hwndDlg, 1003), 
                            PP_BACKGROUNDCOLORINDEX, 0, &attrFound,
		       sizeof(orgcolor), &orgcolor, QPF_NOINHERIT);
			    
bkcolor = CLR_CYAN;   
WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                        PP_BACKGROUNDCOLORINDEX,
                        sizeof(ULONG),     
                        &bkcolor);     
                                      
WinEnableControl(hwndDlg, 1003, TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg, 1000), FALSE);

queryMRSet(hwndDlg);

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);

if( strlen(mailServer) > 0 && strlen(userName) > 0 && strlen(passWord) > 0 )
   WinSetWindowText(WinWindowFromID(hwndDlg, 1005), mailServer);
   
while( PAUSEAC )
   {
   DosSleep(500);
   };
   
WinSetDlgItemText(hwndDlg, 1003, "Checking for mail");

sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

if (sock < 0)
   {
   WinSetDlgItemText(hwndDlg, 1003, "Can't open socket!");
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      WinSetDlgItemText(hwndDlg, 1003, "Can't get host name!");
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         WinSetDlgItemText(hwndDlg, 1003, "Can't connect to port!");
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 2000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            }
         if( strnicmp(receivebuf, "+OK", 3) != 0 )
            {
            WinSetDlgItemText(hwndDlg, 1003, "Busy or locked!");
            }
         }      
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, statbuf, strlen(statbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            WinSetDlgItemText(hwndDlg, 1003, "STAT error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            }
         }
      }
   // send(sock, quitbuf, strlen(quitbuf), 0);
   // soclose(sock);   
   }
      
if( strlen(receivebuf) > 2 && strnicmp(receivebuf, "+OK", 3) == 0 )
   { 
   strcpy(mrreport, "MR : ");
   strndel(receivebuf, 4);
   if( receivebuf[0] == '0' )
      strcat(mrreport, "NO messages");
   else
      {  
      BOOL retd;
      INT delnum;
      
         
      if( pgmData[19] )
         {
         CHAR topc[260];
         CHAR report[20];
         CHAR numm[20];
         INT numlines, nmsg, fx, fz;
            
         
         GOTHAIL = FALSE;   
         fx = 0;
         report[0] = '\0';
         do
            {
            report[fx] = receivebuf[fx];
            fx++;
            }
         while (receivebuf[fx] != ' ' && receivebuf[fx] != '\0' );
         report[fx] = '\0';   
            
         nmsg = atoi (&report[0]);
            
         for( fz=0;fz<nmsg;fz++ )
            {
            INT lnum, newlnum, totrec;
           
            itoa(fz+1,numm,10);
            strcpy(topc, "TOP ");
            strcat(topc, numm);
            strcat(topc, " 0");
            strcat(topc, termn);
            
            memset(&rcbuf, 0, sizeof(rcbuf));
            memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, topc, strlen(topc), 0);
            
            lnum = 0;
            totrec = 0;
            do
               {
               newlnum = lnum;

               cnts = 0;
               do
                  {
                  if( cnts > 0 )
                     DosSleep(100);
                  rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  cnts++;
                  }
               while(rval <= 0 && cnts < MAXTRIES);   

               // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
               
               if( rval == SOCEWOULDBLOCK )
                  DosBeep(100, 50);
               lnum = getStr2(newlnum, rcbuf, receivebufA);
               }
            while( lnum != -1 ); 
               
            zeroData();
            if( !GOTHAIL )
               {
               retd = saveheaderDataToFile(rcbuf);
               }
            else
               retd = FALSE;   
            if( retd )
               GOTHAIL = TRUE;
            }
               
         if( GOTHAIL )
            {
            if( pgmData[20] == 0 )
               {
               DosBeep(1200, 50);
               DosBeep(1800, 100);
               DosBeep(2000, 200);
               DosBeep(1800, 150);
               DosBeep(1200, 50);
               }
            if( pgmData[20] == 1 )
               {
               CHAR fqfn[260];
                  
                  
               strcpy(fqfn, fqNCPath);
               if( fqfn[strlen(fqfn)-1] != '\\' )
                  strcat(fqfn, "\\");
               strcat(fqfn, "NETCHAT.EXE");
               if( !isNCActive() )
                  // callPgmDSS(fqfn, netChatArg, SSF_TYPE_PM, SSF_CONTROL_VISIBLE, NULL, NULL);
                  callPgm(fqfn, netChatArg, PROG_PM,  SWP_ACTIVATE, fqNCPath, NULL);
                  // callPgm(fqfn, NULL, PROG_PM,  SWP_ACTIVATE, fqNCPath, NULL);
               else
                  {
                  DosBeep(1200, 50);
                  DosBeep(1800, 100);
                  DosBeep(2000, 200);
                  DosBeep(1800, 150);
                  DosBeep(1200, 50);
                  }                  
               }
            }
         }
      for( ig=5,ih=0;ih<strlen(receivebuf);ig++,ih++ )
         {
         mrreport[ig] = receivebuf[ih];
         if( receivebuf[ih+1] == ' ' )
            {
            mrreport[ig+1] = '\0';    
            strcat(mrreport, " message(s)"); 
            ih = strlen(receivebuf) + 1;
            }
         }
      }
      
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   WinSetDlgItemText(hwndDlg, 1003, mrreport);
      
   if( pgmData[7] == 0 )
      {
      MRnotify(hwndDlg, pgmData[8], mrreport);
      }
   if( pgmData[7] == 1 )
      {
      if( strlen(mrreport) > 6 )
         {     
         if( strncmp(mrreport, "MR : ", 5) == 0 && strncmp(mrreport, "MR : NO", 7) != 0 )
            {
            if( pgmData[14] ) 
               startMailProg();
            MRnotify(hwndDlg, pgmData[8], mrreport);
            if( pgmData[15] ) 
               {
               USHORT usReturn;
               HWND hNewFrame;
               
               hNewFrame = OpenPREVIEW(hwndDlg, 0);
               usReturn = (USHORT) WinProcessDlg(hNewFrame);
               }
            }
         }
      }
   }         

send(sock, quitbuf, strlen(quitbuf), 0);
soclose(sock);   
if( orgcolor == CLR_RED )
   DosSleep(3000);
bkcolor = orgcolor;   
WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                        PP_BACKGROUNDCOLORINDEX,
                        sizeof(ULONG),     
                        &bkcolor);     

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID MRnotify(HWND hwndDlg, INT mode, CHAR *msg)
{
switch( mode )
   {
   case 0:
      break;
      
   case 1:
      if( pgmData[19] && GOTHAIL && pgmData[20] == 0 )
         {
         }
      else
         {   
         DosBeep(900, 50);
         DosBeep(1200, 50);
         DosBeep(1500, 50);
         DosBeep(900, 50);
         DosBeep(1200, 50);
         DosBeep(1500, 50);
         }
      break;
      
   case 2:
      {
      ULONG bkgcolor;
      INT n;
      
      for( n=0;n<6;n++ )
         {
         bkgcolor = CLR_WHITE;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                                 PP_BACKGROUNDCOLORINDEX,
                                 sizeof(ULONG),     
                                 &bkgcolor);     
         WinUpdateWindow(WinWindowFromID(hwndDlg, 1003));                        
         DosSleep(250); 

         bkgcolor = CLR_CYAN;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                                 PP_BACKGROUNDCOLORINDEX,
                                 sizeof(ULONG),     
                                 &bkgcolor);     
         WinUpdateWindow(WinWindowFromID(hwndDlg, 1003));                        
         DosSleep(250);
         } 
      }
      break;

   case 3:
      {
      USHORT usReturn;
      HWND hNewFrame;
      HWND hwndO;


      // debugMsgULong(pgmData[11], "pgmData[11]");   
      if( pgmData[11] == 0 )
         {
         hwndO = WinQueryFocus(HWND_DESKTOP);
         strcpy(mmsg, msg);
         FLOATME = 0;
         hNewFrame = OpenNOTIFY1(hwndDlg, 0);
         usReturn = (USHORT) WinProcessDlg(hNewFrame);
         FLOATME = 1;
         WinSetFocus(HWND_DESKTOP, hwndO);
         }
      // DosBeep(100, 100);
      }
      break;
      
   case 4:
      if( SOUNDS && strlen(waveFile) > 0 )
         playWavFile(waveFile, 100);
      break;
   }
}




VOID subcpview(HWND hwndDlg)
{
WinEnableWindow(WinWindowFromID(hwndDlg,FID_SYSMENU), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1000), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1001), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1002), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1003), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1004), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1005), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1010), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1011), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1012), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1015), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1016), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1018), FALSE);
WinEnableWindow(WinWindowFromID(hwndDlg,1019), FALSE);
oldProc1 = WinSubclassWindow(WinWindowFromID(hwndDlg,1000), (PFNWP)PREVIEWDlgProc);
oldProc2 = WinSubclassWindow(WinWindowFromID(hwndDlg,1001), (PFNWP)PREVIEWDlgProc);
oldProc3 = WinSubclassWindow(WinWindowFromID(hwndDlg,1002), (PFNWP)PREVIEWDlgProc);
oldProc4 = WinSubclassWindow(WinWindowFromID(hwndDlg,1003), (PFNWP)PREVIEWDlgProc);
oldProc5 = WinSubclassWindow(WinWindowFromID(hwndDlg,1004), (PFNWP)PREVIEWDlgProc);
oldProc6 = WinSubclassWindow(WinWindowFromID(hwndDlg,1005), (PFNWP)PREVIEWDlgProc);
oldProc7 = WinSubclassWindow(WinWindowFromID(hwndDlg,1010), (PFNWP)PREVIEWDlgProc);
oldProc8 = WinSubclassWindow(WinWindowFromID(hwndDlg,1011), (PFNWP)PREVIEWDlgProc);
oldProc9 = WinSubclassWindow(WinWindowFromID(hwndDlg,1012), (PFNWP)PREVIEWDlgProc);
oldProc10 = WinSubclassWindow(WinWindowFromID(hwndDlg,1015), (PFNWP)PREVIEWDlgProc);
oldProc11 = WinSubclassWindow(WinWindowFromID(hwndDlg,1016), (PFNWP)PREVIEWDlgProc);
oldProc12 = WinSubclassWindow(WinWindowFromID(hwndDlg,1018), (PFNWP)PREVIEWDlgProc);
oldProc13 = WinSubclassWindow(WinWindowFromID(hwndDlg,1019), (PFNWP)PREVIEWDlgProc);
}


VOID unsubcpview(HWND hwndDlg)
{
WinEnableWindow(WinWindowFromID(hwndDlg,FID_SYSMENU), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1000), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1001), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1002), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1003), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1004), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1005), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1010), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1011), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1012), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1015), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1016), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1018), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg,1019), TRUE);
WinSubclassWindow(WinWindowFromID(hwndDlg,1000), oldProc1);
WinSubclassWindow(WinWindowFromID(hwndDlg,1001), oldProc2);
WinSubclassWindow(WinWindowFromID(hwndDlg,1002), oldProc3);
WinSubclassWindow(WinWindowFromID(hwndDlg,1003), oldProc4);
WinSubclassWindow(WinWindowFromID(hwndDlg,1004), oldProc5);
WinSubclassWindow(WinWindowFromID(hwndDlg,1005), oldProc6);
WinSubclassWindow(WinWindowFromID(hwndDlg,1010), oldProc7);
WinSubclassWindow(WinWindowFromID(hwndDlg,1011), oldProc8);
WinSubclassWindow(WinWindowFromID(hwndDlg,1012), oldProc9);
WinSubclassWindow(WinWindowFromID(hwndDlg,1015), oldProc10);
WinSubclassWindow(WinWindowFromID(hwndDlg,1016), oldProc11);
WinSubclassWindow(WinWindowFromID(hwndDlg,1018), oldProc12);
WinSubclassWindow(WinWindowFromID(hwndDlg,1019), oldProc13);
}



VOID previewMail(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufx[bsize];
CHAR receivebufW[bsize];
CHAR rcvbuf[64];
// CHAR mailserverbuf[260];
CHAR serverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR totbytes[260];
CHAR totmessages[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
INT dontblock, cnts;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;

subcpview(hwndDlg);

PREVIEWBUSY = TRUE;

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);

WinSetDlgItemText(hwndDlg, 1011, "");
WinSetDlgItemText(hwndDlg, 1012, "");

zeroData();
sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

// socks[0] = sock;
// select(socks, 1, 0, 0, 100);

if (sock < 0)
   {
   // WinSetDlgItemText(hwndDlg, 1003, "Can't open socket!");
   unsubcpview(hwndDlg);
   WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      unsubcpview(hwndDlg);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         // debugMsgStr("Made it this far!", "LINE: 682");
         // WinSetDlgItemText(hwndDlg, 1003, "Can't connect to port!");
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         unsubcpview(hwndDlg);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 1000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            // debugMsgStr("Made it this far!", "LINE: 712");
            // WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            // debugMsgStr("Made it this far!", "LINE: 727");
            // WinSetDlgItemText(hwndDlg, 1003, "Connect error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         /* if( strnicmp(receivebuf, "+OK", 3) != 0 )
            {
            WinSetDlgItemText(hwndDlg, 1003, "Busy or locked!");
            }  */
         }      
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR tmsg[260];
         CHAR tbyte[260];
         INT gf, bf;
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, statbuf, strlen(statbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            // debugMsgStr("Made it this far!", "LINE: 745");
            // WinSetDlgItemText(hwndDlg, 1003, "STAT error!");
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
            
         strcpy(receivebufx, receivebuf);   
         strndel(receivebufx, 4);
         strdelc(receivebufx, '\x0a');
         strdelc(receivebufx, '\x0d');
         
         gf = 0;
         do
            {
            tmsg[gf] = receivebufx[gf];
            gf++;
            }
         while( receivebufx[gf] != ' ' );
         tmsg[gf] = '\0';
          
         gf++;   
         bf = 0;   
         do
            {
            tbyte[bf] = receivebufx[gf];
            gf++;
            bf++;
            }
         while( receivebufx[gf] != '\0' );
         tbyte[bf] = '\0';
         
         WinSetDlgItemText(hwndDlg, 1011, tmsg);
         WinSetDlgItemText(hwndDlg, 1012, tbyte);
         }
      
      if( strlen(receivebuf) > 4  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         INT vb, vc, slen;
         CHAR listc[260];
         CHAR num[80];
         CHAR TTnum[80];
         CHAR TUnum[80];
         INT vnum, er;
         CHAR TMPn[80];
         
         
         strndel(receivebuf, 4);
         vb = 0;
         do
            {
            num[vb] = receivebuf[vb];
            vb++;
            }
         while( receivebuf[vb] != ' ' );   
         num[vb] = '\0';

         vnum = atoi (&num[0]);
            
         for( vb=0;vb<vnum;vb++ )
            {
            INT lnum, newlnum, totrec;
            
            itoa(vb+1,num,10);
            strcpy(listc, "LIST ");
            strcat(listc, num);
            strcat(listc, termn);
            
            memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, listc, strlen(listc), 0);

            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   
                     
            // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 


            savesizeData(vb, receivebufA);
            if( vb == 0 )
               WinSetDlgItemText(hwndDlg, 1003, pvdat[vb].INSIZE);   
            
            itoa(vb+1,num,10);
            strcpy(listc, "TOP ");
            strcat(listc, num);
            strcat(listc, " 0");
            strcat(listc, termn);
            
            memset(&receivebuf, 0, sizeof(receivebuf));
            memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, listc, strlen(listc), 0);
            
            // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
            // lnum = getStr1(receivebuf, receivebufA);

            // dbgWriteStr("LINE: 1158", receivebufA);
            lnum = 0;
            totrec = 0;
            do
               {
               newlnum = lnum;

               cnts = 0;
               do
                  {
                  if( cnts > 0 )
                     DosSleep(100);
                  rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  cnts++;
                  }
               while(rval <= 0 && cnts < MAXTRIES);   
                     
               // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
               
               if( rval == SOCEWOULDBLOCK )
                  DosBeep(100, 50);
               lnum = getStr2(newlnum, receivebuf, receivebufA);
               }
            while( lnum != -1 ); 

            saveheaderData(vb, receivebuf);
            if( vb == 0 )
               {
               WinSetDlgItemText(hwndDlg, 1001, pvdat[vb].INDATE); 
               WinSetDlgItemText(hwndDlg, 1002, pvdat[vb].INSUBJECT); 
               }
            WinSendMsg(WinWindowFromID(hwndDlg, 1005), 
                             LM_INSERTITEM,
                             MPFROM2SHORT(LIT_END, 0), 
                             MPFROMP(pvdat[vb].INFROM));
            WinSendMsg (WinWindowFromID(hwndDlg, 1005),
                                                       LM_SELECTITEM,
                                                       (MPARAM)0,
                                                       MPFROMSHORT(TRUE));   
            }  
         }       
      }
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   }
DosBeep(400, 50);
PREVIEWBUSY = FALSE;
unsubcpview(hwndDlg);
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}



BOOL saveheaderDataToFile(CHAR *buf)
{
CHAR indata[bsize];
INT nx, sz;
CHAR separator[] = "=";
CHAR ncargm[] = "-M";
CHAR *res;
CHAR ncmsg[] = "Subject: &&$~NETCHATMSG~$&&";


sz = strlen(buf);

if( sz <= bsize )
   {
   strcpy(indata, buf);

   res = NULL;
   res = strstr(indata, ncmsg);
   
   if( res == NULL )
      return(FALSE);
   
   if( pgmData[20] == 1 )   
      {
      strcpy(netChatArg, ncargm);
      } 
   return(TRUE);   
   }
return(FALSE);     
}



VOID saveheaderData(INT indx, CHAR *buf)
{
CHAR indata[bsize];
INT nx, sz;
CHAR indate[] = "Date: ";
CHAR infrom[] = "From: ";
CHAR insubject[] = "Subject: ";
CHAR *res;


sz = strlen(buf);

if( sz <= bsize )
   {
   strcpy(indata, buf);
   res = NULL;
   res = strstr(indata, indate);
   if( res != NULL )
      {
      nx = 0;
      do
         {
         pvdat[indx].INDATE[nx] = res[nx+strlen(indate)];
         nx++;
         }
      while(res[nx+strlen(indate)] != '\x0a');
      pvdat[indx].INDATE[nx-1] = '\0';
      }
   else
      strcpy(pvdat[indx].INDATE, "Unknown");   
      
   res = NULL;
   res = strstr(indata, infrom);
   if( res != NULL )
      {
      nx = 0;
      do
         {
         pvdat[indx].INFROM[nx] = res[nx+strlen(infrom)];
         nx++;
         }
      while(res[nx+strlen(infrom)] != '\x0a');
      pvdat[indx].INFROM[nx-1] = '\0';
      }
   else
      strcpy(pvdat[indx].INFROM, "Unknown");   
      
   res = NULL;
   res = strstr(indata, insubject);
   if( res != NULL )
      {
      nx = 0;
      do
         {
         pvdat[indx].INSUBJECT[nx] = res[nx+strlen(insubject)];
         nx++;
         }
      while(res[nx+strlen(insubject)] != '\x0a');
      pvdat[indx].INSUBJECT[nx-1] = '\0';
      }
   else
      strcpy(pvdat[indx].INSUBJECT, "Unknown");   
   }   
}



VOID savesizeData(INT indx, CHAR *buf)
{
CHAR num[80];
INT vc, sz;


sz = strlen(buf);
if( sz < 80 )
   {
   for( vc=0;vc<sz;vc++ )
      {
      num[vc] = buf[vc];
      }
   }   

if( strlen(num) > 4 )
   {
   strndel(num, 4);
   vc = 0;
   do
      {
      if( num[vc] != ' ' )
         strndel(num, 1);
      }
   while( num[vc] != ' ' );
   if( num[0] == ' ' )
      strndel(num, 1);
      
   vc = 0;
   do
      {
      pvdat[indx].INSIZE[vc] = num[vc];
      vc++;
      }
   while( num[vc] != '\x0a' && num[vc] != '\x0d' );   
   pvdat[indx].INSIZE[vc] = '\0'; 
   }
}



VOID deleteAllMail(PVOID deletemaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufx[bsize];
CHAR receivebufW[bsize];
CHAR rcvbuf[64];
// CHAR mailserverbuf[260];
CHAR serverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR totbytes[260];
CHAR totmessages[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
INT dontblock, cnts;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)deletemaildat)->hwndDlg;

subcpview(hwndDlg);

// PREVIEWBUSY = TRUE;

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);


sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

if (sock < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      unsubcpview(hwndDlg);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         unsubcpview(hwndDlg);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 1000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
      if( strlen(receivebuf) > 4  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         ULONG bnum, seld, seldn;
         INT vb, vc, slen;
         CHAR listc[260];
         CHAR num[80];
         CHAR TTnum[80];
         CHAR TUnum[80];
         INT vnum, er;
         INT all;
                  
         
         
         all = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                   LM_QUERYITEMCOUNT, 0, 0);
         for( seld=0;seld<all;seld++ )
            {
            itoa(seld+1,TTnum,10);
            strcpy(listc, "DELE ");
            strcat(listc, TTnum);
            strcat(listc, termn);
            memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, listc, strlen(listc), 0);

            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebufA, bsize, 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   
                     
            // rval = recv(sock, receivebufA, bsize, 0); 
            
            if( strnicmp(receivebufA, "+OK", 3) != 0 )
               {
               DosSleep(500);
               memset(&receivebufA, 0, sizeof(receivebufA));
               send(sock, listc, strlen(listc), 0);
               rval = recv(sock, receivebufA, bsize, 0); 
               }
            }
         }
      }
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   }
// DosBeep(400, 50);
// PREVIEWBUSY = FALSE;
unsubcpview(hwndDlg);
WinSendDlgItemMsg(hwndDlg, 1005,
                  LM_DELETEALL, 0, 0);
WinSetDlgItemText(hwndDlg, 1001, "");
WinSetDlgItemText(hwndDlg, 1002, "");
WinSetDlgItemText(hwndDlg, 1003, "");
WinSetDlgItemText(hwndDlg, 1011, "");
WinSetDlgItemText(hwndDlg, 1012, "");
chkdat3.hwndDlg = ((PFCBD)deletemaildat)->hwndDlg;
_beginthread(previewMail, NULL, BSTACK, (PVOID)&chkdat3); 

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}



VOID deleteMail(PVOID deletemaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufx[bsize];
CHAR receivebufW[bsize];
CHAR rcvbuf[64];
// CHAR mailserverbuf[260];
CHAR serverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR totbytes[260];
CHAR totmessages[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
INT dontblock, cnts;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)deletemaildat)->hwndDlg;

subcpview(hwndDlg);

// PREVIEWBUSY = TRUE;

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);


sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

if (sock < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      unsubcpview(hwndDlg);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         unsubcpview(hwndDlg);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 1000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
      if( strlen(receivebuf) > 4  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         ULONG bnum, seld, seldn;
         INT vb, vc, slen;
         CHAR listc[260];
         CHAR num[80];
         CHAR TTnum[80];
         CHAR TUnum[80];
         INT vnum, er;
         
         
         seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                      LM_QUERYSELECTION,
                                                      MPFROMLONG(LIT_FIRST),
                                                      MPFROMLONG(0));

         if( seld != LIT_NONE )
            {
            itoa(seld+1,TTnum,10);
            strcpy(listc, "DELE ");
            strcat(listc, TTnum);
            strcat(listc, termn);
            memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, listc, strlen(listc), 0);

            cnts = 0;
            do
               {
               if( cnts > 0 )
                  DosSleep(100);
               rval = recv(sock, receivebufA, bsize, 0); 
               cnts++;
               }
            while(rval <= 0 && cnts < MAXTRIES);   
                     
            // rval = recv(sock, receivebufA, bsize, 0); 
            
            if( strnicmp(receivebufA, "+OK", 3) != 0 )
               {
               DosSleep(500);
               memset(&receivebufA, 0, sizeof(receivebufA));
               send(sock, listc, strlen(listc), 0);
               rval = recv(sock, receivebufA, bsize, 0); 
               }
            }
         do
            {
            seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                        LM_QUERYSELECTION,
                                                        MPFROMLONG(seld),  
                                                        MPFROMLONG(0));
            if( seld != LIT_NONE )
               {                                            
               itoa(seld+1,TTnum,10);
               strcpy(listc, "DELE ");
               strcat(listc, TTnum);
               strcat(listc, termn);
               memset(&receivebufA, 0, sizeof(receivebufA));
               send(sock, listc, strlen(listc), 0);

               cnts = 0;
               do
                  {
                  if( cnts > 0 )
                     DosSleep(100);
                  rval = recv(sock, receivebufA, bsize, 0); 
                  cnts++;
                  }
               while(rval <= 0 && cnts < MAXTRIES);   
                     
               // rval = recv(sock, receivebufA, bsize, 0); 
               
               if( strnicmp(receivebufA, "+OK", 3) != 0 )
                  {
                  DosSleep(500);
                  memset(&receivebufA, 0, sizeof(receivebufA));
                  send(sock, listc, strlen(listc), 0);
                  rval = recv(sock, receivebufA, bsize, 0); 
                  }
               }   
            }
         while(seld != LIT_NONE);   
         }
      }
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   }
// DosBeep(400, 50);
// PREVIEWBUSY = FALSE;
unsubcpview(hwndDlg);
WinSendDlgItemMsg(hwndDlg, 1005,
                  LM_DELETEALL, 0, 0);
WinSetDlgItemText(hwndDlg, 1001, "");
WinSetDlgItemText(hwndDlg, 1002, "");
WinSetDlgItemText(hwndDlg, 1003, "");
WinSetDlgItemText(hwndDlg, 1011, "");
WinSetDlgItemText(hwndDlg, 1012, "");
chkdat3.hwndDlg = ((PFCBD)deletemaildat)->hwndDlg;
_beginthread(previewMail, NULL, BSTACK, (PVOID)&chkdat3); 

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID downloadMail(PVOID downloadmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufx[bsize];
CHAR receivebufW[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR totbytes[260];
CHAR totmessages[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
// ULONG bs;
INT dontblock, cnts;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)downloadmaildat)->hwndDlg;

subcpview(hwndDlg);

// PREVIEWBUSY = TRUE;

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);


sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

// sock = -1;

if (sock < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      unsubcpview(hwndDlg);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         unsubcpview(hwndDlg);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 1000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
      if( strlen(receivebuf) > 4  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         ULONG bnum, seld, seldn;
         INT vb, vc, slen, gf;
         CHAR listc[260];
         CHAR num[80];
         CHAR TTnum[80];
         CHAR TUnum[80];
         CHAR TMPnum[80];
         INT vnum, er;
         APIRET rc;
         CHAR endt[] = "\x0a\x0d";
         CHAR *rbuf;
         INT lnum, newlnum;
         INT numf;
         
         numf = 0;
         seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                      LM_QUERYSELECTION,
                                                      MPFROMLONG(LIT_FIRST),
                                                      MPFROMLONG(0));

         if( seld != LIT_NONE )
            {
            CHAR dlmsg[80];
            CHAR dlnum[10];
               
               
            ltoa(pgmData[16], dlnum,10);
            strcpy(dlmsg, "MailRun Preview   Downloading message ");
            itoa(seld+1,TTnum,10);
            strcat(dlmsg, TTnum);
            strcpy(listc, "TOP ");
            strcat(listc, TTnum);
            strcat(listc, " ");
            strcat(listc, dlnum);
            strcat(listc, termn);
	  WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), dlmsg);
            memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, listc, strlen(listc), 0);

            lnum = 0;
            do
               {
               newlnum = lnum;

               cnts = 0;
               do
                  {
                  if( cnts > 0 )
                     DosSleep(100);
                  rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  cnts++;
                  }
               while(rval <= 0 && cnts < MAXTRIES);   
                     
               // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
               
               // DosBeep(100, 100);
               // debugWriteStr("receivebufA", receivebufA);                  
               
               // debugMsgStr(receivebufA, "receivebufA : ");                  
               lnum = getStr2(newlnum, receivebuf, receivebufA);
               }
            while( lnum != -1 ); 
               
            lnum = 0;
            do
               {
               strndel(receivebuf, 1);
               }
            while( receivebuf[0] != '\x0d' );   
            strndel(receivebuf, 1); 
            
            if( receivebuf[strlen(receivebuf)-3] == '\x2e' )
               {
               receivebuf[strlen(receivebuf)-5] = '\0';
               }
            dload(numf, receivebuf);
            }
         do
            {
            seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                        LM_QUERYSELECTION,
                                                        MPFROMLONG(seld),  
                                                        MPFROMLONG(0));
            if( seld != LIT_NONE )
               {      
               CHAR dlmsg[80];
               CHAR dlnum[10];
               
               
               ltoa(pgmData[16], dlnum,10);
               strcpy(dlmsg, "MailRun Preview   Downloading message ");
               numf++;                                      
               itoa(seld+1,TTnum,10);
               strcat(dlmsg, TTnum);
               strcpy(listc, "TOP ");
               strcat(listc, TTnum);
               strcat(listc, " ");
               strcat(listc, dlnum);
               strcat(listc, termn);
    	     WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), dlmsg);
               send(sock, listc, strlen(listc), 0);

               lnum = 0;  
               do
                  {
                  memset(&receivebufA, 0, sizeof(receivebufA));
                  newlnum = lnum;

                  cnts = 0;
                  do
                     {
                     if( cnts > 0 )
                        DosSleep(100);
                     rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                     cnts++;
                     }
                  while(rval <= 0 && cnts < MAXTRIES);   
                     
                  // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  // debugMsgStr(receivebufA, "receivebufA : ");                  
                  //  debugWriteStr("receivebufA", receivebufA);                  
                  //  debugWriteStr("Got this Far!", "Line: ");                  
                  lnum = getStr2(newlnum, receivebuf, receivebufA);
                  }
               while( lnum != -1 ); 

               lnum = 0;
               do
                  {
                  strndel(receivebuf, 1);
                  }
               while( receivebuf[0] != '\x0d' );   
               strndel(receivebuf, 1); 
            
               if( receivebuf[strlen(receivebuf)-3] == '\x2e' )
                  {
                  receivebuf[strlen(receivebuf)-5] = '\0';
                  }
               dload(numf, receivebuf);
               }   
            }
         while(seld != LIT_NONE);  
         }
      }
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   }
DosBeep(400, 50);
// PREVIEWBUSY = FALSE;
WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), "MailRun Preview   Downloading completed!");
DosSleep(500);
WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), "MailRun Preview");
unsubcpview(hwndDlg);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID dload(INT num, CHAR *dStr)
{
FILE *han;
CHAR nums[10];
INT numb;
CHAR dln[260];

strcpy(dln, dloadname);
numb = num;
if( num == 0 )
   {
   strcat(dln, ".mrm");
   han = fopen(dln, "w+b" );
   }
else
   {
   itoa(num, nums, 10);
   strcat(dln, nums);
   strcat(dln, ".mrm");
   han = fopen(dln, "w+b" );
   }   
fwrite(dStr, strlen(dStr), 1, han);
fclose(han);
}


VOID dloadM(CHAR *dStr)
{
FILE *han;
CHAR newLine[] = "\n";
CHAR nLine[] = "--------------------------------------------------\n";


han = fopen("H:\\Desktop\\DbugMsg.DOC", "ab" );
fwrite(newLine, strlen(newLine), 1, han);
fwrite(newLine, strlen(newLine), 1, han);
fwrite(nLine, strlen(nLine), 1, han);
fwrite(newLine, strlen(newLine), 1, han);
fwrite(dStr, strlen(dStr), 1, han);
fclose(han);
}


INT getStr1(CHAR *tmp, CHAR *dStr)
{
INT cz;


cz = 0;

do
   {
   tmp[cz] = dStr[cz];
   cz++;   
   }
while( (cz < bsize-3) && (dStr[cz] != '\0') );
return(cz);
}



INT getStr2(INT cz, CHAR *tmp, CHAR *dStr)
{
INT cw;
BOOL ENDRCV;


ENDRCV = FALSE;
cw = 0;
do
   {
   tmp[cz] = dStr[cw];
   if( tmp[cz] == '\x0a' && tmp[cz-1] == '\x0d' && tmp[cz-2] == '\x2e' && tmp[cz-3] == '\x0a' && tmp[cz-4] == '\x0d' )
      {
      tmp[cz+1] = '\0';
      ENDRCV = TRUE;
      }
   cz++;   
   cw++;   
   }
while( (cz < bsize-4) && (dStr[cw] != '\0') && (ENDRCV == FALSE) );

if( ENDRCV )
   return(-1);
if( (cz >= bsize-5) )
   {
   if( tmp[cz-3] != '\x0d' && tmp[cz-2] != '\x0a' && tmp[cz-1] != '\x2e' )
      {
      tmp[cz] = '\0';
      strcat(tmp, "\x0d\x0a\0");
      }
   else
      tmp[cz] = '\0';
   return(-1);
   }
return(cz);
}



VOID downloadALLMail(PVOID downloadmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufx[bsize];
CHAR receivebufW[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR totbytes[260];
CHAR totmessages[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
INT dontblock, cnts;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)downloadmaildat)->hwndDlg;

subcpview(hwndDlg);

// PREVIEWBUSY = TRUE;

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);


sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

// sock = -1;

if (sock < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      unsubcpview(hwndDlg);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         unsubcpview(hwndDlg);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 1000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
      if( strlen(receivebuf) > 4  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         ULONG bnum, seld, seldn;
         INT vb, vc, slen, gf, numd;
         CHAR listc[260];
         CHAR num[80];
         CHAR TTnum[80];
         CHAR TUnum[80];
         CHAR TMPnum[80];
         INT vnum, er;
         APIRET rc;
         CHAR endt[] = "\x0a\x0d";
         CHAR *rbuf;
         INT lnum, newlnum;
         // INT numf;
         
         // numf = 0;
         seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                      LM_QUERYITEMCOUNT, 0, 0);
                                                      
         for( numd=0;numd<seld;numd++ )
            {
            CHAR dlmsg[80];
            CHAR dlnum[10];
               
               
            ltoa(pgmData[16], dlnum,10);
            strcpy(dlmsg, "MailRun Preview   Downloading message ");
            itoa(numd+1,TTnum,10);
            strcat(dlmsg, TTnum);
            strcpy(listc, "TOP ");
            strcat(listc, TTnum);
            strcat(listc, " ");
            strcat(listc, dlnum);
            strcat(listc, termn);
            memset(&receivebufA, 0, sizeof(receivebufA));
    	  WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), dlmsg);
            send(sock, listc, strlen(listc), 0);

            lnum = 0;
            do
               {
               newlnum = lnum;

               cnts = 0;
               do
                  {
                  if( cnts > 0 )
                     DosSleep(100);
                  rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  cnts++;
                  }
               while(rval <= 0 && cnts < MAXTRIES);   
                     
               // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
               
               lnum = getStr2(newlnum, receivebuf, receivebufA);
               }
            while( lnum != -1 ); 
               
            lnum = 0;
            do
               {
               strndel(receivebuf, 1);
               }
            while( receivebuf[0] != '\x0d' );   
            strndel(receivebuf, 1); 
            
            if( receivebuf[strlen(receivebuf)-3] == '\x2e' )
               {
               receivebuf[strlen(receivebuf)-5] = '\0';
               }
            dload(numd, receivebuf);
            }
         }
      }
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   }
DosBeep(400, 50);
// PREVIEWBUSY = FALSE;
WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), "MailRun Preview   Downloading completed!");
DosSleep(500);
WinSetWindowText(WinWindowFromID(WinQueryWindow(hwndDlg, QW_PARENT), FID_TITLEBAR), "MailRun Preview");
unsubcpview(hwndDlg);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID downloadMailV(PVOID downloadmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
ULONG bkcolor;
ULONG orgcolor, attrFound;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR maddr[] = "grobin";
CHAR myaddr[] = "grobin@erinet.com";
CHAR eaddr[] = "erinet.com";
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufx[bsize];
CHAR receivebufW[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR totbytes[260];
CHAR totmessages[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
static MBD mdat; 
INT socks[1];
INT dontblock, cnts;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = ((PFCBD)downloadmaildat)->hwndDlg;

subcpview(hwndDlg);

// PREVIEWBUSY = TRUE;

strcpy(serverbuf, mailServer);
strcpy(userbuf, "USER ");
strcat(userbuf, userName);
strcat(userbuf, termn);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);


sock_init();

sock = socket(AF_INET, SOCK_STREAM, 0);

if (sock < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
   soclose(sock);   
   }
else
   {
   hp = gethostbyname(serverbuf);
   if (!hp) 
      {
      unsubcpview(hwndDlg);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
      soclose(sock);   
      } 
   else 
      {
      memset(&server, 0, sizeof(server));
      bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
      server.sin_port = htons(mailreceiveport);
      server.sin_family = AF_INET;
        
      if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
         {
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         unsubcpview(hwndDlg);
         WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
         }
      else 
         {
         dontblock = 1;
         ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));
         memset(&receivebuf, 0, sizeof(receivebuf));

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         CHAR er[260];
      
      
         socks[0] = sock;
         select(socks, 1, 0, 0, 1000);
         
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, userbuf, strlen(userbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
                    
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
         
      if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         memset(&receivebuf, 0, sizeof(receivebuf));
         send(sock, passwordbuf, strlen(passwordbuf), 0);

         cnts = 0;
         do
            {
            if( cnts > 0 )
               DosSleep(100);
            rval = recv(sock, receivebuf, bsize, 0); 
            cnts++;
            }
         while(rval <= 0 && cnts < MAXTRIES);   
                     
         // rval = recv(sock, receivebuf, bsize, 0); 
         
         if (rval <= 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            unsubcpview(hwndDlg);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1015),TRUE);
            }
         }      
         
      if( strlen(receivebuf) > 4  && strnicmp(receivebuf, "+OK", 3) == 0 )
         {
         ULONG bnum, seld, seldn;
         INT vb, vc, slen, gf;
         CHAR listc[260];
         CHAR num[80];
         CHAR TTnum[80];
         CHAR TUnum[80];
         CHAR TMPnum[80];
         INT vnum, er;
         APIRET rc;
         CHAR endt[] = "\x0a\x0d";
         CHAR *rbuf;
         INT lnum, newlnum;
         INT numf;
         
         numf = 0;
         seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                      LM_QUERYSELECTION,
                                                      MPFROMLONG(LIT_FIRST),
                                                      MPFROMLONG(0));

         if( seld != LIT_NONE )
            {
            CHAR dlnum[10];
               
               
            ltoa(pgmData[16], dlnum,10);
            itoa(seld+1,TTnum,10);
            strcpy(listc, "TOP ");
            strcat(listc, TTnum);
            strcat(listc, " ");
            strcat(listc, dlnum);
            strcat(listc, termn);
            memset(&receivebuf, 0, sizeof(receivebuf));
            // memset(&receivebufA, 0, sizeof(receivebufA));
            send(sock, listc, strlen(listc), 0);
            lnum = 0;
            do
               {
               memset(&receivebufA, 0, sizeof(receivebufA));
               newlnum = lnum;

               cnts = 0;
               do
                  {
                  if( cnts > 0 )
                     DosSleep(100);
                  rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  cnts++;
                  }
               while(rval <= 0 && cnts < MAXTRIES);   
                     
               // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
               
               lnum = getStr2(newlnum, receivebuf, receivebufA);
               }
            while( lnum != -1 ); 
               
            lnum = 0;
            do
               {
               strndel(receivebuf, 1);
               }
            while( receivebuf[0] != '\x0d' );   
            strndel(receivebuf, 1); 
            
            if( receivebuf[strlen(receivebuf)-3] == '\x2e' )
               {
               receivebuf[strlen(receivebuf)-5] = '\0';
               }
            strcpy(mdat.str, receivebuf);   
            mdat.hwndDlg = hwndDlg;
            _beginthread(dloadV, NULL, BSTACK, (PVOID)&mdat);
            }
         do
            {
            DosSleep(500);
            seld = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                                        LM_QUERYSELECTION,
                                                        MPFROMLONG(seld),  
                                                        MPFROMLONG(0));
            if( seld != LIT_NONE )
               {      
               CHAR dlnum[10];
               
               
               ltoa(pgmData[16], dlnum,10);
               numf++;                                      
               itoa(seld+1,TTnum,10);
               strcpy(listc, "TOP ");
               strcat(listc, TTnum);
               strcat(listc, " ");
               strcat(listc, dlnum);
               strcat(listc, termn);
               memset(&receivebuf, 0, sizeof(receivebuf));
               memset(&receivebufA, 0, sizeof(receivebufA));
               send(sock, listc, strlen(listc), 0);

               lnum = 0;
               do
                  {
                  memset(&receivebufA, 0, sizeof(receivebufA));
                  newlnum = lnum;

                  cnts = 0;
                  do
                     {
                     if( cnts > 0 )
                        DosSleep(100);
                     rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                     cnts++;
                     }
                  while(rval <= 0 && cnts < MAXTRIES);   
                     
                  // rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                  
                  lnum = getStr2(newlnum, receivebuf, receivebufA);
                  }
               while( lnum != -1 ); 

               lnum = 0;
               do
                  {
                  strndel(receivebuf, 1);
                  }
               while( receivebuf[0] != '\x0d' );   
               strndel(receivebuf, 1); 
            
               if( receivebuf[strlen(receivebuf)-3] == '\x2e' )
                  {
                  receivebuf[strlen(receivebuf)-5] = '\0';
                  }
               strcpy(mdat.str, receivebuf);   
               mdat.hwndDlg = hwndDlg;
               _beginthread(dloadV, NULL, BSTACK, (PVOID)&mdat);
               }   
            }
         while(seld != LIT_NONE);  
         }
      }
   send(sock, quitbuf, strlen(quitbuf), 0);
   soclose(sock);   
   }
DosBeep(400, 50);
// PREVIEWBUSY = FALSE;
unsubcpview(hwndDlg);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}



VOID dloadV(PVOID viewdat)
{
USHORT usReturn;
HWND hNewFrame;
HAB habT;
HMQ hmqT;
HWND hwndDlg;
CHAR mStr[bsize];


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = ((PFMBD)viewdat)->hwndDlg;
strcpy(mStr, ((PFMBD)viewdat)->str);

strcpy(receivebufA, mStr);
hNewFrame = OpenVIEWMR(hwndDlg, 0);
usReturn = (USHORT) WinProcessDlg(hNewFrame);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}



INT playWavFile(CHAR *fname, INT volnum)
{
CHAR waveStrVol[127];
CHAR waveStr[127];
CHAR volnumStr[127];
ULONG   dwError;            
INT vnumStr;
if( strlen(fname) == 0 )
   return(0);
strcpy(waveStrVol, "set mailrunio audio volume ");
itoa(volnum, volnumStr, 10);
strcat(waveStrVol, volnumStr);
strcat(waveStrVol, " wait");
strcpy(waveStr, "open ");
strcat(waveStr, fname);
strcat(waveStr, " alias mailrunio shareable wait");
dwError = pmciSendString(waveStr, NULL, 0, 0, 0 );
if ( dwError != 0 )
   {
   return(0);
   }
dwError = pmciSendString(waveStrVol, NULL, 0, 0, 0 );
if ( dwError != 0 )
   {
   return(0);
   } 
dwError = pmciSendString("play mailrunio wait", NULL, 0, NULLHANDLE, 0 );
if ( dwError != 0 )
   {
   pmciSendString ("close mailrunio wait", NULL, 0, 0, 0 );
   return(0);  
   }
dwError = pmciSendString ("close mailrunio wait", NULL, 0, 0, 0 );
return(1);
}


VOID menuChoice(HWND hwndDlg, HWND hwndFrame, HWND hwndPopup, ULONG msg, MPARAM mp1, MPARAM mp2)
{
switch (SHORT1FROMMP(mp1))
   { 
   case ID_MRQUIT :
      WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
      break;
         
   case ID_MRABOUT :
      {
      USHORT usReturn;
      HWND hNewFrame;
      
      FLOATME = 0;
      hNewFrame = OpenABOUT(hwndDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      FLOATME = 1;
      }
      break; 
         
   case ID_MRSETTINGS :
      {
      USHORT usReturn;
      HWND hNewFrame;
         
      FLOATME = 0;
      hNewFrame = OpenSETTINGS(hwndDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      FLOATME = 1;
      }
      break;
         
   case ID_MRMINIMIZENOW :
      {
      WinSetWindowPos(hwndFrame, HWND_TOP, pgmData[0], pgmData[1], pgmData[2], pgmData[3], SWP_MOVE | SWP_SIZE |SWP_MINIMIZE);
      }
      break;
         
   case ID_MRMINIMIZE :
      {
      if( pgmData[6] )
         {
         pgmData[6] = 0;
         WinCheckMenuItem(hwndPopup, ID_MRMINIMIZE, FALSE);
         }
      else
         {
         pgmData[6] = 1;
         WinCheckMenuItem(hwndPopup, ID_MRMINIMIZE, TRUE);
         }   
      saveMRSet(hwndDlg);
      }
      break;
         
   case ID_MRAUTOCHECKSTART :
      {
      chkdat1.hwndDlg = hwndDlg;

      // debugMsgULong(pgmData[8], "pgmData[8]");
      pgmData[11] = 0;
      saveMRSet(hwndDlg);
      DosKillThread(suspendthread);
      if( strlen(mailServer) > 0 && strlen(userName) > 0 && strlen(passWord) > 0 ) 
         {
         ULONG bkgndcolor;
         
         bkgndcolor = CLR_CYAN;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                                 PP_BACKGROUNDCOLORINDEX,
                                 sizeof(ULONG),     
                                 &bkgndcolor);     
         mailthread = _beginthread(checkForMail, NULL, BSTACK, (PVOID)&chkdat1);
         }
      else
         {
         msgOKBox(hwndDlg, "Attention!", "You must enter your domain name, user name, and password in the MailRun settings page before running it.");
         }
      }
      break;
         
   case ID_MRAUTOCHECKSTOP :
      {
      ULONG bkgndcolor;
       
      PAUSESP = FALSE;
      bkgndcolor = CLR_RED;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                              PP_BACKGROUNDCOLORINDEX,
                              sizeof(ULONG),     
                              &bkgndcolor);     
      STOPME = 1;
      // WinEnableControl(hwndDlg, 1000, TRUE);
      DosKillThread(mailthread);
      DosKillThread(mailthread);
      pgmData[11] = 0;
      saveMRSet(hwndDlg);
      DosKillThread(suspendthread);
      WinSetDlgItemText(hwndDlg, 1003, "");
      /*
      if( DosKillThread(mailthread) != 0 )
         {
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         }
      */   
      }
      break;
         
   case ID_MRCHECKNOW :
      {
      chkdat2.hwndDlg = hwndDlg;

      PAUSESP = FALSE;
      pgmData[11] = 0;
      saveMRSet(hwndDlg);
      DosKillThread(suspendthread);
      if( strlen(mailServer) > 0 && strlen(userName) > 0 && strlen(passWord) > 0 ) 
         {
         mailthread2 = _beginthread(checkForMailNow, NULL, BSTACK, (PVOID)&chkdat2);
         }
      else
         {
         msgOKBox(hwndDlg, "Attention!", "You must enter your domain name, user name, and password in the MailRun settings page before running it.");
         }
      }
      break;
      
   case ID_MRSTARTPROG :
      {
      startMailProg();
      }
      break;
      
   case ID_MRPREVIEW :
      {
      USHORT usReturn;
      HWND hNewFrame;

      FLOATME = 0;
      hNewFrame = OpenPREVIEW(hwndDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      FLOATME = 1;
      }
      break;
      
      
   case ID_NETCHATSET :
      {
      USHORT usReturn;
      HWND hNewFrame;
      
      
      hNewFrame = OpenNCSET(hwndDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      }
      break; 
      
   }
}   


VOID startMPreview(PVOID hwnd)
{
HAB habT;
HMQ hmqT;
USHORT usReturn;
HWND hNewFrame;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

DosBeep(100, 100);
hNewFrame = OpenPREVIEW((HWND)hwnd, 0);
usReturn = (USHORT) WinProcessDlg(hNewFrame);
DosBeep(300, 100);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID startMProg(PVOID hwnd)
{
HAB habT;
HMQ hmqT;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

startMailProg();

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}



VOID startMailProg(VOID)
{
if( strlen(mProg) > 0 )
   {
   CHAR spath[260];
   INT kd, mark;
         
   if( WinQueryObject(mProg) != NULLHANDLE )
      {
      strcpy(spath, mProg);
      for( kd=0;kd<strlen(spath);kd++ )
         {
         if( spath[kd] == '\\' )
            mark = kd;
         }
      if( mark == 2 )
         spath[3] = '\0';
      else   
         spath[mark] = '\0';
      callPgm(mProg, mProgArgs, PROG_DEFAULT,  SWP_ACTIVATE, spath, mProg); 
      }
   else   
      msgOKBox(HWND_DESKTOP, "Attention!", "Invalid program or program path/name entered incorrectly!");
   }
else
   {
   msgOKBox(HWND_DESKTOP, "Attention!", "You must enter your mail program in the MailRun settings page.");
   }
}      


void strdelc(char *s, char c)
{
while ( *s )
   {
   if ( *s == c )
      strcpy( s, s+1 );
   else
      s++;
   }
}


int strndel(char *s, int n)
{
int len;

len = strlen(s);
if( len < n )
   return(0);
strcpy(s, s+n);
return(1);
}


char * strinsert(char *s, char insert)
{
char *sptr;

sptr = (char*)calloc(strlen(s)+1, sizeof(char));

if( sptr == NULL )
   return(NULL);

strcpy(sptr, s);
*s = insert;
strcpy(s+1, sptr);
free(sptr);
return(s);
}




VOID callPgm(PSZ PgmName, PSZ PgmInputs, SHORT PgmType,
	         ULONG swapStuff, PSZ startDir,  PSZ title )
{
PROGDETAILS  pDetails;

pDetails.Length          = sizeof(PROGDETAILS);
pDetails.progt.progc     = PgmType;
pDetails.progt.fbVisible = SHE_VISIBLE;
pDetails.pszTitle        = title;
pDetails.pszExecutable   = PgmName;
pDetails.pszParameters   = PgmInputs;
pDetails.pszStartupDir   = startDir;
pDetails.pszIcon         = "";
pDetails.pszEnvironment  = NULL;
// pDetails.pszEnvironment  = "WORKPLACE\0\0";
pDetails.pszEnvironment  = "";
pDetails.swpInitial.fl   = swapStuff; /* window positioning */
pDetails.swpInitial.cy   = 0;    /* width of window */
pDetails.swpInitial.cx   = 0;    /* height of window */
pDetails.swpInitial.y    = 0;    /* lower edge of window */
pDetails.swpInitial.x    = 0;    /* left edge of window */
pDetails.swpInitial.hwndInsertBehind = HWND_TOP;
pDetails.swpInitial.hwnd             = NULLHANDLE;
pDetails.swpInitial.ulReserved1      = 0;
pDetails.swpInitial.ulReserved2      = 0;

WinStartApp( NULLHANDLE, &pDetails, PgmInputs, NULL, 1);
}




BOOL callPgmDSS(PSZ PgmName, PSZ PgmInputs, UINT PgmType, ULONG SSFStuff, PSZ startDir,  PSZ title )
{
STARTDATA   StartData;      
ULONG       SessID;           
PID         pid;              
UCHAR ObjBuf[255];
APIRET rc;


// ***** callPgmDSS(fqfn, netChatArg, SSF_TYPE_PM, SSF_CONTROL_VISIBLE, NULL, NULL);
// ***** SSF_TYPE_WINDOWABLEVIO = 2 or SSF_TYPE_WINDOWEDVDM = 7 
// ***** SSF_CONTROL_VISIBLE | SSF_CONTROL_NOAUTOCLOSE

StartData.Length = sizeof(STARTDATA);
StartData.Related = SSF_RELATED_INDEPENDENT;  
StartData.FgBg = SSF_FGBG_FORE;     
StartData.TraceOpt = SSF_TRACEOPT_NONE;
StartData.PgmTitle = title;     
StartData.PgmName = PgmName;       
StartData.PgmInputs = PgmInputs;  
StartData.TermQ = 0;                
StartData.Environment = NULL;       
StartData.InheritOpt = SSF_INHERTOPT_SHELL;   
StartData.SessionType = PgmType;  
StartData.IconFile = 0;             
StartData.PgmHandle = 0;         
StartData.PgmControl = SSFStuff;
StartData.InitXPos = 0;
StartData.InitYPos = 0;
StartData.InitXSize = 0;         
StartData.InitYSize = 0;         
StartData.Reserved = 0;

StartData.ObjectBuffer = ObjBuf;   
StartData.ObjectBuffLen = 100;     
rc = DosStartSession(&StartData, &SessID, &pid);
if (rc == 0)
   return(TRUE);
else
   return(FALSE);   
}





INT msgBoxOKCANCEL(HWND hwndDlg, CHAR *title, CHAR *msg)
{
if ( WinMessageBox(HWND_DESKTOP,
                          hwndDlg,
                          msg,
                          title,
                          0,
                          MB_ICONEXCLAMATION | MB_OKCANCEL) == MBID_CANCEL )
   {
   return(0);
   }
else
   return(1);
}


/*
VOID msgOK(CHAR *title, CHAR *message)
{
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              message,
              title,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}
*/


VOID debugMsgStr(CHAR *str, CHAR *varName)
{
CHAR dMsg[255] = "Debug Message string ... ";

strcat(dMsg, varName),
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}

VOID debugMsgInt(INT num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message Int ... ";

strcat(dMsg, varName),
itoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}

VOID debugMsgULong(ULONG num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message ULong ... ";

strcat(dMsg, varName),
ultoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}


VOID debugMsgLong(LONG num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message Long ... ";

strcat(dMsg, varName),
ltoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}


VOID debugMsgCH(CHAR ch, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message char ... ";

strcat(dMsg, varName),
str[0] = ch;
str[1] = '\0';
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}



BOOL isNCActive(VOID)
{
SWCNTRL sw;
USHORT numTasks, bufSize, i;
PSWBLOCK pswb;
PVOID bm;

numTasks = WinQuerySwitchList(0, NULL, 0);
bufSize = sizeof(SWBLOCK) * numTasks;
DosAllocMem(&bm, bufSize, PAG_READ | PAG_WRITE | PAG_COMMIT);
pswb = bm;
WinQuerySwitchList(0, pswb, bufSize);
for( i=0;i<numTasks;i++)
   {
   sw = *(PSWCNTRL) ((CHAR*)&(pswb[i].aswentry[0].swctl) - sizeof(ULONG)*i);
   if( strcmp(sw.szSwtitle, "NetChat for OS/2") == 0 )
      {
      DosFreeMem(bm);
      return(TRUE);
      }
   }
DosFreeMem(bm);
return(FALSE);
}



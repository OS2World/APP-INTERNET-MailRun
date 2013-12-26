/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : NOTIFY1.C                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

/* ##START Form.41 Top of source file */
/* ##END Top of source file */
#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_GPI
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* ##START Form.43 Pre include files */
/* ##END Pre include files */
#include "MAIN.H"
#include "NOTIFY1.H"
#include "NOTIFY1.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <global.h>
#include <xtra.h>
#include <xtrarc.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY NOTIFY1DlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PNOTIFY1FORMINFO pNOTIFY1FormInfo=(PNOTIFY1FORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */

 ULONG ultimer;
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(NOTIFY1FORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pNOTIFY1FormInfo=(PNOTIFY1FORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      PAUSEAC = TRUE;

      if( pgmData[13] )
         {
         DosBeep(900, 50);
         DosBeep(1200, 50);
         DosBeep(1500, 50);
         DosBeep(900, 50);
         DosBeep(1200, 50);
         DosBeep(1500, 50);
         }
         
      if( pgmData[9] )
         ultimer = WinStartTimer(0,hwndDlg,ID_FORMTIMER,pgmData[10]*1000);

      {
      ULONG dtHeight, dtWidth, lHeight, lWidth;
      SWP swp;
      dtHeight = WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN);
      dtWidth = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
      WinQueryWindowPos(hwndDlg, (PSWP) &swp);
      lWidth = (dtWidth/2) - (swp.cx/2); 
      lHeight = (dtHeight/2) - (swp.cy/2); 
      WinSetWindowPos(hwndDlg, HWND_TOP, lWidth, lHeight, 0, 0, SWP_MOVE | SWP_SHOW | SWP_ACTIVATE);
      }

      WinSendDlgItemMsg(hwndDlg, 1002,
                        SPBM_SETLIMITS,
                        MPFROMLONG(60),                  
                        MPFROMLONG(1));                    

      WinSendDlgItemMsg(hwndDlg, 1002,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(pgmData[12]), 0);


      WinSetDlgItemText(hwndDlg, 1004, mmsg);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   /* Form event Destroyed WM_DESTROY */
   case WM_DESTROY :
      {
      /* ##START Form.3  */
      /* Form events - Destroyed */


      WinSendDlgItemMsg(hwndDlg, 1002,
                        SPBM_QUERYVALUE,
                        MPFROMP(&pgmData[12]),   
                        MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
                        
      PAUSEAC = FALSE;

      saveMRSet(hwndDlg);
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1000 Clicked/Selected */
      case 1000:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - ~OK  1000 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~OK / Suspend  1001 */

         PAUSEAC = FALSE;

         if( pgmData[11] == 0 )
            {
            pgmData[11] = 1;
            WinSendDlgItemMsg(hwndDlg, 1002,
                           SPBM_QUERYVALUE,
                           MPFROMP(&pgmData[12]),   
                           MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
                           
            saveMRSet(hwndDlg);
            _beginthread(suspendChk, NULL, 32768, (PVOID)hwndDlg);              
            }
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1006 Clicked/Selected */
      case 1006:
         {
         /* ##START 1006.0  */
         /* Event Clicked/selected - OK-Start preview  1006 */
         HAB hab;
         HWND hwnds;


         // hwnds = WinQueryWindow(hwndFrame, QW_OWNER);

         WinStopTimer(hab, hwndDlg, ID_FORMTIMER);

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);

         // _beginthread(startMPreview, NULL, 16384, (PVOID)&hwnds);              

         PAUSESP = TRUE;

         WinPostMsg(WinQueryWindow(hwndFrame, QW_OWNER), WM_COMMAND, MPFROM2SHORT(ID_MRPREVIEW, 0), 0);
         /* ##END  */
         }
         break;
      /* Button 1007 Clicked/Selected */
      case 1007:
         {
         /* ##START 1007.0  */
         /* Event Clicked/selected - OK-Start program  1007 */
         HAB hab;

         WinStopTimer(hab, hwndDlg, ID_FORMTIMER);

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);

         _beginthread(startMProg, NULL, 16384, (PVOID)NULLHANDLE);              

         // WinPostMsg(WinQueryWindow(hwndFrame, QW_OWNER), WM_COMMAND, MPFROM2SHORT(ID_MRSTARTPROG, 0), 0);

         // startMailProg();
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* Spin Button 1002 Event Handlers */
      case 1002:
         switch (SHORT2FROMMP(mp1)) {
         /* Enter */
         case SPBN_SETFOCUS:
            {
            /* ##START 1002.4  */
            /* Event Enter - Spin Button  1002 */
            HAB hab;

            WinStopTimer(hab, hwndDlg, ID_FORMTIMER);
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Code sections - User defined messages */

 case WM_TIMER :
    {
    switch (SHORT1FROMMP(mp1))
       {
       case ID_FORMTIMER:
          WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
          break;
       
       /* case ID_SUSPENDTIMER:
          pgmData[11] = 0;
          saveMRSet(hwndDlg);
          DosBeep(100, 300);
          break; */
       
       default:
          break;
       }         
    }
    break;
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenNOTIFY1(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           NOTIFY1DlgProc, 
           0, ID_NOTIFY1FORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

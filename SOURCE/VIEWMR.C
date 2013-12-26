/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : VIEWMR.C                                                       */
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
#include "VIEWMR.H"
#include "VIEWMR.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY VIEWMRDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PVIEWMRFORMINFO pVIEWMRFormInfo=(PVIEWMRFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(VIEWMRFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pVIEWMRFormInfo=(PVIEWMRFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Event Form events, Opened */

      CHAR numhdr[40];
      CHAR mhdr[40];
      CHAR mhdr1[] = "View mail (max. ";
      CHAR mhdr2[] = " lines) From : ";
      CHAR shdr[1536];
      CHAR infrom[] = "From: ";
      CHAR *res;
      INT sz, nx, szh;

      ltoa(pgmData[16], numhdr, 10);
      strcpy(mhdr, mhdr1);
      strcat(mhdr, numhdr);
      strcat(mhdr, mhdr2);
      strcpy(shdr, mhdr);
      szh = strlen(shdr);
      sz = strlen(receivebufA);
      if( sz <= bsize )
         {
         res = NULL;
         res = strstr(receivebufA, infrom);
         if( res != NULL )
            {
            nx = 0;
            do
               {
               shdr[nx+szh] = res[nx+strlen(infrom)];
               nx++;
               }
            while(res[nx+strlen(infrom)] != '\x0a');
            shdr[(nx+szh)-1] = '\0';
            }
         else
            strcat(shdr, "Unknown");  
         }      
            
      WinSetDlgItemText(hwndFrame, FID_TITLEBAR, shdr);

      if( receivebufA[strlen(receivebufA)-2] == '\x2e' )
         receivebufA[strlen(receivebufA)-2] = '\0';
      if( receivebufA[strlen(receivebufA)-1] == '\x2e' )
         receivebufA[strlen(receivebufA)-1] = '\0';
      WinSetDlgItemText(hwndDlg, 1000, receivebufA);
      // DosBeep(400, 100);

      oldWinProc = WinSubclassWindow(WinWindowFromID(hwndDlg, 1000), saveFileProc);
      WinSetWindowPtr(WinWindowFromID(hwndDlg, 1000), 0, (PVOID) oldWinProc);
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
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      } /* end switch */
      break;

   /* Allow frame window to handle accelerators */
   case WM_TRANSLATEACCEL:
        if (WinSendMsg(hwndFrame, msg, mp1, mp2 ))
           return (MRESULT) TRUE;
        return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );
   break;
 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenVIEWMR(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_TASKLIST | FCF_MAXBUTTON | FCF_MINBUTTON | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_VIEWMRFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_VIEWMRFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              VIEWMRDlgProc, 
              0, ID_VIEWMRFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}

/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : NCSET.C                                                        */
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
#include "NCSET.H"
#include "NCSET.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY NCSETDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      {
      /* ##START Form.1  */
      /* Form events - Opened */


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

      if( pgmData[20] == 0 )
         WinCheckButton(hwndDlg, 1003, 1);

      if( pgmData[20] == 1 )
         WinCheckButton(hwndDlg, 1004, 1);

      WinSetDlgItemText(hwndDlg, 1005, fqNCPath);

      if( pgmData[19] )
         {
         WinCheckButton(hwndDlg, 1002, 1);
         WinEnableControl(hwndDlg, 1003, TRUE);
         WinEnableControl(hwndDlg, 1004, TRUE);
         WinEnableControl(hwndDlg, 1005, TRUE);
         WinEnableControl(hwndDlg, 1006, TRUE);
         }
      else   
         {
         WinEnableControl(hwndDlg, 1003, FALSE);
         WinEnableControl(hwndDlg, 1004, FALSE);
         WinEnableControl(hwndDlg, 1005, FALSE);
         WinEnableControl(hwndDlg, 1006, FALSE);
         }
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
      /* Button 1000 Clicked/Selected */
      case 1000:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - ~Save  1000 */


         if( WinQueryButtonCheckstate(hwndDlg,1002) )
            pgmData[19] = 1;
         else   
            pgmData[19] = 0;

         if( WinQueryButtonCheckstate(hwndDlg,1003) )
            pgmData[20] = 0;
            
         if( WinQueryButtonCheckstate(hwndDlg,1004) )
            pgmData[20] = 1;

         WinQueryDlgItemText(hwndDlg, 1005, sizeof(fqNCPath), fqNCPath);
            
         saveMRSet(hwndDlg);
            
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~Cancel  1001 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* Check Box 1002 Event Handlers */
      case 1002:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1002.0  */
            /* Event Clicked/Selected - Enable detection of NetChat hail  1002 */




            if( WinQueryButtonCheckstate(hwndDlg,1002) )
               {
               WinEnableControl(hwndDlg, 1003, TRUE);
               WinEnableControl(hwndDlg, 1004, TRUE);
               if( WinQueryButtonCheckstate(hwndDlg,1004) )
                  {
                  WinEnableControl(hwndDlg, 1005, TRUE);
                  WinEnableControl(hwndDlg, 1006, TRUE);
                  }
               }
            else
               {
               WinEnableControl(hwndDlg, 1003, FALSE);
               WinEnableControl(hwndDlg, 1004, FALSE);
               WinEnableControl(hwndDlg, 1005, FALSE);
               WinEnableControl(hwndDlg, 1006, FALSE);
               }
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Radio Button 1003 Event Handlers */
      case 1003:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1003.0  */
            /* Event Clicked/Selected - Notifiy of NetChat hail with bee  1003 */

            if( WinQueryButtonCheckstate(hwndDlg,1003) )
               {
               WinEnableControl(hwndDlg, 1005, FALSE);
               WinEnableControl(hwndDlg, 1006, FALSE);
               }
            else   
               {
               WinEnableControl(hwndDlg, 1005, TRUE);
               WinEnableControl(hwndDlg, 1006, TRUE);
               }
            /* ##END  */
            }
            break;
         /* Mouse button 1 double click */
         case BN_DBLCLICKED:
            {
            /* ##START 1003.1  */
            /* Event Mouse button 1 double click - Notifiy of NetChat hail with bee  1003 */
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Radio Button 1004 Event Handlers */
      case 1004:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1004.0  */
            /* Event Clicked/Selected - Start NetChat immediately to han  1004 */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;


            if( WinQueryButtonCheckstate(hwndDlg,1004) )
               {
               WinEnableControl(hwndDlg, 1005, TRUE);
               WinEnableControl(hwndDlg, 1006, TRUE);
               }
            else   
               {
               WinEnableControl(hwndDlg, 1005, FALSE);
               WinEnableControl(hwndDlg, 1006, FALSE);
               }
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenNCSET(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           NCSETDlgProc, 
           0, ID_NCSETFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

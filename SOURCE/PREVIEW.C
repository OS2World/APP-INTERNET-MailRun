/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : PREVIEW.C                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

/* ##START Form.41 Top of source file */
/* Code sections - Top of source file */
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
#include "PREVIEW.H"
#include "PREVIEW.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
#include <DLOAD.h>
#include <VIEWMR.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY PREVIEWDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PPREVIEWFORMINFO pPREVIEWFormInfo=(PPREVIEWFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(PREVIEWFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pPREVIEWFormInfo=(PPREVIEWFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      PAUSEAC = TRUE;
      saveMRSet(hwndDlg);
      // chkdat3.hwndDlg = hwndDlg;
      // _beginthread(previewMail, NULL, BSIZE, (PVOID)&chkdat3);

      PREVIEWBUSY = FALSE;
      oldMPointer = WinQueryPointer(HWND_DESKTOP);
      newMPointer = WinQuerySysPointer(HWND_DESKTOP, SPTR_WAIT, FALSE);

      if( pgmData[17] )
         {
         WinSendDlgItemMsg(hwndDlg, 1005,
                           LM_DELETEALL, 0, 0);
         WinSetDlgItemText(hwndDlg, 1001, "");
         WinSetDlgItemText(hwndDlg, 1002, "");
         WinSetDlgItemText(hwndDlg, 1003, "");
         WinSetDlgItemText(hwndDlg, 1011, "");
         WinSetDlgItemText(hwndDlg, 1012, "");
         // zeroData();
         chkdat3.hwndDlg = hwndDlg;
         mthread = _beginthread(previewMail, NULL, BSTACK, (PVOID)&chkdat3);
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
      /* Event Form events, Destroyed */

      PAUSESP = FALSE;
      PAUSEAC = FALSE;
      DosKillThread(mthread);
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1010 Clicked/Selected */
      case 1010:
         {
         /* ##START 1010.0  */
         /* Event Clicked/selected - ~OK  1010 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1015 Clicked/Selected */
      case 1015:
         {
         /* ##START 1015.0  */
         /* Event Clicked/selected - ~Refresh  1015 */

         WinSendDlgItemMsg(hwndDlg, 1005,
                           LM_DELETEALL, 0, 0);
         WinSetDlgItemText(hwndDlg, 1001, "");
         WinSetDlgItemText(hwndDlg, 1002, "");
         WinSetDlgItemText(hwndDlg, 1003, "");
         WinSetDlgItemText(hwndDlg, 1011, "");
         WinSetDlgItemText(hwndDlg, 1012, "");
         // zeroData();
         chkdat3.hwndDlg = hwndDlg;
         mthread = _beginthread(previewMail, NULL, BSTACK, (PVOID)&chkdat3);
         /* ##END  */
         }
         break;
      /* Button 1000 Clicked/Selected */
      case 1000:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - ~Delete  1000 */
         INT selv;

         selv = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                        LM_QUERYITEMCOUNT, 0, 0);

         if( selv )
            {
            selv =(LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG(LIT_FIRST),
                                          MPFROMLONG(0));
            if(selv == LIT_NONE)
               {
               msgOKBox(hwndDlg, "Attention!", "No mail message have been selected!");
                  return(0);
               }                              
            }
         else
            {
            msgOKBox(hwndDlg, "Attention!", "You must have some mail messages before you can delete them!");
               return(0);
            }


         if ( WinMessageBox(HWND_DESKTOP,
                            hwndDlg,
         		   "Press Yes to delete all SELECTED messages in your mail box or No to cancel operation.",
         		   "Are You Sure ...",
         		   0,
         		   MB_ICONQUESTION | MB_DEFBUTTON2 | MB_YESNO) == MBID_NO )
            {		   
            return(0);
            }
         else  
            { 
            if( selv != LIT_NONE )
               {
               // DosBeep(100, 300);
               chkdat4.hwndDlg = hwndDlg;
               mthread = _beginthread(deleteMail, NULL, BSTACK, (PVOID)&chkdat4);
               }
            }
         /* ##END  */
         }
         break;
      /* Button 1004 Clicked/Selected */
      case 1004:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - D~ownload  1004 */
         INT retn;

         retn = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                        LM_QUERYITEMCOUNT, 0, 0);

         if( retn )
            {
            retn =(LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG(LIT_FIRST),
                                          MPFROMLONG(0));
            if(retn == LIT_NONE)
               {
               msgOKBox(hwndDlg, "Attention!", "No mail message have been selected!");
                  return(0);
               }                              
            }
         else
            {
            msgOKBox(hwndDlg, "Attention!", "You must have some mail messages before you can download them!");
               return(0);
            }



         {
         USHORT usReturn;
         HWND hNewFrame;

         hNewFrame = OpenDLOAD(hwndDlg, 0);
         usReturn = (USHORT) WinProcessDlg(hNewFrame);

         if( usReturn )
            {
            chkdat4.hwndDlg = hwndDlg;
            mthread = _beginthread(downloadMail, NULL, BSTACK, (PVOID)&chkdat4);
            }
         }
         /* ##END  */
         }
         break;
      /* Button 1016 Clicked/Selected */
      case 1016:
         {
         /* ##START 1016.0  */
         /* Event Clicked/selected - Do~wnload All  1016 */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;

         INT selv;


         selv = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                        LM_QUERYITEMCOUNT, 0, 0);

         if( !selv )
            {
            msgOKBox(hwndDlg, "Attention!", "You must have some mail messages before you can download them!");
               return(0);
            }

         /* if ( WinMessageBox(HWND_DESKTOP,
                            hwndDlg,
         		   "Press Yes to download ALL messages in your mail box or No to cancel operation.",
         		   "Are You Sure ...",
         		   0,
         		   MB_ICONQUESTION | MB_DEFBUTTON2 | MB_YESNO) == MBID_NO )
            return(0); */

         if( selv != 0 )
            {
            USHORT usReturn;
            HWND hNewFrame;

            hNewFrame = OpenDLOAD(hwndDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);

            if( usReturn )
               {
               chkdat4.hwndDlg = hwndDlg;
               mthread = _beginthread(downloadALLMail, NULL, BSTACK, (PVOID)&chkdat4);
               }
            }
         /* ##END  */
         }
         break;
      /* Button 1018 Clicked/Selected */
      case 1018:
         {
         /* ##START 1018.0  */
         /* Event Clicked/selected - D~elete All  1018 */

         INT selv;


         selv = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                        LM_QUERYITEMCOUNT, 0, 0);

         if( !selv )
            {
            msgOKBox(hwndDlg, "Attention!", "You must have some mail messages before you can delete them!");
               return(0);
            }

         if ( WinMessageBox(HWND_DESKTOP,
                            hwndDlg,
         		   "Press Yes to delete ALL messages in your mail box or No to cancel operation.",
         		   "Are You Sure ...",
         		   0,
         		   MB_ICONQUESTION | MB_DEFBUTTON2 | MB_YESNO) == MBID_NO )
            return(0);


         if( selv != 0 )
            {
            chkdat4.hwndDlg = hwndDlg;
            mthread = _beginthread(deleteAllMail, NULL, BSTACK, (PVOID)&chkdat4);
            }
         /* ##END  */
         }
         break;
      /* Button 1019 Clicked/Selected */
      case 1019:
         {
         /* ##START 1019.0  */
         /* Event ~View  1019, Clicked/selected */
         INT retn;

         retn = (LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                        LM_QUERYITEMCOUNT, 0, 0);

         if( retn )
            {
            retn =(LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG(LIT_FIRST),
                                          MPFROMLONG(0));
            if(retn == LIT_NONE)
               {
               msgOKBox(hwndDlg, "Attention!", "No mail message have been selected!");
                  return(0);
               }                              
            }
         else
            {
            msgOKBox(hwndDlg, "Attention!", "You must have some mail messages before you can view them!");
               return(0);
            }


         chkdat4.hwndDlg = hwndDlg;
         mthread = _beginthread(downloadMailV, NULL, BSTACK, (PVOID)&chkdat4);

         /*
         {
         USHORT usReturn;
         HWND hNewFrame;

         hNewFrame = OpenDLOAD(hwndDlg, 0);
         usReturn = (USHORT) WinProcessDlg(hNewFrame);

         chkdat4.hwndDlg = hwndDlg;
         _beginthread(downloadMailV, NULL, BSTACK, (PVOID)&chkdat4);
         }
         */


         /*
         {
         USHORT usReturn;
         HWND hNewFrame;

         hNewFrame = OpenVIEWMR(hwndDlg, 0);
         usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }
         */
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* List Box 1005 Event Handlers */
      case 1005:
         switch (SHORT2FROMMP(mp1)) {
         /* Click/Selected */
         case LN_SELECT:
            {
            /* ##START 1005.0  */
            /* Event Click/Selected - List Box  1005 */

            ULONG sel;

            WinSetDlgItemText(hwndDlg, 1001, "");
            WinSetDlgItemText(hwndDlg, 1002, "");
            WinSetDlgItemText(hwndDlg, 1003, "");

            sel =(LONG)WinSendDlgItemMsg(hwndDlg, 1005,
                                         LM_QUERYSELECTION,
                                         MPFROMLONG(LIT_FIRST),
                                         MPFROMLONG(0));

            if( sel != LIT_NONE )
               {                            
               WinSetDlgItemText(hwndDlg, 1001, pvdat[sel].INDATE);
               WinSetDlgItemText(hwndDlg, 1002, pvdat[sel].INSUBJECT);
               WinSetDlgItemText(hwndDlg, 1003, pvdat[sel].INSIZE);
               }
            /* ##END  */
            }
            break;
         /* Mouse button 1 double click */
         case LN_ENTER:
            {
            /* ##START 1005.3  */
            /* Event Mouse button 1 double click - List Box  1005 */

            WinSendMsg(hwndDlg, WM_COMMAND, MPFROM2SHORT(1019,0), 0);
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      } /* end switch */
      break;

   /* Allow frame window to handle accelerators */
   case WM_TRANSLATEACCEL:
        if (WinSendMsg(hwndFrame, msg, mp1, mp2 ))
           return (MRESULT) TRUE;
        return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );
   break;
 /* ##START Form.38 User defined messages */
 /* Code sections - User defined messages */


 case WM_MOUSEMOVE :
    if ( PREVIEWBUSY )
       { 
       WinSetPointer(HWND_DESKTOP, newMPointer);
          return(MRESULT)TRUE;
       }
    else
       return (WinDefDlgProc(hwndDlg, msg, mp1, mp2));
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenPREVIEW(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_TASKLIST | FCF_MAXBUTTON | FCF_MINBUTTON | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_PREVIEWFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "MailRun Preview", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_PREVIEWFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              PREVIEWDlgProc, 
              0, ID_PREVIEWFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}

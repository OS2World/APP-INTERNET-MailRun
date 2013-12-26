/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : DLOAD.C                                                        */
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
#include "DLOAD.H"
#include "DLOAD.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY DLOADDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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
      CHAR mcwd[260];

      {
      SWP swp, swpD;
      int dtWidth;
      int offX, offY;
      dtWidth = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
      offX = 50;
      offY = 70;
      WinQueryWindowPos(WinQueryWindow(hwndDlg, QW_OWNER), (PSWP) &swp);
      WinQueryWindowPos(hwndDlg, (PSWP) &swpD);
      if( swp.x < 5 )
         swp.x += ((-swp.x) + 1); 
      if( (swp.x+offX+swpD.cx) > (dtWidth-5) )
         {
         int over;
         over = (swp.x+offX+swpD.cx) - (dtWidth-5);
         offX = - (offX+over);   
         }
      if( (swp.y-70) < 5 )
         offY = - offY; 
      WinSetWindowPos(hwndDlg, HWND_TOP, 
                      swp.x+offX, swp.y-offY, 0, 0,
      		SWP_ACTIVATE | SWP_MOVE | SWP_SHOW );
      }

      WinEnableWindow(WinWindowFromID(hwndDlg, FID_SYSMENU), FALSE);
      if( strlen(dloadname) == 0 )
         {
         _getcwd(mcwd, sizeof(mcwd));
         if( mcwd[strlen(mcwd)-1] != '\\' )
            strcat(mcwd, "\\");
         strcpy(dloadname, mcwd);   
         strcat(dloadname, "mymail");   
         }
         
      WinSetDlgItemText(hwndDlg, 1000, dloadname);

      WinSendDlgItemMsg(hwndDlg, 1000, EM_SETSEL,
                        MPFROM2SHORT(0, strlen(dloadname)), 0);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Form events, Closed */

      WinDismissDlg(hwndDlg, FALSE);
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~OK  1001 */

         WinQueryDlgItemText(hwndDlg, 1000, sizeof(dloadname), dloadname);

         if( strlen(dloadname) == 0 )
            {
            msgOKBox(hwndDlg, "Attention", "You must enter a fully qualified file name! (minus extention)");
            }
         else
            {
            INT vk;
            INT mark;
            CHAR tn[260];
            
            strcpy(tn, dloadname);
            for( vk=0,mark=0;vk<strlen(tn);vk++ )   
               {
               if( tn[vk] == '\\' )
                  mark = vk;
               }
            if( mark <= 1 )
               {
               msgOKBox(hwndDlg, "Attention", "Path is NOT valid!");
               return(0);
               }
            if( mark == 2 )      
               tn[3] = '\0';
            else
               tn[mark] = '\0';     
                
            if( !chkValidPath(tn) )
               {
               msgOKBox(hwndDlg, "Attention", "Path is NOT valid!");
                  return(0);
               }
               
            for( vk=0;vk<9;vk++ )
               {
               CHAR num[5];
               
               strcpy(tn, dloadname);
               if( vk > 0 )
                  {
                  if( tn[strlen(tn)-1] != '\\' )
                     strcat(tn, "\\");
                  itoa(vk, num, 10);   
                  strcat(tn, num);    
                  strcat(tn, ".mrm");
                  }
               else
                  strcat(tn, ".mrm");   
               if( existFile(tn) )
                  {
                  if( !msgBoxOKCANCEL(hwndDlg, "Attention!", 
                                     "Base file name already exists! Press OK to continue and replace these file(s) or Cancel to quit operation.") )
                     return(0);
                  } 
               }     
               
            WinDismissDlg(hwndDlg, TRUE);
            WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
            }
         /* ##END  */
         }
         break;
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Cancel  1002 */

         WinDismissDlg(hwndDlg, FALSE);
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
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
HWND OpenDLOAD(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           DLOADDlgProc, 
           0, ID_DLOADFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

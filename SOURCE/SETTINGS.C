/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : SETTINGS.C                                                     */
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
#include "SETTINGS.H"
#include "SETTINGS.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <global.h>
#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY SETTINGSDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
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

      queryMRSet(hwndDlg);

      WinSendDlgItemMsg(hwndDlg, 1028,
                        SPBM_SETLIMITS,
                        MPFROMLONG(60),                  
                        MPFROMLONG(1));                    

      WinSendDlgItemMsg(hwndDlg, 1028,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(pgmData[10]), 0);
                        
      WinSendDlgItemMsg(hwndDlg, 1036,
                        SPBM_SETLIMITS,
                        MPFROMLONG(50),                  
                        MPFROMLONG(1));                    

      WinSendDlgItemMsg(hwndDlg, 1036,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(pgmData[16]), 0);
                        
      WinSetDlgItemText(hwndDlg, 1004, mailServer);
      WinSetDlgItemText(hwndDlg, 1005, userName);
      WinSetDlgItemText(hwndDlg, 1006, passWord);
      WinSetDlgItemText(hwndDlg, 1022, waveFile);
      WinSetDlgItemText(hwndDlg, 1024, mProg);
      WinSetDlgItemText(hwndDlg, 1039, mProgArgs);

      WinSendDlgItemMsg(hwndDlg, 1008,
                        SPBM_SETLIMITS,
                        MPFROMLONG(100000),
                        MPFROMLONG(15));  

      if( pgmData[4] > 100000 )
         pgmData[4] = 60;
         
      if( pgmData[4] < 15 )
         pgmData[4] = 15;
         
         
      WinSendDlgItemMsg(hwndDlg, 1008,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(pgmData[4]), 
                        0);

      if( pgmData[18] )
         {
         WinCheckButton(hwndDlg, 1038, 1);
         }

      if( pgmData[17] )
         {
         WinCheckButton(hwndDlg, 1037, 1);
         }

      if( pgmData[14] )
         {
         WinCheckButton(hwndDlg, 1030, 1);
         }

      if( pgmData[15] )
         {
         WinCheckButton(hwndDlg, 1034, 1);
         }

      if( pgmData[13] )
         {
         WinCheckButton(hwndDlg, 1032, 1);
         }

      if( pgmData[9] )
         {
         WinCheckButton(hwndDlg, 1023, 1);
         }

      switch( pgmData[5] )
         {
         case 0:
            WinCheckButton(hwndDlg, 1010, 0);
            WinCheckButton(hwndDlg, 1026, 0);
            WinCheckButton(hwndDlg, 1031, 1);
            break;
            
         case 1:
            WinCheckButton(hwndDlg, 1010, 0);
            WinCheckButton(hwndDlg, 1026, 1);
            WinCheckButton(hwndDlg, 1031, 0);
            break;
            
         case 2:
            WinCheckButton(hwndDlg, 1010, 1);
            WinCheckButton(hwndDlg, 1026, 0);
            WinCheckButton(hwndDlg, 1031, 0);
            break;
         }   

      if( pgmData[6] )
         {
         WinCheckButton(hwndDlg, 1021, 1);
         }

      if( pgmData[7] )
         {
         WinCheckButton(hwndDlg, 1012, 1);
         }
      else
         {
         WinCheckButton(hwndDlg, 1011, 1);
         }   

      switch( pgmData[8] )
         {
         case 0:
            WinCheckButton(hwndDlg, 1014, 1);
            WinEnableControl(hwndDlg, 1022, FALSE);
            WinEnableControl(hwndDlg, 1023, FALSE);
            WinEnableControl(hwndDlg, 1028, FALSE);
            WinEnableControl(hwndDlg, 1029, FALSE);
            WinEnableControl(hwndDlg, 1032, FALSE);
            break;
            
         case 1:
            WinCheckButton(hwndDlg, 1015, 1);
            WinEnableControl(hwndDlg, 1022, FALSE);
            WinEnableControl(hwndDlg, 1023, FALSE);
            WinEnableControl(hwndDlg, 1028, FALSE);
            WinEnableControl(hwndDlg, 1029, FALSE);
            WinEnableControl(hwndDlg, 1032, FALSE);
            break;
            
         case 2:
            WinCheckButton(hwndDlg, 1016, 1);
            WinEnableControl(hwndDlg, 1022, FALSE);
            WinEnableControl(hwndDlg, 1023, FALSE);
            WinEnableControl(hwndDlg, 1028, FALSE);
            WinEnableControl(hwndDlg, 1029, FALSE);
            WinEnableControl(hwndDlg, 1032, FALSE);
            break;
            
         case 3:
            WinCheckButton(hwndDlg, 1017, 1);
            WinEnableControl(hwndDlg, 1022, FALSE);
            WinEnableControl(hwndDlg, 1032, TRUE);
            WinEnableControl(hwndDlg, 1023, TRUE);
            if( pgmData[9] )
               {
               WinEnableControl(hwndDlg, 1028, TRUE);
               WinEnableControl(hwndDlg, 1029, TRUE);
               }
            else
               {
               WinEnableControl(hwndDlg, 1028, FALSE);
               WinEnableControl(hwndDlg, 1029, FALSE);
               }   
            break;
            
         case 4:
            WinCheckButton(hwndDlg, 1018, 1);
            WinEnableControl(hwndDlg, 1022, TRUE);
            WinEnableControl(hwndDlg, 1023, FALSE);
            WinEnableControl(hwndDlg, 1028, FALSE);
            WinEnableControl(hwndDlg, 1029, FALSE);
            WinEnableControl(hwndDlg, 1032, FALSE);
            break;
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

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1019 Clicked/Selected */
      case 1019:
         {
         /* ##START 1019.0  */
         /* Event Clicked/selected - ~OK  1019 */
         ULONG interval;
         ULONG bkgndcolor;

         WinSendDlgItemMsg(hwndDlg, 1008,
                           SPBM_QUERYVALUE,
                           MPFROMP(&interval),   
                           MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
                           
         if( interval > 100000 )
            pgmData[4] = 60;
         else
            {
            if( interval < 15 )
               pgmData[4] = 15;
            else   
               pgmData[4] = interval;
            }
            
         if( WinQueryButtonCheckstate(hwndDlg,1038) )
            {
            pgmData[18] = 1;
            }
         else   
            {
            pgmData[18] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1037) )
            {
            pgmData[17] = 1;
            }
         else   
            {
            pgmData[17] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1030) )
            {
            pgmData[14] = 1;
            }
         else   
            {
            pgmData[14] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1034) )
            {
            pgmData[15] = 1;
            }
         else   
            {
            pgmData[15] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1032) )
            {
            pgmData[13] = 1;
            }
         else   
            {
            pgmData[13] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1031) )
            {
            pgmData[5] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1026) )
            {
            pgmData[5] = 1;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1010) )
            {
            pgmData[5] = 2;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1021) )
            {
            pgmData[6] = 1;
            }
         else
            {
            pgmData[6] = 0;
            }   


         if( WinQueryButtonCheckstate(hwndDlg,1011) )
            {
            pgmData[7] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1012) )
            {
            pgmData[7] = 1;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1014) )
            {
            pgmData[8] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1015) )
            {
            pgmData[8] = 1;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1016) )
            {
            pgmData[8] = 2;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1017) )
            {
            pgmData[8] = 3;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1018) )
            {
            pgmData[8] = 4;
            }

         if( pgmData[8] > 4 || pgmData[8] < 0 )
            pgmData[8] = 1;

         WinQueryDlgItemText(hwndDlg, 1004, CCHMAXPATH, mailServer);
         WinQueryDlgItemText(hwndDlg, 1005, CCHMAXPATH, userName);
         WinQueryDlgItemText(hwndDlg, 1006, CCHMAXPATH, passWord);
         WinQueryDlgItemText(hwndDlg, 1022, CCHMAXPATH, waveFile);
         WinQueryDlgItemText(hwndDlg, 1024, CCHMAXPATH, mProg);
         WinQueryDlgItemText(hwndDlg, 1039, CCHMAXPATH, mProgArgs);


         WinSendDlgItemMsg(hwndDlg, 1028,
                           SPBM_QUERYVALUE,
                           MPFROMP(&pgmData[10]),   
                           MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));

         WinSendDlgItemMsg(hwndDlg, 1036,
                           SPBM_QUERYVALUE,
                           MPFROMP(&pgmData[16]),   
                           MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));

         pgmData[11] = 0;
         saveMRSet(hwndDlg);
         queryMRSet(hwndDlg);

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1020 Clicked/Selected */
      case 1020:
         {
         /* ##START 1020.0  */
         /* Event Clicked/selected - ~Cancel  1020 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Event Code sections, User defined messages */



 case WM_CONTROL:
    switch (SHORT1FROMMP(mp1))
       {
       case 1010:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1010) )
                {
                WinCheckButton(hwndDlg, 1026, 0);
                WinCheckButton(hwndDlg, 1031, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1026:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1026) )
                {
                WinCheckButton(hwndDlg, 1010, 0);
                WinCheckButton(hwndDlg, 1031, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1031:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1031) )
                {
                WinCheckButton(hwndDlg, 1026, 0);
                WinCheckButton(hwndDlg, 1010, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1011:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1011) )
                {
                WinCheckButton(hwndDlg, 1012, 0);
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1012:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1012) )
                {
                WinCheckButton(hwndDlg, 1011, 0);
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1014:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1014) )
                {
                WinCheckButton(hwndDlg, 1015, 0);
                WinCheckButton(hwndDlg, 1016, 0);
                WinCheckButton(hwndDlg, 1017, 0);
                WinCheckButton(hwndDlg, 1018, 0);
                WinEnableControl(hwndDlg, 1022, FALSE);
                WinEnableControl(hwndDlg, 1023, FALSE);
                WinEnableControl(hwndDlg, 1028, FALSE);
                WinEnableControl(hwndDlg, 1029, FALSE);
                WinEnableControl(hwndDlg, 1032, FALSE);
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1015:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1015) )
                {
                WinCheckButton(hwndDlg, 1014, 0);
                WinCheckButton(hwndDlg, 1016, 0);
                WinCheckButton(hwndDlg, 1017, 0);
                WinCheckButton(hwndDlg, 1018, 0);
                WinEnableControl(hwndDlg, 1022, FALSE);
                WinEnableControl(hwndDlg, 1023, FALSE);
                WinEnableControl(hwndDlg, 1028, FALSE);
                WinEnableControl(hwndDlg, 1029, FALSE);
                WinEnableControl(hwndDlg, 1032, FALSE);
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1016:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1016) )
                {
                WinCheckButton(hwndDlg, 1015, 0);
                WinCheckButton(hwndDlg, 1014, 0);
                WinCheckButton(hwndDlg, 1017, 0);
                WinCheckButton(hwndDlg, 1018, 0);
                WinEnableControl(hwndDlg, 1022, FALSE);
                WinEnableControl(hwndDlg, 1023, FALSE);
                WinEnableControl(hwndDlg, 1028, FALSE);
                WinEnableControl(hwndDlg, 1029, FALSE);
                WinEnableControl(hwndDlg, 1032, FALSE);
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;

       case 1017:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1017) )
                {
                WinCheckButton(hwndDlg, 1014, 0);
                WinCheckButton(hwndDlg, 1016, 0);
                WinCheckButton(hwndDlg, 1015, 0);
                WinCheckButton(hwndDlg, 1018, 0);
                WinEnableControl(hwndDlg, 1022, FALSE);
                WinEnableControl(hwndDlg, 1023, TRUE);
                WinEnableControl(hwndDlg, 1032, TRUE);
                if( pgmData[9] )
                   {
                   WinEnableControl(hwndDlg, 1028, TRUE);
                   WinEnableControl(hwndDlg, 1029, TRUE);
                   }
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;
          
       case 1023:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1023) )
                {
                WinEnableControl(hwndDlg, 1028, TRUE);
                WinEnableControl(hwndDlg, 1029, TRUE);
                pgmData[9] = 1;
                }
             else
                {
                WinEnableControl(hwndDlg, 1028, FALSE);
                WinEnableControl(hwndDlg, 1029, FALSE);
                pgmData[9] = 0;
                }
             }
          return(MRESULT)TRUE;
          
       case 1018:
          if (HIUSHORT(mp1) == BN_CLICKED)
             {
             if( WinQueryButtonCheckstate(hwndDlg, 1018) )
                {
                WinCheckButton(hwndDlg, 1014, 0);
                WinCheckButton(hwndDlg, 1016, 0);
                WinCheckButton(hwndDlg, 1017, 0);
                WinCheckButton(hwndDlg, 1015, 0);
                WinEnableControl(hwndDlg, 1022, TRUE);
                WinEnableControl(hwndDlg, 1023, FALSE);
                WinEnableControl(hwndDlg, 1028, FALSE);
                WinEnableControl(hwndDlg, 1029, FALSE);
                WinEnableControl(hwndDlg, 1032, FALSE);
                }
             else
                {
                // WinCheckButton(hwndDlg, 1014, 0);
                }
             }
          return(MRESULT)TRUE;
          
       default:
          return(MRESULT)TRUE;
       }
       break;
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenSETTINGS(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           SETTINGSDlgProc, 
           0, ID_SETTINGSFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

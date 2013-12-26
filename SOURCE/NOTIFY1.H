/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : NOTIFY1.H                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef NOTIFY1WINDOW_H
#define NOTIFY1WINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenNOTIFY1(HWND hwndOwner, PVOID pInfo);

typedef struct _NOTIFY1FORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* Code sections - Window structure members */

   CHAR mailmsg[260];
   /* ##END Window structure members */
} NOTIFY1FORMINFO;
typedef NOTIFY1FORMINFO * PNOTIFY1FORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
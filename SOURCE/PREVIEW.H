/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : PREVIEW.H                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenPREVIEW(HWND hwndOwner, PVOID pInfo);

typedef struct _PREVIEWFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} PREVIEWFORMINFO;
typedef PREVIEWFORMINFO * PPREVIEWFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
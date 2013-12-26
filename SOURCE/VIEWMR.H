/******************************************************************************/
/*                                                                            */
/* Program: MAILRUN.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : VIEWMR.H                                                       */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef VIEWMRWINDOW_H
#define VIEWMRWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenVIEWMR(HWND hwndOwner, PVOID pInfo);

typedef struct _VIEWMRFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} VIEWMRFORMINFO;
typedef VIEWMRFORMINFO * PVIEWMRFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
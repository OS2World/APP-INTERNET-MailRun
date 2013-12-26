# PROGRAM - Makefile (MAILRUN.MAK) 
#
#       Makefile variables from Build Options 
#
CFLAGS=/c /O /Gm /Ss /W3 /Tl- -I. -I..\SUBPROCS -IG:\VISPROC
LFLAGS=/ST:524688 /A:16 /NOI /NOE /NOD 
L_ADDITIONAL_LIBS=OS2386.LIB DDE4MBS.LIB SO32DLL.LIB TCP32DLL.LIB 
L_ADDITIONAL_OBJS=
COMPILER=ICC
LINKER=LINK386
#
#       Additional definitions 
#
SUBPROCS=..\\SUBPROCS\\
EXCL=!
OBJECTS= \
          ABOUT.OBJ \
          DLOAD.OBJ \
          Main.OBJ \
          NCSET.OBJ \
          NOTIFY1.OBJ \
          PREVIEW.OBJ \
          SETTINGS.OBJ \
          VIEWMR.OBJ \
          xtra.OBJ 

ALL: ..\MAILRUN.EXE 
#
#       Statements to compile the classes
#
ABOUT.OBJ:  ABOUT.C ABOUT.H ABOUT.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) ABOUT.C
DLOAD.OBJ:  DLOAD.C DLOAD.H DLOAD.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) DLOAD.C
Main.OBJ:  Main.C Main.H Main.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) Main.C
NCSET.OBJ:  NCSET.C NCSET.H NCSET.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) NCSET.C
NOTIFY1.OBJ:  NOTIFY1.C NOTIFY1.H NOTIFY1.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) NOTIFY1.C
PREVIEW.OBJ:  PREVIEW.C PREVIEW.H PREVIEW.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) PREVIEW.C
SETTINGS.OBJ:  SETTINGS.C SETTINGS.H SETTINGS.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) SETTINGS.C
VIEWMR.OBJ:  VIEWMR.C VIEWMR.H VIEWMR.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) VIEWMR.C
xtra.OBJ:  $(SUBPROCS)xtra.c 
    $(COMPILER) $(CFLAGS) $(SUBPROCS)xtra.c
#
#       Statements to compile resources for the classes
#
MAILRUN.RES:  MAILRUN.RC \
               ABOUT.RCH ABOUT.RC \
               DLOAD.RCH DLOAD.RC \
               Main.RCH Main.RC \
               NCSET.RCH NCSET.RC \
               NOTIFY1.RCH NOTIFY1.RC \
               PREVIEW.RCH PREVIEW.RC \
               SETTINGS.RCH SETTINGS.RC \
               VIEWMR.RCH VIEWMR.RC 
    RC -r MAILRUN.RC
#
#       Statements to link the EXE file
#
..\MAILRUN.EXE:  $(OBJECTS) MAILRUN.DEF MAILRUN.RES MAILRUN.MAK 
    $(LINKER) @<<
           $(LFLAGS) $(L_ADDITIONAL_OBJS)  +
          ABOUT.OBJ  +
          DLOAD.OBJ  +
          Main.OBJ  +
          NCSET.OBJ  +
          NOTIFY1.OBJ  +
          PREVIEW.OBJ  +
          SETTINGS.OBJ  +
          VIEWMR.OBJ +
          xtra.OBJ ,
          ..\MAILRUN.EXE,, $(L_ADDITIONAL_LIBS), MAILRUN.DEF 
<<
    RC MAILRUN.RES ..\MAILRUN.EXE

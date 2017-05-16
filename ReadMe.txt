MailRun version 1.23
----------------------
1997 - Gary L. Robinson.
2012 - Released as Open Source under the GNU GPL V2 license.
--------------------------------------------------------------




What is MailRun?
-----------------

  MailRun is a small (both in the size of the executable file and the amount of screen real estate if takes up) and fast program to monitor your POP3 mail account.

  It can be set to notify you in, numerous ways, when you have new incoming mail including starting other programs, beeping you, prompting you with a dialog, and playing .WAV files.   

  It's highly configurable and also has a mail preview feature to take a sneak peek at what is in your mail box without having to download it.

  Other features allow downloading the header file and a maximum of 50 lines, deleting files from your mail box, and running multiple copies to monitor multiple mail boxes.

  MailRun can be sized to take up a very small rectangular area and and also be set to float to the top of everything else if desired.

  MailRun also can notify NetChat uers, if desired, when they are being Hailed by someone for a chat session.


Why is MailRun?
----------------

  MailRun was written to be a more flexible POP3 mail monitor than currently is available. It takes up less screen space, it's executable is smaller in size, has numerous ways of notifying you of incoming mail, and has several other features not found together in any other POP3 mail watcher.

  It also was written to work in conjunction with NetChat if desired.


Program Requirements 
----------------

  MailRun requires OS/2 3.x or OS/2 4.x. It should run well in machines with small amounts of memory (6-8mb).

  It also requires you to have TCP/IP installed and an internet provider with an e-mail account. 



MailRun Support 
----------------

  MailRun is primarily supported by me through e-mail and/or a live pre-arranged NetChat session with me.

  My schedule is very erratic and seldom the same from one week to the next, though.

  E-mail is probably the most reliable way of getting to me with a problem report. Please send all the details you can if you send a report of a problem. A "It ain't workin dude!" report doesn't do either of us any good! The devil is in the details .....

  Send all e-mail to either grobin@iname.com or hkypuck@hotmail.com

  These mail boxes are usually read every day.

  E-mail can also be left at the MailTo link on my web page at http://www.coax.net/people/grobin or the MailTo link at NetChat Support Page at http://cud.cow-net.com/badams/index.htm

  
Installing MailRun 
----------------

  Installing MailRun is a huge and tedious task.   

  Step 1 is to copy the single file mailrun.exe to a directory by itself or it can be put in the NetChat directory to conserve space.

  Step 2 is to put an icon on your launch bar or Desktop for it.

  That's it. I hope the installation did not wear you out!


Using MailRun 
----------------

  MailRun should have it's settings pages filled out before going on to the Quick Start section.

  For a Quick Start start, though, only the internet account information area needs to be set if you don't mind using the other program setting defaults.

  When MailRun is first started it appears in the lower left quadrant of the screen.

  All of it's features are accessable through a popup menu. Place your mouse pointer near the top of it's window (in the grey area) and click the right mouse button once to see the popup menu.

  MailRun is moved by putting the mouse pointer on the top part of it's small window (grey area) and holding down on Mouse Button 1 (left) and dragging it to a new location.

  It can be resized by placing the mouse pointer at the edge or corners of it's window and when you see the double arrow then hold down on Mouse Button 1 or 2 and drag to resize.

  Double clicking on the main MailRun screen with mouse button 1 will close the program.


    
Initial setup for MailRun 
----------------

  First bring up the popup menu for mailRun.

  All of it's features are accessable through a popup menu. Place your mouse pointer near the top of it's window (in the grey area) and click the right mouse button once to see the popup menu.

  Select Settings near the bottom of the menu. This will bring up the main mailRun Settings dialog.


  Internet account information -- This area has three entry fields : 

      Domain name -- The domain name is usually everything to the right of the @ symbol in your internet address. eg., bigdude@hailbop.com would have a domain name of hailbop.com

      User name --- The user name is usually everything to the left of the @ symbol in your internet address. eg., bigdude@hailbop.com would have a user name of bigdude 

      Password -- The password is the password assigned to you by your internet provider to access your internet account and/or your mail box.


  Notification methods -- This area has five main ways to notify you when new mail arrives in your mail box. Whichever of the five you select (radio buttons) it can also do either or both of the check box selections at the bottom.

      None -- This selection causes MailRun not to notify you in any way except in it's own windows readout.

      Beep -- This selection causes MailRun execute a small series of beeps.

      Flash -- This selection causes MailRun to lash it's own window readout - a silent type of notification.

      Popup dialog -- This selection causes MailRun to popup a dialog window no matter what ele you are doing on the Desktop. The dialog box has two initial sub-settings for it. Select Beep if you want the popup dialog box to also beep you and select Autoclose if you want the dialog to automatically close regardless if you press the OK button on the dialog or not. If this is selected then set the autoclose time (in seconds) in the spin button below that choice. The autoclose time interval can also be reset on the fly in the popup dialog.

      Play .WAV file -- This selection causes MailRun to run a user selectable .wav file. Enter the fully qualified name of the wave file in the entry field below the button.

      Start program on notification (menu item also) -- This selection can be used in addition to one of the five radio button selections or by itself. It will start almost any other program (OS/2, DOS, or Windows) when new mail arrives in your account.

      Start MailRun Preview screen (menu item also) -- This selection can be used in addition to one of the five radio button selections or by itself. It will start the MailRun mail Preview feature when new mail arrives in your account.


  Program startup -- This area has two main selections to set to determine what, if anything, you want MailRun to automatically do when it starts up.

      Minimize -- Selecting this will cause MailRun to be started in a minimized state.

      Mail messages -- Selecting this will give you the choice of having MailRun start in a dormant state and not check for incoming mail, check only once then stop checking, or to start in Autocheck mode and check at the intervals set below in the Autocheck spin box.


  Mail notification -- This area has only two choices to decide when you want to be notified.

      Every time MR checks for mail -- This selection will notify you every time MailRun checks for mail. this is usually just used for testing purposes and probably won't be used by most people.

      Only when mail is found -- This is the default and normal selection. This selection will cause MailRun to notify you whenever there is mail in your mail box.

    
  Autocheck (seconds) -- Set this spin button to the interval that you want MailRun to use to notify you of mail in your mail box. It has a minimum setting of 15 seconds and a maximum setting of 100,000 seconds.

  Max. lines to download -- This spin button sets the maximum number of lines in a mail message to download (in addition to the header information) in a Mail Preview download operation.

  Start mail query on preview open -- This selection makes the Mail Preview dialog to query your mail box when you start it. Otherwise the Preview dialog starts and waits for you to decide what to do.

  Force window to float to top -- This selection makes the main MailRun window float to the top of the screen every few seconds regardless if it is covered up by other program windows.


NetChat settings for MailRun
----------------------------- 

  MailRun can be somewhat integrated with NetChat to make mailRun either beep you when it detects a Hail message in your mail box or to start NetChat in Monitor ON mode when it detects a Hail message. 

  To enable this integration first check the check box for "Enable detection of NetChat hailing messages".

  Then select whether what you want MailRun to do when it finds a NetChat message in your mail box.

  If you set MailRun to start NetChat in Monitor ON mode then you must also type in the complete path to where NetChat is located. Just the complete path. Do not put the name of the netchat.exe file in the entry field.


Quick Start 
-------------

  For a Quick Start start only the internet account information area (on the main settings page) needs to be set if you don't mind using the other program setting defaults.

  Additionally, if you want to use it integrated with NetChat, the NetChat settings page for mailRun needs to be set also.

  Both of these settings pages are accessable by placing the mouse pointer over the upper grey area of the MailRun main screen and clicking right mouse button once to activate the popup menu. 

  Then select Settings and/or NetChat Settings to bring up the respective settings dialog boxes.

  After filling out the minimum settings and saving them close the program and restart it to test the program.


MailRun popup menu items 
--------------------------

  Start autochecking for mail -- This selection makes MailRun start looking for mail in your mail account at the time interval set in the Settings dialog.

  Stop autochecking for mail -- This selection will basically "turn off" MailRun and stop it from checking for mail.

  Check for mail now -- This selection will make MailRun check once for mail immediately. It can be selected at any time - whether MailRun is in autocheck mode or not.

  Minimize at program startup -- This selection will force MailRun to be minimized when it is started.

  Minimize now -- This selection causes MailRun to be minimized immediately.

  Start mail program -- This selection will start your mail program if you entered one on the Settings page under the notification method section. You do not have to have the check box on the settings page actually checked to start your mail program from this menu item.

  Quit -- Closes MailRun.

  Settings ... -- This selection brings up the main Settings dialog for MailRun.

  NetChat Settings ... -- This selection brings up the dialog for the NetChat integration settings.

  About -- This selection brings up the About dialog box. This is where you can get the info on what version you are using and info on where to register the program.



MailRun preview dialog
----------------------- 

  The MailRun preview dialog is used to preview what you have in your mail account. It has several features to make this a useful tool.

  The Preview dialog can be set to query your mail account when the dialog is first is opened. It will get the basic information of what is currently in your account. It displays a list of the messages in the dialog's list box, the total number of messages there, and the total number of bytes in all the messages combined.

  You can also scroll the messages and see individual information for each one. The subject line, date, time, and size are all displayed for the currently selected message.

  Messages can be deleted individually or all the messages can be deleted at the same time by pressing the appropriate button.

  Messages can also be individually downloaded or all messages can be downloaded. Note that MailRun can download a maximum of 50 lines of a message (in addition to the header).   

  Messages can also be viewed without downloading them by selecting the desired message and pressing the View button. Note that you can only view a maximum of 50 lines (in addition to the header).

  The Query mail button will query and/or refresh all the information on whats currently in your mail account. 



MailRun notification dialog
--------------------------- 

  MailRun can be set to notify you of incoming mail by popping up a dialog and showing you how many messages are waiting for you in your mail box.

  The mail notification dialog has several interesting features of its own.

  When you are notified of incoming mail with this dialog you can simply press OK and be done with it.

  You can also set it to automatically close the dialog box after a user specified interval even if you don't press OK. This is accomplished in the Notification methods section of the main settings dialog.

  When you are actually notified you can modify the behavior of this dialog on-the-fly too.

  When notified you can press OK and the dialog closes. It will notify you again at the user specified interval if you still have mail in the account.

  However, you can temporarily suspend this behavior if you are in the middle of doing something. When notified press the OK-Suspend button. This will temporarily suspend MailRun's notification for the time value (in minutes) set in the spin box in the lower right corner of the dialog box.

  The suspend time value itself can be changed on the fly. Just click into the area of the spin button that actually displays the suspend value. That will stop the autoclose feature (if it is set on) and allow you to set the Suspend value to something new.

  After setting the new value then press OK-Suspend and it will suspend checking for mail until the time interval that you just set has passed.

  The suspend feature can be thought of as something similar to a "snooze" feature on an alarm clock.

  The OK-Start preview button will close the notifation dialog and will start the MailRun Preview program.

  The OK-Start program will close the dialog and start the program (if any is specified) that is pointed to in the "Start program on notification" entry field.  


Registering MailRun 
----------------------

  MailRun was included free with NetChat and did not need to be separately registered. You were registered for it when you registered for NetChat.

  MailRun was currently not sold in any other manner and was only available with NetChat.

Since 2012 MailRun is open source software under the GNU GPL license. 



    
                                 

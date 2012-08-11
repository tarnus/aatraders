Inigo Surguy
Why did I write this?

I wrote ICron for Windows NT before Windows 2000's Scheduled Task service was available. 
At the time, the only scheduling options were using "At", which is fine for very simple tasks, 
but hopeless for doing anything like running a program every minute, and third party programs 
like WinCron, which does essentially the right thing, but doesn't run as a service so a user must 
be logged in for it to work (which makes it useless for running on a server).

ICron solves these problems by running as a Windows service, and uses the standard Unix 
crontab form so it's easy to specify when things will run down to a granularity of a minute.

How to use it

Install it as a service with:

icronservice /install /silent

While the service is installed, start it with:

net start icron /filename=<filename>

The filename is the complete path to the windowscron.txt file located in the config directory.

--------------------------------

Uninstall the service with:

icronservice /uninstall /silent

and stop it with

net stop icron

---------------------------------

If no /crontab argument is given, $WINDOWS_DIR%/crontab is used as the crontab file

The crontab is only read when the service starts - to reread it, stop and restart the service.

The syntax of the crontab file is identical to the Unix crontab; a series of lines specifying a command 
and the times to execute them at. For example:

10,12-13 4,5 * * * c:\execute.bat

will run "c:\execute.bat" at 4:10, 4:12, 4:13, 5:10, 5:12, and 5:13 every day.

The fields are minutes, hours, weekday, day of month, month, and "string to execute". * signifies all.


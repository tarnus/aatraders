unit Unit1;

{
   ICronService is Inigo's Cron, an implementation of Cron for a Windows NT system.
   It runs as an NT service called ICron.

   Install as a service by running "icronservice /install /silent", uninstall with
   "icronservice /uninstall /silent", and while it is installed, start and stop it
   with "net start icron /filename=c:|temp\crontab" and "net stop icron"

   If no filename is specified, %WINDOWS_DIR%\crontab is used as the crontab file.

   The crontab is only read when the service starts - to reread it, stop and restart
   the service.

   Syntax of the crontab file is identical to the Unix crontab.
   
   This is covered under the GNU Public License. There should be a file "license.txt"
   included in this distribution - if not, the license can be obtained from the GNU
   web pages (http://www.gnu.org/). 

   Inigo Surguy
   Copyright 2000
   First version written 27/28 May 2000
}

{
   Possible problems:
       Changing the date/time on the system will obviously not run jobs in between
       the changed times... not really anything that I can do about that, just
       be aware.

       If the system is not responding for the whole period during which a cron
       job should be triggered, then the timer might not be called until too late,
       so the job will not be run. There is no "catch-up" - it seemed too likely
       to cause problems with running jobs twice.

       A malformed cron line will cause the service not to start.

   Improvements:
       More useful exception handling... say which lines caused the errors (maybe in system log)
       Add warnings to the system log
       Add a description automatically - the registry key
           \\HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\ICron\Description
}

{
   TService1.readCronFile reads from the specified cron file on startup.
   Each non-comment line is passed to a new TCronLine object, which parses
   it using methods from StringTokenizer, and stores the numbers as a set
   inside the private variables minutes, hours, etc.
   
   These CronLines are stored in the lines array of TService. On every
   call from Timer1, formQuery is called to step through each CronLine in
   lines, and call it with the current date and time. If the CronLine's
   checkMatch method returns true, then TCronLine.execute is called, which
   calls ShellExecute to execute the specified program.
}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, SvcMgr, Dialogs,
  ExtCtrls, ShellAPI;

type
   TMinutes=0..59;
   THours=0..23;
   TWeekdays=0..6;
   TDaysOfMonth=1..31;
   TMonths=1..12;
   TStringArray=array of string;
   TByteSet=set of byte;

{
   Splits a string by separator (must be a single character), and return it as an
   array of strings, or a set of bytes
}
type
   TStringTokenizer = class(TObject)
       public
           // Calls the overloaded version with no max tokens
           class function tokenize(strInput, strSeparator : string): TStringArray; overload;
           // Splits a string into an array of strings.
           // Tokens above iMaxTokens are included as part of the last token.
           class function tokenize(strInput, strSeparator : string; iMaxTokens:integer): TStringArray; overload;
           // Expects eg "1,2-5,9,10,35-40" and returns a set from this, if strSeparator is ","
           class function tokenizeToSet(strInput, strSeparator : string): TByteSet;
           // Expects eg "23-25" and returns a set with values [ 23, 24, 25 ]
           class function rangeToSet(strInput: string) : TByteSet;
   end;

{
   Represents a line of the cron file
}
type
   TCronLine = class(TObject)
       private
           // These are set by the constructor, and checked by checkMatch
           minutes: set of TMinutes;
           hours: set of THours;
           weekdays: set of TWeekdays;
           daysofmonth: set of TDaysOfMonth;
           months : set of TMonths;
           // Set by the constructor, called by execute
           strExecutable: string;
       public
           // Expects a line in the format of unix crontab line, eg
           //          10,12-13 4,5 * * * c:\execute.bat
           // where the fields are "minutes, hours, weekday, day of month, month, string to execute"
           // So the above will call execute.bat at 4:10, 4:12, 4:13 and 5:10, 5:12, 5:13 every day
           // * signifies all times
           // Days of the week are 0 based, where 0 is Sunday
           constructor create(strLine : string);
           // Check the passed in date/time against the stored values in the above private sets
           function checkMatch(iMinute, iHour, iWeekday, iDayOfMonth, iMonth: integer) : boolean;
           // Call the string specified by strExecute
           function execute: integer;
   end;
   TCronLines=array of TCronLine;



type
   TICron = class(TService)
       Timer1: TTimer;
       procedure Timer1Timer(Sender: TObject);
       procedure ServiceStart(Sender: TService; var Started: Boolean);
   private
       lines: TCronLines;
       iLastMinute: integer;

    { Private declarations }
       procedure readCronFile;
       procedure formQuery;
       procedure sendQuery( iMin, iHour, iDayOfWeek, iDay, iMonth: integer);
       function getCronFilename: String;
   public
       function GetServiceController: TServiceController; override;
    { Public declarations }
   end;

var
  ICron: TICron;

const
   CRON_FILENAME = 'crontab';

implementation

{$R *.DFM}

{  A standard service method }
procedure ServiceController(CtrlCode: DWord); stdcall;
begin
  ICron.Controller(CtrlCode);
end;

{  A standard service method }
function TICron.GetServiceController: TServiceController;
begin
  Result := ServiceController;
end;

{ Go through the parameters, checking for /FILENAME=somefilename }

// THIS PROBABLY WON'T WORK AT THE MOMENT - PROBABLY GOT THE BOUNDS OF COPY WRONG
// ALSO - DEFAULT CRON FILE SHOULD BE STORED IN THE WINDOWS DIRECTORY
function TICron.getCronFilename: String;
var
   i:integer;
   strParam: string;
   strFilename: string;
   pcWindowsDirectory: array[0..255] of char;
   strWindowsDirectory: string;
const
   FILEPARAM='/filename=';
begin
   GetWindowsDirectory(pcWindowsDirectory, sizeof(pcWindowsDirectory));
   strWindowsDirectory:=pcWindowsDirectory;
   strFilename:=strWindowsDirectory+'\'+CRON_FILENAME;

   if (paramCount>1) then
       for i:=1 to paramCount-1 do
           begin
           strParam:=param[i];
           if (  UpperCase(copy(strParam, 0, length(FILEPARAM))) = UpperCase(FILEPARAM)) then
               strFilename:=copy(strParam, length(FILEPARAM)+1, length(strParam)-length(FILEPARAM));
           end;

   getCronFilename:=strFilename;
end;

procedure TICron.readCronFile;
var
   fileInput: TextFile;
   strLine : string;
   aLine : TCronLine;
   iLinesSoFar: integer;
   strCronFilename: string;
begin
   iLinesSoFar:=0;
   // A number plucked out of the air - should be the number of lines in the file
   // Doesn't matter too much, since it will expand anyway
   setLength(lines, 100);

   strCronFilename:=getCronFilename;

   // Read file in
   AssignFile(fileInput, strCronFilename);
   Reset(fileInput);
   while not Eof(fileInput) do
      begin
        ReadLn(fileInput, strLine);
        strLine:=Trim(strLine);
        if ((length(strLine)>0) and (strLine[1]<>';')) then      // ; signifies a comment
           begin
           aLine:=TCronLine.Create(strLine);
           lines[iLinesSoFar]:=aLine;       // Add to the array of lines
           inc(iLinesSoFar);
           // Increase array size if we're approaching the limits
           if ((High(lines)-iLinesSoFar)<5) then setLength(lines, High(lines)+100);
           end;
      end;
   CloseFile(fileInput);

   // Trim array to reasonable size
   lines:=Copy(lines, 0, iLinesSoFar);
end;

{  On startup, read the cronfile into the lines array }
procedure TICron.ServiceStart(Sender: TService; var Started: Boolean);
begin
//   LogMessage('Attempting to start ICron', EVENTLOG_INFORMATION_TYPE, 0, 6005);
// Logging messages turns out to be rather more complicated than I thought - you need
// a DLL with the text in, and add a link to it in the registry under
// HKEY_LOCAL_MACHINE/system/current control set/services/eventlog/
   readCronFile;
end;

{  Interrogate all the cronlines every minute }
procedure TICron.Timer1Timer(Sender: TObject);
begin
   formQuery;
end;

{  Called by Timer1Timer at least every minute... actually the timer is currently
   set to every 25 seconds. This is because we cannot trust the timer to be exact
   for minute values, so we get called more frequently and check whether we've
   already run before running again

   Calls sendQuery to run through each of the cronlines with the current time
}
procedure TICron.formQuery;
var
   Present: TDateTime;
   iDayOfWeek, iYear, iMonth, iDay, iHour, iMin, iSec, iMSec: Word;
begin
   // Get the date/time
   Present:= Now;
   DecodeDate(Present, iYear, iMonth, iDay);
   DecodeTime(Present, iHour, iMin, iSec, iMSec);
   // Delphi weekdays are 1 based, cron ones are 0 based
   iDayOfWeek:=DayOfWeek(Present)-1;

   // Do not run more than once per minute
   if (iMin=iLastMinute) then exit;

   iLastMinute:=iMin;
   sendQuery(iMin, iHour, iDayOfWeek, iDay, iMonth);
end;

{  Run through each of the lines, calling it if it matches }
procedure TICron.sendQuery( iMin, iHour, iDayOfWeek, iDay, iMonth: integer);
var
   i : integer;
   aCronLine: TCronLine;
begin
   for i:=0 to High(lines) do
       begin
       aCronLine:=lines[i];
       if (aCronLine.checkMatch( iMin, iHour, iDayOfWeek, iDay, iMonth)) then aCronLine.execute;
       end;
end;

// ----------------------------------------------------------------------------

{ Tokenize a string into an array of strings, no maximum number of tokens }
class function TStringTokenizer.tokenize(strInput, strSeparator : string): TStringArray;
begin
   tokenize:=TStringTokenizer.tokenize(strInput, strSeparator, -1);
end;

{ Tokenize a string into an array of strings }
class function TStringTokenizer.tokenize(strInput, strSeparator : string; iMaxTokens:integer): TStringArray;
var
   i: integer;
   strCurrentToken : string;
   saTokens: TStringArray;
   iTokensFound: integer;
begin
   // This is always about twice as large as it could possibly be - a little wasteful
   setLength(saTokens, length(strInput));
   iTokensFound:=0;

   // Go through character by character, checking for matches to strSeparator
   for i:=1 to length(strInput) do
       begin
       if ((strInput[i]=strSeparator) and not ((iMaxTokens<>-1) and (iTokensFound=iMaxTokens))) then
           begin
           saTokens[ iTokensFound ]:=strCurrentToken;
           inc(iTokensFound);
           strCurrentToken:='';
           end
       else
           strCurrentToken:=strCurrentToken+strInput[i];
       end;
   // Don't forget the last token
   saTokens[ iTokensFound ]:=strCurrentToken;
   inc(iTokensFOund);

   // Trim array down to correct size, and send it back
   tokenize:=Copy(saTokens, 0, iTokensFound);
end;


class function TStringTokenizer.tokenizeToSet(strInput, strSeparator : string): TByteSet;
var
   aStringArray: TStringArray;
   i : integer;
   setCurrent: TByteSet;
begin
   // Set to the empty set
   setCurrent:=[];

   aStringArray:=TStringTokenizer.tokenize(strInput, strSeparator);
   for i:=0 to high(aStringArray) do
           // Okay, there should be a better way of checking whether the string's valid...
           if (aStringArray[i]<>'*') then
               begin
               if (pos('-', aStringArray[i])>0) then
                   setCurrent:=setCurrent + TStringTokenizer.rangeToSet( aStringArray[i])
               else
                   setCurrent:=setCurrent + [ strToInt(aStringArray[i]) ];
               end;

   tokenizeToSet:=setCurrent;
end;

{ Convert a string of the form 1-12 to a set containing all the number in between (inclusive) }
class function TStringTokenizer.rangeToSet(strInput:string) : TByteSet;
var
   strLeft, strRight: string;
   i, iLeft, iRight, iSwap : integer;
   setCurrent: TByteSet;
begin
   setCurrent:=[ ];
   strLeft:=copy(strInput, 0, pos('-', strInput)-1);
   strRight:=copy(strInput, pos('-',strInput)+1, length(strInput)-pos(strInput, '-')-1);

   iLeft:=strToInt(strLeft);
   iRight:=strToInt(strRight);
   if (iLeft>iRight) then
       begin
       iSwap:=iLeft; iLeft:=iRight; iRight:=iSwap;
       end;

   for i:=iLeft to iRight do
       setCurrent:=setCurrent + [ i ];

   rangeToSet:=setCurrent;
end;

// ----------------------------------------------------------------------------

{ Create the cronline - expects a string of the form "1,4 5 * * something.bat" }
constructor TCronLine.create(strLine : string);
var
   aStringArray : TStringArray;
begin
   aStringArray:=TStringTokenizer.tokenize(strLine, ' ', 5);
   if (High(aStringArray)<>5) then

   else
       begin
       minutes:=TStringTokenizer.tokenizeToSet(aStringArray[0], ',');
       hours:=TStringTokenizer.tokenizeToSet(aStringArray[1], ',');
       weekdays:=TStringTokenizer.tokenizeToSet(aStringArray[2], ',');
       daysofmonth:=TStringTokenizer.tokenizeToSet(aStringArray[3], ',');
       months:=TStringTokenizer.tokenizeToSet(aStringArray[4], ',');

       strExecutable:=aStringArray[5];
       end;
end;

{ Does the CronLine object match to the conditions being passed in? }
function TCronLine.checkMatch(iMinute, iHour, iWeekday, iDayOfMonth, iMonth : integer) : boolean;
begin
   if (((minutes=[]) or (iMinute in minutes))
      and ((hours=[]) or (iHour in hours))
      and ((weekdays=[]) or (iWeekday in weekdays))
      and ((daysofmonth=[]) or (iDayOfMonth in daysofmonth))
      and ((months=[]) or (iMonth in months))) then
       checkMatch:=true
   else
       checkMatch:=false;
end;

{ Execute the Cronline's command }
function TCronLine.execute;
var
   pOut1 : array[0..1023] of char;  // No command line should be longer than 1k, surely?
   pOut2 : array[0..1023] of char;
   aStringArray : TStringArray;
begin
   aStringArray:=nil;
   // If there's a space, then pass parameters to the command, so use ShellExecute
   // Otherwise use WinExec (probably could call ShellExecute with less parameters, actually)
   if (pos(' ',strExecutable)>0) then
       begin
       aStringArray:=TStringTokenizer.tokenize(strExecutable, ' ', 1);
       execute:=ShellExecute(0, NIL, StrPCopy(pOut1, aStringArray[0]), StrPCopy( pOut2, aStringArray[1]), '', SW_SHOWNORMAL);
       end
   else
       execute:=WinExec(StrPCopy(pOut1, strExecutable), SW_SHOWNORMAL);
end;

end.

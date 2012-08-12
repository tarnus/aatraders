<?
/***************************************************************************

pseudo-cron v1.3.1
(c) 2003,2004 Kai Blankenhorn
www.bitfolge.de/pseudocron
kaib@bitfolge.de
---
revision x.x.1 added by DigiLog multimedia
for debugging and extending the version 1.3
www.digilog.de
jwagner@digilog.de
---

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA	02111-1307, USA.

****************************************************************************


Usually regular tasks like backup up the site's database are run using cron
jobs. With cron jobs, you can exactly plan when a certain command is to be 
executed. But most homepage owners can't create cron jobs on their web 
server – providers demand some extra money for that.
The only thing that's certain to happen quite regularly on a web page are 
page requests. This is where pseudo-cron comes into play: With every page 
request it checks if any cron jobs should have been run since the previous 
request. If there are, they are run and logged.

Pseudo-cron uses a syntax very much like the Unix cron's one. For an 
overview of the syntax used, see a page of the UNIXGEEKS. The syntax 
pseudo-cron uses is different from the one described on that page in 
the following points:

	-	there is no user column
	-	the executed command has to be an include()able file (which may contain further PHP code) 


All job definitions are made in a text file on the server with a 
user-definable name. A valid command line in this file is, for example:

*	2	1,15	*	*	samplejob.inc.php

This runs samplejob.inc.php at 2am on the 1st and 15th of each month.

You may also pass parameters to the included file:

*	2	1,15	*	*	samplejob.inc.php parameter1 "parameter 2 with space" parameter3

The parameters can be accessed from within the included code by means of the standard 
$argv variable that usually holds command line parameters. A possible use would be:

*	2	1,15	*	*	sendEmail.inc.php recipient@domain.com "My Subject" "My mail body /n including newline characters."

The file sendEmail.inc.php would contain just this code:

mail($argv[1], $argv[2], $argv[3]);



Features:
	-	runs any PHP script
	-	can pass parameters to called PHP script
	-	periodical or time-controlled script execution
	-	logs all executed jobs
	-	can be run from an IMG tag in an HTML page
	-	follow Unix cron syntax for crontabs


Usage:
	-	Modify the variables in the config section below to match your server.
	-	Write a PHP script that does the job you want to be run regularly. Be
		sure that any paths in it are relative to pseudo-cron.
	-	Set up your crontab file with your script
	-	put an include("pseudo-cron.inc.php"); statement somewhere in your most
		accessed page or call pseudo-cron-image.php from an HTML img tag
	-	Wait for the next scheduled run :)


Note:
You can log messages to pseudo-cron's log file from cron jobs by calling
		logMessage("log a message");
		
		

Release notes for v1.2.2:

This release changed the way cron jobs are called. The file paths you specify in
the crontab file are now relative to the location of pseudo-cron.inc.php, instead
of to the calling script. Example: If /include/pseudo-cron.inc.php is included
in /index.php and your cronjobs are in /include/cronjobs, then your crontab file
looked like this:

10	1	*	*	*	include/cronjobs/dosomething.php	# do something

Now you have to change it to

10	1	*	*	*	cronjobs/dosomething.php	# do something

After you install the new version, each of your cronjobs will be run once,
and the .job files will have different names than before.



Changelog:

v1.3.2	07-07-06
	added:	Flag to execute job using url. (Mark Dickenson)
	moved: 	markLastRun($job, $lastScheduled); in runJob
			function to execute BEFORE the cron is executed.
			This prevents multiple executions of the cron task
			on an active site.


v1.3.1	09-21-05
	added:	parameter passing to included php code.
	fixed:	cron parsing was defective (e.g. with	0 0 1 10 *	code did not terminate).
			 cron parser was completely replaced by a class from http://www.phpclasses.org
			 (http://www.phpclasses.org/browse/package/2568.html)
	fixed:	cron jobs were always executed (even if no schedule was due)
	fixed:	code cleaned to avoid php throwing notices
			 

v1.3	06-15-04
	added:	the number of jobs run during one call of pseudocron
	 can now be limited.
	added:	additional script to call pseudocron from an HTML img tag
	improved storage of job run times
	fixed a bug with jobs marked as run although they did not complete


v1.2.2	01-17-04
	added:	send an email for each completed job
	improved:	easier cron job configuration (relative to pseudo-cron, not
	 to calling script. Please read the release notes on this)


v1.2.1	02-03-03
	fixed:	jobs may be run too often under certain conditions
	added:	global debug switch
	changed: typo in imagecron.php which prevented it from working


v1.2	01-31-03
	added:	more documentation
	changed: log file should now be easier to use
	changed: log file name


v1.1	01-29-03
	changed: renamed pseudo-cron.php to pseudo-cron.inc.php
	fixed:	comments at the end of a line don't work
	fixed:	empty lines in crontab file create nonsense jobs
	changed: log file grows big very quickly
	changed: included config file in main file to avoid directory confusion
	added:	day of week abbreviations may now be used (three letters, english)


v1.0	01-17-03
	inital release

***************************************************************************/


/****************************************/
/*	 config section			 */
/****************************************/

// || PLEASE NOTE:
// || all paths used here and in cron scripts 
// || must be absolute or relative to pseudo-cron.inc.php!
// ||
// || To easily use absolute paths, have a look at how the
// || crontab location is defined below.


// The file that contains the job descriptions.
// For a description of the format, see http://www.unixgeeks.org/security/newbie/unix/cron-1.html
// and http://www.bitfolge.de/pseudocron
$cronTab = dirname(__FILE__)."/cronjobs/crontab.txt";

// The directory where the script can store information on completed jobs and its log file.
// include trailing slash
$writeDir = dirname(__FILE__)."/cronjobs/";

// Control logging, true=use log file, false=don't use log file
$useLog = false ;

// Where to send cron results.
// $sendLogToEmail = "youraddess@mail.domain";
// Set empty ("") to send no emails.
$sendLogToEmail = "";
// Maximum number of jobs run during one call of pseudocron.
// Set to a low value if your jobs take longer than a few seconds and if you scheduled them
// very close to each other. Set to 0 to run any number of jobs.
$maxJobs = 0;

// Turn on / off debugging output
// DO NOT use this on live servers!
$debug = false;

// Turn on / off the ability to call a job though a url
$call_url_job = true;

/****************************************/
/*	 don't change anything here	 */
/****************************************/

include("CronParser.php");

define("PC_MINUTE",	1);
define("PC_HOUR",	2);
define("PC_DOM",	3);
define("PC_MONTH",	4);
define("PC_DOW",	5);
define("PC_CMD",	7);
define("PC_COMMENT",	8);
define("PC_ARGS", 19);
define("PC_CRONLINE", 20);

$resultsSummary = "";

function logMessage($msg) {
	GLOBAL $writeDir, $useLog, $debug, $resultsSummary;
	if ($msg[strlen($msg)-1]!="\n") {
		$msg.="\n";
	}
	if ($debug) echo $msg;

	$resultsSummary.= $msg;
	if ($useLog) {
		$logfile = $writeDir."pseudo-cron.log";
		$file = fopen($logfile,"a");
		fputs($file,date("r",time())."	".$msg);
		fclose($file);
	}
}

function lTrimZeros($number) {
	GLOBAL $debug;
	while ($number[0]=='0') {
		$number = substr($number,1);
	}
	return $number;
}

function multisort(&$array, $sortby, $order='asc') {
	foreach($array as $val) {
		$sortarray[] = $val[$sortby];
	}
	$c = $array;
	$const = $order == 'asc' ? SORT_ASC : SORT_DESC;
	$s = array_multisort($sortarray, $const, $c, $const);
	$array = $c;
	return $s;
}

function getLastScheduledRunTime($job) {
	GLOBAL $debug;

	$cron_string = $job[PC_MINUTE].' '.$job[PC_HOUR].' '.$job[PC_DOM].' '.$job[PC_MONTH].' '.$job[PC_DOW];

	//Constructor
	$cronPars = new CronParser();

	//Feed the cron string
	$cronPars->calcLastRan($cron_string);

	if ($debug) print_r($cronPars->getLastRan());	//Print Date Array

	//Return timestamp of last scheduled run time
	return $cronPars->getLastRanUnix();

}

function getJobFileName($job) {
	GLOBAL $writeDir;
	GLOBAL $debug;
	$jobArgHash = ( count($job[PC_ARGS])>1 ? '_'.md5(implode('', $job[PC_ARGS])) : '' );
	$jobfile = $writeDir.urlencode($job[PC_CMD]).$jobArgHash.".job";
	return $jobfile;
}

function getLastActualRunTime($job) {
	GLOBAL $debug;
	$jobfile = getJobFileName($job);
	if (file_exists($jobfile)) {
		return filemtime($jobfile);
	}
	return 0;
}

function markLastRun($job, $lastRun) {
	$jobfile = getJobFileName($job);
	touch($jobfile);
}

function runJob($job)
{
	GLOBAL $debug, $sendLogToEmail, $resultsSummary, $call_url_job;
	$resultsSummary = "";

	$lastActual = $job["lastActual"];
	$lastScheduled = $job["lastScheduled"];

	if ($lastScheduled>$lastActual)
	{
		logMessage("Running	".$job[PC_CRONLINE]);
		logMessage("	Last run:		 ".date("r",$lastActual));
		logMessage("	Last scheduled: ".date("r",$lastScheduled));
		logMessage("	Time Difference: " . round(($lastScheduled - $lastActual) / 60 / 5));
		markLastRun($job, $lastScheduled);
		$argv = $job[PC_ARGS];
		if ($debug)
		{
			$e = @error_reporting(0);
			if($call_url_job)
			{
				if(@ini_get("allow_url_fopen") == 1)
				{
					logMessage($job[PC_CMD] . "&scheduler_passes=" . round(($lastScheduled - $lastActual) / 60 / 5));
					$fp = @fopen ($job[PC_CMD] . "&scheduler_passes=" . round(($lastScheduled - $lastActual) / 60 / 5),"r");
					if($fp)
					{
						while(!@feof($fp)){
							$getreturn = trim(@fgets($fp)) . "<br>\n";
							echo($getreturn);
						}
						fclose ($fp);
					}
				}
				else
				if(function_exists('curl_init'))
				{
					$ch=curl_init();
					logMessage($job[PC_CMD] . "&scheduler_passes=" . round(($lastScheduled - $lastActual) / 60 / 5));
					curl_setopt($ch, CURLOPT_URL, $job[PC_CMD] . "&scheduler_passes=" . round(($lastScheduled - $lastActual) / 60 / 5));
					curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
					$var = curl_exec ($ch);
					curl_close ($ch);
					echo(trim($var) . "<br>\n");
				}
			}
			else
			{
				include($job[PC_CMD]);	 // display errors only when debugging
			}
			@error_reporting($e);
		} else {
			$e = @error_reporting(0);
			if($call_url_job)
			{
				if(@ini_get("allow_url_fopen") == 1)
				{
					$fp = @fopen ($job[PC_CMD] . "&scheduler_passes=" . round(($lastScheduled - $lastActual) / 60 / 5),"r");
					if($fp)
					{
						while(!@feof($fp)){
							@fgets($fp);
						}
						fclose ($fp);
					}
				}
				else
				if(function_exists('curl_init'))
				{
					$ch=curl_init();
					curl_setopt($ch, CURLOPT_URL, $job[PC_CMD] . "&scheduler_passes=" . round(($lastScheduled - $lastActual) / 60 / 5));
					curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
					$var = curl_exec ($ch);
					curl_close ($ch);
				}
			}
			else
			{
				@include($job[PC_CMD]);	 // any error messages are supressed
			}
			@error_reporting($e);
		}

		logMessage("Completed	".$job[PC_CRONLINE]);
		if ($sendLogToEmail!="")
		{
			mail($sendLogToEmail, "[cron] ".$job[PC_COMMENT], $resultsSummary);
		}
		return true;
	} else {
		if ($debug) {
			logMessage("Skipping	".$job[PC_CRONLINE]);
			logMessage("	Last run:		 ".date("r",$lastActual));
			logMessage("	Last scheduled: ".date("r",$lastScheduled));
			logMessage("	Time Difference: " . round(($lastScheduled - $lastActual) / 60 / 5));
			logMessage("Completed	".$job[PC_CRONLINE]);
		}
		return false;
	}
}

function parseCronFile($cronTabFile) {
	GLOBAL $debug;
	$file = file($cronTabFile);
	$job = Array();
	$jobs = Array();
	for ($i=0;$i<count($file);$i++) {
		if ($file[$i][0]!='#') {
			if (preg_match("~^([-0-9,/*]+)\\s+([-0-9,/*]+)\\s+([-0-9,/*]+)\\s+([-0-9,/*]+)\\s+([-0-7,/*]+|(-|/|Sun|Mon|Tue|Wed|Thu|Fri|Sat)+)\\s+([^#]*)\\s*(#.*)?$~i",$file[$i],$job)) {
				$jobNumber = count($jobs);
				if(!array_key_exists(PC_COMMENT, $job))	$job[PC_COMMENT]='';
				$jobs[$jobNumber] = $job;
				if ($jobs[$jobNumber][PC_DOW][0]!='*' AND !is_numeric($jobs[$jobNumber][PC_DOW])) {
					$jobs[$jobNumber][PC_DOW] = str_replace(
						Array("Sun","Mon","Tue","Wed","Thu","Fri","Sat"),
						Array(0,1,2,3,4,5,6),
					$jobs[$jobNumber][PC_DOW]);
				}
				$jobs[$jobNumber][PC_CMD] = trim($job[PC_CMD]);
				$jobs[$jobNumber][PC_ARGS] = Array();
				if (preg_match_all('~(("([^"]*)")|(\S+))\s*~i', $jobs[$jobNumber][PC_CMD], $jobArgs, PREG_PATTERN_ORDER)) {
					for($ii=0; $ii<count($jobArgs[1]); $ii++){
						$jobArg = ($jobArgs[3][$ii]==='' ? $jobArgs[1][$ii] : $jobArgs[3][$ii]);
						if($ii==0)	$jobs[$jobNumber][PC_CMD] = $jobArg;
						$jobs[$jobNumber][PC_ARGS][$ii] = str_replace(Array('\r','\n'), Array("\r","\n"), $jobArg);
					}
				}
				$jobs[$jobNumber][PC_COMMENT] = trim(substr($job[PC_COMMENT],1));
				$jobs[$jobNumber][PC_CRONLINE] = $file[$i];
			}
			$jobs[$jobNumber]["lastActual"] = getLastActualRunTime($jobs[$jobNumber]);
			$jobs[$jobNumber]["lastScheduled"] = getLastScheduledRunTime($jobs[$jobNumber]);
		}
	}
	multisort($jobs, "lastScheduled");
	if ($debug) var_dump($jobs);
	return $jobs;
}

if ($debug) echo "<pre>";

$jobs = parseCronFile($cronTab);
$jobsRun = 0;
for ($i=0;$i<count($jobs);$i++) {
	if ($maxJobs==0 || $jobsRun<$maxJobs) {
		if (runJob($jobs[$i])) {
			$jobsRun++;
		}
	}
}
if ($debug) echo "</pre>";
?>
{literal}<SCRIPT LANGUAGE="JavaScript">
<!--
// JavaScript Source File -- Created with NetObjects ScriptBuilder
// Category:    Date and Time
// AUTHOR:      Maxim V. Kollegov, All Rights Reserved.
//              http://www.geocities.com/SiliconValley/Lakes/8620
//              Modified with permission by Joe Hage - Team ScriptBuilder
//              Feel free to reuse this code provided you include this
//              AUTHOR section in your pages.
// DESC:        Display a ticking countdown clock on your web page.
// Sample HTML: COUNTDOWN.HTML
// PLATFORMS:   Netscape Navigator 3.0 and higher,
//			    Microsoft Internet Explorer 3.02 and higher
// ======================================================================
//change your event date event here.
var eventdate = new Date("June 26, 2004 22:00:00 CST");

function toSt(n) {
  s=""
  if(n<10) s+="0"
  return s+n.toString();
}
 
function countdown() {
  cl=document.clock;
  d=new Date();
  count=Math.floor((eventdate.getTime()-d.getTime())/1000);
  if(count<=0)
    {cl.days.value ="----";
     cl.hours.value="--";
     cl.mins.value="--";
     cl.secs.value="--";
     return;
   }
  cl.secs.value=toSt(count%60);
  count=Math.floor(count/60);
  cl.mins.value=toSt(count%60);
  count=Math.floor(count/60);
  cl.hours.value=toSt(count%24);
  count=Math.floor(count/24);
  cl.days.value=count;    
  
  setTimeout("countdown()",500);
}
// end hiding script-->

</SCRIPT>{/literal}
<div align="center">
<FORM name="clock">
<table style="border: thin solid #3FA9FC;" cellpadding="0" cellspacing="0"><tr bgcolor="#000000" align="center"><td>
<TABLE BORDER=0 CELLSPACING=5 CELLPADDING=0 BGCOLOR="#000000">
<TR>
<TD ALIGN=CENTER WIDTH="31%" BGCOLOR="#000080"><FONT COLOR="#FFFFFF" face="verdana,arial,helvetica"><B>Days:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH="23%" BGCOLOR="#000080"><FONT COLOR="#FFFFFF" face="verdana,arial,helvetica"><B>Hours:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH="23%" BGCOLOR="#000080"><FONT COLOR="#FFFFFF" face="verdana,arial,helvetica"><B>Mins:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH="23%" BGCOLOR="#000080"><FONT COLOR="#FFFFFF"><B>Secs:</B></FONT></TD>
</TR>
<TR>
<TD ALIGN=CENTER><INPUT name="days" size=4></TD>
<TD ALIGN=CENTER><INPUT name="hours" size=2></TD>
<TD ALIGN=CENTER><INPUT name="mins" size=2></TD>
<TD ALIGN=CENTER><INPUT name="secs" size=2></TD>
</TR>
<TR>
<TD COLSPAN="4" BGCOLOR="#000080">
<CENTER><P><FONT face="verdana,arial,helvetica" SIZE="+2" COLOR="#FFFF00">2-Person Team Tourney Start</FONT></CENTER>
</TD>
</TR>
<TR>
<TD COLSPAN="4" BGCOLOR="#000000">
<CENTER><P><FONT COLOR="#00FF00" SIZE=+1 face="verdana,arial,helvetica">
{literal}
<SCRIPT LANGUAGE="JavaScript">
<!--
document.write(" "+eventdate.toLocaleString()+" ");
countdown();
// end hiding script-->
</SCRIPT>
{/literal}
</FONT>
</CENTER>
</TD>
</TR>
</TABLE></td></tr></table>
</FORM></div>
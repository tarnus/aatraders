<body onload="self.focus();" bgcolor="#000000" text="darkred" marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 link="#52ACEA" vlink="#52ACEA" alink="#52ACEA">
{literal}
<script language="JavaScript">
<!--
function checkform ( form )
{
  // ** START **
  if (form.email.value == "") {
    alert( "{/literal}{$l_contact_admin_email_alert}{literal}" );
    form.email.focus();
    return false ;
  }

  if (form.contact_name.value == "") {
    alert( "{/literal}{$l_contact_admin_name_alert}{literal}" );
    form.contact_name.focus();
    return false ;
  }

  if (form.comments.value == "") {
    alert( "{/literal}{$l_contact_admin_comment_alert}{literal}" );
    form.comments.focus();
    return false ;
  }

  // ** END **
	form.submit();
}

// -->
</script>
{/literal}

<table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
<tr>
	<td align="center">
{literal}
<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="650" height="300" id="3D Solar System" align="middle">
<param name="allowScriptAccess" value="sameDomain" />
<param name="movie" value="templates/{/literal}{$templatename}{literal}images/aat-title.swf" />
<param name="quality" value="high" />
<param name="bgcolor" value="#000000" />
<embed src="templates/{/literal}{$templatename}{literal}images/aat-title.swf" quality="high" bgcolor="#000000" width="650" height="300" name="3D Solar System" align="middle" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />
</object>
{/literal}
	</td>
</tr>

		</table>
<div align="center">
  <table width="90%" border="0" cellspacing="0" cellpadding="0">
  <tr>
		<td width="9"><img src = "templates/{$templatename}images/spacer.gif" alt="" width="9" height="20" /></td>
    	<td width="100%" align="left" valign="top">
 <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>

          <td colspan="2"><img src = "templates/{$templatename}images/spacer.gif" alt="" width="100%" height="7"></td>
          </tr>
        <tr>
          <td colspan="2" height="23">&nbsp;</td>
        </tr>
        <tr>
          <td colspan="2"><img src = "templates/{$templatename}images/spacer.gif" alt="" width="100%" height="5"></td>
          </tr>

		  
        <tr>
          <td colspan="2"><img src = "templates/{$templatename}images/newstabm.gif" alt="" width="100%" height="5"></td>
        </tr>
        <tr>
          <td colspan="2">
		  <table width="100%" border="0" cellpadding="0" cellspacing="1" class="newsborder">
            <tr>
              <td align="left" valign="top" class="news">
			  <table width="100%" border="0" cellspacing="0" cellpadding="2">
                <tr>
                  <td colspan="2"><div class="hr"><hr /></div>
						<table align="center" border="0" cellpadding="4" cellspacing="0">
							<FORM onSubmit="return checkform(contactus)" ACTION="contact_admin_thanks.php" METHOD="POST" enctype="multipart/form-data" name="contactus" id="contactus">
							<tr>
	                            <td valign="top" align="center" colspan="2"><img src="templates/{$templatename}images/spacer.gif" width="300" height="1"></td>
							</tr>
							<TR align="center">
	                        	<TD VALIGN=TOP align="right"><FONT FACE="Arial,Helvetica" class="artSHead"><B>{$l_contact_admin_name} </B></font></TD>
    	                        <TD align="left"><INPUT NAME="contact_name" VALUE="" SIZE=30 MAXLENGTH=50><font color="red">*</font></TD>
		                    </TR>
                            <TR align="center">
	                            <TD VALIGN=TOP align="right"><FONT FACE="Arial,Helvetica" class="artSHead"><B>{$l_contact_admin_email} </B></font></TD>
    	                        <TD align="left"><INPUT NAME="email" VALUE="" SIZE=30 MAXLENGTH=50 ><font color="red">*</font></TD>
        		            </TR>
							<TR>
							    <TD COLSPAN=2 align="center"><img src="templates/{$templatename}images/spacer.gif" width="5" height="5"></TD>
							</TR>	
							<TR>
							    <TD COLSPAN=2 align="center"><FONT FACE="Arial,Helvetica" class="artSHead"><B>{$l_contact_admin_comment}:</B></font><BR></TD>
							</TR>		
							<TR>
	                            <TD COLSPAN=2 align="center"><TEXTAREA NAME="comments" ROWS="8" COLS="50" WRAP="virtual"></TEXTAREA></TD>
		                    </TR>	
							<TR>
							    <TD COLSPAN=2 align="center"><img src="templates/{$templatename}images/spacer.gif" width="5" height="10"></TD>
							</TR>	
							<TR>
							    <TD COLSPAN=2 align="center"><INPUT TYPE="submit" NAME="newclassifieduserbutton" VALUE="{$l_contact_admin_submit}"><BR></TD>
							</TR>													
							</FORM>
							<tr>
								<td colspan="2" align="center"><a href="javascript:window.close();">{$l_contact_admin_close}</a></td>
							</tr>
						</table>
                      <div class="hr"><hr /></div>
					  
				  </td>
                </tr>
              </table>
			  </td>
            </tr>
          </table>
		  </td>
          </tr>
        <tr>
          <td colspan="2"><img src = "templates/{$templatename}images/spacer.gif" alt="" width="100%" height="15"></td>

        </tr>

	  
      </table>
</td>
 </tr>
 </table>




{literal}
<style type="text/css">
<!--
body {
	font-family: Verdana, Arial, Helvetica, sans-serif;
	font-size: 10px;
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/bgmain.gif');
	margin: 0px;
}
td {
	font-size: 10px;
}

.bgmain {
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/main_bg2.gif');
	background-repeat: repeat-x;
	height: 287px;
}
.loginbg {
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/header_01.gif');
	background-repeat: no-repeat;
	height: 40px;
	width: 368px;
}

.crbg {
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/crbg.gif');
	height: 22px;
	padding-top: 2px;
	padding-bottom: 2px;
	font-weight: bold;
	color: #FFFFFF;
}
 
.mcbg {
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/mcbg.gif');
	background-repeat: repeat-y;
	width: 779px;
	padding: 0px;
}

.mcheader {
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/mc_header.gif');
	background-repeat: no-repeat;
	height: 21px;
	width: 100%;
	text-indent: 20px;
	color: #FFFFFF;
	font-weight: bold;
}

.maincbbg {
	background-image: url('templates/{/literal}{$templatename}{literal}images_fnn/mcb_bg.gif');
	background-repeat: repeat-y;
	width: 368px;
}

-->
</style>
{/literal}
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td valign="top" class="bgmain"><table width="780" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td valign="top"><table width="780" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td colspan="3" rowspan="2" class="loginbg"><img src="templates/{$templatename}images_fnn/spacer.gif" alt="spacer" height="15"/><center>
            {$l_news_bestviewed}</center></td>
            <td colspan="4" width="412">{$gotomain}</td>
            <td><img src="templates/{$templatename}images_fnn/spacer.gif" width="1" height="25" alt="1" /></td>
          </tr>
          <tr>
            <td colspan="4" rowspan="2" valign="top" width="412">{$l_news_info}</td>
            <td><img src="templates/{$templatename}images_fnn/spacer.gif" width="1" height="15" alt="1" /></td>
          </tr>
          <tr>
            <td colspan="3"><img src="templates/{$templatename}images_fnn/top_logo.gif" alt="logo" width="368" height="83" border="0" /></td>
            <td><img src="templates/{$templatename}images_fnn/spacer.gif" width="1" height="83" alt="1" /></td>
          </tr>
          <tr>
            <td colspan="6"><img src="templates/{$templatename}images_fnn/spacer.gif" width="1" height="41" alt="1" /></td>
          </tr>
          	<tr>
		<td colspan="7" valign="top" class="mcbg">
			<img src="templates/{$templatename}images_fnn/header_11.gif" width="779" height="24" alt="header" />
			<table width="100%" border="0" cellspacing="8" cellpadding="0">
<tr>
	<td colspan="2" class="crbg" align="center" style="font-size: 14px;">
<a href="news.php?startdate={$previousday}">{$l_news_prev|ucfirst}</a><img src="templates/{$templatename}images_fnn/spacer.gif" width="160" height="1" alt="1" />{$l_news_for} {$today}<img src="templates/{$templatename}images_fnn/spacer.gif" width="160" height="1" alt="1" /><a href="news.php?startdate={$nextday}">{$l_news_next|ucfirst}</a>
</td>
</tr>

              <tr>
                <td width="100%" valign="top"><div align="center">
                  <table border="0" align="center" cellpadding="0" cellspacing="0">
                      <tr>
                        <td class="mcheader">{$l_news_fedannouncements}</td>
                      </tr>
                      <tr>
                        <td class="maincbbg"><table width="97%" border="0" align="center" cellpadding="0" cellspacing="0">
                            <tr>
                              <td>

			<div style="position:relative;width:100%;height:300px;overflow:auto">
			<div id="iescroller" style="position:absolute;left:0px;top:0px;width:100%;">
<div align="center"><table width=\"335\">{php}
	$emptycheck = 0;
	for($i = 0; $i < $newscount; $i++){
		if($newstype[$i] == "general" || $newstype[$i] == "bounty" || $newstype[$i] == "promoted" || $newstype[$i] == "demoted")
		{
			$emptycheck = 1;
			if($newstype[$i] == "general")
			{
				$bgcolor = "#494949";
			}
			else if($newstype[$i] == "bounty")
			{
				$bgcolor = "#0c4274";
			}
			else if($newstype[$i] == "promoted")
			{
				$bgcolor = "#228B22";
			}
			else if($newstype[$i] == "demoted")
			{
				$bgcolor = "#8B0000";
			}
			else
			{
				$bgcolor = "#000033";
			}
		echo"<tr>";
		echo"<td bgcolor=\"$bgcolor\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $newsdate[$i] . "</b></div><br>" . $newstext[$i] ."<br><hr></td>";
		echo"</tr>";
		}
	}
	if(	$emptycheck == 0)
	{
		echo"<tr>";
		echo"<td bgcolor=\"#494949\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $dummynewsdate . "</b></div><br>" . $dummynewstext ."<br><hr></td>";
		echo"</tr>";
	}
{/php}</table></div>

			</div></div>

                              </td>
                            </tr>
                        </table></td>
                      </tr>
                      <tr>
                        <td><img src="templates/{$templatename}images_fnn/mcb_footer.gif" alt="footer" width="368" height="10" /></td>
                      </tr>
                          </table>
                  <table border="0" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                          <td class="mcheader">{$l_news_planetarynews}</td>
                        </tr>
                        <tr>
                          <td class="maincbbg"><table width="97%" border="0" align="center" cellpadding="0" cellspacing="0">
                              <tr>
                                <td>
<div style="position:relative;width:100%;height:300px;overflow:auto">
			<div id="iescroller1" style="position:absolute;left:0px;top:0px;width:100%;">
<div align="center"><table width=\"335\">{php}
	$emptycheck = 0;
	for($i = 0; $i < $newscount; $i++){
		if($newstype[$i] == "indi" || $newstype[$i] == "planet" || $newstype[$i] == "colonist" || $newstype[$i] == "found_planets" || $newstype[$i] == "new_ports" || $newstype[$i] == "addedsectors")
		{
			$emptycheck = 1;
			if($newstype[$i] == "indi")
			{
				$bgcolor = "#7B68EE";
			}
			else if($newstype[$i] == "planet")
			{
				$bgcolor = "#74470c";
			}
			else if($newstype[$i] == "colonist")
			{
				$bgcolor = "#4169A1";
			}
			else
			{
				$bgcolor = "#000033";
			}
		echo"<tr>";
		echo"<td bgcolor=\"$bgcolor\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $newsdate[$i] . "</b></div><br>" . $newstext[$i] ."<br><hr></td>";
		echo"</tr>";
		}
	}
	if(	$emptycheck == 0)
	{
		echo"<tr>";
		echo"<td bgcolor=\"#7B68EE\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $dummynewsdate . "</b></div><br>" . $dummynewstext ."<br><hr></td>";
		echo"</tr>";
	}
{/php}</table></div>

			</div></div>
                                </td>
                              </tr>
                          </table></td>
                        </tr>
                        <tr>
                          <td><img src="templates/{$templatename}images_fnn/mcb_footer.gif" alt="footer" width="368" height="10" /></td>
                        </tr>
                          </table>
                </div></td>
<td width="100%" valign="top"><div align="center">
                  <table border="0" align="center" cellpadding="0" cellspacing="0">
                      <tr>
                        <td class="mcheader">{$l_news_afteractionnews}</td>
                      </tr>
                      <tr>
                        <td class="maincbbg"><table width="97%" border="0" align="center" cellpadding="0" cellspacing="0">
                            <tr>
                              <td>
<div style="position:relative;width:100%;height:300px;overflow:auto">
			<div id="iescroller2" style="position:absolute;left:0px;top:0px;width:100%;">
<div align="center"><table width=\"335\">{php}
	$emptycheck = 0;
	for($i = 0; $i < $newscount; $i++){
		if($newstype[$i] == "killed" || $newstype[$i] == "killedpod" || $newstype[$i] == "suicide")
		{
			$emptycheck = 1;
			if($newstype[$i] == "killed")
			{
				$bgcolor = "#800000";
			}
			else if($newstype[$i] == "killedpod")
			{
				$bgcolor = "#006400";
			}
			else if($newstype[$i] == "suicide")
			{
				$bgcolor = "#FF1493";
			}
			else
			{
				$bgcolor = "#000033";
			}
		echo"<tr>";
		echo"<td bgcolor=\"$bgcolor\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $newsdate[$i] . "</b></div><br>" . $newstext[$i] ."<br><hr></td>";
		echo"</tr>";
		}
	}
	if(	$emptycheck == 0)
	{
		echo"<tr>";
		echo"<td bgcolor=\"#006400\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $dummynewsdate . "</b></div><br>" . $dummynewstext ."<br><hr></td>";
		echo"</tr>";
	}
{/php}</table></div>

			</div></div>
                              </td>
                            </tr>
                        </table></td>
                      </tr>
                      <tr>
                        <td><img src="templates/{$templatename}images_fnn/mcb_footer.gif" alt="footer" width="368" height="10" /></td>
                      </tr>
                          </table>
                  <table border="0" align="center" cellpadding="0" cellspacing="0">
                        <tr>
                          <td class="mcheader">{$l_news_planetshipnews}</td>
                        </tr>
                        <tr>
                          <td class="maincbbg"><table width="97%" border="0" align="center" cellpadding="0" cellspacing="0">
                              <tr>
                                <td>
<div style="position:relative;width:100%;height:300px;overflow:auto">
			<div id="iescroller3" style="position:absolute;left:0px;top:0px;width:100%;">
<div align="center"><table width=\"335\">{php}
	$emptycheck = 0;
	for($i = 0; $i < $newscount; $i++){
		if($newstype[$i] == "planetattack" || $newstype[$i] == "shipattack")
		{
			$emptycheck = 1;
			if($newstype[$i] == "planetattack")
			{
				$bgcolor = "#606000";
			}
			else
			{
				$bgcolor = "#000033";
			}
		echo"<tr>";
		echo"<td bgcolor=\"$bgcolor\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $newsdate[$i] . "</b></div><br>" . $newstext[$i] ."<br><hr></td>";
		echo"</tr>";
		}
	}
	if(	$emptycheck == 0)
	{
		echo"<tr>";
		echo"<td bgcolor=\"#000033\" style=\"filter:alpha(opacity=85);opacity:.85;\"><div align=\"center\" style=\"color:white;\"><b>" . $dummynewsdate . "</b></div><br>" . $dummynewstext ."<br><hr></td>";
		echo"</tr>";
	}
{/php}</table></div>
			</div></div>
                                </td>
                              </tr>
                          </table></td>
                        </tr>
                        <tr>
                          <td><img src="templates/{$templatename}images_fnn/mcb_footer.gif" alt="footer" width="368" height="10" /></td>
                        </tr>
                          </table>
                </div></td>
              </tr>
            </table>			  
			<table width="775" border="0" align="center" cellpadding="0" cellspacing="0">
              <tr>
                <td class="crbg" align="center">{$gotomain}</td>
              </tr>
            </table>
			</td>
		<td>
			<img src="templates/{$templatename}images_fnn/spacer.gif" width="1" height="24" alt="" /></td>
	</tr>
	<tr>
		<td>
			<img colspan="8" src="templates/{$templatename}images_fnn/spacer.gif" width="131" height="1" alt="" /></td>
	</tr>
</table>          </td>
      </tr>
      
    </table></td>
  </tr>
</table>



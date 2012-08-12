<?php
// Step 20 - Select Configuration to edit or create new game configuration
?>
	<table width="667" border="0" cellspacing="0" cellpadding="0" align="center">
	  <tr>
	      <td>
	        <table bgcolor="#000000" width="80%" border="1" cellspacing="0" cellpadding="0" align="center">
	          <tr>
	            <td>
	              <div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Create New Game / Edit Existing Game</font></b></div>
	            </td>
	          </tr>
	          <tr>
	            <td>
	              <table width="100%" border="1" cellspacing="0" cellpadding="3">
					<tr><td align="center">
					Selection: <select name="game_number">
<?php
	$totalgames = 0;
	$filelist = get_dirlist($gameroot."config/");
	$newcommands = 0;
	sort($filelist);
	for ($c=0; $c<count($filelist); $c++) { 
		if(strstr($filelist[$c], "config_local")){
			$gamenumber =  str_replace("config_local", "", str_replace(".php", "", $filelist[$c])); 
			$fs = fopen($gameroot."config/".$filelist[$c], "r");
			$items = fgets($fs);
			$items = fgets($fs);
			$gamename = AAT_substr(trim($items), 3);
			fclose($fs);
?>
			<option value="<?=$gamenumber;?>" <?php
			?>>Edit: <?=$gamename;?></option>
<?php
			$totalgames++;
		}
	}?>
					<option value="<?=$totalgames;?>">Create New Game</option>
					</select><br><br>
		<input type="hidden" name="step" value="20">
          <input type="submit" value="Submit">
			      </td>
			    </tr>
			</table>
		</td>
	</tr>
</table>
		</td>
	</tr>
</table>

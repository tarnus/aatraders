<?php
// 5: Full Database Backup
// This tool will create a complete backup of the current games database for archival purposes.

get_post_ifset("extended");

function enc($data) 
{
	$encdata = mcrypt_ecb (MCRYPT_TripleDES,(Keysize), $data, MCRYPT_ENCRYPT, $iv); 
	$hextext=bin2hex($encdata); 
	return $hextext; 
}

function hex2bin($data) 
{
	$len = AAT_strlen($data); 
	return pack("H" . $len, $data); 
}

class encrypt
{
	var $intArray = array(); 
	var $byteArray = array(); 
	var $int1 = 0; 
	var $int2 = 0; 
	var $key = null; 
	var $keylen = 0; 

	function encrypt( $key )
	{
		$this->setKey( $key ); 
	}

	function setKey( $key )
	{
		$this->key = null; 
		$key = md5( (string)$key ); 
		for( $idx = 0; $idx < 32; $idx += 4 )
		{
			$this->key .= md5( AAT_substr( $key, $idx, 4 ) ); 
		} 
		$this->keylen = AAT_strlen( $this->key ); 
		$bytes = $this->keylen / 2; 
		$bits = $bytes * 8; 
		return( $this->key ); 
	} 

	function init()
	{
		// Save the key in a Byte Array 
		$this->intArray = array(); 
		$this->byteArray = array(); 
		$this->int1 = 0; 
		$this->int2 = 0; 
		if( ( AAT_strlen( $this->key ) % 2 ) > 0 )
		{
			// if the key is not an even number of characters, lose the last one 
			// this is supposed to be a string of bytes (hex pairs) 
			$this->key .= AAT_substr( $this->key, 0, -1 ); 
		} 
		$this->keylen = AAT_strlen( $this->key ); 

		for( $idx = 0, $idx2 = 0; $idx < 128; $idx++, $idx2+=2 )
		{
			if( $idx2 >= $this->keylen )
			{
				$idx2 = 0; 
			}
			$this->byteArray[$idx] = hexdec( AAT_substr( $this->key, $idx2, 2 ) ); 
			$this->intArray[$idx] = $idx; 
		}
		for( $idx = 0; $idx < 128; $idx++ )
		{
			$idx2 = ( $idx2 + $this->intArray[$idx] + $this->byteArray[$idx] ) % 128; 
			$temp = $this->intArray[$idx]; 
			$this->intArray[$idx] = $this->intArray[$idx2]; 
			$this->intArray[$idx2] = $temp; 
		} 
	} 

	function cipher_byte( $byte )
	{
		if( !is_int( $byte ))
		{
			$byte = ord( $byte ); 
		} 
		$this->int1 = ( $this->int1 + 1 ) % 128; 
		$this->int2 = ( $this->int2 + $this->intArray[$this->int1] ) % 128; 

		$temp = $this->intArray[$this->int1]; 
		$this->intArray[$this->int1] = $this->intArray[$this->int2]; 
		$this->intArray[$this->int2] = $temp; 
		$intX = $this->intArray[($this->intArray[$this->int1] + $this->intArray[$this->int2]) % 128]; 
		return( $byte ^ $intX + 128); 
	} 

	function cipher_string( $string )
	{
		$this->init(); 
		for( $idx = 0, $len = AAT_strlen( $string ); $idx < $len; $idx++ )
		{
			$cipher .= chr( $this->cipher_byte( ord( $string{$idx} ) ) ); 
		} 
		return( $cipher ); 
	} 
} 

function get_def($dbname, $table)
{
	global $fieldnames, $firstfield, $db;
	$count = 0;
	$def = "";
	$firstfield = "";
	$def .= "DROP TABLE IF EXISTS `$table`;\n";
	$result = $db->Execute("SHOW CREATE TABLE `$table`");
	$def .= $result->fields['Create Table'];

//	$def .= "CREATE TABLE $table (\n";
	$result = $db->Execute("SHOW FIELDS FROM $table");

	while(!$result->EOF)
	{
		$row = $result->fields;
//		$def .= "	$row[Field] $row[Type]";
 		$fieldnames[$count] = $row['Field'];
 		if($firstfield == "")
 		{
 			$firstfield = $row['Field'];
 		}

		$count++;
/*		if ($row["Default"] != "")
		{
			$def .= " DEFAULT '$row[Default]'";
		}
		if ($row["Null"] != "YES")
		{
			$def .= " NOT NULL";
		}
	   	if ($row['Extra'] != "")
	   	{
	   		$def .= " $row[Extra]";
	   	}
		$def .= ",\n";
*/
		$result->MoveNext();
	}
/*	$def = AAT_ereg_replace(",\n$","", $def);
	$result = $db->Execute("SHOW KEYS FROM $table");
	while(!$result->EOF)
	{
		$row = $result->fields;
		$kname=$row['Key_name'];
		if(($kname != "PRIMARY") && ($row['Non_unique'] == 0))
		{
			$kname="UNIQUE|$kname";
		}
		if(!isset($index[$kname])){
			$index[$kname] = array();
		}
		$index[$kname][] = $row['Column_name'];
		$result->MoveNext();
	}
	while(list($x, $columns) = @each($index))
	{
		$def .= ",\n";
		if($x == "PRIMARY")
		{
			$def .= "   PRIMARY KEY (" . implode($columns, ", ") . ")";
		}
		else if (AAT_substr($x,0,6) == "UNIQUE")
		{
			$def .= "   UNIQUE ".AAT_substr($x,7)." (" . implode($columns, ", ") . ")";
		}
		else
		{
			$def .= "   KEY $x (" . implode($columns, ", ") . ")";
		}
	 }

	 $def .= "\n);";
*/
	 return (stripslashes($def . ";"));
}

function get_content($dbname, $table, $namelist) {
	global $encrypt, $path, $backup_encryption_type, $db, $game_number, $firstfield, $extended;

	$fp = fopen ($path.$table . "_data" . $game_number . ".sql","w");

	if($fp)
	{
		$content="";
		$valuelist = "";
		$totalrecords = 1;
		$result = $db->Execute("SELECT * FROM $table order by $firstfield ASC");
		$insert = "INSERT INTO $table (" .$namelist . ") VALUES ";
		while(!$result->EOF)
		{
			$row = $result->fields;
			$value = "(";
			foreach($row as $element)
			{
				if(!isset($element))
				{
					$value .= "NULL,";
				}
				else if($element != "")
				{
					$value .= $db->qstr($element) . ",";
				}
				else
				{
					$value .= "'',";
				}
			}
			$value = AAT_ereg_replace(",$","",$value);
			$value .= ")";

			if(!($totalrecords % $extended)){
				$valuelist .= "$value\n";
				$content = $insert . $valuelist;
				if($backup_encryption_type == 1)
				{
					$content = $encrypt->cipher_string( $content );
				}
				if($backup_encryption_type == 2)
				{
					$content = enc( $content );
				}

				fwrite ($fp,$content);
				$valuelist = "";
			}
			else
			{
				$valuelist .= "$value,";
			}
			$totalrecords++;

			$result->MoveNext();
		}

		if(substr($valuelist, -1) == ",")
		{
			$valuelist = substr($valuelist, 0, -1);
		}

		if($valuelist != "")
		{
			$content = $insert . $valuelist . ";";
			if($backup_encryption_type == 1)
			{
				$content = $encrypt->cipher_string( $content );
			}
			if($backup_encryption_type == 2)
			{
				$content = enc( $content );
			}

			fwrite ($fp,$content);
		}
		fclose ($fp);
	}
}

?>
<tr>
<td>
<?
if($db_type == "mysql")
{
	if ($command=="BACKUP")
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='server_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='account_creation_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0' WHERE name='enable_scheduler'");
		db_op_result($debug_query,__LINE__,__FILE__);

		$path = $gameroot;

		flush();

		$stamp = date("Y_m_d-H_i_s");
		$path = $path . "backup/full/" . $stamp . "/";

		echo "<b>Starting Database Backup: $stamp</b><br><br>";
		flush();

		mkdir($path);
		$fs = @fopen("backup/full/" . $stamp . "/.htaccess", "w");
		@fwrite($fs, "Deny from all\n");
		@fclose($fs);

		$fs = @fopen("backup/full/" . $stamp . "/index.html", "w");
		@fclose($fs);

		if($backup_encryption_type == 1)
		{
			$encrypt =& new encrypt( $ADODB_CRYPT_KEY );
		}

		if($backup_encryption_type == 2)
		{
			DEFINE ("Keysize", $ADODB_CRYPT_KEY); 
			$td = mcrypt_module_open (MCRYPT_TripleDES, "", MCRYPT_MODE_ECB, ""); 
			$iv = mcrypt_create_iv (mcrypt_enc_get_iv_size ($td), MCRYPT_RAND); 
		}

		$table_list = array();
		$ADODB_FETCH_MODE = ADODB_FETCH_NUM;
		$result = $db->Execute("SHOW TABLES");
		while(!$result->EOF)
		{
			$table_list[] = $result->fields[0];
			$result->MoveNext();
		}
		$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;

		$tablecount = count($table_list);
		for ($c=0; $c < $tablecount; $c++)
		{
			$tablename = $table_list[$c];

			echo "Backing up table: $tablename<br>";
			flush();
			@set_time_limit(120);
			if(!file_exists($path . $tablename . "_table" . $game_number . ".sql"))
			{
				@unlink($path.$tablename . "_table" . $game_number . ".sql");
				@unlink($path.$tablename . "_data" . $game_number . ".sql");
			}

			$cur_time=date("Y-m-d H:i");
			unset($fieldnames);
			$newfile = get_def($dbname,$tablename);

			$fp = fopen ($path . $tablename . "_table" . $game_number . ".sql","w");
			if($fp)
			{
				fwrite ($fp,$newfile);
				fclose ($fp);
			}

			$namelist = "";
			for($i = 0; $i < count($fieldnames); $i++)
			{
				$namelist .= $fieldnames[$i];
				if($i != count($fieldnames) - 1)
				{
					$namelist .= ",";
				}
			}
			get_content($dbname,$tablename, $namelist);
		}
		echo "<br><b>Database Backup Complete</b><br><br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0' WHERE name='server_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0' WHERE name='account_creation_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='enable_scheduler'");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
	else
	{
		echo "<FORM ACTION=admin.php METHOD=POST>";
		echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
		echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
		echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Full_Database_Backup\">";
		echo "<table align=\"center\"><TR nowrap><TD>Click the BACKUP button if you want to backup your entire database.&nbsp;&nbsp;</TD></tr>";
		echo "<TR nowrap><TD>Records Per Insert: <select name=\"extended\">\n";
			echo "	<option value=\"1\">1</option>\n";
			echo "	<option value=\"5\">5</option>\n";
			echo "	<option value=\"10\">10</option>\n";
			echo "	<option value=\"20\">20</option>\n";
			echo "	<option value=\"30\">30</option>\n";
			echo "	<option value=\"40\">40</option>\n";
			echo "	<option value=\"50\" selected>50</option>\n";
			echo "	<option value=\"60\">60</option>\n";
			echo "	<option value=\"70\">70</option>\n";
			echo "	<option value=\"80\">80</option>\n";
			echo "	<option value=\"90\">90</option>\n";
			echo "	<option value=\"100\">100</option>\n";
		echo "  </select>\n<br><br></TD></TR>";
		echo "<tr><TD><INPUT TYPE=SUBMIT NAME=command VALUE=\"BACKUP\"></TD></TR>";
		echo "</table></form>";
	}
}
else
{
	echo "<br><b>Backup option can only be used for MySql databases</b><br>";
}
?>
</td></tr>

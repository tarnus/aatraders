<?php
/**
 * ADOdb Lite Cache Module for Mysql
 * 
 * Portions of the Cache Coding came from ADOdb
 */

/* 
  V4.65 22 July 2005  (c) 2000-2005 John Lim (jlim@natsoft.com.my). All rights reserved.
  Released under both BSD license and Lesser GPL library license. 
  Whenever there is any discrepancy between the two licenses, 
  the BSD license will take precedence. See License.txt. 
*/

GLOBAL $ADODB_CACHE_DIR;	// directory to cache recordsets

if (!isset($ADODB_CACHE_DIR)) {
	$ADODB_CACHE_DIR = '/tmp';
} else {
	if (strpos($ADODB_CACHE_DIR,'://') !== false) 
		die("Illegal path http:// or ftp://");
}

eval('class mysql_cache_EXTENDER extends '. $last_module . '_ADOConnection { }');

class mysql_cache_ADOConnection extends mysql_cache_EXTENDER
{
	var $cacheSecs = 3600; /// cache for 1 hour
	var $numCacheHits = 0; 
	var $numCacheMisses = 0;
	var $fnCacheExecute = false;

	function &CacheGetAssoc($secs2cache, $sql=false, $inputarr=false,$force_array = false, $first2cols = false)
	{
		if (!is_numeric($secs2cache)) {
			$first2cols = $force_array;
			$force_array = $inputarr;
		}
		$rs =& $this->CacheExecute($secs2cache, $sql, $inputarr);
		if (!$rs) {
			$false = false;
			return $false;
		}
		$arr =& $rs->GetAssoc($force_array,$first2cols);
		return $arr;
	}
	
	function CacheGetOne($secs2cache,$sql=false,$inputarr=false)
	{
		$ret = false;
		$rs = &$this->CacheExecute($secs2cache,$sql,$inputarr);
		if ($rs) {		
			if (!$rs->EOF) $ret = reset($rs->fields);
			$rs->Close();
		} 
		
		return $ret;
	}
	
	function CacheGetCol($secs, $sql = false, $inputarr = false,$trim=false)
	{
	  	$rv = false;
	  	$rs = &$this->CacheExecute($secs, $sql, $inputarr);
	  	if ($rs) {
			if ($trim) {
				while (!$rs->EOF) {
					$rv[] = trim(reset($rs->fields));
					$rs->MoveNext();
		   		}
			} else {
				while (!$rs->EOF) {
					$rv[] = reset($rs->fields);
					$rs->MoveNext();
		   		}
			}
	   		$rs->Close();
	  	}
	  	return $rv;
	}
 
	function &CacheGetAll($secs2cache,$sql=false,$inputarr=false)
	{
		return $this->CacheGetArray($secs2cache,$sql,$inputarr);
	}
	
	function &CacheGetArray($secs2cache,$sql=false,$inputarr=false)
	{
	global $ADODB_COUNTRECS;
		
		$savec = $ADODB_COUNTRECS;
		$ADODB_COUNTRECS = false;
		$rs =& $this->CacheExecute($secs2cache,$sql,$inputarr);
		$ADODB_COUNTRECS = $savec;
		
		if (!$rs) 
			if (defined('ADODB_PEAR')) return ADODB_PEAR_Error();
			else {
				$false = false;
				return $false;
			}
		$arr =& $rs->GetArray();
		$rs->Close();
		return $arr;
	}
	
	function &CacheGetRow($secs2cache,$sql=false,$inputarr=false)
	{
		$rs =& $this->CacheExecute($secs2cache,$sql,$inputarr);
		if ($rs) {
			$arr = false;
			if (!$rs->EOF) $arr = $rs->fields;
			$rs->Close();
			return $arr;
		}
		$false = false;
		return $false;
	}
	
	function &CacheSelectLimit($secs2cache,$sql,$nrows=-1,$offset=-1,$inputarr=false)
	{	
		if (!is_numeric($secs2cache)) {
			if ($sql === false) $sql = -1;
			if ($offset == -1) $offset = false;
									  // sql,	nrows, offset,inputarr
			$rs =& $this->SelectLimit($secs2cache,$sql,$nrows,$offset,$this->cacheSecs);
		} else {
			if ($sql === false) ADOConnection::debugoutput( "Warning: \$sql missing from CacheSelectLimit()");
			$rs =& $this->SelectLimit($sql,$nrows,$offset,$inputarr,$secs2cache);
		}
		return $rs;
	}
	
	/**
	* Flush cached recordsets that match a particular $sql statement. 
	* If $sql == false, then we purge all files in the cache.
 	*/
	function CacheFlush($sql=false,$inputarr=false)
	{
	global $ADODB_CACHE_DIR;
	
		if (strlen($ADODB_CACHE_DIR) > 1 && !$sql) {
			if (strncmp(PHP_OS,'WIN',3) === 0) {
				$cmd = 'del /s '.str_replace('/','\\',$ADODB_CACHE_DIR).'\adodb_*.cache';
			} else {
				//$cmd = 'find "'.$ADODB_CACHE_DIR.'" -type f -maxdepth 1 -print0 | xargs -0 rm -f';
				$cmd = 'rm -rf '.$ADODB_CACHE_DIR.'/[0-9a-f][0-9a-f]/'; 
				// old version 'rm -f `find '.$ADODB_CACHE_DIR.' -name adodb_*.cache`';
			}
			if ($this->debug) {
				ADOConnection::debugoutput( "CacheFlush: $cmd<br><pre>\n", system($cmd),"</pre>");
			} else {
				exec($cmd);
			}
			return;
		} 
		
		$f = $this->_gencachename($sql.serialize($inputarr),false);
		$this->adodb_write_file($f,''); // is adodb_write_file needed?
		if (!@unlink($f)) {
			if ($this->debug) ADOConnection::debugoutput( "CacheFlush: failed for $f");
		}
	}
	
	/**
	* Private function to generate filename for caching.
	* Filename is generated based on:
	*
	*  - sql statement
	*  - database type (oci8, ibase, ifx, etc)
	*  - database name
	*  - userid
	*  - setFetchMode (adodb 4.23)
	*
	* When not in safe mode, we create 256 sub-directories in the cache directory ($ADODB_CACHE_DIR). 
	* Assuming that we can have 50,000 files per directory with good performance, 
	* then we can scale to 12.8 million unique cached recordsets. Wow!
 	*/
	function _gencachename($sql,$createdir)
	{
	global $ADODB_CACHE_DIR;
	static $notSafeMode;
		
		if ($this->fetchMode === false) { 
		global $ADODB_FETCH_MODE;
			$mode = $ADODB_FETCH_MODE;
		} else {
			$mode = $this->fetchMode;
		}
		$m = md5($sql.$this->databaseType.$this->database.$this->user.$mode);
		
		if (!isset($notSafeMode)) $notSafeMode = !ini_get('safe_mode');
		$dir = ($notSafeMode) ? $ADODB_CACHE_DIR.'/'.substr($m,0,2) : $ADODB_CACHE_DIR;
			
		if ($createdir && $notSafeMode && !file_exists($dir)) {
			$oldu = umask(0);
			if (!mkdir($dir,0771)) 
				if ($this->debug) ADOConnection::debugoutput( "Unable to mkdir $dir for $sql");
			umask($oldu);
		}
		return $dir.'/adodb_'.$m.'.cache';
	}
	
	
	/**
	 * Execute SQL, caching recordsets.
	 *
	 * @param [secs2cache]	seconds to cache data, set to 0 to force query. 
	 *					  This is an optional parameter.
	 * @param sql		SQL statement to execute
	 * @param [inputarr]	holds the input data  to bind to
	 * @return 		RecordSet or false
	 */
	function &CacheExecute($secs2cache,$sql=false,$inputarr=false)
	{

			
		if (!is_numeric($secs2cache)) {
			$inputarr = $sql;
			$sql = $secs2cache;
			$secs2cache = $this->cacheSecs;
		}
		
		if (is_array($sql)) {
			$sqlparam = $sql;
			$sql = $sql[0];
		} else
			$sqlparam = $sql;
			
		$md5file = $this->_gencachename($sql.serialize($inputarr),true);
		$err = '';
		
		if ($secs2cache > 0){
			$rs =& $this->csv2rs($md5file,$err,$secs2cache,$this->arrayClass);
			$this->numCacheHits += 1;
		} else {
			$err='Timeout 1';
			$rs = false;
			$this->numCacheMisses += 1;
		}
		if (!$rs) {
		// no cached rs found
			if ($this->debug) {
				if (get_magic_quotes_runtime()) {
					ADOConnection::debugoutput("Please disable magic_quotes_runtime - it corrupts cache files :(");
				}
				if ($this->debug !== -1) ADOConnection::debugoutput( " $md5file cache failure: $err (see sql below)");
			}
			
			$rs = &$this->Execute($sqlparam,$inputarr);

			if ($rs) {
				$eof = $rs->EOF;
				$rs = &$this->_rs2rs($rs); // read entire recordset into memory immediately
				$txt = $this->_rs2serialize($rs,false,$sql); // serialize
		
				if (!$this->adodb_write_file($md5file,$txt,$this->debug)) {
					if ($fn = $this->raiseErrorFn) {
						$fn($this->databaseType,'CacheExecute',-32000,"Cache write error",$md5file,$sql,$this);
					}
					if ($this->debug) ADOConnection::debugoutput( " Cache write error");
				}
				if ($rs->EOF && !$eof) {
					$rs->MoveFirst();
					//$rs = &csv2rs($md5file,$err);		
					$rs->connection = &$this; // Pablo suggestion
				}  
				
			} else
				@unlink($md5file);
		} else {
			$this->_errorMsg = '';
			$this->_errorCode = 0;
			
			if ($this->fnCacheExecute) {
				$fn = $this->fnCacheExecute;
				$fn($this, $secs2cache, $sql, $inputarr);
			}
		// ok, set cached object found
			$rs->connection = &$this; // Pablo suggestion
			if ($this->debug){ 
					
				$inBrowser = isset($_SERVER['HTTP_USER_AGENT']);
				$ttl = $rs->timeCreated + $secs2cache - time();
				$s = is_array($sql) ? $sql[0] : $sql;
				if ($inBrowser) $s = '<i>'.htmlspecialchars($s).'</i>';
				
				ADOConnection::debugoutput( " $md5file reloaded, ttl=$ttl [ $s ]");
			}
		}
		return $rs;
	}

	/**
	* Convert database recordset to an array recordset
	* input recordset's cursor should be at beginning, and
	* old $rs will be closed.
	*
	* @param rs			the recordset to copy
	* @param [nrows]  	number of rows to retrieve (optional)
	* @param [offset] 	offset by number of rows (optional)
	* @return 			the new recordset
	*/
	function &_rs2rs(&$rs,$nrows=-1,$offset=-1,$close=true)
	{
		if (! $rs) {
			$false = false;
			return $false;
		}
		$dbtype = $rs->databaseType;
		if (!$dbtype) {
			$rs = &$rs;  // required to prevent crashing in 4.2.1, but does not happen in 4.3.1 -- why ?
			return $rs;
		}
		if (($dbtype == 'array' || $dbtype == 'csv') && $nrows == -1 && $offset == -1) {
			$rs->MoveFirst();
			$rs = &$rs; // required to prevent crashing in 4.2.1, but does not happen in 4.3.1-- why ?
			return $rs;
		}
		$flds = array();
		for ($i=0, $max=$rs->FieldCount(); $i < $max; $i++) {
			$flds[] = $rs->FetchField($i);
		}

		$arr =& $rs->GetArrayLimit($nrows,$offset);
		//print_r($arr);
		if ($close) $rs->Close();
		
		$arrayClass = $this->arrayClass;
		
		$rs2 = new $arrayClass();
		$rs2->connection = &$this;
		$rs2->sql = $rs->sql;
		$rs2->dataProvider = $this->dataProvider;
		$rs2->InitArrayFields($arr,$flds);
		$rs2->fetchMode = isset($rs->adodbFetchMode) ? $rs->adodbFetchMode : $rs->fetchMode;
		return $rs2;
	}

	/**
	 * convert a recordset into special format
	 *
	 * @param rs	the recordset
	 *
	 * @return	the CSV formated data
	 */
	function _rs2serialize(&$rs,$conn=false,$sql='')
	{
		$max = ($rs) ? $rs->FieldCount() : 0;
		
		if ($sql) $sql = urlencode($sql);
		// metadata setup
		
		if ($max <= 0 || $rs->dataProvider == 'empty') { // is insert/update/delete
			if (is_object($conn)) {
				$sql .= ','.$conn->Affected_Rows();
				$sql .= ','.$conn->Insert_ID();
			} else
				$sql .= ',,';
			
			$text = "====-1,0,$sql\n";
			return $text;
		}
		$tt = ($rs->timeCreated) ? $rs->timeCreated : time();
		
		## changed format from ====0 to ====1
		$line = "====1,$tt,$sql\n";
		
		if ($rs->databaseType == 'array') {
			$rows =& $rs->_array;
		} else {
			$rows = array();
			while (!$rs->EOF) {	
				$rows[] = $rs->fields;
				$rs->MoveNext();
			} 
		}
		
		for($i=0; $i < $max; $i++) {
			$o =& $rs->FetchField($i);
			$flds[] = $o;
		}
	
		$savefetch = isset($rs->adodbFetchMode) ? $rs->adodbFetchMode : $rs->fetchMode;
		$class = $rs->connection->arrayClass;
		$rs2 = new $class();
		$rs2->sql = $rs->sql;
		$rs2->oldProvider = $rs->dataProvider; 
		$rs2->InitArrayFields($rows,$flds);
		$rs2->fetchMode = $savefetch;
		return $line.serialize($rs2);
	}

	
/**
* Open CSV file and convert it into Data. 
*
* @param url  		file/ftp/http url
* @param err		returns the error message
* @param timeout	dispose if recordset has been alive for $timeout secs
*
* @return		recordset, or false if error occured. If no
*			error occurred in sql INSERT/UPDATE/DELETE, 
*			empty recordset is returned
*/
	function &csv2rs($url,&$err,$timeout=0, $rsclass='ADORecordSet_array')
	{
		$false = false;
		$err = false;
		$fp = @fopen($url,'rb');
		if (!$fp) {
			$err = $url.' file/URL not found';
			return $false;
		}
		@flock($fp, LOCK_SH);
		$arr = array();
		$ttl = 0;
		
		if ($meta = fgetcsv($fp, 32000, ",")) {
			// check if error message
			if (strncmp($meta[0],'****',4) === 0) {
				$err = trim(substr($meta[0],4,1024));
				fclose($fp);
				return $false;
			}
			// check for meta data
			// $meta[0] is -1 means return an empty recordset
			// $meta[1] contains a time 
	
			if (strncmp($meta[0], '====',4) === 0) {
			
				if ($meta[0] == "====-1") {
					if (sizeof($meta) < 5) {
						$err = "Corrupt first line for format -1";
						fclose($fp);
						return $false;
					}
					fclose($fp);
					
					if ($timeout > 0) {
						$err = " Illegal Timeout $timeout ";
						return $false;
					}
					
					$rs = new $rsclass($val=true);
					$rs->fields = array();
					$rs->timeCreated = $meta[1];
					$rs->EOF = true;
					$rs->_numOfFields = 0;
					$rs->sql = urldecode($meta[2]);
					$rs->affectedrows = (integer)$meta[3];
					$rs->insertid = $meta[4];	
					return $rs;
				} 
			# Under high volume loads, we want only 1 thread/process to _write_file
			# so that we don't have 50 processes queueing to write the same data.
			# We use probabilistic timeout, ahead of time.
			#
			# -4 sec before timeout, give processes 1/32 chance of timing out
			# -2 sec before timeout, give processes 1/16 chance of timing out
			# -1 sec after timeout give processes 1/4 chance of timing out
			# +0 sec after timeout, give processes 100% chance of timing out
				if (sizeof($meta) > 1) {
					if($timeout >0){ 
						$tdiff = (integer)( $meta[1]+$timeout - time());
						if ($tdiff <= 2) {
							switch($tdiff) {
							case 4:
							case 3:
								if ((rand() & 31) == 0) {
									fclose($fp);
									$err = "Timeout 3";
									return $false;
								}
								break;
							case 2: 
								if ((rand() & 15) == 0) {
									fclose($fp);
									$err = "Timeout 2";
									return $false;
								}
								break;
							case 1:
								if ((rand() & 3) == 0) {
									fclose($fp);
									$err = "Timeout 1";
									return $false;
								}
								break;
							default: 
								fclose($fp);
								$err = "Timeout 0";
								return $false;
							} // switch
							
						} // if check flush cache
					}// (timeout>0)
					$ttl = $meta[1];
				}
				//================================================
				// new cache format - use serialize extensively...
				if ($meta[0] === '====1') {
					// slurp in the data
					$MAXSIZE = 128000;
					
					$text = fread($fp,$MAXSIZE);
					if (strlen($text)) {
						while ($txt = fread($fp,$MAXSIZE)) {
							$text .= $txt;
						}
					}
					fclose($fp);
					$rs = unserialize($text);
					if (is_object($rs)) $rs->timeCreated = $ttl;
					else {
						$err = "Unable to unserialize recordset";
						//echo htmlspecialchars($text),' !--END--!<p>';
					}
					return $rs;
				}
				
				$meta = false;
				$meta = fgetcsv($fp, 32000, ",");
				if (!$meta) {
					fclose($fp);
					$err = "Unexpected EOF 1";
					return $false;
				}
			}

			// Get Column definitions
			$flds = array();
			foreach($meta as $o) {
				$o2 = explode(':',$o);
				if (sizeof($o2)!=3) {
					$arr[] = $meta;
					$flds = false;
					break;
				}
				$fld = new ADOFieldObject();
				$fld->name = urldecode($o2[0]);
				$fld->type = $o2[1];
				$fld->max_length = $o2[2];
				$flds[] = $fld;
			}
		} else {
			fclose($fp);
			$err = "Recordset had unexpected EOF 2";
			return $false;
		}
		
		// slurp in the data
		$MAXSIZE = 128000;
		
		$text = '';
		while ($txt = fread($fp,$MAXSIZE)) {
			$text .= $txt;
		}
			
		fclose($fp);
		@$arr = unserialize($text);
		//var_dump($arr);
		if (!is_array($arr)) {
			$err = "Recordset had unexpected EOF (in serialized recordset)";
			if (get_magic_quotes_runtime()) $err .= ". Magic Quotes Runtime should be disabled!";
			return $false;
		}
		$rs = new $rsclass();
		$rs->timeCreated = $ttl;
		$rs->InitArrayFields($arr,$flds);
		return $rs;
	}
	

	/**
	* Save a file $filename and its $contents (normally for caching) with file locking
	*/
	function adodb_write_file($filename, $contents,$debug=false)
	{ 
	# http://www.php.net/bugs.php?id=9203 Bug that flock fails on Windows
	# So to simulate locking, we assume that rename is an atomic operation.
	# First we delete $filename, then we create a $tempfile write to it and 
	# rename to the desired $filename. If the rename works, then we successfully 
	# modified the file exclusively.
	# What a stupid need - having to simulate locking.
	# Risks:
	# 1. $tempfile name is not unique -- very very low
	# 2. unlink($filename) fails -- ok, rename will fail
	# 3. adodb reads stale file because unlink fails -- ok, $rs timeout occurs
	# 4. another process creates $filename between unlink() and rename() -- ok, rename() fails and  cache updated
		if (strncmp(PHP_OS,'WIN',3) === 0) {
			// skip the decimal place
			$mtime = substr(str_replace(' ','_',microtime()),2); 
			// getmypid() actually returns 0 on Win98 - never mind!
			$tmpname = $filename.uniqid($mtime).getmypid();
			if (!($fd = @fopen($tmpname,'a'))) return false;
			$ok = ftruncate($fd,0);			
			if (!fwrite($fd,$contents)) $ok = false;
			fclose($fd);
			chmod($tmpname,0644);
			// the tricky moment
			@unlink($filename);
			if (!@rename($tmpname,$filename)) {
				unlink($tmpname);
				$ok = false;
			}
			if (!$ok) {
				if ($debug) ADOConnection::debugoutput( " Rename $tmpname ".($ok? 'ok' : 'failed'));
			}
			return $ok;
		}
		if (!($fd = @fopen($filename, 'a'))) return false;
		if (flock($fd, LOCK_EX) && ftruncate($fd, 0)) {
			$ok = fwrite( $fd, $contents );
			fclose($fd);
			chmod($filename,0644);
		}else {
			fclose($fd);
			if ($debug)ADOConnection::debugoutput( " Failed acquiring lock for $filename<br>\n");
			$ok = false;
		}
	
		return $ok;
	}

}

eval('class mysql_cache_resultset_EXTENDER extends '. $last_module . '_ResultSet { }');

class mysql_cache_ResultSet extends mysql_cache_resultset_EXTENDER
{
	var $timeCreated=0; 	/// datetime in Unix format rs created -- for cached recordsets
}


//==============================================================================================	
// CLASS ADORecordSet_array
//==============================================================================================	

/**
 * This class encapsulates the concept of a recordset created in memory
 * as an array. This is useful for the creation of cached recordsets.
 * 
 * Note that the constructor is different from the standard ADORecordSet
 */

class ADORecordSet_array
{
	var $databaseType = 'array';

	var $_array; 	// holds the 2-dimensional data array
	var $_types;	// the array of types of each column (C B I L M)
	var $_colnames;	// names of each column in array
	var $_skiprow1;	// skip 1st row because it holds column names
	var $_fieldarr; // holds array of field objects
	var $affectedrows = false;
	var $insertid = false;
	var $_inited = '';
	var $connectionId;
	var $fields;
	var $resultId;
	var $_currentRow = 0;
	var $_numOfRows = -1;
	var $_numOfFields = -1;
	var $fetchMode;
	var $EOF;
	/**
	 * Constructor
	 *
	 */
	function ADORecordSet_array($fakeid=1)
	{
		global $ADODB_FETCH_MODE;
		// fetch() on EOF does not delete $this->fields
		$this->ADORecordSet($fakeid); // fake queryID		
		$this->fetchMode = $ADODB_FETCH_MODE;
	}

	function Init()
	{
		if ($this->_inited) return;
		$this->_inited = true;
		if ($this->_queryID) @$this->_initrs();
		else {
			$this->_numOfRows = 0;
			$this->_numOfFields = 0;
		}
		if ($this->_numOfRows != 0 && $this->_numOfFields && $this->_currentRow == -1) {
			
			$this->_currentRow = 0;
			if ($this->EOF = ($this->_fetch() === false)) {
				$this->_numOfRows = 0; // _numOfRows could be -1
			}
		} else {
			$this->EOF = true;
		}
	}

	/**
	 * Setup the array.
	 *
	 * @param array		is a 2-dimensional array holding the data.
	 *			The first row should hold the column names 
	 *			unless paramter $colnames is used.
	 * @param typearr	holds an array of types. These are the same types 
	 *			used in MetaTypes (C,B,L,I,N).
	 * @param [colnames]	array of column names. If set, then the first row of
	 *			$array should not hold the column names.
	 */
	function InitArray($array,$typearr,$colnames=false)
	{
		$this->_array = $array;
		$this->_types = $typearr;	
		if ($colnames) {
			$this->_skiprow1 = false;
			$this->_colnames = $colnames;
		} else  {
			$this->_skiprow1 = true;
			$this->_colnames = $array[0];
		}
		$this->Init();
	}

	/**
	 * Setup the Array and datatype file objects
	 *
	 * @param array		is a 2-dimensional array holding the data.
	 *			The first row should hold the column names 
	 *			unless paramter $colnames is used.
	 * @param fieldarr	holds an array of ADOFieldObject's.
	 */
	function InitArrayFields(&$array,&$fieldarr)
	{
		$this->_array =& $array;
		$this->_skiprow1= false;
		if ($fieldarr) {
			$this->_fieldobjects =& $fieldarr;
		} 
		$this->Init();
	}

	function &GetArray($nRows=-1)
	{
		if ($nRows == -1 && $this->_currentRow <= 0 && !$this->_skiprow1) {
			return $this->_array;
		} else {
			$arr =& ADORecordSet::GetArray($nRows);
			return $arr;
		}
	}

	function _initrs()
	{
		$this->_numOfRows =  sizeof($this->_array);
		if ($this->_skiprow1) $this->_numOfRows -= 1;
		$this->_numOfFields =(isset($this->_fieldobjects)) ? sizeof($this->_fieldobjects):sizeof($this->_types);
	}

	/* Use associative array to get fields array */
	function Fields($colname)
	{
		$mode = isset($this->adodbFetchMode) ? $this->adodbFetchMode : $this->fetchMode;
		if ($mode & ADODB_FETCH_ASSOC) {
			if (!isset($this->fields[$colname])) $colname = strtolower($colname);
			return $this->fields[$colname];
		}
		if (!$this->bind) {
			$this->bind = array();
			for ($i=0; $i < $this->_numOfFields; $i++) {
				$o = $this->FetchField($i);
				$this->bind[strtoupper($o->name)] = $i;
			}
		}
		return $this->fields[$this->bind[strtoupper($colname)]];
	}

	function &FetchField($fieldOffset = -1) 
	{
		if (isset($this->_fieldobjects)) {
			return $this->_fieldobjects[$fieldOffset];
		}
		$o =  new ADOFieldObject();
		$o->name = $this->_colnames[$fieldOffset];
		$o->type =  $this->_types[$fieldOffset];
		$o->max_length = -1; // length not known
		return $o;
	}

	function _seek($row)
	{
		if (sizeof($this->_array) && 0 <= $row && $row < $this->_numOfRows) {
			$this->_currentRow = $row;
			if ($this->_skiprow1) $row += 1;
			$this->fields = $this->_array[$row];
			return true;
		}
		return false;
	}

	function MoveNext() 
	{
		if (!$this->EOF) {		
			$this->_currentRow++;
			$pos = $this->_currentRow;
			if ($this->_numOfRows <= $pos) {
				if (!$this->compat) $this->fields = false;
			} else {
				if ($this->_skiprow1) $pos += 1;
				$this->fields = $this->_array[$pos];
				return true;
			}
			$this->EOF = true;
		}
		return false;
	}

	function _fetch()
	{
		$pos = $this->_currentRow;
		if ($this->_numOfRows <= $pos) {
			if (!$this->compat) $this->fields = false;
			return false;
		}
		if ($this->_skiprow1) $pos += 1;
		$this->fields = $this->_array[$pos];
		return true;
	}

	function _close() 
	{
		return true;	
	}

} // ADORecordSet_array

if(!class_exists('ADOFieldObject'))
{
	class ADOFieldObject { 
		var $name = '';
		var $max_length=0;
		var $type="";
	}
}

?>
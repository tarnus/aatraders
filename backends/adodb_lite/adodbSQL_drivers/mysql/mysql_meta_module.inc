<?php
/**
 * ADOdb Lite Meta Module for Mysql
 * 
 * Portions of the Meta Coding came from ADOdb
 */

/* 
  (c) 2000-2005 John Lim (jlim@natsoft.com.my). All rights reserved.
  Released under both BSD license and Lesser GPL library license. 
  Whenever there is any discrepancy between the two licenses, 
  the BSD license will take precedence. See License.txt. 
*/

eval('class mysql_meta_EXTENDER extends '. $last_module . '_ADOConnection { }');

class mysql_meta_ADOConnection extends mysql_meta_EXTENDER
{
	var $metaTablesSQL = "SHOW TABLES";	
	var $metaColumnsSQL = "SHOW COLUMNS FROM %s";

	function MetaError($err=false)
	{
		include_once(ADODB_DIR."/adodb-error.inc.php");
		if ($err === false)
			$err = $this->ErrorNo();

		return adodb_error($this->dataProvider,$this->databaseType,$err);
	}

	function MetaErrorMsg($errno)
	{
		include_once(ADODB_DIR."/adodb-error.inc.php");
		return adodb_errormsg($errno);
	}

	/**
	 * @returns an array with the primary key columns in it.
	 */
	function MetaPrimaryKeys($table, $owner=false)
	{
		// owner not used in base class - see oci8
		$p = array();
		$objs =& $this->MetaColumns($table);
		if ($objs) {
			foreach($objs as $v) {
				if (!empty($v->primary_key))
					$p[] = $v->name;
			}
		}
		if (sizeof($p))
			return $p;
		if (function_exists('ADODB_VIEW_PRIMARYKEYS'))
			return ADODB_VIEW_PRIMARYKEYS($this->databaseType, $this->database, $table, $owner);
		return false;
	}

	/**
	 * @returns assoc array where keys are tables, and values are foreign keys
	 */
	function MetaForeignKeys( $table, $owner = FALSE, $upper = FALSE, $associative = FALSE )
	 {
		 if ( !empty($owner) ) {
			$table = "$owner.$table";
		 }
		 $a_create_table = $this->getRow(sprintf('SHOW CREATE TABLE %s', $table));
		 if ($associative) $create_sql = $a_create_table["Create Table"];
		 else $create_sql  = $a_create_table[1];

		 $matches = array();

		 if (!preg_match_all("/FOREIGN KEY \(`(.*?)`\) REFERENCES `(.*?)` \(`(.*?)`\)/", $create_sql, $matches)) return false;
		 $foreign_keys = array();	 	 
		 $num_keys = count($matches[0]);
		 for ( $i = 0;  $i < $num_keys;  $i ++ ) {
			 $my_field  = explode('`, `', $matches[1][$i]);
			 $ref_table = $matches[2][$i];
			 $ref_field = explode('`, `', $matches[3][$i]);

			 if ( $upper ) {
				 $ref_table = strtoupper($ref_table);
			 }

			 $foreign_keys[$ref_table] = array();
			 $num_fields = count($my_field);
			 for ( $j = 0;  $j < $num_fields;  $j ++ ) {
				 if ( $associative ) {
					 $foreign_keys[$ref_table][$ref_field[$j]] = $my_field[$j];
				 } else {
					 $foreign_keys[$ref_table][] = "{$my_field[$j]}={$ref_field[$j]}";
				 }
			 }
		 }
		 
		 return  $foreign_keys;
	 }

	// not the fastest implementation - quick and dirty - jlim
	// for best performance, use the actual $rs->MetaType().
	function MetaType($t,$len=-1,$fieldobj=false)
	{
		if (empty($this->_metars)) {
			$rsclass = $this->rsPrefix.$this->databaseType;
			$this->_metars =& new $rsclass(false,$this->fetchMode); 
		}

		return $this->_metars->MetaType($t,$len,$fieldobj);
	}

	/**
	 * return the databases that the driver can connect to. 
	 * Some databases will return an empty array.
	 *
	 * @return an array of database names.
	 */
  	function &MetaDatabases()
	{
		$qid = mysql_list_dbs($this->connectionId);
		$arr = array();
		$i = 0;
		$max = mysql_num_rows($qid);
		while ($i < $max) {
			$db = mysql_tablename($qid,$i);
			if ($db != 'mysql') $arr[] = $db;
			$i += 1;
		}
		return $arr;
	}

	/**
	 * @param ttype can either be 'VIEW' or 'TABLE' or false. 
	 * 		If false, both views and tables are returned.
	 *		"VIEW" returns only views
	 *		"TABLE" returns only tables
	 * @param showSchema returns the schema/user with the table name, eg. USER.TABLE
	 * @param mask  is the input mask - only supported by oci8 and postgresql
	 *
	 * @return  array of tables for current database.
	 */ 
	function &MetaTables($ttype=false,$showSchema=false,$mask=false) 
	{	
		$save = $this->metaTablesSQL;
		if ($showSchema && is_string($showSchema)) {
			$this->metaTablesSQL .= " from $showSchema";
		}
		
		if ($mask) {
			$mask = $this->connection->qstr($mask);
			$this->metaTablesSQL .= " like $mask";
		}
		$ret =& $this->_MetaTables($ttype,$showSchema);
		
		$this->metaTablesSQL = $save;
		return $ret;
	}

	function &_MetaTables($ttype=false,$showSchema=false,$mask=false) 
	{
		global $ADODB_FETCH_MODE;

		$false = false;
		if ($mask) {
			return $false;
		}
		if ($this->metaTablesSQL) {
			$save = $ADODB_FETCH_MODE; 
			$ADODB_FETCH_MODE = ADODB_FETCH_NUM; 
			
			if ($this->fetchMode !== false) $savem = $this->SetFetchMode(false);
			
			$rs = $this->connection->Execute($this->metaTablesSQL);
			if (isset($savem)) $this->SetFetchMode($savem);
			$ADODB_FETCH_MODE = $save; 
			
			if ($rs === false) return $false;
			$arr =& $rs->GetArray();
			$arr2 = array();
			
			if ($hast = ($ttype && isset($arr[0][1]))) { 
				$showt = strncmp($ttype,'T',1);
			}
			
			for ($i=0; $i < sizeof($arr); $i++) {
				if ($hast) {
					if ($showt == 0) {
						if (strncmp($arr[$i][1],'T',1) == 0) $arr2[] = trim($arr[$i][0]);
					} else {
						if (strncmp($arr[$i][1],'V',1) == 0) $arr2[] = trim($arr[$i][0]);
					}
				} else
					$arr2[] = trim($arr[$i][0]);
			}
			$rs->Close();
			return $arr2;
		}
		return $false;
	}

	function _findschema(&$table,&$schema)
	{
		if (!$schema && ($at = strpos($table,'.')) !== false) {
			$schema = substr($table,0,$at);
			$table = substr($table,$at+1);
		}
	}

	/**
	 * List columns in a database as an array of ADOFieldObjects. 
	 * See top of file for definition of object.
	 *
	 * @param $table	table name to query
	 * @param $normalize	makes table name case-insensitive (required by some databases)
	 * @schema is optional database schema to use - not supported by all databases.
	 *
	 * @return  array of ADOFieldObjects for current table.
	 */
 	function MetaColumns($table) 
	{
		$this->_findschema($table,$schema);
		if ($schema) {
			$dbName = $this->database;
			$this->connection->SelectDB($schema);
		}
		global $ADODB_FETCH_MODE;
		$save = $ADODB_FETCH_MODE;
		$ADODB_FETCH_MODE = ADODB_FETCH_NUM;
		
		if ($this->fetchMode !== false) $savem = $this->SetFetchMode(false);
		$rs = $this->connection->Execute(sprintf($this->metaColumnsSQL,$table));
		
		if ($schema) {
			$this->connection->SelectDB($dbName);
		}
		
		if (isset($savem)) $this->SetFetchMode($savem);
		$ADODB_FETCH_MODE = $save;
		if (!is_object($rs)) {
			$false = false;
			return $false;
		}
			
		$retarr = array();
		while (!$rs->EOF){
			$fld = new ADOFieldObject();
			$fld->name = $rs->fields[0];
			$type = $rs->fields[1];
			
			// split type into type(length):
			$fld->scale = null;
			if (preg_match("/^(.+)\((\d+),(\d+)/", $type, $query_array)) {
				$fld->type = $query_array[1];
				$fld->max_length = is_numeric($query_array[2]) ? $query_array[2] : -1;
				$fld->scale = is_numeric($query_array[3]) ? $query_array[3] : -1;
			} elseif (preg_match("/^(.+)\((\d+)/", $type, $query_array)) {
				$fld->type = $query_array[1];
				$fld->max_length = is_numeric($query_array[2]) ? $query_array[2] : -1;
			} elseif (preg_match("/^(enum)\((.*)\)$/i", $type, $query_array)) {
				$fld->type = $query_array[1];
				$arr = explode(",",$query_array[2]);
				$fld->enums = $arr;
				$zlen = max(array_map("strlen",$arr)) - 2; // PHP >= 4.0.6
				$fld->max_length = ($zlen > 0) ? $zlen : 1;
			} else {
				$fld->type = $type;
				$fld->max_length = -1;
			}
			$fld->not_null = ($rs->fields[2] != 'YES');
			$fld->primary_key = ($rs->fields[3] == 'PRI');
			$fld->auto_increment = (strpos($rs->fields[5], 'auto_increment') !== false);
			$fld->binary = (strpos($type,'blob') !== false);
			$fld->unsigned = (strpos($type,'unsigned') !== false);
				
			if (!$fld->binary) {
				$d = $rs->fields[4];
				if ($d != '' && $d != 'NULL') {
					$fld->has_default = true;
					$fld->default_value = $d;
				} else {
					$fld->has_default = false;
				}
			}
			
			if ($save == ADODB_FETCH_NUM) {
				$retarr[] = $fld;
			} else {
				$retarr[strtoupper($fld->name)] = $fld;
			}
				$rs->MoveNext();
			}
		
			$rs->Close();
			return $retarr;	
	}

	/**
	  * List indexes on a table as an array.
	  * @param table  table name to query
	  * @param primary true to only show primary keys. Not actually used for most databases
	  *
	  * @return array of indexes on current table. Each element represents an index, and is itself an associative array.
	  
		 Array (
			[name_of_index] => Array
			  (
			  [unique] => true or false
			  [columns] => Array
			  (
			  	[0] => firstname
			  	[1] => lastname
			  )
		)		
	  */
	function MetaIndexes ($table, $primary = FALSE, $owner=false)
	{
		// save old fetch mode
		global $ADODB_FETCH_MODE;
		
		$false = false;
		$save = $ADODB_FETCH_MODE;
		$ADODB_FETCH_MODE = ADODB_FETCH_NUM;
		if ($this->fetchMode !== FALSE) {
			   $savem = $this->SetFetchMode(FALSE);
		}
		
		// get index details
		$rs =& $this->connection->Execute(sprintf('SHOW INDEX FROM %s',$table));
		
		// restore fetchmode
		if (isset($savem)) {
				$this->SetFetchMode($savem);
		}
		$ADODB_FETCH_MODE = $save;
		
		if (!is_object($rs)) {
				return $false;
		}
		
		$indexes = array ();
		
		// parse index data into array
		while (!$rs->EOF)
		{
				if ($primary == FALSE AND $rs->fields[2] == 'PRIMARY') {
					$rs->MoveNext();
						continue;
				}

				if (!isset($indexes[$rs->fields[2]])) {
						$indexes[$rs->fields[2]] = array(
								'unique' => ($rs->fields[1] == 0),
								'columns' => array()
						);
				}

				$indexes[$rs->fields[2]]['columns'][$rs->fields[3] - 1] = $rs->fields[4];

			$rs->MoveNext();
		}
		
		// sort columns by order in the index
		foreach ( array_keys ($indexes) as $index )
		{
				ksort ($indexes[$index]['columns']);
		}
		
		return $indexes;
	}

	/**
	 * List columns names in a table as an array. 
	 * @param table	table name to query
	 *
	 * @return  array of column names for current table.
	 */ 
	function &MetaColumnNames($table, $numIndexes=false) 
	{
		$objarr =& $this->MetaColumns($table);
		if (!is_array($objarr)) {
			$false = false;
			return $false;
		}
		$arr = array();
		if ($numIndexes) {
			$i = 0;
			foreach($objarr as $v) $arr[$i++] = $v->name;
		} else
			foreach($objarr as $v) $arr[strtoupper($v->name)] = $v->name;

		return $arr;
	}

}

eval('class mysql_meta_resultset_EXTENDER extends '. $last_module . '_ResultSet { }');

class mysql_meta_ResultSet extends mysql_meta_resultset_EXTENDER
{
	/**
	 * Get the metatype of the column. This is used for formatting. This is because
	 * many databases use different names for the same type, so we transform the original
	 * type to our standardised version which uses 1 character codes:
	 *
	 * @param t  is the type passed in. Normally is ADOFieldObject->type.
	 * @param len is the maximum length of that field. This is because we treat character
	 * 	fields bigger than a certain size as a 'B' (blob).
	 * @param fieldobj is the field object returned by the database driver. Can hold
	 *	additional info (eg. primary_key for mysql).
	 * 
	 * @return the general type of the data: 
	 *	C for character < 250 chars
	 *	X for teXt (>= 250 chars)
	 *	B for Binary
	 * 	N for numeric or floating point
	 *	D for date
	 *	T for timestamp
	 * 	L for logical/Boolean
	 *	I for integer
	 *	R for autoincrement counter/integer
	 * 
	 *
	*/
	function MetaType($t,$len=-1,$fieldobj=false)
	{
		if (is_object($t)) {
			$fieldobj = $t;
			$t = $fieldobj->type;
			$len = $fieldobj->max_length;
		}
		
		$len = -1; // mysql max_length is not accurate
		switch (strtoupper($t)) {
		case 'STRING': 
		case 'CHAR':
		case 'VARCHAR': 
		case 'TINYBLOB': 
		case 'TINYTEXT': 
		case 'ENUM': 
		case 'SET': 
			if ($len <= $this->blobSize) return 'C';
			
		case 'TEXT':
		case 'LONGTEXT': 
		case 'MEDIUMTEXT':
			return 'X';
			
		// php_mysql extension always returns 'blob' even if 'text'
		// so we have to check whether binary...
		case 'IMAGE':
		case 'LONGBLOB': 
		case 'BLOB':
		case 'MEDIUMBLOB':
			return !empty($fieldobj->binary) ? 'B' : 'X';
			
		case 'YEAR':
		case 'DATE': return 'D';
		
		case 'TIME':
		case 'DATETIME':
		case 'TIMESTAMP': return 'T';
		
		case 'INT': 
		case 'INTEGER':
		case 'BIGINT':
		case 'TINYINT':
		case 'MEDIUMINT':
		case 'SMALLINT': 
			
			if (!empty($fieldobj->primary_key)) return 'R';
			else return 'I';
		
		default: return 'N';
		}
	}

}

?>
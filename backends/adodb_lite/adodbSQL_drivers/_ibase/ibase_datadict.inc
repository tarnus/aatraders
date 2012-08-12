<?php
/**
  V4.65 22 July 2005  (c) 2000-2005 John Lim (jlim@natsoft.com.my). All rights reserved.
  Released under both BSD license and Lesser GPL library license. 
  Whenever there is any discrepancy between the two licenses, 
  the BSD license will take precedence.
	
  Set tabs to 4 for best viewing.
  
  Modified 28 August, 2005 for use with ADOdb Lite by Mark Dickenson
  
*/

// security - hide paths
if (!defined('ADODB_DIR')) die();

class ADODB2_ibase extends ADODB_DataDict {

	var $dbtype = 'ibase';
	var $seqField = false;
	
 	
 	function ActualType($meta)
	{
		switch($meta) {
		case 'C': return 'VARCHAR';
		case 'XL':
		case 'X': return 'VARCHAR(4000)'; 
		
		case 'C2': return 'VARCHAR'; // up to 32K
		case 'X2': return 'VARCHAR(4000)';
		
		case 'B': return 'BLOB';
			
		case 'D': return 'DATE';
		case 'T': return 'TIMESTAMP';
		
		case 'L': return 'SMALLINT';
		case 'I': return 'INTEGER';
		case 'I1': return 'SMALLINT';
		case 'I2': return 'SMALLINT';
		case 'I4': return 'INTEGER';
		case 'I8': return 'INTEGER';
		
		case 'F': return 'DOUBLE PRECISION';
		case 'N': return 'DECIMAL';
		default:
			return $meta;
		}
	}

	function AlterColumnSQL($tabname, $flds)
	{
		if ($this->debug) $this->outp("AlterColumnSQL not supported");
		return array();
	}
	
	
	function DropColumnSQL($tabname, $flds)
	{
		if ($this->debug) $this->outp("DropColumnSQL not supported");
		return array();
	}

//	function MetaType($t,$len=-1,$fieldobj=false)
//	{
//	}

//	function &MetaTables($ttype=false,$showSchema=false,$mask=false) 
//	{
//		global $ADODB_FETCH_MODE;
//	}

//	function &MetaColumns($table,$upper=true) 
//	{
//		global $ADODB_FETCH_MODE;
//	}

//	function MetaPrimaryKeys($table, $owner=false)
//	{
//	}

//     function &MetaIndexes($table, $primary = false, $owner = false)
//     {
//     }

}

?>
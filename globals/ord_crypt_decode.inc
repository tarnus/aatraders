<?php
if (!function_exists('ord_crypt_decode')) {

	function ord_crypt_decode($data) {
		$result = '';
		$data =  @pack("H" . strlen($data), $data); 

		for($i=0; $i < strlen($data); $i++) {
			$char = substr($data, $i, 1);
			$keychar = substr(OrdKey, ($i % strlen(OrdKey))-1, 1);
			$char = chr(ord($char)-ord($keychar));
			$result.=$char;
		}
		return $result;
	}
}
?>

<?php
if (!function_exists('ord_crypt_encode')) {

	function ord_crypt_encode($data) {
		$result = '';
		for($i=0; $i < strlen($data); $i++) {
			$char = substr($data, $i, 1);
			$keychar = substr(OrdKey, ($i % strlen(OrdKey))-1, 1);
			$char = chr(ord($char)+ord($keychar));
			$result.=$char;
		}
		return bin2hex($result); 
	}
}
?>

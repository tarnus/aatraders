<?php
if (!function_exists('cleanjs')) {
	function cleanjs($dontkill)
	{
		global $template_object, $cleanjs;
		$cleanjs = "<script language=\"javascript\" type=\"text/javascript\">\n".
			 "function clean_js()\n".
			 "{\n".
			 "// Here we cycle through all form values (other than buy, or full), and regexp out all non-numerics. (1,000 = 1000)\n".
			 "// Then, if its become a null value (type in just a, it would be a blank value. blank is bad.) we set it to zero.\n".
			 "var form = document.forms[0];\n".
			 "var i = form.elements.length;\n".
			 "while (i > 0)\n".
			 " {\n".
			 " if ((form.elements[i-1].type == 'text') && (form.elements[i-1].name != '$dontkill'))\n".
			 "  {\n".
			 "  var tmpval = form.elements[i-1].value.replace(/\D+/g, \"\");\n".
			 "  if (tmpval != form.elements[i-1].value)\n".
			 "   {\n".
			 "   form.elements[i-1].value = form.elements[i-1].value.replace(/\D+/g, \"\");\n".
			 "   }\n".
			 "  }\n".
			 " if (form.elements[i-1].value == '')\n".
			 "  {\n".
			 "  form.elements[i-1].value ='0';\n".
			 "  }\n".
			 " i--;\n".
			 " }\n".
			 "}\n".
			 "</script>\n";
		$template_object->assign("clean_javascript", $cleanjs);
	}
}
?>

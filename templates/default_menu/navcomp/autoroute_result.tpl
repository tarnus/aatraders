{literal}
	<style type="text/css">

body {
	color: #2d2e2e;
	font-family: Arial, Helvetica, sans-serif;
	font-size: 11px;
	line-height: 14px;
	margin: 0 0 0 0; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	padding: 0 0 0 0; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Centers the page content container in IE 5 browsers. */
	background-image: url(templates/{/literal}{$templatename}{literal}images/galactic_arm4.jpg);
}
	h3 {
	margin:0;
	text-align: center;
	color: #000;
    }
	.header {
    	padding:5px 10px;
		background:#ddd;
	}
.rightColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	width: 200px;
	color: #000;
}
.rightBuyColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	width: 200px;
	color: #000;
}
.leftColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.portfooter {
	background-color: #eef6ed;
	border-top: solid 1px #8ab573; /* Sets the top border properties for an element using shorthand notation */
	padding: 10px 10px 10px 10px; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	color: #000;
}
	.inputcss {
		font-family: Verdana, Geneva, sans-serif;
		font-size: 10px;
	}
	table {
		-moz-opacity:0.9;
		filter:alpha(opacity=90);
		opacity:0.9;
	}

 	a:link {
		color: #542764;
	}
	
   </style>

{/literal}

<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="header"><h3>{$title}</h3></td>
  </tr>

</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
{if $part1 == 1}
  <tr>
    <td class="leftBuyColumn" nowrap><b>{$startmovetype} {$sectorstart}</b></td>
    <td class="rightBuyColumn"><b>{$start_result[0]}</b></td>
  </tr>
{/if}
{if $part2 == 1}
	{foreach key=key value=item from=$warp_list_movetype}
  <tr>
    <td class="leftBuyColumn" nowrap>{$warp_list_movetype[$key]} {$warp_list_sector[$key]}</td>
    <td class="rightBuyColumn">{$move_result[$key]}</td>
  </tr>
	{/foreach}
{/if}
{if $part3 == 1}
  <tr>
    <td class="leftBuyColumn" nowrap><b>{$endmovetype} {$endsector}</b></td>
    <td class="rightBuyColumn"><b>{$endmove_result[0]}</b></td>
  </tr>
{/if}
  <tr><td colspan="3" align="center" class="portfooter">
  	<a style="color: #542764;" href="navcomp.php">{$l_autoroute_return}</a>
  	<br><br>{$gotomain}</td></tr>
</table>

</td></tr></table>

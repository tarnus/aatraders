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
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.rightBuyColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
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
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}

.rightColumnMini {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.rightBuyColumnMini {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftBuyColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
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

 	a:link {
		color: #542764;
	}

   </style>

{/literal}

<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
<tr><td colspan="5" align="center" class="portfooter">
<img src="templates/{$templatename}images/planet{$titleimage}.png" alt="" width="100" height="100"><br>{$planetname}</h3><br><br>
	{if $capture == 0}
		<b><u>{$l_planet_notdef}</u></b><BR>
	{else}
		<b><u>{$l_planet_captured}</u></b><BR>
		{if $ownership != ""}
			<b><u>{$ownership}</u></b><BR>
		{/if}
	{/if}
	<BR>
	<a href="planet.php?planet_id={$planet_id}">{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>
	{if $allow_ibank}
		{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
	{/if}
	<A HREF ="bounty.php">{$l_by_placebounty}</A><br>
	<br>
  	{$gotomain}</td></tr>
</table>

<?php require_once('F:\aatrade\aatrade\backends\template_lite\src\plugins\function.html_css_menu.php'); $this->register_function("html_css_menu", "tpl_function_html_css_menu");  require_once('F:\aatrade\aatrade\backends\template_lite\src\plugins\block.strip.php'); $this->register_block("strip", "tpl_block_strip");  require_once('F:\aatrade\aatrade\backends\template_lite\src\plugins\modifier.upper.php'); $this->register_modifier("upper", "tpl_modifier_upper");  require_once('F:\aatrade\aatrade\backends\template_lite\src\plugins\modifier.date.php'); $this->register_modifier("date", "tpl_modifier_date");  require_once('F:\aatrade\aatrade\backends\template_lite\src\plugins\modifier.capitalize.php'); $this->register_modifier("capitalize", "tpl_modifier_capitalize");  /* V2.10 Template Lite 4 January 2007  (c) 2005-2007 Mark Dickenson. All rights reserved. Released LGPL. 2007-07-30 17:53:38 Central Daylight Time */  $this->config_load("test.conf", null, null); ?>
<?php $this->assign('title', "foo"); ?>
<?php $_templatelite_tpl_vars = $this->_vars;
echo $this->_fetch_compile_include("header.tpl", array());
$this->_vars = $_templatelite_tpl_vars;
unset($_templatelite_tpl_vars);
 ?>
<PRE>

<?php $this->assign('foo', "up"); ?>
<?php $this->assign('bar', 0); ?>
01: <?php echo $this->_vars['lala']; ?> (// Array)
02: <?php echo $this->_vars['lala']['up']; ?> (// first entry)
03: <?php echo $this->_vars['lala'][$this->_vars['foo']]; ?> (// first entry)
04: <?php echo $this->_vars['lala'][$this->_confs['blah']]; ?> (// first entry)
05: <?php echo $this->_confs['snah']; ?> (// 0)
06: <?php echo $this->_confs['bold']; ?> (// Array)
07: <?php echo $this->_confs['bold'][0]; ?> (// up)
08: <?php echo $this->_confs['bold'][$this->_vars['bar']]; ?> (// up)
09: <?php echo $this->_confs['bold'][$this->_confs['snah']]; ?> (// up)
10:  *}


<?php if ($this->_confs['bold']): ?><b><?php endif; ?>

Title: <?php echo $this->_run_modifier($this->_confs['title'], 'capitalize', 'plugin', 1); ?>
<?php if ($this->_confs['bold']): ?></b><?php endif; ?>

<?php echo 'this is a block of literal text'; ?>


The current date and time is <?php echo $this->_run_modifier(time(), 'date', 'plugin', 1, "Y-m-d H:i:s"); ?>

The value of global assigned variable $SCRIPT_NAME is <?php echo $_SERVER['SCRIPT_NAME']; ?>

Example of accessing server environment variable SERVER_NAME: <?php echo $_SERVER['SERVER_NAME']; ?>

The value of { $Name } is <b><?php echo $this->_vars['Name']; ?></b>

variable modifier example of { $Name|upper }

<b><?php echo $this->_run_modifier($this->_vars['Name'], 'upper', 'plugin', 1); ?></b>


An example of a foreach loop:

<?php $this->_foreach['test'] = array('total' => count((array)$this->_vars['FirstName']), 'iteration' => 0);
if (count((array)$this->_vars['FirstName'])): foreach ((array)$this->_vars['FirstName'] as $this->_vars['value']): $this->_foreach['test']['iteration']++;
 ?>
<?php echo $this->_vars['value']; ?> 
<?php endforeach; else: ?>
	none
<?php endif; ?>

An example of foreach looped key values:

<?php $this->_foreach['foreach1'] = array('total' => count((array)$this->_vars['contacts']), 'iteration' => 0);
if (count((array)$this->_vars['contacts'])): foreach ((array)$this->_vars['contacts'] as $this->_vars['value']): $this->_foreach['foreach1']['iteration']++;
 ?>
	phone: <?php echo $this->_vars['value']['phone']; ?><br>
	fax: <?php echo $this->_vars['value']['fax']; ?><br>
	cell: <?php echo $this->_vars['value']['cell']; ?><br>
<?php endforeach; endif; ?>
<p>

testing strip tags
<?php $this->_tag_stack[] = array('tpl_block_strip', array()); tpl_block_strip(array(), null, $this); ob_start(); ?>
<table border=0>
	<tr>
		<td>
			<A HREF="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
			<font color="red">This is a  test	 </font>
			</A>
		</td>
	</tr>
</table>
<?php $this->_block_content = ob_get_contents(); ob_end_clean(); $this->_block_content = tpl_block_strip($this->_tag_stack[count($this->_tag_stack) - 1][1], $this->_block_content, $this); echo $this->_block_content; array_pop($this->_tag_stack); ?>

<table>
	<tr>
		<td>
			<?php echo tpl_function_html_css_menu(array('menu_list' => $this->_vars['menu_list'],'menu_list_sub' => $this->_vars['menu_list_sub'],'menu_list_sub_sub' => $this->_vars['menu_list_sub_sub'],'menu_id' => "second"), $this);?>
		</td>
	</tr>
</table>

<table>
	<tr>
		<td>
			<?php echo tpl_function_html_css_menu(array('menu_list' => $this->_vars['menu_list'],'menu_list_sub' => $this->_vars['menu_list_sub'],'menu_list_sub_sub' => $this->_vars['menu_list_sub_sub'],'menu_id' => "first",'enable_vertical' => 1), $this);?>
		</td>
	</tr>
</table>

</PRE>

<?php $this->assign('var', 2); ?>
<?php if (!(1 & $this->_vars['var'])): ?>
	Yes it's even.<br><br>
<?php endif; ?>
<?php $this->assign('var', 3); ?>
<?php if ((1 & $this->_vars['var'])): ?>
	Yes it's odd.<br><br>
<?php endif; ?>
<?php $this->assign('var', 2); ?>
<?php if (!((1 & $this->_vars['var']))): ?>
	No not odd.<br><br>
<?php endif; ?>


<?php $this->assign('var', 8); ?>
<?php if (!($this->_vars['var'] % 4)): ?>
	Yes it is divisible by 4.<br><br>
<?php endif; ?>

<?php $this->assign('var', 8); ?>
<?php if (!(1 & ($this->_vars['var'] / 2))): ?>
	Yes it is even by 2.<br><br>
<?php endif; ?>

<?php $this->assign('var', 6); ?>
<?php if (!(1 & ($this->_vars['var'] / 3))): ?>
 Yes it is even by 3.<br><br>
<?php endif; ?>
<?php $_templatelite_tpl_vars = $this->_vars;
echo $this->_fetch_compile_include("footer.tpl", array());
$this->_vars = $_templatelite_tpl_vars;
unset($_templatelite_tpl_vars);
 ?>

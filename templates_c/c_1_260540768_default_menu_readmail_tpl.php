<?php require_once('/home/aatrade_current/backends/template_lite/src/plugins/function.math.php'); $this->register_function("math", "tpl_function_math");  /* V2.10 Template Lite 4 January 2007  (c) 2005-2007 Mark Dickenson. All rights reserved. Released LGPL. 2013-06-22 21:39:51 CDT */ ?>
<H1><?php echo $this->_vars['title']; ?></H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr>
	  <td width="100%">
		<div align="center">
		  <center>
		  <table border="0" cellspacing="1" width="100%">
			<tr>
			  <td width="100%" bgcolor="black" colspan="2">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%" bordercolorlight="black" bordercolordark="silver">
					<tr>
					  <td width="75%" align="left"><font color="white" size="2"><b><?php echo $this->_vars['l_readm_center']; ?></b></font></td>
					  <td width="21%" align="center" nowrap><font color="white" size="2"><?php echo $this->_vars['cur_D']; ?>&nbsp;<?php echo $this->_vars['cur_T']; ?></font></td>
					  <td width="4%" align="center" ><A HREF="main.php"><img alt="<?php echo $this->_vars['l_readm_return']; ?>" src="templates/<?php echo $this->_vars['templatename']; ?>images/c95x.png" width="16" height="14" border="0"></a></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>
<?php if ($this->_vars['totalpages'] > 1): ?>
			<tr>
			  <td width="100%" bgcolor="black" colspan="2">
	<TABLE border=0 cellpadding=2 cellspacing=1 width="100%">
	<form action="message_read.php" method="post">
	<TR>
		<td align="left" width="33%">
			<?php if ($this->_vars['currentpage'] != 1): ?>
				<a href="message_read.php?page=<?php echo $this->_vars['previouspage']; ?>"><?php echo $this->_vars['l_common_prev']; ?></a>
			<?php else: ?>
				&nbsp;
			<?php endif; ?>
		</td>
		<TD align='center' width="33%">
	<?php echo tpl_function_math(array('equation' => "x + y",'x' => 1,'y' => $this->_vars['totalpages'],'assign' => "forpages"), $this);?>
	<?php echo $this->_vars['l_common_selectpage']; ?> <select name="page">
	<?php for($for1 = 1; ((1 < $this->_vars['forpages']) ? ($for1 < $this->_vars['forpages']) : ($for1 > $this->_vars['forpages'])); $for1 += ((1 < $this->_vars['forpages']) ? 1 : -1)):  $this->assign('i', $for1); ?>
		<option value="<?php echo $this->_vars['i']; ?>"
		<?php if ($this->_vars['currentpage'] == $this->_vars['i']): ?>
			selected
		<?php endif; ?>
		> <?php echo $this->_vars['l_common_page']; ?> <?php echo $this->_vars['i']; ?> </option>
	<?php endfor; ?>
	</select>
	&nbsp;<input type="submit" value="<?php echo $this->_vars['l_submit']; ?>">
	</TD>
		<td align="right" width="33%">
			<?php if ($this->_vars['currentpage'] != $this->_vars['totalpages']): ?>
				<a href="message_read.php?page=<?php echo $this->_vars['nextpage']; ?>"><?php echo $this->_vars['l_common_next']; ?></a>
			<?php else: ?>
				&nbsp;
			<?php endif; ?>
		</td>
	</tr>
	</form>
	</table>
			  </td>
			</tr>
<?php endif; ?>
			<?php if ($this->_vars['nomessages'] == 1): ?>
			<tr>
			  <td width="100%" bgcolor="black" bordercolorlight="black" bordercolordark="silver" colspan="2">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%"  bordercolorlight="black" bordercolordark="silver">
					<tr>
					  <td width="100%" align="center"><font color="red"><?php echo $this->_vars['l_readm_nomessage']; ?></font></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>
			<?php else: ?>
			<?php extract($this->_vars, EXTR_REFS);  
			for($i = 0; $i < $messagecount; $i++){
			echo "<tr>";
			echo "  <td width=\"100%\" align=\"center\" bgcolor=\"black\" height=\"4\" colspan=\"2\"></td>";
			echo "</tr>";
			echo "<tr>";
            echo "  <td rowspan=\"3\" width= \"64\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\" valign=\"middle\" align=\"center\"><img src=\"images/avatars/$avatar[$i]\"></td>";
			echo "  <td width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bgcolor=\"black\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"20%\" height=\"19\"><font color=\"white\" size=\"2\"><b>$l_readm_sender</b></td>";
			echo "		  <td width=\"55%\" height=\"19\"><font color=\"yellow\" size=\"2\">$sender[$i]</font></td>";
			echo "		  <td width=\"21%\" height=\"19\" align=\"center\"><font color=\"white\" size=\"2\">$msgsent[$i]</font></td>";
			echo "		  <td width=\"4%\" height=\"19\" align=\"center\" bordercolorlight=\"black\" bordercolordark=\"black\"><A class=\"but\" HREF=\"message_read.php?action=delete&ID=$msgid[$i]\"><img src=\"templates/$templatename/images/c95x.png\" width=\"16\" height=\"14\" border=\"0\"></a></td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bgcolor=\"black\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"20%\" height=\"19\"><font color=\"white\" size=\"2\"><b>$l_readm_captn</b></font></td>";
			echo "		  <td width=\"80%\" height=\"19\"><font color=\"yellow\" size=\"2\">$sendname[$i]</font></td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bgcolor=\"black\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"20%\" height=\"19\"><font color=\"white\" size=\"2\"><b>$l_readm_subject</b></font></td>";
			echo "		  <td width=\"80%\" height=\"19\"><b><font color=\"yellow\" size=\"2\">$subject[$i]</font></b></td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td colspan=\"2\" width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bgcolor=\"white\" bordercolorlight=\"black\" bordercolordark=\"silver\">";
			echo "		<tr>";
			echo "		  <td width=\"100%\"><font color=\"black\" size=\"2\">$message[$i]</font></td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td colspan=\"2\" width=\"100%\" align=\"center\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\" bordercolordark=\"silver\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"100%\" align=\"center\" valign=\"middle\"><A class=\"but\" HREF=\"message_read.php?action=delete&ID=$msgid[$i]\">$l_readm_del</A> |";
			if($senderid[$i] != 0){
			if($senderid[$i] > 3)
				echo "				<A class=\"but\" HREF=\"message_read.php?name=$senderid[$i]&msgid=$msgid[$i]&action=block\">$l_readm_block</A> |";
			echo "				<A class=\"but\" HREF=\"message_send.php?name=$senderid[$i]&msgid=$msgid[$i]&quote=0\">$l_readm_repl</A> |";
			echo "				<A class=\"but\" HREF=\"message_send.php?name=$senderid[$i]&msgid=$msgid[$i]&quote=1\">$l_readm_quote</A>";
			}
			echo "		  </td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			}
			 ?>
			<?php endif; ?>
			<tr>
			  <td colspan="2" width="100%" align="center" bgcolor="black" height="4"></td>
			</tr>
			<tr>
			  <td colspan="2" width="100%" align="center" bgcolor="#000000" height="4">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%" bgcolor="#000000" bordercolorlight="#000000" bordercolordark="#C0C0C0" height="8">
					<tr>
					  <td width="50%"><p align="left"><font color="#FFFFFF" size="2"><?php echo $this->_vars['l_readm_title2']; ?></font></td>
					  <td width="50%"><p align="right"><font color="#FFFFFF" size="2"><A class="but" HREF="message_read.php?action=delete_all"><?php echo $this->_vars['l_readm_delete']; ?></a></font></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>

		  </table>
		  </center>
		</div>
	  </td>
	</tr>

<tr><td><br><br><?php echo $this->_vars['gotomain']; ?><br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

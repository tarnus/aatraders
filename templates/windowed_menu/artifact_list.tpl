<H1>{$title}</H1>

<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
	<tr>
		<td bgcolor="#000000" valign="top" align="center" colspan=2>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td>
						<table border=1 cellspacing=0 cellpadding=5 width="100%" align=center>
							<tr bgcolor="#585980">
								<td align='center'><font color=white><B>{$l_artifact_imagename}</b></font></td>
								<td align='center'><font color=white><B>{$l_artifact_classname}</b></font></td>
								<td align='center'><font color=white><B>{$l_artifact_description}</b></font></td>
								<td align='center'><font color=white><B>{$l_artifact_incomplete}</b></font></td>
							</tr>
							{foreach key=key value=item from=$classname}
								<tr bgcolor=#000000>
									<td align='center'><font color="#ffffff"><b><img src="images/artifacts/{$imagename[$key]}.gif" border=0></b></font></td>
									<td align='center'><font color="#ffffff"><b>{$classname[$key]}</b></font></td>
									<td align='left'><font color="#ffffff"><b>{$description[$key]}</b></font></td>
									{if $completed[$key] == 1 && $delayedprocess[$key] == 1}
										<td align='center'><font color="#ffffff"><b><a href="artifact_process.php?artifact={$class[$key]}">{$l_artifact_process}</a></b></font></td>
									{else}
										<td align='center'><font color="#ffffff"><b>{$incomplete[$key]}</b></font></td>
									{/if}
								</tr>
							{/foreach}
						</table>
					</td>
				</tr>
				<tr>
					<td>
						<br><br>{$gotomain}<br><br>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>



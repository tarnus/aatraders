<H1>{$title}</H1>

<table width="750" border="0" cellspacing="0" cellpadding="0" align="center" bgcolor="#1A640F">

<tr>
	<td colspan="3" valign="middle"><table align="center" width="80%"><tr><td align="center" valign="middle"><FONT color="White" size="+1"><b>{if $status=="DealerWin" || $status == "Bust" || $status == "SBust"}
{$l_dealerwins}
{elseif $status=="DealerBust"}
{$l_dealerbust}
{elseif $status=="Push"}
{$l_push}
{elseif $status=="DealerBlackJack"}
{$l_dealerblackjack}
{/if}
{if $status=="SDealerWin"}
{$l_dealerwins}
{elseif $status=="SDealerBust"}
{$l_dealerbust}
{elseif $status=="SPush"}
{$l_push}
{elseif $status=="SDealerBlackJack"}
{$l_dealerblackjack}
{elseif $status=="PlayerWin" || $status=="PlayerBlackJack" || $status=="PlayerBlackJackIns" || $status=="SPlayerWin" || $status=="SPlayerBlackJack"}
{$l_dealerloses}

{/if}</b></font></td><td valign="middle" align="center"><table border="1" cellspacing="1"  bgcolor="#1A640F" bordercolorlight="black" bordercolordark="silver" cellpadding="0" align="center">
<tr>
<td ><font color="white"><b>Credits</b></FONT></td><td><font color="white"><b>{$cash}</b></FONT></td>
</tr>
<tr>
<td ><font color="white"><b>Bet</b></FONT></td><td><font color="white"><b>{$bet}</b></FONT></td>
</tr>
</table></td><td align="center" valign="middle"><FONT color="White" size="+1"><b>
{if $status == "Bust"}
{$l_playerbust}
{elseif $status=="PlayerWin" || $status=="DealerBust" || $status=="SDealerBust"}
{$l_playerwins}
{elseif $status=="PlayerBlackJack" || $status=="PlayerBlackJackIns"}
{$l_playerblackjack}
{elseif $status=="Push"}
{$l_push}
{elseif $status == "SBust"}
{$l_playerbust}
{elseif $status=="SPlayerWin"}
{$l_playerwins}
{elseif $status=="SPlayerBlackJack"}
{$l_playerblackjack}
{elseif $status=="SPush"}
{$l_push}
{elseif $status=="DealerWin" || $status=="DealerBlackJack" || $status=="SDealerWin" || $status=="SDealerBlackJack"}
{$l_playerloses}
{/if}</b></font></td></tr></TABLE>
</td>
</tr>
  <tr> 
    <td  align="center" rowspan="2" bgcolor="#1A640F" valign="top"><img src="templates/{$templatename}/images/casino/spacer.gif" width="114" height="5"><br>

<table border="1" cellspacing="1" width="80" bgcolor="#1A640F" bordercolorlight="black" bordercolordark="silver" cellpadding="0" align="center">
{if $hand==0 && $split_flag==2}
<tr>
<td align="center"><font color="white"><b>{$l_firsthand}</b></FONT></td>
</tr>
{elseif $hand==1 && $split_flag==2}
<tr>
<td align="center"><font color="white"><b>{$l_secondhand}</b></FONT></td>
</tr>

{/if}

{if $hand==0}
{if $status == "Bust" || $status == "" || $status == "DealerWin"|| $status == "PlayerWin" || $status == "DealerBust" || $status == "Push" || $status == "PlayerBlackJack" || $status == "DealerBlackJack" || $status == "PlayerBlackJackIns" || $status == "Bet" || $status == "no bet" && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Bet">{$l_bet}</a></td>
</tr>

{elseif $status == "Insurance"}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Insurance">{$l_insurance}</a></td>
</tr>
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Hit">{$l_hit}</a></td>
</tr>
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Stand">{$l_stand}</a></td>
</tr>

	{if $playercards==2 && $split_flag==0}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=DoubleD">{$l_doubledown}</a></td>
</tr>	

	{/if}
{else}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Hit">{$l_hit}</a></td>
</tr>
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Stand">{$l_stand}</a></td>
</tr>

	{if $playercards==2 && $split_flag==0 && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=DoubleD">{$l_doubledown}</a></td>
</tr>	

	{/if}
{/if}
{else}
{if $status == "SBust" || $status == "" || $status == "SDealerWin"|| $status == "SPlayerWin" || $status == "SDealerBust" || $status == "SPush" || $status == "SPlayerBlackJack" || $status == "SDealerBlackJack" || $status == "SPlayerBlackJackIns" || $status == "Bet" && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Bet">{$l_bet}</a></td>
</tr>

{elseif $status == "SInsurance" && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Insurance&hand=1">{$l_insurance}</a></td>
</tr>
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Hit&hand=1">{$l_hit}</a></td>
</tr>
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Stand&hand=1">{$l_stand}</a></td>
</tr>

	{if $playercards==2 && $split_flag==0 && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=DoubleD&hand=1">{$l_doubledown}</a></td>
</tr>	

	{/if}
{else}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Hit&hand=1">{$l_hit}</a></td>
</tr>	
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Stand&hand=1">{$l_stand}</a></td>
</tr>

	{if $playercards==2 && $split_flag==0 && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=DoubleD&hand=1">{$l_doubledown}</a></td>
</tr>	
	{/if}
{/if}
{/if}

{if $split_flag == 1 && $availcash==1}
<tr>
<td align="center"><a href="casino.php?casinogame=casino_blackjack&action=Split">{$l_split}</a></td>
</tr>

{/if}
<tr>
<td align="center"><a href="port.php">{$l_lobby}</a></td>
</tr>
</table>
</td>
    <td background="templates/{$templatename}/images/casino/blackjack/bjtop2.jpg" align="center" valign="middle"><img src="templates/{$templatename}/images/casino/spacer.gif" width="522" height="1">
    <TABLE cellpadding="0" cellspacing="0" border="0" align="center">
    	<tr>
    		<td align="center"><font color="White"><b>
</td
    	</tr>    
    	<tr>
    		<td align="center">
{if $status != "Bet"}
{$dealerout}
{/if}</td
    	</tr>
    </table>

</td>
    <td><img src="templates/{$templatename}/images/casino/blackjack/bjtop3.jpg" width="114" height="146"></td>
  </tr>
  <tr> 

    <td background="templates/{$templatename}/images/casino/blackjack/bjmid2.jpg" align="center" valign="middle"><img src="templates/{$templatename}/images/casino/spacer.gif" width="522" height="1"><br>
    <TABLE align="center"><tr><td>
{if $status != "Bet"}
{$playerout}
{/if}
</td></tr>
<tr>
<td align="center"><FONT color="White" ><b>
{if $status == "Bust"}
{$l_playerbust}
{elseif $status=="PlayerWin" || $status=="DealerBust" }
{$l_playerwins}
{elseif $status=="PlayerBlackJack" || $status=="PlayerBlackJackIns"}
{$l_playerblackjack}
{elseif $status=="Push"}
{$l_push}
{elseif $status=="DealerWin" || $status=="DealerBlackJack" }
{$l_playerloses}
{/if}</B></FONT>
</td>
</tr>
{if $status == "Bet"}<tr><td colspan="3" align="center"><br>
<center><form action="casino.php" method="post">
					<input type="Hidden" name="casinogame" value="casino_blackjack">
	<font color="White"><b>{$l_place_bet}: <input type="text" name="bet_amt" width="10" size="10" value="{$old_bet}">
					<input type="Hidden" name="action" value="Deal">
					<input type="Submit" value="Bet">
</form></b></font></center></td></tr>{elseif $status=="no bet"}
<tr><td colspan="3" align="center"><br><font color="White"><b>{$l_nobet}</b></font></center></td></tr>{/if}</TABLE>   

</td>
    <td><img src="templates/{$templatename}/images/casino/blackjack/bjmid3.gif" width="114" height="141"></td>
  </tr>
  <tr  bgcolor="#1A640F"> 
    <td><img src="templates/{$templatename}/images/casino/blackjack/bjlow1.gif" width="114" height="120"></td>
    <td> <TABLE align="center"><tr><td>
{if $split_flag==2 || $hand==1}
{$playersplitout}
{/if}
</td></tr>
<tr>
<td align="center"><FONT color="White" ><b>
{if $status == "SBust"}
{$l_playerbust}
{elseif $status=="SPlayerWin" ||  $status=="SDealerBust"}
{$l_playerwins}
{elseif $status=="SPlayerBlackJack"}
{$l_playerblackjack}
{elseif $status=="SPush"}
{$l_push}
{elseif $status=="SDealerWin" || $status=="SDealerBlackJack" }
{$l_playerloses}
{/if}</B></FONT>
</td>
</tr>
</TABLE></td>
    <td><img src="templates/{$templatename}/images/casino/blackjack/bjlow3.gif" width="114" height="120"></td>
  </tr>

</table>


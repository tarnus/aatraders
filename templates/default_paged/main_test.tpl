{* $Id: main.tpl,v 1.11 2004/07/12 14:17:41 svowl Exp $ *}
{include file="page_title.tpl" title=$lng.lbl_welcome_to_admin_area}

{if $current_passwords_security or $default_passwords_security}

{capture name=dialog}

{if $current_passwords_security}
{$lng.txt_your_password_insecured}
<BR><BR>
{if $active_modules.Simple_Mode}
<DIV align="right">{include file="buttons/button.tpl" button_title=$lng.lbl_modify_profile href="`$catalogs.provider`/register.php?mode=update" title=$lng.lbl_modify_profile}</DIV>
{else}
<DIV align="right">{include file="buttons/button.tpl" button_title=$lng.lbl_modify_profile href="register.php?mode=update" title=$lng.lbl_modify_profile}</DIV>
{/if}
<BR><BR>
{/if}

{if $default_passwords_security}
{capture name=accounts}
{section name=acc loop=$default_passwords_security}
{if $default_passwords_security[acc] ne $current_passwords_security.0}
{assign var="display_default_passwords_security" value="1"}
&nbsp;&nbsp;&nbsp;{$default_passwords_security[acc]}<BR>
{/if}
{/section}
{/capture}
{if $display_default_passwords_security}
{$lng.txt_default_passwords_insecured|substitute:"accounts":$smarty.capture.accounts}
<BR><BR>
<DIV align="right">{include file="buttons/button.tpl" button_title=$lng.lbl_users_management href="users.php" title=$lng.lbl_users_management}</DIV>
{/if}
{/if}

{/capture}
{include file="dialog_message.tpl" title=$lng.lbl_password_security_warning alt_content=$smarty.capture.dialog extra="width=100%"}

{/if}

<!-- IN THIS SECTION -->

{include file="dialog_tools.tpl"}

<!-- IN THIS SECTION -->

<BR>

{$lng.txt_top_info_text}

<BR><BR>

<!-- QUICK MENU -->

{include file="main/quick_menu.tpl"}

<!-- QUICK MENU -->

<A name="orders"/>
{capture name=dialog}

{$lng.txt_top_info_orders}

<BR><BR>

<DIV align="center">
<TABLE border="0" cellpadding="0" cellspacing="0" width="90%">
<TR>
<TD class="TableHead">
<TABLE border="0" cellpadding="3" cellspacing="1" width="100%">

<TR class="TableHead">
<TD>{$lng.lbl_status}</TD>
<TD nowrap align="center">{$lng.lbl_since_last_log_in}</TD>
<TD align="center">{$lng.lbl_today}</TD>
<TD nowrap align="center">{$lng.lbl_this_week}</TD>
<TD nowrap align="center">{$lng.lbl_this_month}</TD>
</TR>

{foreach key=key item=item from=$orders}
<TR{cycle values=" class='DialogBox', class='TableSubHead'"}>
<TD nowrap>{if $key eq "P"}{$lng.lbl_processed}{elseif $key eq "Q"}{$lng.lbl_queued}{elseif $key eq "F" or $key eq "D"}{$lng.lbl_failed}/{$lng.lbl_declined}{elseif $key eq "I"}{$lng.lbl_not_finished}{/if}:</TD>
{section name=period loop=$item}
<TD align="center">{$item[period]}</TD>
{/section}
</TR>
{/foreach}

<TR{cycle values=" class='DialogBox', class='TableSubHead'"}>
<TD align="right"><B>{$lng.lbl_gross_total}:</B></TD>
{section name=period loop=$gross_total}
<TD align="center">{include file="currency.tpl" value=$gross_total[period]}</TD>
{/section} 
</TR>

<TR{cycle values=" class='DialogBox', class='TableSubHead'"}>
<TD align="right"><B>{$lng.lbl_total_paid}:</B></TD>
{section name=period loop=$total_paid}
<TD align="center">{include file="currency.tpl" value=$total_paid[period]}</TD>
{/section}
</TR>

</TABLE>
</TD>
</TR>
</TABLE>
</DIV>

<BR><BR>

<DIV align="right">{include file="buttons/button.tpl" button_title=$lng.lbl_search_orders href="orders.php" title=$lng.lbl_search_orders}</DIV>

{if $last_order}
<BR><BR>

{include file="main/subheader.tpl" title=$lng.lbl_last_order}

<TABLE border="0" cellpadding="3" cellspacing="1" width="100%">

<TR>
<TD>&nbsp;&nbsp;</TD>
<TD>
<TABLE border="0" cellpadding="3" cellspacing="1">

<TR>
<TD class="FormButton">{$lng.lbl_order_id}:</TD>
<TD>#{$last_order.orderid}</TD>
</TR>

<TR>
<TD class="FormButton">{$lng.lbl_order_date}:</TD>
<TD>{$last_order.date|date_format:$config.Appearance.datetime_format}</TD>
</TR>

<TR>
<TD class="FormButton">{$lng.lbl_order_status}:</TD>
<TD>{include file="main/order_status.tpl" status=$last_order.status mode="static"}</TD>
</TR>

<TR>
<TD class="FormButton">{$lng.lbl_customer}:</TD>
<TD>{$last_order.title} {$last_order.firstname} {$last_order.lastname}</TD>
</TR>

<TR>
<TD class="FormButton" valign="top">{$lng.lbl_ordered}:</TD>
<TD>
{if $last_order.products}
{section name=product loop=$last_order.products}
<B>{$last_order.products[product].product|truncate:"30":"..."}</B>
[{$lng.lbl_price}: {include file="currency.tpl" value=$last_order.products[product].price}, {$lng.lbl_amount}: {$last_order.products[product].amount}]
{if $last_order.products[product].product_options}
<BR>
{$lng.lbl_options}: {$last_order.products[product].product_options|replace:"\n":"; "}
{/if}
<BR>
{/section}
{/if}
{if $last_order.giftcerts}
{section name=gc loop=$last_order.giftcerts}
<B>{$lng.lbl_gift_certificate} #{$last_order.giftcerts[gc].gcid}</B>
[{$lng.lbl_price}: {include file="currency.tpl" value=$last_order.giftcerts[gc].amount}]
<BR>
{/section}
{/if}
</TD>
</TR>

</TABLE>
</TD>
</TR>

</TABLE>

<BR>

<DIV align="right">{include file="buttons/button.tpl" button_title=$lng.lbl_order_details_label href="order.php?orderid=`$last_order.orderid`" title=$lng.lbl_order_details_label}</DIV>

{/if}



{/capture}
{include file="dialog.tpl" title=$lng.lbl_orders_info content=$smarty.capture.dialog extra="width=100%"}

<BR><BR>

<A name="topsellers"/>
{capture name=dialog}

{$lng.txt_top_info_top_sellers}

<BR><BR>

<DIV class="TopLabel" align="center">{$lng.lbl_top_N_products|substitute:"N":$max_top_sellers}</DIV>

<BR>

<TABLE border="0" cellpadding="0" cellspacing="0" width="100%">
<TR>
<TD class="TableHead">
<TABLE border="0" cellpadding="3" cellspacing="1" width="100%">

<TR class="TableHead">
<TD width="25%" nowrap align="center">{$lng.lbl_since_last_log_in}</TD>
<TD width="25%" nowrap align="center">{$lng.lbl_today}</TD>
<TD width="25%" nowrap align="center">{$lng.lbl_this_week}</TD>
<TD width="25%" nowrap align="center">{$lng.lbl_this_month}</TD>
</TR>

{capture name=top_products}
<TR class="DialogBox">
{foreach key=key item=item from=$top_sellers}
<TD align="center"{if $item} valign="top"{/if}>
{if $item}
{assign var="is_top_products" value="1"}
<TABLE border="0" cellpadding="2" cellspacing="1" width="100%">
{section name=period loop=$item}
<TR{cycle name=col`%period.index%` values=", class='TableSubHead'"}>
<TD>{math equation="x+1" x=%period.index%}.</TD>
<TD><A href="product_modify.php?productid={$item[period].productid}">{$item[period].product|truncate:"20":"..."}</A></TD>
<TD>{$item[period].count}</TD>
</TR>
{/section}
</TABLE>
{else}
{$lng.txt_no_top_products_statistics}
{/if}
</TD>
{/foreach}
</TR>
{/capture}

{if $is_top_products}

{$smarty.capture.top_products}

</TABLE>
</TD>
</TR>
</TABLE>

<BR>

<DIV class="TopLabel" align="center">{$lng.lbl_top_N_categories|substitute:"N":$max_top_sellers}</DIV>

<BR>

<TABLE border="0" cellpadding="0" cellspacing="0" width="100%">
<TR>
<TD class="TableHead">
<TABLE border="0" cellpadding="3" cellspacing="1" width="100%">

<TR class="TableHead">
<TD width="25%" nowrap align="center">{$lng.lbl_since_last_log_in}</TD>
<TD width="25%" nowrap align="center">{$lng.lbl_today}</TD>
<TD width="25%" nowrap align="center">{$lng.lbl_this_week}</TD>
<TD width="25%" nowrap align="center">{$lng.lbl_this_month}</TD>
</TR>

<TR class="DialogBox">
{foreach key=key item=item from=$top_categories}
<TD align="center"{if $item} valign="top"{/if}>
{if $item}
<TABLE border="0" cellpadding="2" cellspacing="1" width="100%">
{section name=period loop=$item}
<TR{cycle name=col`%period.index%` values=", class='TableSubHead'"}>
<TD>{math equation="x+1" x=%period.index%}.</TD>
<TD><A href="category_modify.php?cat={$item[period].categoryid}">{$item[period].category}</A></TD>
<TD>{$item[period].count}</TD>
</TR>
{/section}
</TABLE>
{else}
{$lng.txt_no_top_categories_statistics}
{/if}
</TD>
{/foreach}
</TR>

{else}

<TR class="DialogBox">
<TD colspan="4" align="center">{$lng.txt_no_statistics}</TD>
</TR>

{/if}

</TABLE>
</TD>
</TR>
</TABLE>

<BR><BR>

<DIV align="right">{include file="buttons/button.tpl" button_title=$lng.lbl_search_orders href="orders.php" title=$lng.lbl_search_orders}{$lng.txt_how_setup_store_bottom}</DIV>

{/capture}
{include file="dialog.tpl" title=$lng.lbl_top_sellers content=$smarty.capture.dialog extra="width=100%"}


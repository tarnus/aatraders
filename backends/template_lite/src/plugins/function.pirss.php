<?
#Powerweb
#Powerweb (c)2006 by Jan Czarnowski	(piratos@coftware.de)
#This project's homepage is: http://piratos.byethost33.com
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
#GNU General Public License for more details.
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA	02111-1307	USA

/* Input:
 *			- url = Url to pull RSS feed.  Include http:// or hrrps://
 *			- assign = Variable to assign RSS array data to be processed by the template
 *			- encoding = Optional encoding method
 *			- maxnews = Optional maximum number of news items to retrieve.  Default is 10 news items.
 *
 * Data is stored in the following array elements:
 *			- pirsslink = Contains url link to news item
 *			- pirsstitle = News item title
 *			- pirssdescription = Description of news item
 *			- pirsscontent = Body of news item
 *
 * Modified by Mark Dickenson 20 July 2007 to allow template creator to useful
 * any display formatting desired for the information.
 */


function tpl_function_pirss($params, &$tpl)
{

	if (!isset($params['url'])) {
		$tpl->trigger_error("html_table: missing 'url' parameter");
		return;
	}
	else
	{
		$url = $params['url'];
	}

	if (!isset($params['assign'])) {
		$tpl->trigger_error("html_table: missing 'assign' parameter");
		return;
	}
	else
	{
		$assign = $params['assign'];
	}

	$encoding = isset($params['encoding']) ? $params['endcoding'] : '';
	$max_news = isset($params['maxnews']) ? $params['maxnews'] : 10;

	$data = implode('', @file($url));
	$outar=array();
	$io=-1;
	if ($data)
	{
		if ($encoding && function_exists('mb_convert_encoding'))
		{
			$data = mb_convert_encoding($data, $encoding, 'auto');
		}
		$data=str_replace('<![CDATA[','',$data);
		$data=str_replace(']]>','',$data);
		$item='<item>';
		$v=0;
		$tp1=strpos($data,$item);
		if (!$tp1)
		{
			$item='<item ';
			$tp1=strpos($data,$item);
			$v=1;
		}
		$tp1e=strpos($data,'</item>',$tp1);
		$m=0;
		while ($tp1 and $tp1e and $m<$max_news)
		{
			$beschreibung="";
			$link="";
			$titel="";
			$content="";
			$m++;
			$tp1=$tp1+strlen($item);
			$tp2=strpos($data,'<title>',$tp1)+7;
			$tp3=strpos($data,'</title>',$tp2);
			$titel=substr($data,$tp2,$tp3-$tp2);
			$ts1=strpos($data,'<link>',$tp1);
			if ($ts1==false)
			{
				$ts1=strpos($data,'<guid ',$tp1);
				if (!ts1==false)
				{
					while ($data[$ts1]<>'>' && $ts1<$al)
					{
						$ts1++;
					}
					$ts1++;
					$ts2=strpos($data,'</guid>',$ts1);
					$link=substr($data,$ts1,$ts2-$ts1);
				}
			}
			else
			{
				$ts1=$ts1+6;
				$ts2=strpos($data,'</link>',$ts1);
				$link=substr($data,$ts1,$ts2-$ts1);
			}
			$ts1=strpos($data,'<description>',$tp1);
			if ($ts1 and ($ts1<$tp1e))
			{
				$ts1=$ts1+13;
				$ts2=strpos($data,'</description>',$ts1);
				if ($ts2<$tp1e)
				{
					$beschreibung=substr($data,$ts1,$ts2-$ts1);
				}
			}
			$ts1=strpos($data,'<content:encoded>',$tp1);
			if ($ts1 and ($ts1<$tp1e))
			{
				$ts1=$ts1+17;
				$ts2=strpos($data,'</content:encoded>',$ts1);
				if ($ts2<$tp1e)
				{
					$content=substr($data,$ts1,$ts2-$ts1);
				}
			}
			$io++;
			$outar[$io]['pirsslink']=$link;
			$outar[$io]['pirsstitle']=$titel;
			$outar[$io]['pirssdescription']=html_entity_decode($beschreibung);
			$outar[$io]['pirsscontent']=$content;
			$data2=substr($data,$tp1e+strlen($item));
			$data=$data2;
			$tp1=strpos($data,$item);
			$tp1e=strpos($data,'</item>',$tp1);
		}
		$tpl->assign_by_ref($assign, $outar);
	}
}
?>
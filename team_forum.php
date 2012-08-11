<?php
include("config/config.php");
include ("languages/$langdir/lang_readmail.inc");
include ("languages/$langdir/lang_mailto2.inc");
include("languages/$langdir/lang_teams.inc");
include("languages/$langdir/lang_forums.inc");
include ("globals/clean_words.inc");

get_post_ifset("command, post_id, topic_id, topicmessage, topictitle, sticky");

$title=$l_forums_titlemain;

if (checklogin()) {
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if ((!isset($command)) || ($command == ''))
{
$command = 'showtopics';
}

$time = date("Y-m-d H:i:s");

/* Get user info */
$result		= $db->SelectLimit("SELECT {$db_prefix}players.*, {$db_prefix}teams.team_name, {$db_prefix}teams.description, {$db_prefix}teams.creator, {$db_prefix}teams.id
						FROM {$db_prefix}players
						LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team = {$db_prefix}teams.id
						WHERE {$db_prefix}players.player_id=$playerinfo[player_id]", 1);
$playerinfo	= $result->fields;

/*
   Get Team Info
*/
$result_team   = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
$team		  = $result_team->fields;

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

if($playerinfo['team'] != 0){
		$result = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
		$whichteam = $result->fields;
		$isowner = ($playerinfo['player_id'] == $whichteam['creator']);

	if($command == "showtopics"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$debug_query = $db->Execute("select * from {$db_prefix}team_forum_topics where forum_id=$forumdata[forum_id] order by topic_status desc,lastpostdate desc");
		db_op_result($debug_query,__LINE__,__FILE__);
		$reccount = $debug_query->RecordCount();

		$template_object->assign("forumname", $forumdata['forum_name']);
		$template_object->assign("l_forums_title", $l_forums_title);
		$template_object->assign("l_forums_topics", $l_forums_topics);
		$template_object->assign("reccount", $reccount);
		$template_object->assign("l_forums_date", $l_forums_date);
		$template_object->assign("showdate", date($local_date_full_format, strtotime($time)));
		$template_object->assign("templatename", $templatename);
		$template_object->assign("istopics", ($debug_query && $reccount > 0));

		if ($debug_query && $reccount > 0){
			$template_object->assign("l_forums_topic2", $l_forums_topic2);
			$template_object->assign("l_forums_author", $l_forums_author);
			$template_object->assign("l_forums_date2", $l_forums_date2);
			$template_object->assign("l_forums_posts", $l_forums_posts);
			$template_object->assign("l_forums_new", $l_forums_new);
			$template_object->assign("l_forums_views", $l_forums_views);
			$count = 0;
			while (!$debug_query->EOF){
				$topicinfo = $debug_query->fields;

				$topictype = "";
				if($topicinfo['topic_status'] == 9)
					$topictype = $l_forums_sticky;

				if($topicinfo['topic_status'] == 0)
					$topictype = $l_forums_locked;

				$query2 = $db->Execute("select * from {$db_prefix}team_forum_posts where topic_id=$topicinfo[topic_id] order by post_time");
				db_op_result($query2,__LINE__,__FILE__);
				$num2 = $query2->RecordCount();

				if($num2 > 0){
					$post_player_id = $query2->fields['post_player_id'];
				}

				$query3 = $db->Execute("select * from {$db_prefix}team_forum_players where player_id='$post_player_id'");
				db_op_result($query3,__LINE__,__FILE__);
				$admins = $query3->RecordCount();

				if($admins > 0) {
					$admin = $query3->fields['admin'];
				}

				$accounttype = "";
				if($admin==1)
					$accounttype = $l_forums_coord;
				if($admin==2)
					$accounttype = $l_forums_admin;

				$query2 = $db->Execute("select * from {$db_prefix}team_forum_posts where topic_id=$topicinfo[topic_id] and post_time>='$forumplayer[lastonline]' order by post_time");
				db_op_result($query2,__LINE__,__FILE__);
				$newposts = $query2->RecordCount();
				$post_id = $query2->fields['post_id'];

				if(!isset($post_id))
					$post_id=0;

				$query2 = $db->Execute("select * from {$db_prefix}team_forum_posts where topic_id=$topicinfo[topic_id] and post_player_id='$forumplayer[player_id]'");
				db_op_result($query2,__LINE__,__FILE__);
				$clientmatch = $query2->RecordCount();

				if($clientmatch != 0)
					$clientmatch = "yellow";
				else $clientmatch = "white";

/*				print "$topicinfo[topic_id]<br>";
				print "$newposts<br>";
				print "$topictype$topicinfo[topic_title]<br>";
				print "$accounttype$topicinfo[topic_poster]<br>";
				print "$topicinfo[topic_time]<br>";
				print "$num2<br>";
				print "$topicinfo[topic_views]<br>";
				print "$topicinfo[topic_status]<br>";
				print "$clientmatch<br><br>";
*/
				$client[$count] = $clientmatch;
				$newpost[$count] = $newposts;
				$topicid[$count] = $topicinfo['topic_id'];
				$postid[$count] = $post_id;
				$topictypes[$count] = $topictype;
				$topictitle[$count] = $topicinfo['topic_title'];
				$accounttypes[$count] = $accounttype;
				$topicposter[$count] = $topicinfo['topic_poster'];
				$topicdates[$count] = date($local_date_full_format, strtotime($topicinfo['topic_time']));
				$number[$count] = $num2;
				$topicviews[$count] = $topicinfo['topic_views'];
				$count++;
				$debug_query->MoveNext();
			}
			$template_object->assign("client", $client);
			$template_object->assign("newpost", $newpost);
			$template_object->assign("topicid", $topicid);
			$template_object->assign("postid", $postid);
			$template_object->assign("topictypes", $topictypes);
			$template_object->assign("topictitle", $topictitle);
			$template_object->assign("accounttypes", $accounttypes);
			$template_object->assign("topicposter", $topicposter);
			$template_object->assign("topicdates", $topicdates);
			$template_object->assign("number", $number);
			$template_object->assign("topicviews", $topicviews);
			$template_object->assign("count", $count);
		}else{
			$template_object->assign("l_readm_nomessage", $l_readm_nomessage);
		}
		$template_object->assign("l_forums_posttopic", $l_forums_posttopic);
		$template_object->assign("l_team_notmember", $l_team_notmember);
		$template_object->assign("l_forums_showtopic", $l_forums_showtopic);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teamforum-showtopics.tpl");
		include ("footer.php");
		die();
	}

	if($command == "posttopic"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		if(trim($l_forums_subject) == '' || !isset($l_forums_subject))
			$l_forums_subject = $l_none;

		$template_object->assign("l_forums_subject", $l_forums_subject);
		$template_object->assign("l_forums_message", $l_forums_message);
		$template_object->assign("l_forums_normaltopic", $l_forums_normaltopic);
		$template_object->assign("l_forums_stickytopic", $l_forums_stickytopic);
		$template_object->assign("isadmin", $forumplayer['admin']);
		$template_object->assign("l_team_notmember", $l_team_notmember);
		$template_object->assign("l_forums_showtopic", $l_forums_showtopic);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teamforum-posttopic.tpl");
		include ("footer.php");
		die();
	}

	if($command == "finishtopic"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->Execute("select * from {$db_prefix}team_forums where forum_id=$forumdata[forum_id] and private=1");
		db_op_result($query,__LINE__,__FILE__);
		$private=$query->RecordCount();

		if(!isset($topictitle) || empty($topictitle))
			$topictitle = $l_forums_new;

		$query=$db->Execute("insert into {$db_prefix}team_forum_topics (topic_title, topic_poster, topic_time, topic_views, topic_replies, forum_id, topic_status, lastpostdate) values (". $db->qstr(clean_words($topictitle)) . ", " . $db->qstr($playerinfo['character_name']) . ", '$time', 1, 0, $forumdata[forum_id], $sticky, '$time')");
		db_op_result($query,__LINE__,__FILE__);

		$debug_query = $db->SelectLimit("select topic_id from {$db_prefix}team_forum_topics where topic_title=". $db->qstr(clean_words($topictitle)) . " and topic_poster=" . $db->qstr($playerinfo['character_name']) . " and topic_time='$time' and topic_views=1 and topic_replies=0 and forum_id=$forumdata[forum_id] and topic_status=$sticky and lastpostdate='$time'", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$topic_id = $debug_query->fields['topic_id'];

		$query=$db->Execute("insert into {$db_prefix}team_forum_posts (topic_id, forum_id, post_time, post_edit_time, post_edit_count, post_username, post_player_id) values ($topic_id, $forumdata[forum_id], '$time', '$time', 0, " . $db->qstr($playerinfo['character_name']) . ", $playerinfo[player_id])");
		db_op_result($query,__LINE__,__FILE__);

		$debug_query = $db->SelectLimit("select post_id from {$db_prefix}team_forum_posts where topic_id='$topic_id' and forum_id=$forumdata[forum_id] and post_time='$time' and post_edit_time='$time' and post_edit_count=0 and post_username=" . $db->qstr($playerinfo['character_name']) . " and post_player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$post_id = $debug_query->fields['post_id'];

		$query=$db->Execute("insert into {$db_prefix}team_forum_posts_text (post_id, post_text, topic_id, forum_id) values ($post_id, ". $db->qstr(clean_words($topicmessage)) . ", $topic_id, $forumdata[forum_id])");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_topics where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);
		$topics=$query->RecordCount();

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id] and topic_id=$topic_id");
		db_op_result($query,__LINE__,__FILE__);
		$topicposts=$query->RecordCount();

		$query=$db->Execute("update {$db_prefix}team_forum_topics set topic_replies=$topicposts, lastpostdate='$time' where topic_id=$topic_id");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);
		$posts=$query->RecordCount();

		$query=$db->Execute("update {$db_prefix}team_forums set forum_topics=$topics, forum_posts=$posts, lastposttime='$time' where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		$forumplayer['postcount']++;
		$query=$db->Execute("update {$db_prefix}team_forum_players set postcount=$forumplayer[postcount] where player_id='$playerinfo[player_id]'");
		db_op_result($query,__LINE__,__FILE__);

		unset($_SESSION['currentprogram'], $currentprogram);
		close_database();
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=team_forum.php?command=readtopic&topic_id=$topic_id\">";
	}

	if($command == "readtopic"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->Execute("select * from {$db_prefix}team_forum_topics where topic_id=$topic_id and forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);
		$num=$query->RecordCount();
		if($num > 0) {
			$topic_views = $query->fields['topic_views'];
			$topic_status = $query->fields['topic_status'];
			$topic_title = $query->fields['topic_title'];
			$topic_status = $query->fields['topic_status'];
		}

		$topictype = "";
		if($topic_status == 9)
			$topictype = $l_forums_sticky2;

		if($topic_status == 0)
			$topictype = $l_forums_locked2;

		$topic_views++;

		$query=$db->Execute("update {$db_prefix}team_forum_topics set topic_views=$topic_views where topic_id=$topic_id and forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where topic_id=$topic_id and forum_id=$forumdata[forum_id] order by post_time");
		db_op_result($query,__LINE__,__FILE__);
		$num=$query->RecordCount();
		$template_object->assign("topic_id", $topic_id);
		$template_object->assign("topic_status", $topic_status);
		$template_object->assign("forumadmin", $forumplayer['admin']);
		$template_object->assign("topictype", $topictype);
		$template_object->assign("l_forums_reply", $l_forums_reply);
		$template_object->assign("totalposts", $num-1);
		$template_object->assign("l_forums_subject", $l_forums_subject);
		$template_object->assign("topic_title", $topic_title);
		$template_object->assign("l_forums_date", $l_forums_date);
		$template_object->assign("templatename", $templatename);
		$template_object->assign("topicstartdate", date($local_date_full_format, strtotime($time)));
		$template_object->assign("l_readm_sender", $l_readm_sender);
		$template_object->assign("l_forums_edited", $l_forums_edited);
		$template_object->assign("l_forums_lastedit", $l_forums_lastedit);
		$template_object->assign("totalposts2", $num);

		if($num > 0) {
			$count = 0;
			while (!$query->EOF){
				$postinfo = $query->fields;

/*				$post_id = mysql_result($result, $i, "post_id");
				$post_username = mysql_result($result, $i, "post_username");
				$post_edit_time = mysql_result($result, $i, "post_edit_time");
				$post_edit_count = mysql_result($result, $i, "post_edit_count");
				$post_time = mysql_result($result, $i, "post_time");
				$post_player_id = mysql_result($result, $i, "post_player_id");
*/
				$query3 = $db->Execute("select * from {$db_prefix}team_forum_players where player_id='$postinfo[post_player_id]'");
				db_op_result($query3,__LINE__,__FILE__);
				$admins = $query3->RecordCount();

				if($admins > 0) {
					$admin = $query3->fields['admin'];
				}

				$accounttype = "";
				if($admin==1)
					$accounttype = $l_forums_coord;
				if($admin==2)
					$accounttype = $l_forums_admin;

				$date = explode(" ", $post_time);
				$temp = explode("-", $date[0]);
				$clock = explode(":", $date[1]);

				$newdate = mktime($clock[0], $clock[1], $clock[2], $temp[1], $temp[2], $temp[0]);

				$post_time = date("M j, Y g:ia", $newdate);

				$date = explode(" ", $post_edit_time);
				$temp = explode("-", $date[0]);
				$clock = explode(":", $date[1]);

				$newdate = mktime($clock[0], $clock[1], $clock[2], $temp[1], $temp[2], $temp[0]);

				$post_edit_time = date("M j, Y g:ia", $newdate);

				$query2=$db->Execute("select * from {$db_prefix}team_forum_posts_text where post_id=$postinfo[post_id]");
				db_op_result($query2,__LINE__,__FILE__);
				$num2=$query2->RecordCount();

				if($num2 > 0) {
					$post_text = $query2->fields['post_text'];
				}

				$query3 = $db->SelectLimit("select avatar from {$db_prefix}players where player_id='$postinfo[post_player_id]'", 1);
				db_op_result($query3,__LINE__,__FILE__);
				$avatar = $query3->fields['avatar'];

/*				print "$postinfo[post_id]<br>";
				print "$accounttype$postinfo[post_username]\t$postinfo[post_player_id]<br>";
				print "$postinfo[post_edit_time]<br>";
				print "$postinfo[post_edit_count]<br>";
				print "$postinfo[post_time]<br>";
				print "$post_text<br>";
				print "$topic_status<br><br>";
*/
				$postid[$count] = $postinfo['post_id'];
				$avatarimg[$count] = $avatar;
				$accounttypes[$count] = $accounttype;
				$postusername[$count] = $postinfo['post_username'];
				$postdate[$count] = date($local_date_full_format, strtotime($postinfo['post_time']));
				$posttext[$count]=nl2br(str_replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;", str_replace("  ","&nbsp;&nbsp;",$post_text)));
				$posteditcount[$count] = 0;
				if($postinfo['post_edit_count'] != 0){
					if($postinfo['post_edit_count'] > 1)
						$shows[$count] = "times";
					else $shows[$count] = "time";

					$posteditdate[$count] = date($local_date_full_format, strtotime($postinfo['post_edit_time']));
					$posteditcount[$count] = $postinfo['post_edit_count'];
				}
				$topicstatus[$count] = $topic_status;
				$isposter[$count] = ($forumplayer['player_id'] == $postinfo['post_player_id']);
				$count++;
				$query->MoveNext();
			}
		}

		$template_object->assign("count", $count);
		$template_object->assign("postid", $postid);
		$template_object->assign("avatarimg", $avatarimg);
		$template_object->assign("accounttypes", $accounttypes);
		$template_object->assign("postusername", $postusername);
		$template_object->assign("postdate", $postdate);
		$template_object->assign("posttext", $posttext);
		$template_object->assign("posteditdate", $posteditdate);
		$template_object->assign("posteditcount", $posteditcount);
		$template_object->assign("shows", $shows);
		$template_object->assign("l_readm_del", $l_readm_del);
		$template_object->assign("l_forums_edit", $l_forums_edit);
		$template_object->assign("l_readm_repl", $l_readm_repl);
		$template_object->assign("isposter", $isposter);
		$template_object->assign("l_forums_lock", $l_forums_lock);
		$template_object->assign("l_team_notmember", $l_team_notmember);
		$template_object->assign("l_forums_showtopic", $l_forums_showtopic);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teamforum-readtopic.tpl");
		include ("footer.php");
		die();
	}

	if($command == "postreply"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$template_object->assign("topic_id", $topic_id);
		$template_object->assign("l_forums_showtopic", $l_forums_showtopic);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teamforum-postreply.tpl");
		include ("footer.php");
		die();
	}

	if($command == "finishreply"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->Execute("select * from {$db_prefix}team_forums where forum_id=$forumdata[forum_id] and private=1");
		db_op_result($query,__LINE__,__FILE__);
		$private=$query->RecordCount();

		$query=$db->Execute("insert into {$db_prefix}team_forum_posts (topic_id, forum_id, post_time, post_edit_time, post_edit_count, post_username, post_player_id) values ($topic_id, $forumdata[forum_id], '$time', '$time', 0, " . $db->qstr($playerinfo['character_name']) . ", $playerinfo[player_id])");
		db_op_result($query,__LINE__,__FILE__);

		$debug_query = $db->SelectLimit("select post_id from {$db_prefix}team_forum_posts where topic_id='$topic_id' and forum_id=$forumdata[forum_id] and post_time='$time' and post_edit_time='$time' and post_edit_count=0 and post_username=" . $db->qstr($playerinfo['character_name']) . " and post_player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$post_id = $debug_query->fields['post_id'];

		$query=$db->Execute("insert into {$db_prefix}team_forum_posts_text (post_id, post_text, topic_id, forum_id) values ($post_id, ". $db->qstr(clean_words($topicmessage)) . ", $topic_id, $forumdata[forum_id])");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);
		$posts=$query->RecordCount();

		$query=$db->Execute("update {$db_prefix}team_forums set forum_posts=$posts, lastposttime='$time' where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id] and topic_id=$topic_id");
		db_op_result($query,__LINE__,__FILE__);
		$posts=$query->RecordCount();

		$query=$db->Execute("update {$db_prefix}team_forum_topics set topic_replies=$posts, lastpostdate='$time' where topic_id=$topic_id");
		db_op_result($query,__LINE__,__FILE__);

		$forumplayer['postcount']++;
		$query=$db->Execute("update {$db_prefix}team_forum_players set postcount=$forumplayer[postcount] where player_id='$playerinfo[player_id]'");
		db_op_result($query,__LINE__,__FILE__);

		unset($_SESSION['currentprogram'], $currentprogram);
		close_database();
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=team_forum.php?command=readtopic&topic_id=$topic_id#$post_id\">";
	}

	if($command == "edit"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->SelectLimit("select post_text from {$db_prefix}team_forum_posts_text where post_id=$post_id and forum_id=$forumdata[forum_id]", 1);
		db_op_result($query,__LINE__,__FILE__);
		$posttext = $query->fields['post_text'];

		$template_object->assign("post_id", $post_id);
		$template_object->assign("topic_id", $topic_id);
		$template_object->assign("posttext", $posttext);
		$template_object->assign("l_forums_showtopic", $l_forums_showtopic);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teamforum-edit.tpl");
		include ("footer.php");
		die();
	}

	if($command == "finishedit"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->SelectLimit("select post_edit_count from {$db_prefix}team_forum_posts where post_id=$post_id", 1);
		db_op_result($query,__LINE__,__FILE__);
		$post_edit_count = $query->fields['post_edit_count'];

		$post_edit_count++;

		$query=$db->Execute("update {$db_prefix}team_forum_posts set post_edit_time='$time', post_edit_count=$post_edit_count where post_id=$post_id");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("update {$db_prefix}team_forum_posts_text set post_text=". $db->qstr(clean_words($topicmessage)) ." where post_id=$post_id");
		db_op_result($query,__LINE__,__FILE__);

		unset($_SESSION['currentprogram'], $currentprogram);
		close_database();
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=team_forum.php?command=readtopic&topic_id=$topic_id#$post_id\">";
	}

	if($command == "delete"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->Execute("delete from {$db_prefix}team_forum_posts where post_id=$post_id and forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);
		$query=$db->Execute("delete from {$db_prefix}team_forum_posts_text where post_id=$post_id and forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);
		$posts=$query->RecordCount();

		$query=$db->Execute("update {$db_prefix}team_forums set forum_posts=$posts, lastposttime='$time' where forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}team_forum_posts where topic_id=$topic_id order by post_time");
		db_op_result($query,__LINE__,__FILE__);
		$num=$query->RecordCount();

		if($num == 0){
			$query=$db->Execute("delete from {$db_prefix}team_forum_topics where topic_id=$topic_id and forum_id=$forumdata[forum_id]");
			db_op_result($query,__LINE__,__FILE__);

			$query=$db->Execute("select * from {$db_prefix}team_forum_topics where forum_id=$forumdata[forum_id]");
			db_op_result($query,__LINE__,__FILE__);
			$topics=$query->RecordCount();

			$query=$db->Execute("select * from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id]");
			db_op_result($query,__LINE__,__FILE__);
			$posts=$query->RecordCount();

			$query=$db->Execute("update {$db_prefix}team_forums set forum_topics=$topics, forum_posts=$posts, lastposttime='$time' where forum_id=$forumdata[forum_id]");
			db_op_result($query,__LINE__,__FILE__);

			unset($_SESSION['currentprogram'], $currentprogram);
			close_database();
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=team_forum.php?command=showtopics\">";
		}else{
			unset($_SESSION['currentprogram'], $currentprogram);
			close_database();
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=team_forum.php?command=readtopic&topic_id=$topic_id\">";
		}
	}

	if($command == "lock"){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->Execute("select * from {$db_prefix}team_forum_topics where forum_id=$forumdata[forum_id] and topic_id=$topic_id");
		db_op_result($query,__LINE__,__FILE__);
		$topics=$query->RecordCount();

		if($topics>0){
				$topic_status = $query->fields['topic_status'];
		}
		$topic_status = 1 - $topic_status;

		$query=$db->Execute("update {$db_prefix}team_forum_topics set topic_status=$topic_status where topic_id=$topic_id and forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		unset($_SESSION['currentprogram'], $currentprogram);
		close_database();
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=team_forum.php?command=readtopic&topic_id=$topic_id\">";
	}

}else{
	$template_object->assign("l_team_notmember", $l_team_notmember);
	$template_object->assign("l_forums_showtopic", $l_forums_showtopic);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."teamforum-die.tpl");
	include ("footer.php");
	die();
}

?>


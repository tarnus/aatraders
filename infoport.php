<?php
include("config/config.php");
include ("languages/$langdir/lang_readmail.inc");
include ("languages/$langdir/lang_mailto2.inc");
include("languages/$langdir/lang_teams.inc");
include("languages/$langdir/lang_forums.inc");
include ("globals/clean_words.inc");

get_post_ifset("post_id, topic_id");

$title=$l_fedinfo;

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

$time = date("Y-m-d H:i:s");

$debug_query = $db->SelectLimit("select * from {$db_prefix}casino_forums where casino_sector=1", 1);
db_op_result($debug_query,__LINE__,__FILE__);

if($debug_query->RecordCount() == 1)
{
		$debug_query = $db->SelectLimit("select * from {$db_prefix}casino_forums where casino_sector=1", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query=$db->Execute("select * from {$db_prefix}casino_topics where topic_id=$topic_id and forum_id=$forumdata[forum_id]");
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

		$query=$db->Execute("update {$db_prefix}casino_topics set topic_views=$topic_views where topic_id=$topic_id and forum_id=$forumdata[forum_id]");
		db_op_result($query,__LINE__,__FILE__);

		$query=$db->Execute("select * from {$db_prefix}casino_posts where topic_id=$topic_id and forum_id=$forumdata[forum_id] order by post_time");
		db_op_result($query,__LINE__,__FILE__);
		$num=$query->RecordCount();
		$template_object->assign("topic_id", $topic_id);
		$template_object->assign("topic_status", $topic_status);
		$template_object->assign("forumadmin", ($playerinfo['player_id'] <= 3));
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

				$accounttype = "";

				if($postinfo['post_player_id'] <= 3)
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

				$query2=$db->Execute("select * from {$db_prefix}casino_posts_text where post_id=$postinfo[post_id]");
				db_op_result($query2,__LINE__,__FILE__);
				$num2=$query2->RecordCount();

				if($num2 > 0) {
					$post_text = $query2->fields['post_text'];
				}

				$query3 = $db->SelectLimit("select avatar from {$db_prefix}players where player_id='$postinfo[post_player_id]'", 1);
				db_op_result($query3,__LINE__,__FILE__);
				$avatar = $query3->fields['avatar'];

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
				$isposter[$count] = ($playerinfo['player_id'] == $postinfo['post_player_id']);
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
		$template_object->assign("is_infoport", 1);
		$template_object->display($templatename."casinoforum-readtopic.tpl");
		include ("footer.php");
		die();
}

?>


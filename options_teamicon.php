<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: options.php

include ("config/config.php");
include ("languages/$langdir/lang_options_teamicon.inc");
include ("globals/RecurseDir.inc");

get_post_ifset("action, galleryimage, gallery");

$title = $l_opt_title;

if ((!isset($i)) || ($i == ''))
{
	$i = 0;
}

if (checklogin())
{
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

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

if($playerinfo['team'] == 0){
	$template_object->assign("error_msg", $l_opt_noteam);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."options_teamicondie.tpl");
	include ("footer.php");
	die();
}

$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
$teamstuff = $result_team->fields;

if($teamstuff['id'] != $playerinfo['player_id']){
	$template_object->assign("error_msg", $l_opt_notleader);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."options_teamicondie.tpl");
	include ("footer.php");
	die();
}

if($action == "selectgraphic" and ($galleryimage != '' or isset($galleryimage))){

	if($teamstuff['icon'] != "default_icon.gif"){
		$junkold = explode("/", $teamstuff['icon']);
		$galleryold = $junkold[0];
		$pictureold = $junkold[1];
		if($galleryold == "uploads"){
			@unlink($gameroot."images/icons/uploads/$pictureold");
		}
	}
	$teamstuff['icon'] = $gallery."/$galleryimage";
	$debug_query = $db->Execute("UPDATE {$db_prefix}teams SET icon='$teamstuff[icon]' WHERE id=$teamstuff[id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}

if($action == "uploadgraphic" and $allow_icon_upload == 1){

	if($teamstuff['icon'] != "default_icon.gif"){
		$junkold = explode("/", $teamstuff['icon']);
		$galleryold = $junkold[0];
		$pictureold = $junkold[1];
		if($galleryold == "uploads"){
			@unlink($gameroot."images/icons/uploads/$pictureold");
		}
	}

	$img_src=$_FILES['img_src']['tmp_name'];
	if($img_src != '' and isset($img_src))	   
	{
		$checkit = GetImageSize($img_src); 
		if($checkit[2] > 0 and $checkit[2] < 4){

			$imagewidth = $checkit[0];
			$imageheight = $checkit[1];

			if($imagewidth < 65 and $imageheight < 65){
				if ($checkit[2] == 1)
				{
					copy($img_src,$gameroot."images/icons/uploads/$teamstuff[id].gif");
					$galleryimage="$teamstuff[id].gif";
				}

				if ($checkit[2] == 2)		  	
				{
					copy($img_src,$gameroot."images/icons/uploads/$teamstuff[id].jpg");
					$galleryimage="$teamstuff[id].jpg";	
				}

				if ($checkit[2] == 3)		  	
				{
					copy($img_src,$gameroot."images/icons/uploads/$teamstuff[id].png");
					$galleryimage="$teamstuff[id].png";	
				}

				$teamstuff['icon'] = "uploads/$galleryimage";
				$debug_query = $db->Execute("UPDATE {$db_prefix}teams SET icon='$teamstuff[icon]' WHERE id=$teamstuff[id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			}else{
				$template_object->assign("error_msg", $l_opt_errorsize);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."options_teamicondie.tpl");
				include ("footer.php");
				die();
			}
		}else{
			$template_object->assign("error_msg", $l_opt_errortype);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."options_teamicondie.tpl");
			include ("footer.php");
			die();
		}
	}else{
		$template_object->assign("error_msg", $l_opt_errornographic);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."options_teamicondie.tpl");
		include ("footer.php");
		die();
	}
}

if($gallery == '' or !isset($gallery)){
	if($teamstuff['icon'] != "default_icon.gif"){
		$junk = explode("/", $teamstuff['icon']);
		$gallery = $junk[0];
	}
}

if($teamstuff['icon'] != "default_icon.gif"){
	$junk = explode("/", $teamstuff['icon']);
	$picture = $junk[1];
}

$dirlist=RecurseDir($gameroot."images/icons"); 
chdir($gameroot); 
$directorycount = 0;
foreach ($dirlist as $key=>$val) { 
	$gallerybase = str_replace($gameroot."images/icons/", "", $val);
	if($gallery == '' or !isset($gallery) or $gallery == "uploads")
		$gallery = $gallerybase;
	if($gallery == $gallerybase)
		$selected = "selected";
	else $selected = "";

	$galleryarray = explode("/", $gallerybase);

	if($gallerybase != "CVS" and $gallerybase != "uploads" and count($galleryarray) == 1){
		$directoryitem[$directorycount] =  $gallerybase;
		$directoryselect[$directorycount] = $selected;
		$directorycount++;
	} 
}

$start_dir = $gameroot."images/icons/$gallery"; 
$filelist = get_dirlist($start_dir);
unset ($galleryimage);

$itemcount = 0;
for ($c=0; $c<count($filelist); $c++) { 
	$gallerypicture =  str_replace($gameroot."images/icons/$gallery/", "", $filelist[$c]); 
	$validimage = 0;

	if(strstr(AAT_strtolower($gallerypicture), ".jpg") or strstr(AAT_strtolower($gallerypicture), ".jpeg") or strstr(AAT_strtolower($gallerypicture), ".gif") or strstr(AAT_strtolower($gallerypicture), ".png"))
		$validimage = 1;

	$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE icon='".str_replace($gameroot."images/icons/", "", $gallery. "/". $filelist[$c])."' and id != $playerinfo[team]", 1);
	if($result_team->RecordCount() == 0 && $validimage == 1){
		if($picture == $gallerypicture)
			$checked = "checked";
		else $checked = "";

		$galleryimage[$itemcount] = $gallerypicture;
		$gallerychecked[$itemcount] = $checked;
		$galleryfile[$itemcount] = str_replace($gameroot."images/icons/$gallery/", "", $filelist[$c]);
		$itemcount++;
	}
}

$template_object->assign("l_opt_currentavatar", $l_opt_currentavatar);
$template_object->assign("currenticon", $teamstuff['icon']);
$template_object->assign("allow_icon_upload", $allow_icon_upload);
$template_object->assign("l_opt_uploadavatar", $l_opt_uploadavatar);
$template_object->assign("l_opt_uploadtypes", $l_opt_uploadtypes);
$template_object->assign("l_opt_uploadavatar", $l_opt_uploadavatar);
$template_object->assign("l_opt_directory", $l_opt_directory);
$template_object->assign("directorycount", $directorycount);
$template_object->assign("directoryitem", $directoryitem);
$template_object->assign("directoryselect", $directoryselect);
$template_object->assign("l_opt_change", $l_opt_change);
$template_object->assign("gallery", $gallery);
$template_object->assign("itemcount", $itemcount);
$template_object->assign("galleryimage", $galleryimage);
$template_object->assign("gallerychecked", $gallerychecked);
$template_object->assign("galleryfile", $galleryfile);
$template_object->assign("l_opt_select", $l_opt_select);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."options_teamicons.tpl");
include ("footer.php");

?>
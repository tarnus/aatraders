<?php
// 1: Site Activity Log
// You can view the site activity as a graph.  It will show the number of users online every 5 minutes for a 24 hour period or a breakdown of activity by hour, day, week, month and year.

include "backends/libchart-1.1/libchart/libchart.php";

get_post_ifset("chart_type");

if(!isset($chart_type))
{
	$chart_type = "LineChart";
}

if($chart_type == "24hourLineChart")
{
	for($imagecount = 0; $imagecount < 12; $imagecount++)
	{
		$chart = new LineChart();

		$result = $db->Selectlimit("SELECT * FROM {$db_prefix}site_activity_log ORDER BY time DESC", 24, $imagecount * 24);
		while (!$result->EOF && $result)
		{
			$row = $result->fields;
			$row['minute'] = str_pad($row['minute'], 2, "0", STR_PAD_LEFT);
			$row['hour'] = str_pad($row['hour'], 2, "0", STR_PAD_LEFT);
			$chart->addPoint(new Point("$row[hour]:$row[minute]", $row['player_count']));
			$result->MoveNext();
		}

		if($result)
		{
			if($result->RecordCount() < 24)
				$chart->addPoint(new Point("Log Start", 0));
		}

		$chart->setTitle("Number of People Online every 5 Minutes, last 24 hours ($player_limit max)");
		$chart->render("templates_c/$imagecount.png");
		unset($chart);
	}
}
else
{
	$chart = new $chart_type();

	$result = $db->Execute("SELECT * FROM {$db_prefix}site_activity_log ORDER BY time DESC LIMIT 24");
	while (!$result->EOF && $result)
	{
		$row = $result->fields;
		$row['minute'] = str_pad($row['minute'], 2, "0", STR_PAD_LEFT);
		$row['hour'] = str_pad($row['hour'], 2, "0", STR_PAD_LEFT);
		$chart->addPoint(new Point("$row[hour]:$row[minute]", $row['player_count']));
		$result->MoveNext();
	}

	if($result)
	{
		if($result->RecordCount() < 24)
			$chart->addPoint(new Point("Log Start", 0));
	}

	$chart->setTitle("Number of People Online every 5 Minutes, last 2 hours ($player_limit max)");
	$chart->render("templates_c/5minute.png");
	unset($chart);


	$chart = new $chart_type();

	$result = $db->Execute("SELECT hour, SUM(player_count) as new_count FROM {$db_prefix}site_activity_log GROUP BY year, month, day, hour ORDER BY time DESC LIMIT 24");
	while (!$result->EOF && $result)
	{
		$row = $result->fields;
		$row['hour'] = str_pad($row['hour'], 2, "0", STR_PAD_LEFT);
		$chart->addPoint(new Point("$row[hour]:00", $row['new_count']/12));
		$result->MoveNext();
	}

	if($result)
	{
		if($result->RecordCount() < 24)
			$chart->addPoint(new Point("Log Start", 0));
	}

	$chart->setTitle("Average Number of People Online per Hour, last 24 hours ($player_limit max)");
	$chart->render("templates_c/24hours.png");
	unset($chart);


	$chart = new $chart_type();

	$result = $db->Execute("SELECT year, month, day, SUM(player_count) as new_count FROM {$db_prefix}site_activity_log GROUP BY year, month, day ORDER BY time DESC LIMIT 30");
	while (!$result->EOF && $result)
	{
		$row = $result->fields;
		$chart->addPoint(new Point("$row[year]-$row[month]-$row[day]", $row['new_count']/288));
		$result->MoveNext();
	}

	if($result)
	{
		if($result->RecordCount() < 30)
			$chart->addPoint(new Point("Log Start", 0));
	}

	$chart->setTitle("Average Number of People Online per Day, last 30 days ($player_limit max)");
	$chart->render("templates_c/30days.png");
	unset($chart);


	$chart = new $chart_type();

	$result = $db->Execute("SELECT year, month, SUM(player_count) as new_count FROM {$db_prefix}site_activity_log GROUP BY year, month ORDER BY time DESC LIMIT 12");
	while (!$result->EOF && $result)
	{
		$row = $result->fields;
		$chart->addPoint(new Point("$row[year]-$row[month]", $row['new_count']/8640));
		$result->MoveNext();
	}

	if($result)
	{
		if($result->RecordCount() < 12)
			$chart->addPoint(new Point("Log Start", 0));
	}

	$chart->setTitle("Average Number of People Online per Month, last 12 months ($player_limit max)");
	$chart->render("templates_c/12months.png");
	unset($chart);
}

?>
					<tr align="center">
						<td align="center">
						<table width="100%" border="0" cellspacing="0" cellpadding="3" align="center">
<tr><td align="center">Select the Chart Type you would like to view: 
<form action="admin.php" method="post" enctype="multipart/form-data">
<select name="chart_type">
		<option value="LineChart" <?php
		if($chart_type == "LineChart")
			echo "selected";
		?>>Line Chart</option>
		<option value="PieChart" <?php
		if($chart_type == "PieChart")
			echo "selected";
		?>>Pie Chart</option>
		<option value="VerticalChart" <?php
		if($chart_type == "VerticalChart")
			echo "selected";
		?>>Vertical Chart</option>
		<option value="HorizontalChart" <?php
		if($chart_type == "HorizontalChart")
			echo "selected";
		?>>Horizontal Chart</option>
		<option value="24hourLineChart" <?php
		if($chart_type == "24hourLineChart")
			echo "selected";
		?>>Display 24 Hour Activity Chart</option>
</select>
<input type="hidden" name="game_number" value="<?php
echo $game_number; ?>">
<INPUT TYPE=HIDDEN NAME=admin_password VALUE="<?php
echo $admin_password; ?>">
<input type="hidden" name="menu" value="View_Site_Activity_Log">
&nbsp;&nbsp;<input type="submit" value="Change Chart">
</form><hr>
</td></tr>
						<tr><td align="center">
<?php
if($chart_type == "24hourLineChart")
{
	for($i = 0; $i < 12; $i++)
	{
?>
<img alt="Line chart" src="templates_c/<?php echo $i; ?>.png" style="border: 1px solid gray;"/>
<br>
<?php
	}
}
else
{
?>
<img alt="Line chart" src="templates_c/5minute.png" style="border: 1px solid gray;"/>
<br>
	<img alt="Line chart" src="templates_c/24hours.png" style="border: 1px solid gray;"/>
<br>
	<img alt="Line chart" src="templates_c/30days.png" style="border: 1px solid gray;"/>
<br>
	<img alt="Line chart" src="templates_c/12months.png" style="border: 1px solid gray;"/>
<br>
<?php
}
?>
</td></tr>
			</table>
</td>
					</tr>
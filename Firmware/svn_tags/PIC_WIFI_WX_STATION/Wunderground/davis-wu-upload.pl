#!/usr/bin/perl
#
# pull, format, and upload data to wunderground.com.
# this should be ran every 5-10 minutes.  Any less or
# more doesn't provide good data.

use DBI;
use LWP::UserAgent;
use HTTP::Request;
use POSIX qw(strftime);
use strict;

# set the username and password below
# to the username and password of a mysql user who has
# read access to the tables in the mysql database.
my $db_user = "dbuser";
my $db_passwd = "dbpass";
my $db_name = "dbname";
my $db_host = "dbhost";
my $db_table = "dbtable";

# wunderground access inforation
my $ID = "your wunderground id";
my $PASSWORD = "your wunderground password";
my $WU_URL = "http://weatherstation.wunderground.com/weatherstation/updateweatherstation.php";
my $SOFTWARETYPE="davis-wu-upload.pl";

# set this to a scratch directory where we have
# write access
my $scratchdir = "/var/tmp";
my $scratchfoo = "davislastrun";
my $logfoo     = "davis-wu-upload.log";

# how are your variables stored?
# we assume imperial so you'll have to do the mods yourself
my $tempUnit	= "deg F";
my $windUnit	= "mph";
my $barUnit	= "inHg";
my $rainUnit	= "in";

# --- End of tunables ---

# find out time delta in seconds of when we last ran so we
# send good data to wunderground
my $deltaT = &findlastrun($scratchdir,$scratchfoo);
my $now = time();
my $nowQ = ($now - $deltaT);

my ($count, $winddir, $windspeed, $windgust, $humidity, $temperature, $barometer, $rain);
my ($dewpt, $tempC, %wuf, $key, $wu_url);

#
# Connect to the database.
#
my $dbh = DBI->connect("DBI:mysql:database=$db_name;host=$db_host",$db_user, $db_passwd,{'RaiseError' => 1});

#
# get data within our last run timestamp
#
my $sth = $dbh->prepare("SELECT
  count(timekey),
  sum(winddir),
  sum(windspeed),
  max(windgust),
  sum(humidity),
  sum(temperature),
  sum(barometer) FROM $db_table where timekey > $nowQ");

$sth->execute();

if (($count, $winddir, $windspeed, $windgust, $humidity, $temperature, $barometer) = $sth->fetchrow_array ){

  if($winddir){ $wuf{winddir} = sprintf('%.0f',($winddir/$count)); }else{ $wuf{winddir} = 0 }
  if($windspeed){ $wuf{windspeedmph} = sprintf('%.0f',($windspeed/$count)); }else{ $wuf{windspeedmph} = 0 }
  $wuf{windgustmph}   = $windgust;
  $wuf{humidity}    = sprintf('%.0f',($humidity/$count));
  if($temperature){ $wuf{tempf} = sprintf('%.1f',($temperature/$count)); }else{ $wuf{tempf} = 0 }
  $wuf{baromin}   = sprintf('%.2f',($barometer/$count));
  # calculate the dew point
  $tempC	= 5.0/9.0*($wuf{tempf} - 32.0);	# convert F to C
  $dewpt	= dewpt($tempC, $wuf{humidity});		# outsideDewPt
  $wuf{dewptf}	= sprintf('%.1f',(9.0/5.0)*${dewpt}+32);		# convert C to F

  $sth->finish();
}else{ die "can not query database"; }

# calculate the rain within the last hour
# grab stormrain now
# grab stormrain (now - (60 * 60))
# lasthour = (rainnow - rainthen)
my ($rainnow, $rainthen, $datenow, $datethen);
# get rain now
my $sth = $dbh->prepare("SELECT stormrain,stormdate from $db_table order by timekey desc limit 1");
$sth->execute();
if ( ($rainnow,$datenow) = $sth->fetchrow_array ){ $sth->finish(); }else{ die; }
# get the rain an hour ago
my $timethen = ($now - (60*60));
my $sth = $dbh->prepare("SELECT stormrain,stormdate from $db_table
    where timekey < $timethen order by timekey desc limit 1");
$sth->execute();
if ( ($rainthen,$datethen) = $sth->fetchrow_array ){ $sth->finish(); }else{ die; }
if("$datethen" eq "$datenow"){
  # same storm, calculate the rain delta
  $wuf{rainin} = ($rainnow - $rainthen);
}else{
  # we're in the first hour of a new storm
  $wuf{rainin} = $rainnow;
}

# Disconnect from the database.
$dbh->disconnect();

# build our URL and send the data to wunderground.com
$wuf{dateutc} = strftime("%Y-%m-%d %H:%M:%S",gmtime($now));
$wuf{softwaretype} = $SOFTWARETYPE;
$wuf{weather} = "NA";
$wuf{clouds} = "NA";
$wu_url = $WU_URL."?action=updateraw&ID=".$ID."&PASSWORD=".$PASSWORD;
foreach $key(sort(keys(%wuf))){ $wu_url .= "&".$key."=".$wuf{$key} }
# url built, send it in...
my $ua = LWP::UserAgent->new;
my $req = HTTP::Request->new(GET => $wu_url);
my $resp = $ua->simple_request($req);
my $resp_data = $resp->content;

# log the data
open(foo,"> $scratchdir/$logfoo")||die "can log to $scratchdir/$logfoo";
print foo "$wu_url\n\n$resp_data\n\n";
close foo;
exit(0);


#
# formulas from http://www.usatoday.com/weather/whumcalc.htm
#
sub dewpt ($$) {
  my ($Tc, $RH) = @_;
  my ($Es, $E, $Tdc);

  $Es = 6.11 * 10.0 ** (7.5 * $Tc / (237.7 + $Tc));
  $E = ($RH * $Es) / 100;
  $Tdc = (-430.22 + 237.7 * log($E)) / (-log($E) +19.08);

  return $Tdc;
}

sub findlastrun {
  my ($scratchdir, $scratchfoo) = @_;
  my $now = time();
  if(! -f "$scratchdir/$scratchfoo") {
    open(foo,"> $scratchdir/$scratchfoo") || die "$scratchdir/$scratchfoo not writeable";
    print foo "$now";
    close foo;
    return($now - (60 * 10));  # let's say we ran 10 minutes ago
  }
  # this should never happen
  open(foo,"$scratchdir/$scratchfoo") || die "$scratchdir/$scratchfoo does not exist";
  my $l = <foo>;
  close foo;
  open(foo,"> $scratchdir/$scratchfoo") || die "$scratchdir/$scratchfoo not writeable";
  print foo "$now";
  close foo;
  if($now > $l){ return ($now - $l); }else{ die "last run: $l, now: $now, this can not happen"; }
}

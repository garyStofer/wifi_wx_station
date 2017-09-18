// Parses the xmlResponse from status_xyz.xml and updates the status box
function updateLedStatus(xmlData) 
{
	
	if ( timed_out(	xmlData) )
		return;
	document.getElementById('led1').style.color = (getXMLValue(xmlData, 'led1') == '+') ? '#090' : '#ddd';
	document.getElementById('led2').style.color = (getXMLValue(xmlData, 'led2') == '+') ? '#f90' : '#ddd';
	document.getElementById('led3').style.color = (getXMLValue(xmlData, 'led3') == '+') ? '#f00' : '#ddd';
}
function updateOutputStatus(xmlData) 
{
	
	if ( timed_out(	xmlData) )
		return;

	// Loop over all the outputs
	for(i = 0; i <9; i++)
		document.getElementById('out' + i).style.color = (getXMLValue(xmlData, 'out' + i) == '+') ? '#090' : '#ddd';

}
function updateInputStatus(xmlData) 
{
	
	if ( timed_out(	xmlData) )
		return;

	// Loop over all the inputs
	for(i = 0; i < 10; i++)
	{
		document.getElementById('in' + i).style.color = (getXMLValue(xmlData, 'in' + i) == '+') ? '#ddd' :'#0A0';
	}
	document.getElementById('btn1').style.color = (getXMLValue(xmlData, 'btn1') == '+') ? '#ddd' :'#0A0';
	document.getElementById('btn2').style.color = (getXMLValue(xmlData, 'btn2') == '+') ? '#ddd' :'#0A0';
}
function timed_out(xmlData)
{
	// Check if a time-out occurred
	if(!xmlData)
	{
		document.getElementById('ok_').style.display='none';
		document.getElementById('err').style.display='inline';
		return true;
	}

	// Make sure we're displaying the status display
	document.getElementById('ok_').style.display='inline';
	document.getElementById('err').style.display='none';
	return false;

}


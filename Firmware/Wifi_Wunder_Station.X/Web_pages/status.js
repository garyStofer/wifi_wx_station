function timed_out(xmlData)
{
	var mainstat = document.getElementById('display').style.display;
	var loadstat = document.getElementById('loading').style.display;

	// Check if a timeout occurred
	if(!xmlData)
	{
		mainstat = 'none';
		loadstat = 'inline';
		return true;
	}

	// Make sure we're displaying the status display
	mainstat = 'inline';
	loadstat = 'none';
	return false;

}

// Parses the xmlResponse from status_xyz.xml and updates the status box
function updateLedStatus(xmlData) 
{
	
	if ( timed_out(	xmlData) )
		return;
	document.getElementById('led0').style.color = (getXMLValue(xmlData, 'led0') == '1') ? '#090' : '#ddd';
	document.getElementById('led1').style.color = (getXMLValue(xmlData, 'led1') == '1') ? '#f90' : '#ddd';
	document.getElementById('led2').style.color = (getXMLValue(xmlData, 'led2') == '1') ? '#f00' : '#ddd';
}


function updateOutputStatus(xmlData) 
{
	
	if ( timed_out(	xmlData) )
		return;

	// Loop over all the outputs
	for(i = 0; i < 8; i++)
		document.getElementById('out' + i).style.color = (getXMLValue(xmlData, 'out' + i) == '1') ? '#090' : '#ddd';

}

function updateInputStatus(xmlData) 
{
	
	if ( timed_out(	xmlData) )
		return;

	// Loop over all the inputs
	for(i = 0; i < 4; i++)
		document.getElementById('in' + i).style.color = (getXMLValue(xmlData, 'in' + i) == 'up') ? '#ddd' :'#0A0';
}

function updateADCStatus(xmlData)
{
	
	if ( timed_out(	xmlData) )
		return;

	// Loop over all the ADCs
	for(i = 0; i < 8; i++)
		document.getElementById('adc'+i).innerHTML = getXMLValue(xmlData, 'adc'+i);
}




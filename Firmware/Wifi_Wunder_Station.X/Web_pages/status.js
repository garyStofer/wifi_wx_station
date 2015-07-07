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

function updateADCStatus(xmlData)
{
	
	if ( timed_out(	xmlData) )
		return;

    for(i = 0; i < 6; i++)
	{
        document.getElementById('adc'+i).innerHTML = getXMLValue(xmlData, 'adc'+i);
    }



}
function updateRFSensStatus(xmlData)
{
	if ( timed_out(	xmlData) )
		return;

    for(i = 0; i < 6; i++)
	{
        document.getElementById('RFid'+i).innerHTML = getXMLValue(xmlData, 'rfid'+i);    // The sensors ID
      //  document.getElementById('RFtyp'+i).innerHTML = getXMLValue(xmlData, 'rftyp'+i);  // The sensors type
        document.getElementById('RFvb'+i).innerHTML = getXMLValue(xmlData, 'rfvb'+i);    // battery voltage
        document.getElementById('RFr1_'+i).innerHTML = getXMLValue(xmlData, 'rfr1_'+i);  // Reading 1 i.e. soil moisture if typ==8
        document.getElementById('RFr2_'+i).innerHTML = getXMLValue(xmlData, 'rfr2_'+i);  // reading 2 i.e Raw voltage if typ ==8
        document.getElementById('RFr3_'+i).innerHTML = getXMLValue(xmlData, 'rfr3_'+i);  // Reading 3 ..
        document.getElementById('RFsi'+i).innerHTML = getXMLValue(xmlData, 'rfsi'+i);    // Relative signal strenght
        document.getElementById('RFtm'+i).innerHTML = getXMLValue(xmlData, 'rftm'+i);    // time of most recent readings
    }

}

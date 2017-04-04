/* linearisation for VH400 probe voltage to Volumetric Water Content (VWC)
 Voltage Range 	Equation
0 to 1.1V 	VWC= 10*V-1
1.1V to 1.3V 	VWC= 25*V- 17.5
1.3V  to 1.82V 	VWC= 48.08*V- 47.5
1.82V to 2.2V 	VWC= 26.32*V- 7.89
*/

float Vx;   // Voltage from VH400
float VWC;  // Volumetric Water Content

Vx =  ADC * (3.3/1024); // volts as read on ADC0 input pin.

if ( Vx < 1.1)
	VWC = Vx*10.0 -1;
else if ( Vx < 1.3)
	VWC = Vx*25.0 -17.5;
else if ( Vx < 1.82 )
	VWC = Vx*48.08 - 47.5;
else
	VWC= Vx*26.32- 7.89;
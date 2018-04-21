#include <time.h>

void loop()
	{
	if (irrecv.decode(&results))
	{
	Serial.println(results.value, HEX);
	if(results.value == "setup alarm time hex")
	{
		// Asks 4 numbers here and stores it into HH:MM
		// Confimed with OK
		// Last number can be removed with backpedal button
	}
	if(results.value == "Activate Alarm time")
	{
		if(alarmFlag == true)
		{
			// Deactivates alarm time here
			// Turns alarmFlag off
		}
		else
		{
			// Turns alarmFlag on
		}
	}
	if(results.value == "Change Time")
	{
		// Asks 4 numbers and turns it into HH:MM
		// Confirmed with Ok
		// Changes time to currentTime
	}
    irrecv.resume();
	}
	if("time changes")
	{
		/* Here we change last digit of currentTime to new
		   Last digit for each variable
		   [0] 2
		   [1] 3
		   [2] 5
		   [3] 9
		   Digits r checked from 3 to 0, if currentTime digit equals last digit
		   it changes it to 0 and jump to compare next digit
		 */

		
		// alarmFlag indicates if alarm is turned on, compares currentTime to setupTime
		// If times are equal, turns alarm on
		if(alarmFlag == true)
		{
			if(currentTime == alarmTime)
			{
				// Activates motor and voice
				activatedAlarmMode();
			}
		
		
	}
	}
	
void activatedAlarmMode()
{
	// As Long as alarm is true, motor and voice is activate
	while(alarm)
	{
		// Loops empty
	}
	
	// When alarm goes off, deactivates alarmMode and jumps back to normal
}
delay(100);


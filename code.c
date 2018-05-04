#include <time.h>

void loop()
	{
	if (irrecv.decode(&results))
	{
	Serial.println(time);
	// Mark CH
	if(results.value == FF629D)
	{
		// Asks 4 numbers here and stores it into HH:MM
		// Confimed with OK
		// Last number can be removed with backpedal button
		
		// uses setupTime function to determine time
		time = setTime()
		
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
	// Mark CH+
	if(results.value == FFE21D)
	{
		// Asks 4 numbers and turns it into HH:MM
		// Confirmed with Ok
		// Changes time to currentTime
		time = setTime()
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
void setTime()
{
	int codeNumb = 1;
		while(codeNum < 4)
		{
			if(irrecv.decode(&results))
			{
				int numb = -1;
				int clockTime = 0;
				// mark 0
				if(results.value == 6897)
				{
					numb = 0;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark 1
				if(results.value == 30CF)
				{
					numb = 1;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;

				}
				// mark 2
				if(results.value == 18E7)
				{
					numb = 2;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark 3
				if(results.value == 7A85)
				{
					numb = 3;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark 4
				if(results.value == 10EF)
				{
					numb = 4;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark 5
				if(results.value == 38C7)
				{
					numb = 5;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark 6
				if(results.value == 5AA5)
				{
					numb = 6;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark 7
				if(results.value == 42BD)
				{
					numb = 7;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// Mark 8
				if(results.value == 4AB5)
				{
					numb = 8;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// Mark 9
				if(results.value == 52AD)
				{
					numb = 9;
					int n = 0;
					while(codeNumb > n)
					{
						numb = numb * 10;
						n = n + 1;
					}
					clockTime = clockTime + numb;
					codeNum = codeNum + 1;
				}
				// mark |<<
				if(results.value == 22DD)
				{
					numb = 10;
					
				}
				// mark -
				if(results.value == E01F)
				{
					numb = 11;
				}
				if(numb =/= -1)
				{
					// Do nothing
				}
				
			}
			
		}
	return clockTime;
}
delay(100);


# strfalltime
Based on strftime. Print out any time format based on struct tm in C. Initially made for the Arduino.

Made this since i couldn't find an easy solution to convert epoch to whatever string time format. Most libraries don't have strftime builtin for the arduino from what i've seen.

I decided not to use flash memory for saving the months and day names since it slows down the arduino in general. Anyone can change the return type and all that if they want. I wanted this to work on everything also and not just the arduino.

%z and %Z are not implemented. 

```
#include "strfalltime.h"
```

#Extra features
```
%c%1 - Monday March 01 02:30:35 PM 2019
%c%2 - Monday March 01 21:30:35 2019
%c%3 - 10/23/19 10:30:35 AM
%c%4 - Monday March 01 2019
%c%5 - 10/23/19 22:30:35
%c%6 - Monday 10:30:35 AM March 01 2019
%c%7 - 10:30:35 AM Monday March 01 2019
```

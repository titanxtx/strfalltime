#ifndef STRFALLTIME_H
#define STRFALLTIME_H
#include <string.h>
#include <time.h>
/*
MIT License

Copyright (c) 2019 Joshua Oliva

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
static const char *strfalltime_weekday(int x,int *y){
    switch(x){
        case 0:
            *y=6;
            return "Sunday";
            break;
        case 1: 
            *y=6;
            return "Monday";
            break;
        case 2: 
            *y=7;
            return "Tuesday";
            break;
        case 3: 
            *y=9;
            return "Wednesday";
            break;
        case 4: 
            *y=8;
            return "Thursday";
            break;
        case 5: 
            *y=6;
            return "Friday";
            break;
        case 6: 
            *y=8;
            return "Saturday";
            break;
    }
}
static const char *strfalltime_month(int x,int *y){
    switch(x){
        case 0:
            *y=7;
            return "January";
            break;
        case 1:
            *y=7;
            return "Febuary";
            break;
        case 2:
            *y=5;
            return "March";
            break;
        case 3:
            *y=5;
            return "April";
            break;
        case 4:
            *y=3;
            return "May";
            break;
        case 5:
            *y=4;
            return "June";
            break;
        case 6:
            *y=4;
            return "July";
            break;
        case 7:
            *y=5;
            return "August";
            break;
        case 8:
            *y=9;
            return "September";
            break;
        case  9:
            *y=7;
            return "October";
            break;
        case 10:
            *y=8;
            return "November";
            break;
        case 11:
            *y=8;
            return "December";
            break; 
    }
}
static char *number_pad(char*z,int x, int *y){
    if(x<10)
    {
        *y=sprintf(z,"0%d",x);
        return z;
    }
    else{
        *y=sprintf(z,"%d",x);
        return z;
    }
}
static char *space_pad(char*z,int x, int *y){
    if(x<10)
    {
        *y=sprintf(z," %d",x);
        return z;
    }
    else{
        *y=sprintf(z,"%d",x);
        return z;
    }
}

static int strfalltime_lastweek(int year){
    year+=1900;
    int week=(((year)+((year)/4)-((year)/100)+((year)/400))%7);//this years last week
    year--;
    int week2=(((year)+((year)/4)-((year)/100)+((year)/400))%7);//last years last week
    return 52+((week==4||week2==3)?1:0);
}

size_t strfalltime(char*ptr,size_t maxsize,char*format, struct tm* timeptr){
    maxsize--;
    size_t i=0,j=0;
    unsigned char e=0;
    int amt,val;
    char *z;
    char w[8];
    while(format[i]!='\0'&&i<maxsize)
    {
        if(e==0)
        {
            if(format[i]=='%')
            {
                e=1;
            }
            else{
                ptr[j++]=format[i];
            }
        }
        else if(e==1)
        {
            switch(format[i]){
                case 'a':
                    strncpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt),3);
                    j+=3;
                    break;
                case 'A':
                    strncpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt),amt);
                    j+=amt;
                    break;
                case 'b': 
                    strncpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt),3);
                    j+=3;
                    break;
                case 'B': 
                    strncpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt),amt);
                    j+=amt;
                    break;
                case 'c':
                    if(format[i+1]!='\0'&&format[i+2]!='\0'&&format[i+1]=='%'&&(format[i+2]-'0')>=1&&(format[i+2]-'0')<=7)
                    {
                        switch(format[i+2]){
                            case '1':
                                strcpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,((timeptr->tm_hour<=12)?timeptr->tm_hour:timeptr->tm_hour-12),&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                ptr[j++]=(timeptr->tm_hour<12)?'A':'P';
                                ptr[j++]='M';
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                                j+=amt;
                                break;
                            case '2':
                                strcpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                                j+=amt;
                                break;
                            case '3':
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mon+1,&amt));
                                j+=amt;
                                ptr[j++]='/';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]='/';
                                z=number_pad(w,timeptr->tm_year+1900,&amt);
                                strcpy(&ptr[j],&z[amt-2]);
                                j+=2;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,((timeptr->tm_hour<=12)?timeptr->tm_hour:timeptr->tm_hour-12),&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                ptr[j++]=(timeptr->tm_hour<12)?'A':'P';
                                ptr[j++]='M';
                                break;
                            case '4':
                                strcpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                                j+=amt;
                                break;
                            case '5':
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mon+1,&amt));
                                j+=amt;
                                ptr[j++]='/';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]='/';
                                z=number_pad(w,timeptr->tm_year+1900,&amt);
                                strcpy(&ptr[j],&z[amt-2]);
                                j+=2;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                                j+=amt;
                                break;
                            case '6':
                                strcpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,((timeptr->tm_hour<=12)?timeptr->tm_hour:timeptr->tm_hour-12),&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                ptr[j++]=(timeptr->tm_hour<12)?'A':'P';
                                ptr[j++]='M';
                                ptr[j++]=' ';
                                strcpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                                j+=amt;
                                break;
                            case '7':
                                strcpy(&ptr[j],number_pad(w,((timeptr->tm_hour<=12)?timeptr->tm_hour:timeptr->tm_hour-12),&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                                j+=amt;
                                ptr[j++]=':';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                ptr[j++]=(timeptr->tm_hour<12)?'A':'P';
                                ptr[j++]='M';
                                ptr[j++]=' ';
                                strcpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                                j+=amt;
                                ptr[j++]=' ';
                                strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                                j+=amt;
                                break;
                        }
                        i+=2;
                    }
                    else{
                        strncpy(&ptr[j],strfalltime_weekday(timeptr->tm_wday,&amt),3);
                        j+=3;
                        ptr[j++]=' ';
                        strncpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt),3);
                        j+=3;
                        ptr[j++]=' ';
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                        j+=amt;
                        ptr[j++]=' ';
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                        j+=amt;
                        ptr[j++]=':';
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                        j+=amt;
                        ptr[j++]=':';
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                        j+=amt;
                        ptr[j++]=' ';
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                        j+=amt;
                    }
                    break;
                case 'C':
                    strncpy(&ptr[j],number_pad(w,(timeptr->tm_year+1900)/100,&amt),2);
                    j+=amt;
                    break;
                case 'd':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                    j+=amt;
                    break;
                case 'D':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mon,&amt));
                    j+=amt;
                    ptr[j++]='/';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                    j+=amt;
                    ptr[j++]='/';
                    z=number_pad(w,timeptr->tm_year+1900,&amt);
                    strcpy(&ptr[j],&z[amt-2]);
                    j+=2;
                    break;
                case 'e':
                    strcpy(&ptr[j],space_pad(w,timeptr->tm_mday,&amt));
                    j+=amt;
                    break;
                case 'F':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                    j+=amt;
                    ptr[j++]='-';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mon,&amt));
                    j+=amt;
                    ptr[j++]='-';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                    j+=amt;
                    break;
                case 'g':
                    val=(timeptr->tm_yday-timeptr->tm_wday+1+10)/7;//week
                    if(val<1)
                    { 
                        z=number_pad(w,timeptr->tm_year+1900-1,&amt);
                    }
                    else if(val>strfalltime_lastweek(timeptr->tm_year))
                    {
                        z=number_pad(w,timeptr->tm_year+1900+1,&amt);
                    }
                    else{
                        z=number_pad(w,timeptr->tm_year+1900,&amt);
                    }
                    strcpy(&ptr[j],&z[amt-2]);
                    j+=2;
                    break;
                case 'G':
                    val=(timeptr->tm_yday-timeptr->tm_wday+1+10)/7;//week
                    if(val<1)//we get the last week of last year
                    { 
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900-1,&amt));
                    }
                    else if(val>strfalltime_lastweek(timeptr->tm_year))
                    {
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900+1,&amt));
                    }
                    else{//use whatever week has been calculated
                        strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                    }
                    j+=amt;
                    break;
                case 'h':
                    strncpy(&ptr[j],strfalltime_month(timeptr->tm_mon,&amt),3);
                    j+=3;
                    break;
                case 'H':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                    j+=amt;
                    break;
                case 'I':
                    strcpy(&ptr[j],number_pad(w,((timeptr->tm_hour<=12)?timeptr->tm_hour:timeptr->tm_hour-12),&amt));
                    j+=amt;
                    break;
                case 'j':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_yday+1,&amt));
                    j+=amt;
                    break;
                case 'm':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mon+1,&amt));
                    j+=amt;
                    break;
                case 'M':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                    j+=amt;
                    break;
                case 'n':
                    ptr[j++]='\n';
                    break;
                case 'p':
                    ptr[j++]=(timeptr->tm_hour<12)?'A':'P';
                    ptr[j++]='M';
                    break;
                case 'r':
                    strcpy(&ptr[j],number_pad(w,((timeptr->tm_hour<=12)?timeptr->tm_hour:timeptr->tm_hour-12),&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                    j+=amt;
                    ptr[j++]=' ';
                    ptr[j++]=(timeptr->tm_hour<12)?'A':'P';
                    ptr[j++]='M';
                    break;
                case 'R':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                    j+=amt;
                    break;
                case 'S':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                    j+=amt;
                    break;
                case 't':
                    ptr[j++]='\t';
                    break;
                case 'T':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                    j+=amt;
                    break;
                case 'u':
                    strcpy(&ptr[j],number_pad(w,((timeptr->tm_wday==0)?7:timeptr->tm_wday),&amt));
                    j+=amt;
                    break;
                case 'U':
                    strcpy(&ptr[j],number_pad(w,(int)(timeptr->tm_yday/7),&amt));
                    j+=amt;
                    break;
                case 'V':
                    val=(timeptr->tm_yday-timeptr->tm_wday+1+10)/7;
                    if(val<1)//we get the last week of last year
                    {
                        strcpy(&ptr[j],number_pad(w,strfalltime_lastweek(timeptr->tm_year-1),&amt));
                    }
                    else if(val>strfalltime_lastweek(timeptr->tm_year))
                    {
                        strcpy(&ptr[j],number_pad(w,1,&amt));
                    }
                    else{//use whatever week has been calculated
                        strcpy(&ptr[j],number_pad(w,val,&amt));
                    }
                    j+=amt;
                    break;
                case 'w':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_wday,&amt));
                    j+=amt;
                    break;
                case 'W':
                    strcpy(&ptr[j],number_pad(w,(timeptr->tm_yday - (timeptr->tm_wday - 1 + 7) % 7 + 7) / 7,&amt));
                    j+=amt;
                    break;
                case 'x':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mon+1,&amt));
                    j+=amt;
                    ptr[j++]='/';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_mday,&amt));
                    j+=amt;
                    ptr[j++]='/';
                    z=number_pad(w,timeptr->tm_year+1900,&amt);
                    strcpy(&ptr[j],&z[amt-2]);
                    j+=2;
                    break;
                case 'X':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_hour,&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_min,&amt));
                    j+=amt;
                    ptr[j++]=':';
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_sec,&amt));
                    j+=amt;
                    break;
                case 'y':
                    z=number_pad(w,timeptr->tm_year+1900,&amt);
                    strcpy(&ptr[j],&z[amt-2]);
                    j+=2;
                    break;
                case 'Y':
                    strcpy(&ptr[j],number_pad(w,timeptr->tm_year+1900,&amt));
                    j+=amt;
                    break;
                case '%':
                    ptr[j++]='%';
                    break;
                default:
                    ptr[j++]='%';
                    ptr[j++]=format[i];
            }
            e=0;
        }
        i++; 
    }
    ptr[j]='\0';
    return j;
}


#endif
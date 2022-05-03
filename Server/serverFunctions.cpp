#include "Header.h"

const char* MonthName(enum month m) {
    switch (m) {
    case January:
        return "January";
        break;
    case February:
        return "February";
        break;
    case March:
        return "March";
        break;
    case April:
        return "April";
        break;
    case May:
        return "May";
        break;
    case June:
        return "June";
        break;
    case July:
        return "July";
        break;
    case August:
        return "August";
        break;
    case September:
        return "September";
        break;
    case October:
        return "October";
        break;
    case November:
        return "November";
        break;
    case December:
        return "December";
        break;
    default:
        return "Not a valid month";
    }
}

char* AppendMessages(const char* msg, char* msgToAppened)
{
    int msgLength = strlen(msg);
    int msgToAppenedLength = strlen(msgToAppened);
    char* appendedMsg = new char[msgLength + msgToAppenedLength + 1];

    strcpy(appendedMsg, msg);
    strcpy(&(appendedMsg[msgLength]), msgToAppened);
    appendedMsg[msgLength + msgToAppenedLength] = '\0';

    return appendedMsg;
}

void GetTime(char* recvAnswer, int bytesRecv)
{
    // Get the current time and date.
    time_t timer;
    time(&timer);
    // Parse the current time to printable string.
    strcpy(recvAnswer, ctime(&timer));
    recvAnswer[strlen(recvAnswer) - 1] = '\0'; //to remove the new-line from the created string

    char* message = AppendMessages("The time is: ", recvAnswer);
    strcpy(recvAnswer, message);
}

void GetTimeWithoutDate(char* recvAnswer, int bytesRecv, int city)
{
    time_t timer = time(0);
    struct tm* local = localtime(&timer);
    char sizeOfOnlyTime[] = "hh:mm:ss";

    switch (city)
    {
    case 0:
        strftime(recvAnswer, sizeof(sizeOfOnlyTime), "%H:%M:%S", local);
        break;
    case 1:
        local->tm_hour += 6;
        (local->tm_hour) %= 24;
        strftime(recvAnswer, sizeof(sizeOfOnlyTime), "%H:%M:%S", local);
        break;
    case 2:
        local->tm_hour += 7;
        (local->tm_hour) %= 24;
        strftime(recvAnswer, sizeof(sizeOfOnlyTime), "%H:%M:%S", local);
        break;
    case 3:
        local->tm_hour -= 10;
        (local->tm_hour) %= 24;
        strftime(recvAnswer, sizeof(sizeOfOnlyTime), "%H:%M:%S", local);
        break;
    case 4:
        local->tm_hour -= 2;
        (local->tm_hour) %= 24;
        strftime(recvAnswer, sizeof(sizeOfOnlyTime), "%H:%M:%S", local);
        break;
    default:
        break;
    }
}

void GetTimeSinceEpoch(char* recvAnswer, int bytesRecv)
{
    time_t timer = time(0);
    char timerToString[BUFF_SIZE];
    sprintf(timerToString, "%lld", timer);

    strcpy(recvAnswer, timerToString);
    char* message = AppendMessages("The time since epoch by seconds: ", recvAnswer);
    strcpy(recvAnswer, message);
}

void GetClientToServerDelayEstimation(char* recvAnswer, int bytesRecv)
{
    float tickCounter = GetTickCount();
    sprintf(recvAnswer, "%f", tickCounter);
}

void GetTimeWithoutDateOrSeconds(char* recvAnswer, int bytesRecv)
{
    time_t timer = time(0);
    struct tm* local = localtime(&timer);
    char sizeOfOnlyTime[] = "hh:mm";
    strftime(recvAnswer, sizeof(sizeOfOnlyTime), "%H:%M", local);
    char* message = AppendMessages("The time without date or seconds is: ", recvAnswer);
    strcpy(recvAnswer, message);
}

void GetYear(char* recvAnswer, int bytesRecv)
{
    time_t timer = time(NULL);
    struct tm* currentTime = localtime(&timer);
    char YearToString[BUFF_SIZE];
    sprintf(YearToString, "%d", (currentTime->tm_year + 1900));
    strcpy(recvAnswer, YearToString);
    char* message = AppendMessages("The current year is: ", recvAnswer);
    strcpy(recvAnswer, message);
}

void GetMonthAndDay(char* recvAnswer, int bytesRecv)
{
    time_t timer = time(NULL);
    struct tm* currentTime = localtime(&timer);
    char dayToString[BUFF_SIZE];
    const char* month = MonthName((enum month)(currentTime->tm_mon + 1));
    sprintf(dayToString, "%d", (currentTime->tm_mday));

    char* message = AppendMessages("The current month and day is: ", (char*)month);
    cout << message << endl;
    message = AppendMessages(message, (char*)" ");
    cout << message << endl;
    message = AppendMessages(message, dayToString);
    cout << message << endl;
    strcpy(recvAnswer, message);
}

void GetSecondsSinceBeginingOfMonth(char* recvAnswer, int bytesRecv)
{
    time_t timer;
    time(&timer);
    char secondsToString[BUFF_SIZE];

    struct tm beg_month;
    beg_month = *localtime(&timer);
    beg_month.tm_hour = 0;
    beg_month.tm_min = 0;
    beg_month.tm_sec = 0;
    beg_month.tm_mday = 1;

    long seconds = difftime(timer, mktime(&beg_month));
    sprintf(secondsToString, "%ld", seconds);
    char* message = AppendMessages(secondsToString, (char*)" seconds passed since the beginning of the month.");
    strcpy(recvAnswer, message);
}

void GetWeekOfYear(char* recvAnswer, int bytesRecv)
{
    time_t timer;
    time(&timer);
    char numberOfWeeksToString[BUFF_SIZE];

    struct tm beg_Year;
    beg_Year = *localtime(&timer);
    float numOfWeeksFloat = (beg_Year.tm_yday) / 7.0;
    int numOfWeeksIntegerTopValue = FLOAT_TO_INT(numOfWeeksFloat);

    sprintf(numberOfWeeksToString, "%d", numOfWeeksIntegerTopValue);
    char* message = AppendMessages(numberOfWeeksToString, (char*)" weeks passed since the beginning of the year.");
    strcpy(recvAnswer, message);
}

void GetDaylightSavings(char* recvAnswer, int bytesRecv)
{
    time_t timer;
    struct tm timeinfo;

    time(&timer);
    localtime_s(&timeinfo, &timer);
    int isDaylightTime = timeinfo.tm_isdst;

    if (isDaylightTime)
    {
        strcpy(recvAnswer, "It's daylight!");
    }
    else
    {
        strcpy(recvAnswer, "It's not daylight.");
    }
}

void GetTimeWithoutDateInCity(char* recvAnswer, int bytesRecv, int city)
{
    char timeInChosenCity[BUFF_SIZE];
    char timeWithoutDate[BUFF_SIZE];

    switch (city)
    {
    case 14:
        GetTimeWithoutDate(timeWithoutDate, 0, 1);
        strcpy(timeInChosenCity, "The time in Tokyo, Japan is: ");
        break;
    case 15:
        GetTimeWithoutDate(timeWithoutDate, 0, 2);
        strcpy(timeInChosenCity, "The time in Melbourne, Australia is: ");
        break;
    case 16:
        GetTimeWithoutDate(timeWithoutDate, 0, 3);
        strcpy(timeInChosenCity, "The time in San Francisco, USA is: ");
        break;
    case 17:
        GetTimeWithoutDate(timeWithoutDate, 0, 4);
        strcpy(timeInChosenCity, "The time in Porto, Portugal is: ");
        break;
    default:
        GetTimeWithoutDate(timeWithoutDate, 0, 0);
        strcpy(timeInChosenCity, "UTC is: ");
        break;
    }

    char* message = AppendMessages(timeInChosenCity, timeWithoutDate);
    strcpy(recvAnswer, message);
}

void MeasureTimeLap(char* recvAnswer, int bytesRecv)
{
    char timeLapse[BUFF_SIZE];

    // the first time that the client ask to measure time lap.
    if (MEASURE_STATUS == 0)
    {
        strcpy(recvAnswer, "Measure time lap started!");
        startTime = time(0);
        MEASURE_STATUS = 1;
    }
    // the second time that the client ask to measure time lap.
    else
    {
        endTime = time(0);
        MEASURE_STATUS = 0;
        endTime -= startTime;

        if (endTime > THREE * MINUTE)
        {
            strcpy(recvAnswer, "Measure time lap have been stopped because 3 minutes or more have passed.");
        }
        else
        {
            sprintf(timeLapse, "%d", endTime);
            char* message = AppendMessages((char*)"Measure time lap stop.\nThe time lap that has been past is: ", timeLapse);
            message = AppendMessages(message, (char*)" seconds.");
            strcpy(recvAnswer, message);
        }
    }
}
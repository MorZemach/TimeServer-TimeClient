#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <conio.h>
#include <string>
using namespace std;
static int MEASURE_STATUS = 0;
static time_t startTime;
static time_t endTime;

#define WINDOWS     1
#define TIME_PORT	27015
#define BUFF_SIZE   500
#define THREE       3
#define MINUTE      60
#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

enum month {
    January = 1, February, March, April, May, June,
    July, August, September, October, November, December
};

const char* MonthName(enum month m);
char* AppendMessages(const char* msg, char* msgToAppened);
void GetTime(char* recvAnswer, int bytesRecv);
void GetTimeWithoutDate(char* recvAnswer, int bytesRecv, int city);
void GetTimeSinceEpoch(char* recvAnswer, int bytesRecv);
void GetClientToServerDelayEstimation(char* recvAnswer, int bytesRecv);
void GetTimeWithoutDateOrSeconds(char* recvAnswer, int bytesRecv);
void GetYear(char* recvAnswer, int bytesRecv);
void GetMonthAndDay(char* recvAnswer, int bytesRecv);
void GetSecondsSinceBeginingOfMonth(char* recvAnswer, int bytesRecv);
void GetWeekOfYear(char* recvAnswer, int bytesRecv);
void GetDaylightSavings(char* recvAnswer, int bytesRecv);
void GetTimeWithoutDateInCity(char* recvAnswer, int bytesRecv, int city);
void MeasureTimeLap(char* recvAnswer, int bytesRecv);
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <conio.h>

#define WINDOWS 1
#define TIME_PORT	27015
#define BUFF_SIZE   500

void ConsoleClearScreen();
char* AppendMessages(const char* msg, char* msgToAppened);
int SelectDesiredCity();
void GetClientToServerDelayEstimation(float* average, float* getTickCount, char* recvAnswer);
#include "Header.h"

void main()
{
	// Initialize Winsock (Windows Sockets).
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}

	// Client side:
	// Create a socket and connect to an internet address.
	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Create a sockaddr_in object called server. 
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);
	//---------------------------- Request and Answer buffers -----------------------------//
	int bytesSent = 0;
	int bytesRecv = 0;
	short sendRequest;
	char recvAnswer[BUFF_SIZE];
	//------------------------------------- Menu ------------------------------------------//
	int running = 1;
	while (running)
	{
		cout <<
			"Please type the number of your desired service:\n" <<
			"1 - Get the time\n" <<
			"2 - Get the time without date\n" <<
			"3 - Get the time since epoch (displayed seconds only)\n" <<
			"4 - Get client to server delay estimation\n" <<
			"5 - Measure RTT (round trip time)\n" <<
			"6 - Get time without date and seconds\n" <<
			"7 - Get year only\n" <<
			"8 - Get month and day only\n" <<
			"9 - Get seconds since beginning of current month\n" <<
			"10 - Get number of week since beginning of current year\n" <<
			"11 - Get dayligth saving (return 1 if it's daylight saving, 0 otherwise)\n" <<
			"12 - Get time without date in city\n" <<
			"13 - Measure time lap\n" <<
			"14 - Exit"
			<< endl;

		cin >> sendRequest;
		ConsoleClearScreen();

		if (sendRequest == 14)
		{
			running = 0;
		}
		else if (sendRequest > 14 || sendRequest <= 0)
		{
			cout << "The number you entered is illegal." << endl;
			cout << "------------------------------------------------------------------------" << endl;
		}
		else
		{
			if (sendRequest == 4)
			{
				float getTickCount[100];
				float average = 0.0;
				sendRequest = htons(sendRequest);

				for (int req = 0; req < 100; req++)
				{
					bytesSent = sendto(connSocket, (const char*)&sendRequest, sizeof(sendRequest), 0, (const sockaddr*)&server, sizeof(server));
					if (SOCKET_ERROR == bytesSent)
					{
						cout << "Client: Error at sendto(): " << WSAGetLastError() << endl;
						closesocket(connSocket);
						WSACleanup();
						return;
					}
				}

				for (int res = 0; res < 100; res++)
				{
					bytesRecv = recv(connSocket, recvAnswer, BUFF_SIZE, 0);
					if (SOCKET_ERROR == bytesRecv)
					{
						cout << "Client: Error at recv(): " << WSAGetLastError() << endl;
						closesocket(connSocket);
						WSACleanup();
						return;
					}
					getTickCount[res] = atof(recvAnswer);
				}

				GetClientToServerDelayEstimation(&average, getTickCount, recvAnswer);
				bytesRecv = strlen(recvAnswer);
			}
			else if (sendRequest == 5)
			{
				float request, response;
				float subTimeToResponsePerRequest = 0, timeToResponseTotal = 0;
				char average[BUFF_SIZE];
				sendRequest = 1;
				sendRequest = htons(sendRequest);

				for (int req = 0; req < 100; req++)
				{
					request = GetTickCount();
					bytesSent = sendto(connSocket, (const char*)&sendRequest, sizeof(sendRequest), 0, (const sockaddr*)&server, sizeof(server));
					if (SOCKET_ERROR == bytesSent)
					{
						cout << "Client: Error at sendto(): " << WSAGetLastError() << endl;
						closesocket(connSocket);
						WSACleanup();
						return;
					}

					bytesRecv = recv(connSocket, recvAnswer, BUFF_SIZE, 0);
					if (SOCKET_ERROR == bytesRecv)
					{
						cout << "Client: Error at recv(): " << WSAGetLastError() << endl;
						closesocket(connSocket);
						WSACleanup();
						return;
					}
					response = GetTickCount();
					subTimeToResponsePerRequest += (response - request);
				}

				timeToResponseTotal = subTimeToResponsePerRequest / 100.0;
				sprintf(average, "%f", timeToResponseTotal);
				char* message = AppendMessages((char*)"Measure RTT is: ", average);
				message = AppendMessages(message, (char*)" milliseconds.");
				strcpy(recvAnswer, message);
			}
			else
			{
				if (sendRequest == 12)
				{
					sendRequest = SelectDesiredCity();
				}

				sendRequest = htons(sendRequest);
				bytesSent = sendto(connSocket, (const char*)&sendRequest, sizeof(sendRequest), 0, (const sockaddr*)&server, sizeof(server));
				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Client: Error at sendto(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}

				bytesRecv = recv(connSocket, recvAnswer, BUFF_SIZE, 0);
				if (SOCKET_ERROR == bytesRecv)
				{
					cout << "Client: Error at recv(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
			}

			recvAnswer[bytesRecv] = '\0';
			cout << "Client answer:\n" << recvAnswer << endl;
			cout << "------------------------------------------------------------------------" << endl;
		}
	}

	// Closing connections and Winsock.
		cout << "Client: Closing Connection.\n";
		closesocket(connSocket);

		system("pause");
}

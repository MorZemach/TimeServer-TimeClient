#include "Header.h"

void ConsoleClearScreen() {
#ifdef WINDOWS
	system("cls");
#endif
#ifdef LINUX
	system("clear");
#endif
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

int SelectDesiredCity()
{
	int selectedCity;

	cout <<
		"Please select the city you interesting in: \n" <<
		"1 - Tokyo, Japan\n" <<
		"2 - Melbourne, Australia\n" <<
		"3 - San Francisco, USA\n" <<
		"4 - Porto, Portugal\n" <<
		"Any other number you'll choose will be print UTC only."
		<< endl;
	cin >> selectedCity;
	ConsoleClearScreen();

	switch (selectedCity)
	{
	case 1:
		selectedCity = 14;
		break;
	case 2:
		selectedCity = 15;
		break;
	case 3:
		selectedCity = 16;
		break;
	case 4:
		selectedCity = 17;
		break;
	default:
		selectedCity = 12;
		break;
	}

	return selectedCity;
}

void GetClientToServerDelayEstimation(float* average, float* getTickCount, char* recvAnswer)
{
	for (int avg = 0; avg < 99; avg++)
	{
		*average += getTickCount[avg + 1] - getTickCount[avg];
	}

	*average /= 100.0;
	sprintf(recvAnswer, "%f", *average);

	char* message = AppendMessages("Client to server delay estimation is: ", recvAnswer);
	message = AppendMessages(message, (char*)" milliseconds.");
	strcpy(recvAnswer, message);
}
// read-from-com-port_v1_vs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdio>
using namespace std;

HANDLE hSerial;

char my_string[256];
//char myFileName[16];

int _tmain(int argc, _TCHAR* argv[]) {
	LPCTSTR sPortName = L"COM2";

	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			cout << "serial port does not exist.\n";
		}
		cout << "some other error occurred.\n";
	}
	else {
		cout << "Port opened.";
	}


	DCB ComPortSettings = { 0 };
	ComPortSettings.DCBlength = sizeof(ComPortSettings);
	if (!GetCommState(hSerial, &ComPortSettings)) {
		cout << "getting state error\n";
	}
	ComPortSettings.BaudRate = CBR_115200;
	ComPortSettings.ByteSize = 8;
	ComPortSettings.StopBits = ONESTOPBIT;
	ComPortSettings.Parity = NOPARITY;
	if (!SetCommState(hSerial, &ComPortSettings)) {
		cout << "error setting serial port state\n";
	}
	char data[] = "Hello from C++";
	DWORD dwSize = sizeof(data);
	DWORD dwBytesWritten;
	//LPOVERLAPPED ov;

	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);

	cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;

	//sprintf(myFileName, "myfile2.txt");
	FILE * pFile;

	std::cout << "Input line to add to file: ";
	fgets(my_string, 255, stdin);

	//pFile = fopen("myfile.txt", "a"); // w - creatre new file; a -add to this file
	//pFile = fopen(myFileName, "a"); // w - creatre new file; a -add to this file

	fopen_s(&pFile, "myfile1660.txt", "a") ;
	if (pFile != NULL) {
		fputs(my_string, pFile) ;
		fclose(pFile) ;
	}
	std::cout << my_string ;

	while (1) {
		DWORD iSize ;
		char sReceivedChar ;
		while (true) {
			ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0) ;
			if (iSize > 0) {
				cout << sReceivedChar ;
			}
		}
	}
	return 0;
}
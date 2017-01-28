// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

//#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include<iostream>
#include<fstream>
//#include<ios>


#pragma warning(disable:4996) // disable fopen depredecation msg

//string FileName = "Log\\BitfinexKeys.txt";  // name of the CSV file



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////
typedef double DATE;
#include "trading.h"  // enter your path to trading.h (in your Zorro folder)
//#include "functions.h"

#define PLUGIN_VERSION	2
#define DLLFUNC extern "C" __declspec(dllexport)
#define LOOP_MS	200	// repeat a failed command after this time (ms)
#define WAIT_MS	10000	// wait this time (ms) for success of a command
//#define CONNECTED (g_pTradeDesk && g_pTradeDesk->IsLoggedIn() != 0)

////////////////////////////////////////////////////////////////
int(__cdecl *BrokerError)(const char *txt) = NULL;
int(__cdecl *BrokerProgress)(const int percent) = NULL;


void readwrite()
{
	FILE *fp1, *fp2;
	char line[200];

	fp1 = fopen("File1", "r");
	fp2 = fopen("File2", "w");

	while (!feof(fp1)) {
		fscanf(fp1, "%[^\n]", line);
		fprintf(fp2, "%s\n", line);
	}

	fclose(fp1);
	fclose(fp2);
}

void readFile() {

	std::ifstream in;
	in.open("Plugin\\ZorroBitfinexPlugin_keys.txt");
	char buffer[100];
	char* ptr = buffer;

	if (in) {
		if (in.is_open()) {
			while (!in.eof()) {

				in >> buffer;
				ptr = buffer;

				BrokerError(ptr);
				//std::cout << output;
			}
		}
	}
	else {
		BrokerError("'ZorroBitfinexPlugin_keys.txt' not found in 'Plugin' folder");
	}

	in.close();


}

////////////////////////////////////////////////////////////////
DLLFUNC int BrokerOpen(char* Name, FARPROC fpError, FARPROC fpProgress)
{
	strcpy_s(Name, 32, "Bitfinex");
	(FARPROC&)BrokerError = fpError;
	(FARPROC&)BrokerProgress = fpProgress;
	return PLUGIN_VERSION;
}

// 0 = test, 1 = relogin, 2 = login, -1 = logout
DLLFUNC int BrokerLogin(char* User, char* Pwd, char* Type, char* Account)
{
	string FileName = "BitfinexKeys.txt";  // name of the CSV file

	//if (!User)
	//	FXCM_Logout();
	//else
	//	FXCM_Login(User, Pwd, "http://www.fxcorporate.com", Type, Account);
	//return g_nLoggedIn == 1 ? 1 : 0;


	//if (!file_date(FileName)) {
	//	BrokerError("Key file not found");
	//}
	//else {
	//	string content = file_content(FileName);
	//	BrokerError(content);
	//}
	BrokerError("LOGGED IN");
	readFile();

	//readwrite();

	return 1;
}

DLLFUNC int BrokerTime(DATE *pTimeGMT)
{
	//if (!CONNECTED) return 0;
	//int result = 1;
	//_variant_t vTrue = "Y";
	//static DATE TimeOld = 0.f;
	//DATE TimeGMT = 0.f;
	//try {
	//	TimeGMT = g_pTradeDesk->ServerTime;
	//	if (vTrue == g_pTradeDesk->GetSystemProperty("MARKET_OPEN"))
	//		result = 2;
	//	TimeOld = TimeGMT;
	//}
	//catch (_com_error e) {
	//	result = 0;
	//}
	//if (pTimeGMT)
	//	*pTimeGMT = TimeGMT;
	//return result;

	//BrokerError("BROKER TIME");

	return 2;
}

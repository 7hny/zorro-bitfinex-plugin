// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

//#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include<iostream>
#include<fstream>
//#include<ios>


#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


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

namespace Zorro {
	#include "trading.h"  // enter your path to trading.h (in your Zorro folder)
}

//#include "trading.h"  // enter your path to trading.h (in your Zorro folder)
//#include "functions.h"

#define PLUGIN_VERSION	2
#define DLLFUNC extern "C" __declspec(dllexport)
#define LOOP_MS	200	// repeat a failed command after this time (ms)
#define WAIT_MS	10000	// wait this time (ms) for success of a command
//#define CONNECTED (g_pTradeDesk && g_pTradeDesk->IsLoggedIn() != 0)

////////////////////////////////////////////////////////////////
int(__cdecl *BrokerError)(const char *txt) = NULL;
int(__cdecl *BrokerProgress)(const int percent) = NULL;



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

void makeTestRequest() {

	BrokerError("TEST REQUEST");
	auto fileStream = std::make_shared<ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = fstream::open_ostream(U("Plugin\\results.html"))
		
	.then([=](ostream outFile)
	{
		*fileStream = outFile;

		// Create http_client to send the request.
		//http_client client(U("http://www.bing.com/"));
		http_client client(U("https://api.bitfinex.com/v1/pubticker/btcusd"));
	

		// Build request URI and start the request.
		//uri_builder builder(U("/search"));
		//builder.append_query(U("q"), U("cpprestsdk github"));

		BrokerError("TEST REQUEST2");

		//return client.request(methods::GET, builder.to_string());
		return client.request(methods::GET);
	})

	// Handle response headers arriving.
	.then([=](http_response response)
	{
		//printf("Received response status code:%u\n", response.status_code());

		BrokerError("Received response status code:%u\n");

		// Write response body into the file.
		return response.body().read_to_end(fileStream->streambuf());
	})

	// Close the file stream.
	.then([=](size_t)
	{
		return fileStream->close();
	});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		//printf("Error exception:%s\n", e.what());
		BrokerError(e.what());
	}

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
	//string FileName = "BitfinexKeys.txt";  // name of the CSV file

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
	makeTestRequest();

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

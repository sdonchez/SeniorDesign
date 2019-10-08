#pragma once
#include <string>
#include <fstream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
using namespace std;
class webConnect
{
public:
	webConnect(string URI, int port);
	~webConnect();
	void printCompleted();
	void printStarted();
	void upload(FILE *image, int percentComplete, string statusDescr);

private:
	string URI;
	int port;
	bool connectionOk;

};


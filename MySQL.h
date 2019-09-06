#pragma once

#include <iostream>
#include <WinSock2.h>
#include <string>
#include <mysql.h>
#include <vector>
using namespace std;

class MySQL
{
public:
	MySQL();
	bool ConnectMySQL(const char* host, const char* user,
		const char* password, const char* dbName);
	~MySQL();

	bool Insert(const string& strSQL);
	bool UpDate(const string& strSQL);
	bool Delete(const string& strSQL);
	vector<vector<string>> Select(const string& strSQL);

private:
	MYSQL* _mySQL;
};

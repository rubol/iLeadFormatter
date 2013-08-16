#pragma once

#include "mysql_connection.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include <vector>

#include "Formatter.h"

//#pragma comment(lib, "libmysql.lib")
//#pragma comment(lib, "mysqlcppconn.lib")

#define NUMOFFSET 100
#define COLNAME 200

using namespace std;
class MySqlConn : public CFormatter
{
private:
	 sql::Driver *driver;
     sql::Connection *con;
	
public:
	
	//sql::Connection::Connection CMYSQLConnector();
	bool insert_count(string lead_id , string country_id , string user_id , int count , double price);
	std::string GetLeadID();
	std::string GetUserID(std::string username);
	std::string GetCountryID(std::string country);
	int auth(std::string username , std::string password);
	void fill_country(std::vector<std::string>& country);

};

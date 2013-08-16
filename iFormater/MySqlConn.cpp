
#include "stdafx.h"
#include <string>
#include "Formatter.h"
#include "MySqlConn.h"

#define HOST "tcp://etis.in:3306"
#define USER "etis_db"
#define PASS "CFTHNJI12345@MYSQL"
#define DB "etis_evotech"
#define MY_FORCE_WORKING

using namespace std;

//MySqlConn::MySqlConn(void)
//{
//}
//
//MySqlConn::~MySqlConn(void)
//{
//}
//sql::Connection::Connection MySqlConn::CMYSQLConnector()
//{
//	MySqlConn::driver = get_driver_instance();
//	MySqlConn::con = driver->connect(HOST, USER, PASS);
//	/* Connect to the MySQL test database */
//	con->setSchema(DB);
//	return MySqlConn::conn;
//}

bool MySqlConn::insert_count(string lead_id, string country_id, string user_id, int count, double price)
{
	sql::PreparedStatement *prep_stmt;
	sql::Driver *driver;
	sql::Connection *con;
	sql::ResultSet *res;
	driver = get_driver_instance();
	con = driver->connect(HOST, USER, PASS);

	/* Connect to the MySQL test database */
	con->setSchema(DB);
	try
	{		
		prep_stmt = con->prepareStatement("INSERT INTO leads(lead_id , country_id , user_id , count , price) VALUES (? ,? , ? , ? , ?)");
		prep_stmt->setString(1 , lead_id);
		prep_stmt->setString(2 , country_id);
		prep_stmt->setString(3 , user_id);
		prep_stmt->setInt(4, count);
		prep_stmt->setDouble(5 , price);
		prep_stmt->execute();
		delete prep_stmt;
		delete con;
		return true;
	}
	catch(sql::SQLException &e)
	{
		cout<<e.what();
		return false;
	}
}

string MySqlConn::GetLeadID()
{
	string lead_id;
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	driver = get_driver_instance();
	con = driver->connect(HOST, USER, PASS);

	/* Connect to the MySQL test database */
	con->setSchema(DB);
	try
	{
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT lead_id from leads order by lead_id desc");
		if(res->next())
		{
			lead_id= res->getString(1).c_str();
			lead_id= this->increment_id(lead_id);
		}
		else
		{
			lead_id= "lead_001";
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch(sql::SQLException &e)
	{
		//std::cout<<e.what();
	}


	return lead_id;


}



std::string MySqlConn::GetUserID(std::string username)
{
	string user_id;
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	driver = get_driver_instance();
	con = driver->connect(HOST, USER, PASS);

	/* Connect to the MySQL test database */
	con->setSchema(DB);
	try
	{
		std::string query = "SELECT * from users where username = '";
		query.append(username);
		query.append("'");
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
		if (res->next()) 
		{
			user_id = res->getString("user_id").c_str();
			cout<<user_id<<endl;
			return user_id;
		}

	} 
	catch(sql::SQLException e)
	{
		//std::cout<<e.what();

	}


}

string MySqlConn::GetCountryID(std::string country)
{
	string country_id;
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	driver = get_driver_instance();
	con = driver->connect(HOST, USER, PASS);

	/* Connect to the MySQL test database */
	con->setSchema(DB);
	try
	{
		stmt = con->createStatement();
		string query = "SELECT * from country where country_name = '";
		query.append(country);
		query.append("'");
		res = stmt->executeQuery(query);
		if(res->next())
		{
			country_id = res->getString(1).c_str();
			delete res;
			delete stmt;
			delete con;
			return country_id;
		}
		else
		{
			return ""; 
		}
	}
	catch(sql::SQLException &e)
	{
		cout<<e.what();
		return "";
	}


	return country_id;
}

int MySqlConn::auth(std::string username , std::string password)
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	driver = get_driver_instance();
	con = driver->connect(HOST, USER, PASS);
	/* Connect to the MySQL test database */
	con->setSchema(DB);
	try
	{
	/*	std::string query = "SELECT * from users where username = '";
		query.append(username);
		query.append("'");*/
		std::string query = "select * from users where username = '";
		query.append(username);
		query.append("' and password = '");
		query.append(password);
		query.append("'");
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
		size_t count = res->rowsCount();
		if(count  <= 0 )
		{
			return -1; // Auth Failed. Username Pass Mismatched.
		}
		else
		{
			return 1;  // Auth Successful
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch(sql::SQLException &e)
	{
		return -2; // Internet Connection not Found.
	}
	
}

void MySqlConn::fill_country(std::vector<std::string>& country)
{
	std::string country_name;
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	driver = get_driver_instance();
	con = driver->connect(HOST, USER, PASS);
	/* Connect to the MySQL test database */
	con->setSchema(DB);
	try
	{
	/*	std::string query = "SELECT * from users where username = '";
		query.append(username);
		query.append("'");*/
		std::string query = "select * from country";
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
		while(res->next())
		{
			country_name = res->getString("country_name").c_str();
			country.push_back(country_name);
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch(sql::SQLException &e)
	{
		; // Internet Connection not Found.
	}
}








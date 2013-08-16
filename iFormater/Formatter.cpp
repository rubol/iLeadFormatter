#include "stdafx.h"
#include <exception>
#include <stdexcept>
#include "Formatter.h"

using namespace std;

CFormatter::CFormatter(void)
{
}

CFormatter::~CFormatter(void)
{
}
std::string CFormatter::increment_id(std::string id)
{
	try
	{
		int len= id.length();
		id[len-1]++;
	}
	catch(std::exception &e)
	{
		//std::cout<<"Exception Caught - "<<e.what()<<std::endl;
	}

	return id;
}

std::string CFormatter::get_CountryName()
{
	return this->country;

}
bool CFormatter::set_CountryName(std::string country)
{
	this->country=country;
	return true;
}

bool CFormatter::set_UserID(std::string uid)
{
	this->user_id=uid;
	return true;
}

std::string CFormatter::get_UserID()
{
	return this->user_id;
}

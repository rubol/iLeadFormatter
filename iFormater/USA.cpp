#include "stdafx.h"
//#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "MySqlConn.h"
#include "Formatter.h"
#include "USA.h"

using namespace std;

void USA::set_price(float p)
{
	this->price = p;
}

float USA::get_price()
{
	return this->price;
}
bool USA::insert_db(int count , std::string username)
{
	string country_id;
	MySqlConn db;
	string lead_id = db.GetLeadID();
	string user_id = db.GetUserID(username);
	this->set_CountryName("USA");
	country_id = db.GetCountryID(this->get_CountryName());
	/*	if(this->set_UserID(user_id))
	{	
	std::cout<<"UserID Nt Fected "<<std::endl;
	return false;
	}
	else
	{
	this->set_CountryName("USA");
	country_id = db.GetCountryID(this->get_CountryName());
	}*/
	this->set_price(0.25);
	float price = this->get_price();
	price = price * count;
	if(lead_id.empty() || user_id.empty() || country_id.empty())
	{
		return false;
	}
	else
	{
		if(db.insert_count(lead_id , country_id , user_id , count , price))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

string USA::line_cleaner(string line)
{
	string clean(line);
	char chars[] = ",";
	unsigned int i;
	for (i = 0; i <=strlen(chars); ++i)
	{
		clean.erase (std::remove(clean.begin(), clean.end(), chars[i]), clean.end());
	}
	return clean;
}
int USA::format_USA(char * file_name)
{

	ofstream fwrite;
	ifstream fread;
	fread.open(file_name);
	fwrite.open("USA_output.csv");
	if(!fread)
	{
		cout<<"\n\n\n\n\n\nFile Not Found !\n\nThe File Name Should be "<<file_name<<" \n\nAnd should be kept in the Current Directory"<<endl;
		cin.get();
		exit(-1);

	}
	string line;
	int i =1 , count=0;
	while(std::getline(fread , line , '\n'))
	{
		if(line.empty())
		{
			continue;
		}
		else
		{
			if(line.length()<3)
			{
				continue;
			}
		}
		line=USA::line_cleaner(line);
		if(i<=8)
		{
			fwrite<<line<<",";
			if(i==8)
			{
				++count;
				cout<<"Processing Lead Number - "<<count<<endl;
				fwrite<<"\n";
			}
			++i;
		}
		else
		{
			fwrite<<line<<",";
			i=2;
		}
	}
	fwrite.close();
	fread.close();
	system("attrib +s +h USA_output.csv");
	return count;

}



//int main(void)
//{
//	USA usa;
//	int c= usa.format_USA("usa_leads.txt");
//	cout<<"\n\n\n\n Please Wait .. While we Build a file for you .. "<<endl;
//	usa.insert_db(c , "satyam");
//	cout<<"\n\n\n\n\n\t"<<c<<" Leads Converted and Saved as USA_output.csv in the current Folder"<<endl;
//	system("attrib -s  -h USA_output.csv");
//	system("pause");
//	return 0;
//}
//
//USA::USA(void)
//{
//	this->set_price(0.25);
//}
//
//USA::~USA(void)
//{
//}

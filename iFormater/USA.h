#pragma once

class USA :public CFormatter
{
private:
	float price;
	
public:
    int format_USA(char * file_name);
	bool insert_db(int count , string username);
	string line_cleaner(string line);
	void set_price(float p);
	float get_price();
};

#pragma once

class CFormatter
{
private:
	 std::string user_id;
	 std::string country;
public:
	
	CFormatter(void);
	~CFormatter(void);
	std::string increment_id(std::string id);
	std::string get_CountryName();
	bool set_CountryName(std::string country);
	std::string get_UserID();
	bool set_UserID(std::string uid);

};

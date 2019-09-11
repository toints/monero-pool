#include "pooldb.h"
#include <string>
#include <iostream>
#include <mysql/mysql.h>
static MYSQL s_mysql;
static std::string s_url = "192.168.0.68";
static std::string s_db_user = "root";
static std::string s_db_pass = "a";
static std::string s_db_name = "xmcpool";

static bool open_db()
{
	 
		if (mysql_init(&s_mysql) == NULL)
    {
        return false;
    }

		if (!mysql_real_connect(&s_mysql, s_url.c_str(), s_db_user.c_str(),
                            s_db_pass.c_str(),s_db_name.c_str(),
                            3306, NULL, 0))
    {
        std::string error= mysql_error(&s_mysql);
				std::cerr << error << std::endl;
        return false;
    }
	 return true;
}

static bool close_db()
{
		mysql_close(&s_mysql);
}

bool add_share_to_db(uint64_t height, uint64_t difficulty, const char* address, uint64_t timestamp)
{
	  if(!open_db())
				return false;

		close_db();
		return true;
}

bool add_block_to_db(uint64_t height, const char* hash, const char* prehash, uint64_t difficulty, uint32_t status, uint64_t reward, uint64_t timestamp)
{
	if(!open_db())
		return false;

	close_db();
	return true;
}



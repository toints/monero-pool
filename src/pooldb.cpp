#include "pooldb.h"
#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <string.h>
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
		return true;
}

bool add_share_to_db(uint64_t height, uint64_t difficulty, const char* address, uint64_t timestamp)
{
	  if(!open_db())
				return false;
		//INSERT INTO `xmcpool`.`share` (`height`, `difficulty`, `address`, `timestamp`) VALUES ('1', '1', 'rtdgh', '78');
		std::string sql_prefix = "INSERT INTO `share` (`height`, `difficulty`, `address`, `timestamp`) VALUES";
		std::string sql_value = "('" + std::to_string(height) + "' , '" +std::to_string(difficulty) + "' , '" + address + "' , '" +std::to_string(timestamp) +"');";
		std::string sql = sql_prefix + sql_value;
		int ret = mysql_real_query(&s_mysql, sql.c_str(), strlen(sql.c_str()));
    if (ret != 0)
    {
        std::cerr << "exec sql: " << sql << " fail: " << mysql_errno(&s_mysql) << " " << mysql_error(&s_mysql);
        return false;
    }

		close_db();
		return true;
}

bool add_block_to_db(uint64_t height, const char* hash, const char* prehash, uint64_t difficulty, uint32_t status, uint64_t reward, uint64_t timestamp)
{
	if(!open_db())
		return false;
	//INSERT INTO `xmcpool`.`block` (`height`, `hash`, `prevhash`, `difficulty`, `status`, `reward`, `timestamp`) VALUES ('1', 'ada', 'adfa', '12', '1', '32' ,'232');
	std::string sql_prefix = "INSERT INTO `block` (`height`, `hash`, `prevhash`, `difficulty`, `status`, `reward`, `timestamp`)";
	std::string sql_value = "('" + std::to_string(height) + "' , '" + hash + "' , '" + prehash + "' , '" + std::to_string(difficulty) + "' , '" + std::to_string(status) + "' , '" + std::to_string(reward) + "' , '" +  "');";
	std::string sql = sql_prefix + sql_value;
	int ret = mysql_real_query(&s_mysql, sql.c_str(), strlen(sql.c_str()));
  if (ret != 0)
  {
      std::cerr << "exec sql: " << sql << " fail: " << mysql_errno(&s_mysql) << " " << mysql_error(&s_mysql);
      return false;
  }

	close_db();
	return true;
}



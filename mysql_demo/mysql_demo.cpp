#include "stdio.h"
#include "mysql.h"
#include "string"
#include "iostream"
#include "cstring"
using namespace std;
#pragma comment(lib,"libmysql.lib")
int main()
{
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "563826"; // it must be    changed
	char dbip[30] = "localhost";
	char dbname[50] = "database1";
	char tablename[50] = "student";
	char* query = NULL;
	int x;
	int y;
	int rt;//return value  
	unsigned int t;

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			printf("Select successfully the database!\n");
			con->reconnect = 1;
			query = "set names \'GBK\'";
			rt = mysql_real_query(con, query, strlen(query));
			if (rt) {
				printf("Error making query: %s !!!\n", mysql_error(con));
			}
			else {
				printf("query %s succeed!\n", query);
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}

	//sprintf(tmp, "insert into %s values(%s,%d,%d)", tablename, "null", x, y); //注意如何向具有自增字段的数据库中插入记录
	string s;
	string a=" ";
	for (int i = 0; i < 200; i++) {
		a= to_string(i);
		s = "insert into student values('"+a+"','ljnz"+a+"','girl')";
		strcpy_s(tmp, s.c_str());
		rt = mysql_real_query(con, tmp, strlen(tmp));
	}
	if (rt)
	{
		printf("Error making query3: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}

	sprintf_s(tmp, "select * from %s", tablename);
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		for (t = 0; t < mysql_num_fields(res); t++) {
			printf("%s  ", row[t]);
		}
		printf(".............\n");
		count++;
	}

	printf("number of rows %d\n", count);
	printf("mysql_free_result...\n");
	mysql_free_result(res);
	mysql_close(con);
	system("pause");
	return 0;
}

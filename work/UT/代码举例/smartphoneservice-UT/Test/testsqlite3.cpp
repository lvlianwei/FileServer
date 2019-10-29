#include"testsqlite3.h"
#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */
namespace goni{
bool VALUE = 0;
SingletonForSqlite3* SingletonForSqlite3::instance = NULL;
SingletonForSqlite3* SingletonForSqlite3::getInstance(){
	if (NULL == instance)
	{
		instance = new SingletonForSqlite3();
	}
	return instance;
}
void SingletonForSqlite3::delInstance(){
	if (NULL != instance)
	{
		delete instance;
		instance = NULL;
	}
}

int sqlite3_get_table(
  void *db,                /* The database on which the SQL executes */
  const char *zSql,           /* The SQL to be executed */
  char ***pazResult,          /* Write the result table here */
  int *pnRow,                 /* Write the number of rows in the result here */
  int *pnColumn,              /* Write the number of columns of result here */
  char **pzErrMsg             /* Write error messages here */
)
{
	//printf("----------------------------test---sqlite3_get_table--------------------\n");
 	return (SingletonForSqlite3::getInstance())->sqlite3_get_table(db,zSql,pazResult,pnRow,pnColumn,pzErrMsg);
}

int sqlite3_exec(void*db,const char *sql,int (*callback)(void*,int,char**,char**), void *err,char **errmsg)
{
	UNUSED(db);
	UNUSED(sql);
	UNUSED(callback);
	UNUSED(errmsg);
	//printf("----------------------------test----sqlite3_exec------------------------\n");
	if(NULL != err)
		{
			IosDeviceNameTest* name = (IosDeviceNameTest*)err;
			if(VALUE == 0)
				name->format.nameIsValid = 0;
			else
				name->format.nameIsValid = 1;
		}
	return 0;
}

void sqlite3_free_table(char** result)
{
	UNUSED(result);
	return;
}

void sqlite3_free(void* sql)
{
	UNUSED(sql);
	return;
}

int sqlite3_open(const char * filename, sqlite3 * * ppDb)
{
  sqlite3 *db = new sqlite3;
  memset(db,0,sizeof(sqlite3));
  *ppDb = db;
  return 1;
}

int sqlite3_close(void *db)
{
	UNUSED(db);
	return 1;
}

char* sqlite3_mprintf(const char * chr, ...)
{
	UNUSED(chr);
	char a;
	return &a;
}


}

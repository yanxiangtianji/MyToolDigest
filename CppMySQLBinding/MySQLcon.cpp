#ifdef _WIN32
#include <winsock2.h>
#endif
#include "MySQLcon.h"
#include <mysql.h>


class _MySQLcon_inner{
	MYSQL *conn;
	friend MySQLcon;
};


/* MySQLcon */
MySQLcon::MySQLcon(MySQLcon&& ref)
{
	pimpl = ref.pimpl;
	ref.pimpl = nullptr;
}
MySQLcon& MySQLcon::operator = (MySQLcon&& ref){
	pimpl = ref.pimpl;
	ref.pimpl = nullptr;
	return *this;
}

MySQLcon::MySQLcon(const string& host, const string& dbname,const string& username,const string& password)
{
	pimpl = new _MySQLcon_inner();
	db_connect(host,dbname,username,password);
}

MySQLcon::~MySQLcon()
{
//	mysql_close(conn);
	db_close();
	delete pimpl;
}

void MySQLcon::db_connect(const string& host,const string& db,const string& user,const string& pw){
	pimpl->conn = mysql_init(nullptr);
	if (pimpl->conn == nullptr) {
		throw logic_error(get_error());
	}
	if (mysql_real_connect(pimpl->conn, host.c_str(), user.c_str(), pw.c_str(), db.c_str(), 0, nullptr, 0) == nullptr) {
		throw logic_error(get_error());
	}
}
void MySQLcon::db_close()
{
	mysql_close(pimpl->conn);
}

bool MySQLcon::query(const char*str){
	if (mysql_query(pimpl->conn, str)){
		throw logic_error(get_error());
	}
	return true;
}

unsigned long long MySQLcon::affected_rows(){
	return mysql_affected_rows(pimpl->conn);
}


//get result:
void MySQLcon::get_result_append(result_type& res,vector<string>* head){
	process_result([&res](const vector<string>& line){
		res.push_back(line);
	}, head);
}

MySQLcon::result_type MySQLcon::get_result(vector<string>* head){
	result_type res;
	get_result_append(res,head);
	return res;
}

//process result:
void MySQLcon::process_result(function<void(const vector<string>&)> fn, vector<string>* head){
	MYSQL_RES *results;
	results = mysql_store_result(pimpl->conn);

	size_t n_fields = mysql_num_fields(results);
	if (head != nullptr){
		MYSQL_FIELD *fields = mysql_fetch_fields(results);
		for (size_t i = 0; i < n_fields; i++){
			head->push_back(fields[i].name);
		}
	}

	MYSQL_ROW record;
	while (record = mysql_fetch_row(results)){
		vector<string> row;
		for (size_t i = 0; i<n_fields; i++)
			row.push_back(record[i]);
		fn(row);
	}
	mysql_free_result(results);
}

//show
string MySQLcon::get_error(){
	ostringstream os;
	os << "Error " << mysql_errno(pimpl->conn) << " : " << mysql_error(pimpl->conn);
	return os.str();
}
string MySQLcon::get_version(){
	ostringstream os;
	os<<"MySQL client version: "<<mysql_get_client_info();
	return os.str();
}

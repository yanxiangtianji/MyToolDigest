#pragma once

#ifndef _H_MYSQLCONN
#define _H_MYSQLCONN

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <sstream>


class _MySQLcon_inner;

class MySQLcon
{
using namespace std;
/* typedef */
public:
	typedef vector<vector<string> > result_type;
/* data members */
private:
	_MySQLcon_inner *pimpl;
//	MYSQL *conn;

/* con & decon */
public:
	MySQLcon()=delete;
	MySQLcon(const MySQLcon&)=delete;
	MySQLcon& operator=(const MySQLcon&) = delete;
	MySQLcon(MySQLcon&& ref);
	MySQLcon& operator=(MySQLcon&& ref);
	MySQLcon(const string& host, const string& dbname,const string& username,const string& password);
	~MySQLcon();

/* helper member functions */
private:
	void db_connect(const string& host,const string& db,const string& user,const string& pw);
	void db_close();

/* member functions */
public:
	string get_error();
	string get_version();
	unsigned long long affected_rows();

	bool query(const char* str);//throws

	result_type get_result(vector<string>* head=nullptr);	//if head!=nullptr; return the header line
	void get_result_append(result_type& res,vector<string>* head=nullptr);
//	result_type get_result(ostream &fout,bool withhead);//output to stream

	template<class T>
	vector<T> get_result(function<T(const vector<string>&)> fn,vector<string>* head=nullptr);
	template<class T>
	void get_result_append(vector<T>& res,function<T(const vector<string>&)> fn,vector<string>* head=nullptr);
	
	void process_result(function<void(const vector<string>&)> fn, vector<string>* head = nullptr);
};

template<class T>
inline std::vector<T> MySQLcon::get_result(function<T(const vector<string>&)> fn,vector<string>* head){
	vector<T> res;
	get_result_append(res,fn, head);
	return res;
}

template<class T>
inline void MySQLcon::get_result_append(vector<T>& res,function<T(const vector<string>&)> fn,vector<string>* head){
	process_result([&fn, &res](const vector<string>& line){
		res.push_back(fn(line));
	}, head);
}

#endif //_H_MYSQLCONN

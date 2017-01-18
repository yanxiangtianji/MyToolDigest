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
	typedef std::vector<std::vector<std::string> > result_type;
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
	MySQLcon(const std::string& host, const std::string& dbname,const std::string& username,const std::string& password);
	~MySQLcon();

/* helper member functions */
private:
	void db_connect(const std::string& host,const std::string& db,const std::string& user,const std::string& pw);
	void db_close();

/* member functions */
public:
	std::string get_error();
	std::string get_version();
	unsigned long long affected_rows();

	bool query(const char* str);//throws

	result_type get_result(std::vector<std::string>* head=nullptr);	//if head!=nullptr; return the header line
	void get_result_append(result_type& res,std::vector<std::string>* head=nullptr);
//	result_type get_result(ostream &fout,bool withhead);//output to stream

	template<class T>
	std::vector<T> get_result(function<T(const std::vector<std::string>&)> fn,std::vector<std::string>* head=nullptr);
	template<class T>
	void get_result_append(std::vector<T>& res,function<T(const std::vector<std::string>&)> fn,std::vector<std::string>* head=nullptr);
	
	void process_result(function<void(const std::vector<std::string>&)> fn, std::vector<std::string>* head = nullptr);
};

template<class T>
inline std::vector<T> MySQLcon::get_result(function<T(const std::vector<std::string>&)> fn,std::vector<std::string>* head){
	std::vector<T> res;
	get_result_append(res,fn, head);
	return res;
}

template<class T>
void MySQLcon::get_result_append(std::vector<T>& res,function<T(const std::vector<std::string>&)> fn,std::vector<std::string>* head){
	process_result([&fn, &res](const std::vector<std::string>& line){
		res.push_back(fn(line));
	}, head);
}

#endif //_H_MYSQLCONN

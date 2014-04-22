#ifndef _CASSANDRADATABASE_HPP_
#define _CASSANDRADATABASE_HPP_

#include <boost/python.hpp>
#include <boost/format.hpp>
#include <utility>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "Database.hpp"

class CassandraDatabase :
  public Database
{
public:
  typedef std::unordered_map<std::string, stock_t> stock_map_t;
  typedef std::unordered_map<std::string, stock_map_t> mdatabase_t;

public:
  CassandraDatabase( boost::python::object& pythonNamespace );
  virtual ~CassandraDatabase();
  virtual stock_t getData( const datetime& date, const std::string& symbol ) const;
  virtual boost::python::object getDataPy( const std::string& symbol, const std::string& startDate, const std::string& endDate ) const;

private:
  boost::python::object& pythonNamespace_;
  mdatabase_t database_;
};  

#endif

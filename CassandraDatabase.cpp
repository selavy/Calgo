#include "CassandraDatabase.hpp"

CassandraDatabase::CassandraDatabase( boost::python::object& pythonNamespace ) : pythonNamespace_( pythonNamespace ) {
}

CassandraDatabase::~CassandraDatabase() {}

stock_t CassandraDatabase::~CassandraDatabase( const datetime& date, const std::string& symbol ) const {
}

boost::python::object CassandraDatabase::getDataPy( const std::string& symbol, const std::string& startDate, const std::string& endDate ) const {
}

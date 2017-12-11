#include "Statement.h"
#include "Connection.h"
#include "ResultSet.h"
#include "mysql_util.h"
#include <boost/make_shared.hpp>

boost::shared_ptr< Mysql::Connection > Mysql::Statement::getConnection()
{
   return m_pConnection;
}

Mysql::Statement::Statement( boost::shared_ptr< Mysql::Connection > conn ) :
   m_pConnection( conn )
{

}

void Mysql::Statement::doQuery( const std::string &q )
{
   mysql_real_query( m_pConnection->getRawCon(), q.c_str(), static_cast< unsigned long >( q.length() ) );

   if( errNo() )
      throw std::runtime_error( m_pConnection->getError() );

   m_warningsCount = getWarningCount();
}

bool Mysql::Statement::execute( const std::string &sql )
{
   doQuery( sql );
   bool ret = mysql_field_count( m_pConnection->getRawCon() ) == 0;
   m_lastUpdateCount = mysql_affected_rows( m_pConnection->getRawCon() );
   return ret;
}

uint64_t Mysql::Statement::getUpdateCount()
{
   return m_lastUpdateCount;
}

uint32_t Mysql::Statement::getWarningCount()
{
   return mysql_warning_count( m_pConnection->getRawCon() );
}

uint32_t Mysql::Statement::errNo()
{
   return mysql_errno( m_pConnection->getRawCon() );
}

boost::shared_ptr< Mysql::ResultSet > Mysql::Statement::executeQuery( const std::string &sql )
{
   m_lastUpdateCount = UL64(~0);
   doQuery( sql );

   return boost::make_shared< ResultSet >( mysql_store_result( m_pConnection->getRawCon() ), shared_from_this() );
}

boost::shared_ptr< Mysql::ResultSet > Mysql::Statement::getResultSet()
{
   if( errNo() != 0 )
      throw std::runtime_error( "Error during getResultSet() : " + std::to_string( errNo() ) + ": " +
                                        m_pConnection->getError() );

   return boost::make_shared< ResultSet >( mysql_store_result( m_pConnection->getRawCon() ), shared_from_this() );
}


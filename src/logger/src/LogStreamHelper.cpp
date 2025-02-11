/**
 * @file LogStreamHelper.cpp
 * @author Hugo Fernández Solís (hugofernandezsolis@gmail.com)
 * @date 2025-01-17
 * 
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 */


#include <LogStreamHelper.h>


namespace _priv_logger_ {


//// PUBLIC ///////////////////////////////////      CONSTRUCTORS       ////////////////////////////////////////////////
LogStreamHelper::LogStreamHelper(const LogLevel& iLevel, const std::string& iFile, const int& iLine, const std::string& iFunc):
  level_(iLevel), file_(iFile), line_(iLine), func_(iFunc) {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PUBLIC ///////////////////////////////////    GETTERS & SETTERS    ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PUBLIC ///////////////////////////////////      CLASS METHODS      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//// PUBLIC ///////////////////////////////////        OPERATORS        ////////////////////////////////////////////////
template <typename T>
LogStreamHelper& LogStreamHelper::operator<<(const T& value) {
  stream_ << value;
  return *this;
}

LogStreamHelper& LogStreamHelper::operator<<(OStreamManipulator manip) {
  manip(stream_);
  return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//// PUBLIC ///////////////////////////////////       DESTRUCTORS       ////////////////////////////////////////////////
LogStreamHelper::~LogStreamHelper() {
  Logger::Instance().log(level_, file_ + ':' + std::to_string(line_), func_, stream_.str());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//// PROTECTED ////////////////////////////////      CONSTRUCTORS       ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PROTECTED ////////////////////////////////    SETTERS & GETTERS    ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PROTECTED ////////////////////////////////      CLASS METHODS      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//// PROTECTED ////////////////////////////////        OPERATORS        ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//// PROTECTED ////////////////////////////////       DESTRUCTORS       ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//// PRIVATE //////////////////////////////////      CONSTRUCTORS       ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PRIVATE //////////////////////////////////    SETTERS & GETTERS    ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PRIVATE //////////////////////////////////      CLASS METHODS      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//// PRIVATE //////////////////////////////////        OPERATORS        ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
//// PRIVATE //////////////////////////////////       DESTRUCTORS       ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



} // namespace _priv_logger_
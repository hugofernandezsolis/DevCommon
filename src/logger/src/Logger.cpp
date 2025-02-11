/**
 * @file Logger.cpp
 * @author Hugo Fernández Solís (hugofernandezsolis@gmail.com)
 * @date 2025-01-17
 * 
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 */


#include <Logger.h>

#include <iostream>


namespace _priv_logger_ {


//// PUBLIC ///////////////////////////////////      CONSTRUCTORS       ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PUBLIC ///////////////////////////////////    GETTERS & SETTERS    ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PUBLIC ///////////////////////////////////      CLASS METHODS      ////////////////////////////////////////////////
/**
 * @brief
 * 
 * @return
 */
Logger& Logger::Instance(void) {
  static Logger instance;
  return instance;
}

/**
 * @brief
 * 
 * @param iFilename
 */
void Logger::set_log_file(const std::filesystem::path& iFilename) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (logFile_.is_open()) {
    logFile_.close();
  }
  logFile_.open(iFilename, std::ios::app);
  if (!logFile_.is_open()) {
    std::cerr << "Unable to open log file: " << iFilename << std::endl;
  }
}

/**
 * @brief
 * 
 * @param iLevel
 * @param iFile
 * @param iLine
 * @param iFunc
 * @param iMessage
 */
void Logger::log(const LogLevel& iLevel, const std::string& iFile, const std::string& iFunc, const std::string& iMessage) {
  std::lock_guard<std::mutex> lock(mutex_);

  if (!logFile_.is_open()) {return;}

  std::cout << "Logging in " << LOG_FILE_PATH << std::endl;

  const time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm tmNow;

#ifdef _WIN32
  localtime_s(&tmNow, &now);
  const char delimiter = '\\';
#else
  localtime_r(&now, &tmNow);
  const char delimiter = '/';
#endif

  size_t pos = iFile.rfind(delimiter);
  
  std::string fileName;
  if (pos != std::string::npos) {
    fileName = iFile.substr(pos + 1);
  } else {
    fileName = iFile;
  }

  switch (iLevel) {
    case LogLevel::INFO:
      logFile_ << "[INFO] | ";
    break;
    case LogLevel::WARNING:
      logFile_ << "[WARNING] | ";
    break;
    case LogLevel::ERROR:
      logFile_ << "[ERROR] | ";
    break;
    case LogLevel::DEBUG:
      logFile_ << "[DEBUG] | ";
    break;
  }

  logFile_ << std::put_time(&tmNow, "%d-%m-%Y %H:%M:%S") << " | " << fileName << " | " << iFunc << " | "
           << iMessage << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PUBLIC ///////////////////////////////////        OPERATORS        ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PUBLIC ///////////////////////////////////       DESTRUCTORS       ////////////////////////////////////////////////
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
/**
 * @brief
 */
Logger::Logger(void) {
  std::filesystem::create_directories(logFilePath_.root_path());
  this->set_log_file(logFilePath_);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PRIVATE //////////////////////////////////    SETTERS & GETTERS    ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PRIVATE //////////////////////////////////      CLASS METHODS      ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PRIVATE //////////////////////////////////        OPERATORS        ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// PRIVATE //////////////////////////////////       DESTRUCTORS       ////////////////////////////////////////////////
/**
 * @brief
 */
Logger::~Logger() {
  if (logFile_.is_open()) {
    logFile_.close();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} // namespace _priv_logger_
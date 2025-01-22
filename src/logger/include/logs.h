/**
 * @file logs.h
 * @author Hugo Fernández Solís (hugofernandezsolis@gmail.com)
 * @date 2025-01-17
 * 
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 */


#pragma once


#include <LogStreamHelper.h>


#define LOG_INFO    _priv_logger_::LogStreamHelper(_priv_logger_::LogLevel::INFO,    __FILE__, __LINE__, __func__)
#define LOG_WARNING _priv_logger_::LogStreamHelper(_priv_logger_::LogLevel::WARNING, __FILE__, __LINE__, __func__)
#define LOG_ERROR   _priv_logger_::LogStreamHelper(_priv_logger_::LogLevel::ERROR,   __FILE__, __LINE__, __func__)
#include "epam.h"

std::shared_ptr<Logger> Logger::instance{nullptr};
std::mutex Logger::mtx;
// Logger base
void Logger::SetLevel(LogLevel level){
    m_level = level;
}
Logger::~Logger(){}
// File logger 
FileLogger::FileLogger(){SetFileLogging();};
std::shared_ptr<Logger> FileLogger::getInstance(){
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lck(mtx);
        instance.reset(new FileLogger());
    }
    return instance;
}
void FileLogger::SetFileLogging(const char* filepath){
    m_file = filepath;
    if(m_fout){
        m_fout.close();
    }
    m_fout.open(m_file, std::ios::app);
    if(!m_fout)
        std::cout<<"Failed to open log file."<<std::endl;
}      
void FileLogger::Debug(std::string msg){
    if(m_level <= DEBUG)
        m_fout<<"DEBUG:"<<msg;
}
void FileLogger::Info(std::string msg){
    if(m_level <= INFO)
        m_fout<<"INFO:"<<msg;
}
void FileLogger::Warn(std::string msg){
    if(m_level <= WARNING)
        m_fout<<"WARN:"<<msg;
}
void FileLogger::Error(std::string msg){
    if(m_level <= ERROR)
        m_fout<<"ERROR:"<<msg;
}
void FileLogger::Critical(std::string msg){
    if(m_level <= CRITICAL)
        m_fout<<"CRITICAL:"<<msg;
}
FileLogger::~FileLogger(){
    if(m_fout){
        m_fout.close();
    }
}
// Console logger
std::shared_ptr<Logger> ConsoleLogger::getInstance(){
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lck(mtx);
        instance.reset(new ConsoleLogger());
    }
    return instance;
}
void ConsoleLogger::SetFileLogging(const char* filepath){
    std::cout<<"File logger is not applicable for Console."<<std::endl;
} 
void ConsoleLogger::Debug(std::string msg){
    if(m_level <= DEBUG)
        std::cout<<"DEBUG:"<<msg;
}
void ConsoleLogger::Info(std::string msg){
    if(m_level <= INFO)
        std::cout<<"INFO:"<<msg;
}
void ConsoleLogger::Warn(std::string msg){
    if(m_level <= WARNING)
        std::cout<<"WARN:"<<msg;
}
void ConsoleLogger::Error(std::string msg){
    if(m_level <= ERROR)
        std::cout<<"ERROR:"<<msg;
}
void ConsoleLogger::Critical(std::string msg){
    if(m_level <= CRITICAL)
        std::cout<<"CRITICAL:"<<msg;
}



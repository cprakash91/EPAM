#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <chrono>

enum LogLevel {DEBUG, INFO, WARNING, ERROR, CRITICAL};
//Logger base class
class Logger
{
protected:
    LogLevel m_level;
    static std::shared_ptr<Logger> instance;
    static std::mutex mtx;
public:
    //std::shared_ptr<Logger> getInstance()= 0;
    virtual void SetLevel(LogLevel level);
    virtual void SetFileLogging(const char* filepath="log.txt")=0;         
    virtual void Debug(std::string msg)=0;
    virtual void Info(std::string msg)=0;
    virtual void Warn(std::string msg)=0;
    virtual void Error(std::string msg)=0;
    virtual void Critical(std::string msg)=0;
    virtual ~Logger();
};
// File logger class
class FileLogger: public Logger{
private:
    std::ofstream m_fout;
    const char* m_file = 0;

    FileLogger();
    FileLogger(const FileLogger& ) = delete;
    FileLogger& operator=(const FileLogger&) = delete;

public:
    static std::shared_ptr<Logger> getInstance();
    void SetFileLogging(const char* filepath="log.txt");         
    void Debug(std::string msg);
    void Info(std::string msg);
    void Warn(std::string msg);
    void Error(std::string msg);
    void Critical(std::string msg);
    ~FileLogger();
};
// Console logger class
class ConsoleLogger: public Logger{
private:
    ConsoleLogger(){};
    ConsoleLogger(const ConsoleLogger& ) = delete;
    ConsoleLogger& operator=(const ConsoleLogger&) = delete;

public:
    static std::shared_ptr<Logger> getInstance();
    void SetFileLogging(const char* filepath="");         
    void Debug(std::string msg);
    void Info(std::string msg);
    void Warn(std::string msg);
    void Error(std::string msg);
    void Critical(std::string msg);
    ~ConsoleLogger(){};
};


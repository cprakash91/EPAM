#include "epam.cpp"
#include <thread>
enum LogType {LOG, CONSOLE};

class LogFactory
{
public:
    static std::shared_ptr<Logger> getLogger(LogType logtype){
        std::shared_ptr<Logger> log ;
        switch (logtype)
        {
        case LOG:
            log = FileLogger::getInstance();
            break;
        case CONSOLE:
            log = ConsoleLogger::getInstance();
            break;
        default:
            std::cout<<"Log type is not supported."<<std::endl;
            break;
        }
        return log;
    }
};
void multi_thread_log(){
    std::shared_ptr<Logger> log = LogFactory::getLogger(LOG);
    log->Debug("Debug Level\n");
    log->Info("Info Level \n");
    log->Warn("Warning Level\n");
    log->Error("Error Level\n");
    log->Critical("Critical Level\n");
    log->SetLevel(ERROR);
    log->Warn("Warning Level\n");
    log->Error("Error Level\n");
    log->Critical("Critical Level\n");
}

int main(){
    //std::shared_ptr<Logger> log = LogFactory::getLogger(CONSOLE);
    //multi_thread_log();
    std::thread th[10];
    for(int i =0; i< 10; i++){
        th[i] = std::thread(multi_thread_log);
    }
    for(auto& t : th)
        t.join();
    
}
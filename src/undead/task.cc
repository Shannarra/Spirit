#ifndef TASK

#define TASK

#include "./entity.cc"
#include <string>

namespace undead
{
    class Task
    {
    private:
        
    public:
        Task(std::vector<std::string>, bool);
        ~Task();
    };
    
    Task::Task(std::vector<std::string> code, bool active)
    {
    }
    
    Task::~Task()
    {
    }
    
    
} // namespace Undead


#endif
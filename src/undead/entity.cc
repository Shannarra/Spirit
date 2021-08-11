#ifndef ENTITY
#define  ENTITY

#include "task.cc"
#include <queue>

namespace undead {
    class Entity
    {
    private:
        
    public:
        const std::string Name;
        const std::pair<size_t, size_t> Scope;
        const std::vector<undead::Task*> Tasks;
    public:
        Entity(std::pair<size_t, size_t> scope);
        Entity(std::string, std::pair<size_t, size_t>);
        ~Entity();

        void GenerateTasks(std::pair<size_t, size_t>& range, std::vector<std::string>& text);
    };
    
    Entity::Entity(std::pair<size_t, size_t> scope) : Scope(scope)
    {
    }
    
    Entity::Entity(std::string name, std::pair<size_t, size_t> scope) : Name(name), Scope(scope)
    {
    }
    
    Entity::~Entity()
    {
    }

    void Entity::GenerateTasks(std::pair<size_t, size_t>& range, std::vector<std::string>& text) {
        // std::vector<std::string> curr_task_code;

        // for_each(text) {
        //     if (starts_with(item, "done")) {
        //         auto t = new Task(curr_task_code, true);
        //         this->Tasks.push_back(t);
        //         curr_task_code.clear();
        //     } else {
        //         curr_task_code.push_back(item);
        //     }
        // }

    }
    
}

#endif

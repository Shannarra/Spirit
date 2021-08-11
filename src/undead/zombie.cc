#ifndef ZOMBIE

#define ZOMBIE

#include "./entity.cc"
#include <utility>

namespace undead
{
    class Zombie: public undead::Entity
    {
    private:
    public:
        Zombie(std::pair<unsigned, unsigned>);
        ~Zombie();
    };
    
    Zombie::Zombie(std::pair<unsigned, unsigned> scope) : Entity(scope)
    {
    }
    
    Zombie::~Zombie()
    {
    }
    
} // namespace Undead


#endif
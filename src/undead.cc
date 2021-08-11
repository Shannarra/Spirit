#ifndef UNDEAD
#define UNDEAD

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>


#include "./util.cc"
#include "undead/entity.cc"
#include "undead/zombie.cc"

#define find_substr(original, sub) original.find(sub) != std::string::npos
using svec = std::vector<std::string>;

class Undead
{
private:
    std::vector<size_t> m_Binds;

    std::pair<std::string, std::string> m_CurrentEntityInfo;
public:
    Undead();
    ~Undead();

    std::unordered_map<std::string, undead::Entity*> GenerateEntities(svec& lines);
private:
    bool scope_check_passed(svec& lines);
    void set_entity_binds(svec& lines);

};


Undead::Undead()
{
}

Undead::~Undead()  // pos=0 limits the search to the prefix
                                    // s starts with prefix

{
}

std::unordered_map<std::string, undead::Entity*> Undead::GenerateEntities(svec& lines) {
    std::unordered_map<std::string, undead::Entity*> entities;
    // auto e = undead::Entity(std::pair<size_t, size_t>(1,5));
    // entities["name"] = &e;

    if (scope_check_passed(lines)) {
        set_entity_binds(lines);

        size_t line_number = 1;
        bool expect_summon = false;

        auto allEntityBounds = std::vector<std::pair<size_t, size_t>>();

        for_each(lines) {
            std::string curr_line = "";
            if (find_substr(item, "//")) 
                curr_line = trim(item.substr(0, lines[line_number].find("//")));
            else 
                curr_line = trim(item);

            if (!expect_summon && find_substr(curr_line, "is a") || find_substr(curr_line,  "is an")) {
                auto contents = split(curr_line);
                
                if (entities.find(contents[0]) != entities.end())
                {
                    auto scope = entities[contents[0]]->Scope;
                    std::cout << "Entity with name \""<< contents[0] <<"\" of type \""<< contents[contents.size() - 1] <<
                                "\" has been already declared in the scope: [" << scope.first <<", " << scope.second << "].";
                }

                undead::Entity* entity = nullptr;

                if (contents[contents.size() - 1] == "Zombie") {
                    auto bounds = std::pair<size_t, size_t>(line_number, m_Binds.back());
                    m_Binds.pop_back();

                    allEntityBounds.push_back(bounds);
                    m_CurrentEntityInfo = std::pair<std::string, std::string>(contents[contents.size() - 1], contents[0]);

                    entity = new undead::Zombie(bounds);

                    expect_summon = true;
                }

                if (entity != nullptr && entity != 0) {   
                    entities[contents[0]] = entity;
                }
                continue;
            }

            if (expect_summon) {
                expect_summon = false;

                lowercase(curr_line);
                if (curr_line != "summon") {
                    std::cout << "ERROR: Expected \"summon\" after entity definition on line " << line_number - 1 << ". \
                        \nHint: use \"summon\" on line " << line_number << " instead of \""<< curr_line << "\"";

                    return entities;
                }

                //std::cout << "Ok? : " << (entities[m_CurrentEntityInfo.first] == nullptr) << "\n";
                //if (entities.find(m_CurrentEntityInfo.first) != entities.end()) {
                    //entities[m_CurrentEntityInfo.first]->GenerateTasks(allEntityBounds.back(), lines);
                //}
            }


            line_number++;
        }
    }

    return entities;
}


bool Undead::scope_check_passed(svec& lines) {
    size_t summons = 0, animations = 0;

    for_ref_each(lines) {
        if (find_substr(item, "summon") || find_substr(item, "task")) {
            if (starts_with(item, "say") ||
                starts_with(item, "//") ||
                starts_with(item, "use") || 
                starts_with(item, "\"")) {
                    continue;
                } else {
                    summons++;
                }
        }
        if (find_substr(item, "done") || find_substr(item, "bind")) {
            if (starts_with(item, "say") ||
                starts_with(item, "//") || 
                starts_with(item, "\"")) {
                    continue;
                } else {
                    animations++;
                }
        }
    }

    if (summons != animations) {
        std::cout << "Binds and summons not balanced!\n";
        return false;
    }

    return true;
}

void Undead::set_entity_binds(svec &lines) {
    
    auto reversed = lines;

    std::reverse(reversed.begin(), reversed.end());

    size_t line_n = lines.size();
    for_each(reversed) {
        if (item == "bind") {
            m_Binds.push_back(line_n);
        }
        if (line_n > 0) {
            line_n--;
        }
    }
}

#endif // UNDEAD

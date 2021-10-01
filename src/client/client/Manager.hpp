#include "Macro.hpp"

template<typename T>
class Manager
{
    ATTRIBUTE(std::string,Name);
    ATTRIBUTE(int,id);
    ATTRIBUTE(std::vector<T>,elements);
    STATIC(std::vector<Manager> Managers);

    public :
    std::vector<T> GetByName(std::string name);
    T GetByID(int id);
    void Add(T element);
    void Remove(T element);
};
#include "Macro.hpp"

class InputSource
{
    ATTRIBUTE(int,ID);
    ATTRIBUTE(std::vector<Manageable*>*,Pawns);

    public :
        InputSource(int id);
        int Out(unsigned char* buffer,int length);
        int In(unsigned char* buffer,int length);


};
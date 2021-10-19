#include "Macro.hpp"

class InputSource
{
    ATTRIBUTE(int,ID);
    
    public :
        InputSource(int id);
        int Out(unsigned char* buffer,int length);
        int In(unsigned char* buffer,int length);
        


};
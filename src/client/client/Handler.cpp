#include "Handler.hpp"
#include <pthread.h>
#include <string.h>
#include <memory>


void Handler::RoutineTurnBegin()
{
    for(std::function<void()> f : TurnBegin)
        f();
}
void Handler::RoutineTurnBeginAsync()
{
    for(int i = 0; i < TurnBeginAsync.size();i++)
    {
        pthread_t* th_id = (pthread_t*)malloc(sizeof(pthread_t));
        int* arg = new int(i);
        pthread_create(th_id,NULL,Exec,&TurnBeginAsync[i]);
    }
}

void* Handler::Exec(void* arg)
{
    PRINTLN("EXEC STARTED ")
    (*((std::function<void()>*)arg))();
    PRINTLN("EXEC DONE")
    return NULL;
}

void Handler::Initialize()
{
    TurnBegin = *(new std::vector<std::function<void()>>);
}


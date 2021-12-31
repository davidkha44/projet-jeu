#include "Node.h"

template<class T>
ai::Node<T>::Node()
{
    Parent = NULL;
    Object = NULL;
}

template<class T>
ai::Node<T>::Node(T* obj)
{
    Parent = NULL;
    Object = obj;
}

template<class T>
ai::Node<T>::Node(T* obj,Node<T>* parent)
{
    Parent = parent;
    Object = obj;
}

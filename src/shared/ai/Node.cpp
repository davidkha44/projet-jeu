#include "Node.h"
#include "../engine.h"
#include "../ai.h"
#include "../../client/client/Macro.hpp"


ai::Node::Node()
{

}

ai::Node::Node(void* obj)
{
    Object = obj;
    Parent = NULL;
}
ai::Node::Node(void* obj,Node* parent)
{
    Object = obj;
    Parent = parent;
}

void ai::Node::Print(int indent)
{
    for(int i = 0; i < indent;i++)
        i != indent - 1 ? std::cout << "  " : std::cout << indent <<"|--";
    std::cout << ((ai::BehaviourLeaf*)Object)->ToString() << std::endl;
    for(int i = 0; i < Children.size();i++)
        Children[i]->Print(indent+1);
}

void ai::Node::BigBang(std::vector<ai::Node*> nodes)
{
    ai::Node* currentNode = this;
    int i = 0;
    while(++ i < nodes.size())
    {
        
    }

}
void ai::Node::RecursiveInsert(std::vector<ai::Node*> nodes,int depth)
{
    if(depth > 3)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : nodes)
        Children.push_back(new Node(n->Object));
    for(ai::Node* c : Children)
        c->RecursiveInsert(nodes,_depth);

}
void ai::Node::RecursiveInsert(std::vector<std::vector<ai::Node*>> lnodes,int depth)
{
    if(depth > 3)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : lnodes[depth%2])
        Children.push_back(new Node(n->Object));
    for(ai::Node* c : Children)
        c->RecursiveInsert(lnodes,_depth);
}
template <class T>
void ai::Node::RecursiveInsertWithCallback(std::vector<std::vector<ai::Node*>> lnodes,int depth)
{
    if(depth > 3)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : lnodes[depth%2])
        if(Node* node = T::RecursiveInsertCallback(n->Object))
            Children.push_back(node);     
    for(ai::Node* c : Children)
    {
        ((ai::BehaviourLeaf*)c->Object)->Outcome += ((ai::BehaviourLeaf*)Object)->Outcome;
        if(depth) ((ai::BehaviourLeaf*)c->Object)->Target = ((ai::BehaviourLeaf*)Object)->Caster;
        c->Parent = this;
        c->RecursiveInsertWithCallback<T>(lnodes,_depth);

    }
}
template <class T>
void ai::Node::RecursiveInsertWithCallback(std::vector<ai::Node*> nodes,int depth)
{
    if(depth > 3)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : nodes)
        if(Node* node = T::RecursiveInsertCallback(n->Object))
            Children.push_back(node);     
    for(ai::Node* c : Children)
        c->RecursiveInsertWithCallback<T>(nodes,_depth);
}

template void ai::Node::RecursiveInsertWithCallback<engine::Action>(std::vector<std::vector<ai::Node*>> lnodes,int depth);
template void ai::Node::RecursiveInsertWithCallback<ai::BehaviourTree>(std::vector<std::vector<ai::Node*>> lnodes,int depth);
template void ai::Node::RecursiveInsertWithCallback<ai::BehaviourTree>(std::vector<ai::Node*> lnodes,int depth);

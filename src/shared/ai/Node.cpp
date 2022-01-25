#include "Node.h"
#include "../engine.h"
#include "../ai.h"
#include "../../client/client/Macro.hpp"
#include <stdlib.h>
#include <stdio.h>

#define DEPTH 3

const int MAX = 100000;
const int MIN = -100000;


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
/*int ai::Node::BottomLevel(ai::Tree* tree)
{
    if(!Children.size()) tree->BottomLevel.push_back(this);
    else
        for(int i = 0; i < Children.size();i++)
            Children[i]->BottomLevel(tree);
}
*/
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
    if(depth > DEPTH)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : nodes)
        Children.push_back(new Node(n->Object));
    for(ai::Node* c : Children)
        c->RecursiveInsert(nodes,_depth);

}
void ai::Node::RecursiveInsert(std::vector<std::vector<ai::Node*>> lnodes,int depth)
{
    if(depth > DEPTH)
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
    if(depth > DEPTH)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : lnodes[depth%2])
        if(Node* node = T::RecursiveInsertCallback(n->Object))
            Children.push_back(node);     
    for(ai::Node* c : Children)
    {
        ((ai::BehaviourLeaf*)c->Object)->Outcome = ((ai::BehaviourLeaf*)Object)->Outcome - (depth % 2 ? ((ai::BehaviourLeaf*)c->Object)->Outcome : -((ai::BehaviourLeaf*)c->Object)->Outcome);
        
        if(depth) ((ai::BehaviourLeaf*)c->Object)->Target = ((ai::BehaviourLeaf*)Object)->Caster;
        c->Parent = this;
        c->RecursiveInsertWithCallback<T>(lnodes,_depth);
    }
}
template <class T>
void ai::Node::RecursiveInsertWithCallback(std::vector<ai::Node*> nodes,int depth)
{
    if(depth > DEPTH)
        return;
    int _depth = depth + 1;
    for(ai::Node* n : nodes)
        if(Node* node = T::RecursiveInsertCallback(n->Object))
            Children.push_back(node);     
    for(ai::Node* c : Children)
        c->RecursiveInsertWithCallback<T>(nodes,_depth);
}

int ai::Node::minmax_ab(ai::Node* node,int depth,bool isMax,int alpha,int beta){
	if(node->Children.size() == 0){
		return ((ai::BehaviourLeaf*)node->Object)->Outcome;
	}
	if(depth == 0){		//A décomenter si la racine est un noeud max tout comme ses enfants
		std::vector<int> v;
		for(int i =0;i<node->Children.size();i++){
			int minmax = minmax_ab(node->Children[i],depth + 1,isMax,alpha,beta);
			v.push_back(minmax);
		}				
		int max = *max_element(v.begin(),v.end());
		((ai::BehaviourLeaf*)node->Object)->Outcome = max;
		return max;
	}
	if (isMax){
        int best = MIN;
        for(int i =0;i<node->Children.size();i++){
            int val = minmax_ab(node->Children[i],depth + 1,false,alpha, beta);
            best = std::max(best, val);
            alpha = std::max(alpha, best);
            if (beta <= alpha)
                break;
        }
		((ai::BehaviourLeaf*)node->Object)->Outcome = best;
        return best;
	}
	else{
        int best = MAX;
        for(int i =0;i<node->Children.size();i++){
            int val = minmax_ab(node->Children[i],depth + 1,true,alpha, beta);
            best = std::min(best, val);
            beta = std::min(beta, best);
            if (beta <= alpha)
                break;
        }
		((ai::BehaviourLeaf*)node->Object)->Outcome = best;
        return best;
    }
}

/*Fonction nous renvoyant l'action à choisir après minmax
On remplacera le type const char* par le type action*/
ai::Node* ai::Node::chooseAction(ai::Node* node){
	int minmax = minmax_ab(node,0,true,MIN,MAX);
	std::cout << "Le résultat de minmax_alphabeta est :" << minmax << "\n" << std::endl;
	for(int i = 0;i<node->Children.size();i++){
		if(((ai::BehaviourLeaf*)node->Children[i]->Object)->Outcome == minmax){
			return node->Children[i];
		}
	}
}

ai::Node* ai::Node::Root()
{
    ai::Node* currentNode = this;
    while(currentNode->Parent) currentNode = currentNode->Parent;
    return currentNode;
}


template void ai::Node::RecursiveInsertWithCallback<engine::Action>(std::vector<std::vector<ai::Node*>> lnodes,int depth);
template void ai::Node::RecursiveInsertWithCallback<ai::BehaviourTree>(std::vector<std::vector<ai::Node*>> lnodes,int depth);
template void ai::Node::RecursiveInsertWithCallback<ai::BehaviourTree>(std::vector<ai::Node*> lnodes,int depth);

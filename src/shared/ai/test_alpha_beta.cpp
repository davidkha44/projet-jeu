#include <stdlib.h>
#include <stdio.h>
// CPP program to do level order traversal
// of a generic tree
#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;
const int MIN = -100000;

// Represents a node of an n-ary tree
struct Node
{
	int key;
	const char* name;
	vector<Node *>child;
};

// Utility function to create a new tree node
Node *newNode(int key,const char* name)
{
	Node *temp = new Node;
	temp->key = key;
	temp->name = name;
	return temp;
}

// Prints the n-ary tree level wise
void LevelOrderTraversal(Node * root)
{
	if (root==NULL)
		return;

	// Standard level order traversal code
	// using queue
	queue<Node *> q; // Create a queue
	q.push(root); // Enqueue root
	while (!q.empty())
	{
		int n = q.size();

		// If this node has children
		while (n > 0)
		{
			// Dequeue an item from queue and print it
			Node * p = q.front();
			q.pop();
			cout << p->key << " ";

			// Enqueue all children of the dequeued item
			for (int i=0; i<p->child.size(); i++)
				q.push(p->child[i]);
			n--;
		}

		cout << endl; // Print new line between two levels
	}
}

/*Fonction minmax alphabeta renvoyant le résultat final du parcourt de l'arbre
Fonction surement à adapter avec le type de l'arbre*/
int minmax_ab(Node* node,int depth,bool isMax,int alpha,int beta){
	if(node->child.size() == 0){
		return node->key;
	}
	/*if(depth == 0){		//A décomenter si la racine est un noeud max tout comme ses enfants
		vector<int> v;
		for(int i =0;i<node->child.size();i++){
			int minmax = minmax_ab(node->child[i],depth + 1,isMax,alpha,beta);
			v.push_back(minmax);
		}				
		int max = *max_element(v.begin(),v.end());
		node->key = max;
		return max;
	}*/
	if (isMax){
        int best = MIN;
        for(int i =0;i<node->child.size();i++){
            int val = minmax_ab(node->child[i],depth + 1,false,alpha, beta);
            best = max(best, val);
            alpha = max(alpha, best);
            if (beta <= alpha)
                break;
        }
		node->key = best;
        return best;
	}
	else{
        int best = MAX;
        for(int i =0;i<node->child.size();i++){
            int val = minmax_ab(node->child[i],depth + 1,true,alpha, beta);
            best = min(best, val);
            beta = min(beta, best);
            if (beta <= alpha)
                break;
        }
		node->key = best;
        return best;
    }
}

/*Fonction nous renvoyant l'action à choisir après minmax
On remplacera le type const char* par le type action*/
const char* chooseAction(Node* node){
	int minmax = minmax_ab(node,0,true,MIN,MAX);
	std::cout << "Le résultat de minmax_alphabeta est :" << minmax << "\n" <<endl;
	for(int i = 0;i<node->child.size();i++){
		if(node->child[i]->key == minmax){
			return node->child[i]->name;
		}
	}
}

// Driver program
// int main()
// {
// 	/* Let us create below tree
// 	*			 10
// 	*	 / / \ \
// 	*	 2 34 56 100
// 	*	 / \		 | / | \
// 	*	 77 88	 1 7 8 9./
// 	*/
// 	int minmax;
// 	const char* choice;
// 	Node *root = newNode(0,"a");
// 	(root->child).push_back(newNode(0,"b"));
// 	(root->child).push_back(newNode(0,"c"));
// 	(root->child).push_back(newNode(0,"d"));
// 	//(root->child).push_back(newNode(100));
// 	(root->child[0]->child).push_back(newNode(0,"e"));
// 	(root->child[0]->child).push_back(newNode(0,"f"));
// 	(root->child[1]->child).push_back(newNode(0,"g"));
// 	(root->child[1]->child).push_back(newNode(0,"h"));
// 	(root->child[2]->child).push_back(newNode(0,"i"));
// 	(root->child[2]->child).push_back(newNode(0,"j"));
// 	(root->child[0]->child[0]->child).push_back(newNode(2,"k"));
// 	(root->child[0]->child[0]->child).push_back(newNode(5,"l"));
// 	(root->child[0]->child[1]->child).push_back(newNode(9,"m"));
// 	(root->child[0]->child[1]->child).push_back(newNode(6,"n"));
// 	(root->child[1]->child[0]->child).push_back(newNode(4,"o"));
// 	(root->child[1]->child[1]->child).push_back(newNode(1,"p"));
// 	(root->child[2]->child[0]->child).push_back(newNode(3,"q"));
// 	(root->child[2]->child[0]->child).push_back(newNode(2,"r"));
// 	(root->child[2]->child[1]->child).push_back(newNode(7,"s"));
// 	/*Node *root = newNode(0,"a");
// 	(root->child).push_back(newNode(0,"b"));
// 	(root->child).push_back(newNode(0,"c"));
// 	(root->child).push_back(newNode(0,"d"));
// 	(root->child[0]->child).push_back(newNode(3,"e"));
// 	(root->child[0]->child).push_back(newNode(6,"f"));
// 	(root->child[0]->child).push_back(newNode(4,"g"));
// 	(root->child[1]->child).push_back(newNode(2,"h"));
// 	(root->child[1]->child).push_back(newNode(9,"i"));
// 	(root->child[1]->child).push_back(newNode(5,"j"));
// 	(root->child[2]->child).push_back(newNode(7,"k"));
// 	(root->child[2]->child).push_back(newNode(4,"l"));
// 	(root->child[2]->child).push_back(newNode(8,"m"));*/
// 	/*Node *root = newNode(0,"A");
// 	(root->child).push_back(newNode(0,"b"));
// 	(root->child).push_back(newNode(0,"c"));
// 	//(root->child).push_back(newNode(100));
// 	(root->child[0]->child).push_back(newNode(0,"d"));
// 	(root->child[0]->child).push_back(newNode(0,"e"));
// 	(root->child[1]->child).push_back(newNode(0,"f"));
// 	(root->child[1]->child).push_back(newNode(0,"g"));
// 	(root->child[0]->child[0]->child).push_back(newNode(3,"h"));
// 	(root->child[0]->child[0]->child).push_back(newNode(5,"i"));
// 	(root->child[0]->child[1]->child).push_back(newNode(6,"j"));
// 	(root->child[0]->child[1]->child).push_back(newNode(9,"k"));
// 	(root->child[1]->child[0]->child).push_back(newNode(1,"l"));
// 	(root->child[1]->child[0]->child).push_back(newNode(2,"m"));
// 	(root->child[1]->child[1]->child).push_back(newNode(0,"n"));
// 	(root->child[1]->child[1]->child).push_back(newNode(-1,"o"));*/
// 	cout << "Arbre de départ\n";
// 	LevelOrderTraversal(root);
// 	choice = chooseAction(root);
// 	//std::cout << "Le résultat de minmax_alphabeta est :" << minmax << "\n" <<endl;
// 	std::cout << "On choisit l'action :" << choice << "\n" <<endl;
// 	cout <<"After alpha_beta : \n" <<endl;
// 	LevelOrderTraversal(root);
// 	return 0;
// }*/

#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <string> 
#include <vector>
#include "ActorNode.hpp"

using namespace std;

class MovieNode {
	public:

	MovieNode( const string t, int y ) : title(t), year(y){}

	string const title;
	int year;
	vector<ActorNode*> actors;

	void addActor ( ActorNode* a) {
		actors.push_back( a );
	}
};

#endif //MOVIENODE_HPP

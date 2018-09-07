/*
 * Author: Jamie Vu
 * Date: 09/7/18
 */
#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP
#include <string> 
#include <vector>
#include "ActorNode.hpp"

using namespace std;
class ActorNode;
class MovieNode {
	public:

	MovieNode( const string t, int y ) : title(t), year(y){}

	string const title;
	int year;
	vector<ActorNode*> actors;

	//pushes new actor into vector
	void addActor ( ActorNode* a) {
		actors.push_back( a );
	}

};

#endif //MOVIENODE_HPP

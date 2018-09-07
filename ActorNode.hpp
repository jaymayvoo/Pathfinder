/*
 * Author: Jamie Vu
 * Date: 9/7/18
 */
#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <string> 
#include <vector>
#include <climits>
#include "MovieNode.hpp"
using namespace std;

class MovieNode;

class ActorNode {
	
	public:
		
		/** Contructor. Takes in and initializes actor name and
 		 * adds to unordered map of MovieNodes
 		 */
		ActorNode( const string n) : name(n) { 
		prev = nullptr;
		distance = INT_MAX;
	
		}

		string const name;
		vector<MovieNode*> movies;
		ActorNode* prev;
		int distance;
		string moviePath;
		int movieYear;

		void addMovie ( MovieNode* m) {
			movies.push_back( m );
		}
		
		//overloaded operator used to compare ActorNode distances		
		bool operator<(ActorNode &other) {
			return (this->distance >= other.distance);
		}		

};

//Compare Actor pointers to sort in priotity queue
class ActorPtrComp {
	public:
	bool operator()( ActorNode *lhs, ActorNode *rhs ){
		return *lhs < *rhs;
	}

};

#endif //ACTORNODE_HPP

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <string> 
#include <vector>
#include <climits>
using namespace std;

class MovieNode;

class ActorNode {
	
	public:
		
		/** Contructor. Takes in and initializes actor name and
 		 * adds to unordered map of MovieNodes
 		 */
		ActorNode( const string n) : name(n) { 
		visited = false; 
		prev = nullptr;
		distance = INT_MAX;
		}

		string const name;
		vector<MovieNode*> movies;
		ActorNode* prev;
		bool visited;
		int distance;
		string moviePath;
		int movieYear;

		void addMovie ( MovieNode* m) {
			movies.push_back( m );
		}				

};

#endif //ACTORNODE_HPP

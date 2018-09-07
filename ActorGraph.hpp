/*
 * ActorGraph.h
<<<<<<< HEAD
 * Author: Jamie Vu
 * Date:   9/7/18
=======
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
>>>>>>> fb4c7fe7003cdac4b7af3de5e61eca000cbcf71f
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include "ActorNode.hpp"
#include "MovieNode.hpp"

#include <iostream>
#include <unordered_map>
#include <map>
#include <utility>
#include <vector>

// Maybe include some data structures here

using namespace std;

class ActorGraph {
	private:

	// used to free ActorNodes created in the heap
	void deleteActors() {
		unordered_map<string, ActorNode*>::iterator iter = createdActors.begin();
		while( iter != createdActors.end() ) {
			delete iter->second;
			iter++;
		}	
	}

	// used to free MovieNodes created in the heap
	void deleteMovies() {
		unordered_map<string, MovieNode*>::iterator iter = createdMovies.begin();

		while( iter != createdMovies.end() ) {
			delete iter->second;
			iter++;
		}	

	}	


    public:

        // Maybe add class data structure(s) here
        // keeps track of already created MovieNodes
	unordered_map<string, MovieNode*> createdMovies; 
	
	// keeps track of already created ActorNodes
	unordered_map<string, ActorNode*> createdActors;
    	// keeps track of already created MovieNodes
	map<int, vector<MovieNode*> > movieYears;
    	
	//default constructor of an ActorGraph
	ActorGraph(void);
	
	//destructor
	~ActorGraph();
    
        // Maybe add some more methods here

        /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie relationships.
         *
         * in_filename - input filename
         * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
        bool loadFromFile(const char* in_filename, bool use_weighted_edges);
	void BFS (ActorNode * start);
	void Dijkstra (ActorNode * start);
	void clearGraph();
	bool createMoviesByYear( const char* in_filename);
	bool addActorNodes(  const char* in_filename, int year);
		
};





#endif // ACTORGRAPH_H


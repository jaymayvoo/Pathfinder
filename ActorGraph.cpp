/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <climits> 
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

	unordered_map<string, ActorNode*>::const_iterator findActor;
	unordered_map<string, MovieNode*>::const_iterator findMovie;
	
	ActorNode* newActor, *currActor;
	MovieNode* newMovie, *currMovie;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);

        // we have an actor/movie relationship, now what?
        // check if actor name already created
        findActor = createdActors.find( actor_name );

		//creates new actor node if not in unordered_map
    	if( findActor == createdActors.end() ) {
			newActor = new ActorNode( actor_name );	
			createdActors.insert( make_pair( actor_name, newActor ));
			currActor = newActor;
	}
	else
		currActor = findActor->second;
		
	//check if node movie already created
	findMovie = createdMovies.find( movie_title );

	//creates new movie node if not in unordered_map
	if( findMovie == createdMovies.end() ) {
		newMovie = new MovieNode( movie_title, movie_year );
		createdMovies.insert( make_pair( movie_title, newMovie ) );
		currMovie = newMovie;
	}
	else
		currMovie = findMovie->second;

	currActor->addMovie( currMovie );
	currMovie->addActor( currActor );
		

	}

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
void ActorGraph::BFS ( string actor1 ) {
	unordered_map<string, ActorNode*>::const_iterator a1 = createdActors.find( actor1 );
	ActorNode* currActor = a1->second;
	ActorNode* movieCast;
	MovieNode* currMovie;
	queue<ActorNode*> actorq;
	unordered_set<ActorNode*> set;
	
	actorq.push(currActor);
	currActor->distance = 0;
	set.insert(currActor);
	while( !actorq.empty() ) {
		currActor = actorq.front();
		actorq.pop();
		for( int i = 0; i < (int)currActor->movies.size(); i++ ) {

			currMovie = currActor->movies[i];
			
			for( int j = 0; j < (int)currMovie->actors.size(); j++ ) {
				movieCast = currMovie->actors[j];

				if( set.find(movieCast) != set.end() ) {
					if( movieCast->distance == INT_MAX ) {
						movieCast->distance = (currActor->distance) + 1;
						movieCast->prev = currActor;
						movieCast->moviePath = currMovie->title;
						movieCast->movieYear = currMovie->year;
						actorq.push(movieCast);
						set.insert(movieCast);
					}
				}
			}
		}

	}	

}

void ActorGraph::clearGraph() {
	unordered_map<string, ActorNode*>::iterator it = createdActors.begin();
	while( it != createdActors.end() ) {
		it->second->prev = nullptr;
		it->second->visited = false;
		it->second->distance = INT_MAX;
	}
} 

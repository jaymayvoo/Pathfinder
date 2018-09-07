/*
 * ActorGraph.cpp
 * Author: Jamie Vu
 * Date:   9/7/2018
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
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string.h>
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

	//connects movies and actors together
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
bool ActorGraph::createMoviesByYear(const char* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);
    bool have_header = false;

	unordered_map<string, MovieNode*>::const_iterator findMovie;
	map<int, vector<MovieNode*> >::iterator year;
	MovieNode* newMovie;
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

	//check if node movie already created
	findMovie = createdMovies.find( movie_title );
	//checks if there are any movies made in movie_year in map
	year = movieYears.find(movie_year);
	if( year == movieYears.end() ) {
		vector<MovieNode*>* newYear = new vector<MovieNode*>;
		movieYears.insert(make_pair(movie_year, *newYear));
	}
	//creates new movie node if not in unordered_map
	if( findMovie == createdMovies.end() ) {
		newMovie = new MovieNode( movie_title, movie_year );
		createdMovies.insert( make_pair(movie_title, newMovie) );
		movieYears[movie_year].push_back(newMovie);
	}


	}
	
	if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
bool ActorGraph::addActorNodes(const char* in_filename, int year) {
    // Initialize the file stream
    ifstream infile(in_filename);
    bool have_header = false;

	unordered_map<string, ActorNode*>::const_iterator findActor;
	vector<MovieNode*>::iterator findMovie;
	
	ActorNode* newActor, *currActor;
	MovieNode* currMovie;
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
     
	if( year == movie_year ) { 
		findActor = createdActors.find( actor_name );

		//creates new actor node if not in unordered_map
    	if( findActor == createdActors.end() ) {
			newActor = new ActorNode( actor_name );	
			createdActors.insert( make_pair( actor_name, newActor ));
			currActor = newActor;
		}
		else
			currActor = findActor->second;
		
		//check if node movie already created COME BACK TO THIS
		findMovie =  movieYears[year].begin();
		while( findMovie != movieYears[year].end() ) {
			if( (string)(*findMovie)->title == movie_title ) {
				currMovie = *findMovie;
				break;
			}
			else
				findMovie++;
		}

	//connects movies and actors together
		currActor->addMovie( currMovie );
		currMovie->addActor( currActor );
	}	

	}
	
	if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}


void ActorGraph::BFS ( ActorNode* start ) {
	ActorNode* currActor = start;
	ActorNode* movieCast;
	MovieNode* currMovie;
	queue<ActorNode*> actorq;
	unordered_set<ActorNode*> set;
	
	//pushes initial starting actor onto queue
	actorq.push(currActor);
	currActor->distance = 0;

	//keeps looping until queue is empty
	while( !actorq.empty() ) {
		currActor = actorq.front();
		actorq.pop();

		//iteratres through all of movies current actor stars in
		for( int i = 0; i < (int)currActor->movies.size(); i++ ) {
			//looks at actor's next movie
			currMovie = currActor->movies[i];
			//iterates through the movie's cast
			for( int j = 0; j < (int)currMovie->actors.size(); j++ ) {
				movieCast = currMovie->actors[j];
				//adds cast of movie to queue
				if( movieCast->distance == INT_MAX ) {
					movieCast->distance = (currActor->distance) + 1;
					movieCast->prev = currActor;
					movieCast->moviePath = currMovie->title;
					movieCast->movieYear = currMovie->year;
						actorq.push(movieCast);
				}
			}
		}

	}	
}


void ActorGraph::Dijkstra( ActorNode* start ) {
	ActorNode* movieCast, *currActor = start;
	MovieNode* currMovie;
	//use priority queue to sort distance
	priority_queue<ActorNode*, vector<ActorNode*>, ActorPtrComp> actorq;

	//starts graph at beginning actor
	actorq.push(currActor);
	currActor->distance = 0;
	while( !actorq.empty() ) {
		currActor = actorq.top();
		actorq.pop();
		//searches through movies current actor is in
		for( int i = 0; i < (int)currActor->movies.size(); i++ ) {

			currMovie = currActor->movies[i];
			//iterates through movie's cast
			for( int j = 0; j < (int)currMovie->actors.size(); j++ ) {
				movieCast = currMovie->actors[j];
				//pushes movie cast onto queue and updates distances
				if( movieCast->distance == INT_MAX ) {
					movieCast->distance = currActor->distance+1+(2015- (currMovie->year));
					movieCast->prev = currActor;
					movieCast->moviePath = currMovie->title;
					movieCast->movieYear = currMovie->year;
					actorq.push(movieCast);
				}
			}
		}

	}	

}

//clear graph used to erase distances and previous paths 
void ActorGraph::clearGraph() {
	unordered_map<string, ActorNode*>::iterator it = createdActors.begin();
	while( it != createdActors.end() ) {
		it->second->prev = nullptr;
		it->second->distance = INT_MAX;
		it->second->moviePath = "";
		it->second->movieYear = 0;
		it++;
	}
}

//destructor to free allocated memory
ActorGraph::~ActorGraph() {
	deleteActors();
	deleteMovies();
} 

/*
 * Author: Jamie Vu
 * Date: 09/7/18
 */

#include "ActorGraph.hpp"
#include "UnionFind.hpp"
#include <queue>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

void getPairs( const char* in_filename, vector< pair<string, string> > &pairs ) {
	ifstream infile( in_filename);
	string s;
	
	//skip 1st line, header
	getline( infile, s );	
	//reads file line by line until eof
	while(infile) {
		if( !getline( infile, s) ) break;

		istringstream ss(s);
		vector <string> record;

		while(ss) {
			string next;

			if(!getline( ss, next, '\t')) break;
			
			record.push_back( next );
		}

		if (record.size() != 2 ) continue;
		
		//gets first tab deliminated name
		string fromActor(record[0]);
		// gets second tab delminated name
		string toActor (record[1]);
		//inserts pair of names into vector
		pairs.insert(pairs.end(), make_pair(fromActor, toActor));
		
	}
	if( !infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
	}
	infile.close();

} 

int main( int argc, char* argv[] ) {
	
	ActorGraph graph;
	//UnionFind uf;
	vector< pair<string, string> > comparedActors;
	ifstream dataFile, compareFile;
	int completed = 0;
	ofstream ofile;
	//opens data file (movie_casts.tsv)
	dataFile.open(argv[1]);
	//opens file of actos to compare
	compareFile.open(argv[2]);
	//opens file to write path to
	ofile.open(argv[3]);

	//checks if user wants weighted or unweited
	bool useGraph = false;
	if( strcmp(argv[4], "ufind") ) {
		useGraph = true;
	}
	//fills vector of pairs
	getPairs( argv[2], comparedActors );	
	//create copy of vector of pairs
	vector< pair<string, string> > copyCompare = comparedActors;
	ActorNode *fromActor, *toActor;
	unordered_map<string, ActorNode*>::const_iterator a1;
	unordered_map<string, ActorNode*>::const_iterator a2;
	
	//vector for distance output to be outputted into file
	vector<int> connected((int)comparedActors.size(), 9999);
	// creating actor graph if selected bfs
	if( useGraph ) {
		graph.createMoviesByYear( argv[1] );
		map<int, vector<MovieNode*> >::iterator it = graph.movieYears.begin();
		//checks if iterator reached end of graph or if all distances found
		while( it != graph.movieYears.end() && completed != (int)comparedActors.size() ) {
			graph.addActorNodes( argv[1], it->first );
			
			//searches for actors in currently created graph
		    for( int i = 0; i < (int)comparedActors.size(); ++i ) {
			a1 = graph.createdActors.find( copyCompare[i].first );
			a2 = graph.createdActors.find( copyCompare[i].second );
			//if pairs are in graph, BFS to search
			if( a1 != graph.createdActors.end() && a2 != graph.createdActors.end() ) {
				fromActor = a1->second;
				graph.BFS(fromActor);
				
				toActor = a2->second;
				//keeps iterating backwords to find earliest year
				while( toActor->prev ) {
					toActor = toActor->prev;
				}
				if( toActor == fromActor ) {
					connected[i] = it->first;
					copyCompare[i] = make_pair( "", "1"); //makes sure to not search again
					completed++;
				}
				//clears graph for next pair
				graph.clearGraph();
			}
		  }  
			it++;
		}
	}
/*	else {
		int oldestMovie = uf.getOldestMovie(argv[1] );
		for(int i = oldestMovie; i < 2016; ++i) {
			uf.createSets( argv[1], i );
			
			for( int j = 0; j < (int)comparedActors.size(); j++ ) {
				if( uf.ufind(copyCompare[j].first) == uf.ufind(copyCompare[j].second)) {
					connected[j] = i;
					copyCompare[j] = make_pair("", "n");
				}
			}
		}

	}*/	
	
	ofile<< "Actor1\tActor2\tyear" << endl;	
	//outputs to file
	for( int j = 0; j < (int)comparedActors.size(); j++ ) {
		ofile << comparedActors[j].first << "\t" << comparedActors[j].second << "\t" << connected[j] << endl;
	}

	dataFile.close();
	compareFile.close();
	ofile.close();
	return 0;
}


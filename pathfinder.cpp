#include "ActorGraph.hpp"
#include <queue>
#include <set>
#include <vector>
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
	
		//reads tab deliminated pairs from file
		string fromActor(record[0]);
		string toActor (record[1]);
		//stores the pairs into vector
		pairs.insert(pairs.end(), make_pair(fromActor, toActor));
		
	}
	if( !infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
	}
	infile.close();

} 

int main( int argc, char* argv[] ) {
	
	ActorGraph graph;
	vector< pair<string, string> > comparedActors;
	ifstream dataFile, compareFile;
	ofstream ofile;
	//opens data file (movie_casts.tsv)
	dataFile.open(argv[1]);
	//opens file of actos to compare
	compareFile.open(argv[3]);
	//opens file to write path to
	ofile.open(argv[4]);

	//checks if user wants weighted or unweited
	bool isWeighted = false;
	if( strcmp(argv[2], "u") ) {
		isWeighted = true;
	}
	// creating actor graph
	graph.loadFromFile( argv[1], isWeighted );
	//fills vector of pairs
	getPairs( argv[3], comparedActors );	
	//create header in output file
	ofile<< "(actor)--[movie#@year]-->(actor)--..." << endl;	
	
	ActorNode *fromActor, *toActor;
	unordered_map<string, ActorNode*>::const_iterator a1;

	//searches graph #pairs of time
	for( int i = 0; i < (int)comparedActors.size(); ++i ) {
		//creates a vector to store path
		stack<ActorNode*> path;

		//finds ActorNode with first name in pair
		a1 = graph.createdActors.find( comparedActors[i].first );
		fromActor = a1->second;
		
		//checks to see which algorithm to use
		if( isWeighted )
			graph.Dijkstra(fromActor);
		else
			graph.BFS(fromActor);	

		//finds location of last node
		a1 = graph.createdActors.find(comparedActors[i].second);
		toActor = a1->second;
		//back tracks node until reaches fromActor node and
		//stores its path
		while(toActor->prev) {
			path.push(toActor);
			toActor= toActor->prev;
		}
	//	path.push(fromActor);

		//outputs the path into file
		ofile<< "(" << fromActor->name << ")";
		while( !path.empty() ) {
			ofile << "--" << "[" << path.top()->moviePath << "#@" << path.top()->movieYear
					<< "]-->(" << path.top()->name << ")";
			//pops everytime path is done 
			path.pop();
		}
		graph.clearGraph();
		ofile<<endl;
	}

	dataFile.close();
	compareFile.close();
	ofile.close();
	return 0;
}


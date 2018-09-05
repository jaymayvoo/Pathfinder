#include "ActorGraph.hpp"
#include <queue>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

		string fromActor(record[0]);
		string toActor (record[1]);
		pairs.insert(pairs.end(), make_pair(fromActor, toActor));
		
	}
	if( !infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
	}
	infile.close();

} 

int main( int argc, char* argv[] ) {
	
	ActorGraph graph;
	graph.loadFromFile("movie_casts.tsv",false);

}


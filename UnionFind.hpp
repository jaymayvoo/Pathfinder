#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <unordered_map>
#include <vector>
using namespace std;

class UnionFind {

	public:

	unordered_map<string, int> movieYears;
	unordered_map<string, vector<string> > actorSet;

	void createSets(const char* in_filename, int year) {
    	// Initialize the file stream
    	ifstream infile(in_filename);
    	bool have_header = false;
		unordered_map<string, int>::iterator checkMovie;		
		unordered_map<string, vector<string> >::iterator checkSet;
		unordered_map<string, vector<string> >::iterator checkOther;
		vector<string>::iterator findName;
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
			
			if( movie_year == year ) {
				checkMovie = movieYears.find( movie_title );
				checkSet = actorSet.find( movie_title );
				if( checkMovie == movieYears.end() ) {
					movieYears.insert( make_pair(movie_title, movie_year) );
					vector<string>* cast = new vector<string>;
					actorSet.insert( make_pair(movie_title, *cast) );
					actorSet[movie_title].push_back(actor_name);
				}
				else {
					actorSet[movie_title].push_back(actor_name);
				}
			}
		}
		checkSet = actorSet.begin();
		checkOther = actorSet.begin();
		++checkOther;
		vector<string>::iterator otherName;
		while( checkOther != actorSet.end() ) {
			findName = checkOther->second.begin();
			while( findName != checkOther->second.end() ) {
				while( otherName != checkSet->second.end() ) {
					if( *otherName == *findName ) {
						checkSet->second.insert( checkSet->second.end(), checkOther->second.begin(),
									 checkOther->second.end() );
						delete &(checkOther->second);
						actorSet.erase( checkOther->first );
						break;
					}
						otherName++;				
				}
			}
					checkSet++;
			}
			

		
	
		if (!infile.eof()) {
        	cerr << "Failed to read " << in_filename << "!\n";
    	}
    	infile.close();

}

	string ufind ( string actor ) {
		unordered_map<string, vector<string> >::iterator iter = actorSet.begin();
		vector<string>::iterator it;

		while( iter != actorSet.end() ) {
			it = iter->second.begin();
				while( it != iter->second.end() ) {
					if( actor == *it )
						return *it;
					it++;
				}
			iter++;
		}
		return "N/A";
	}

	int getOldestMovie(const char* in_filename) {
    	int oldestMovie = 2015;
    	// Initialize the file stream
    	ifstream infile(in_filename);
    	bool have_header = false;

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
	
			if ( movie_year < oldestMovie )
				oldestMovie = movie_year;
    	}
		if (!infile.eof()) {
        	cerr << "Failed to read " << in_filename << "!\n";
    		return 0;
		}
		infile.close();
		return oldestMovie;
	 }
};

#endif //UNIONFIND_HPP

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <pacovali@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 02:33:11 by pacovali      #+#    #+#                 */
/*   Updated: 2020/08/15 02:40:21 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Solver.class.hpp"

using namespace std;

int		checkSearchType( const string& type ) {
	int		searchType = -1;
	if ( type == "-astar"  ) {
		searchType = 3;
	} else if ( type == "-greedy" ) {
		searchType = 1;
	} else if ( type == "-costuniform" ) {
		searchType = 2;
	}
	if ( searchType < 0 ) {
		throw runtime_error("Unknown argument");
	}
	return (searchType);
}

int		main ( int ac, char **av ) {
	try {
		if ( ac < 3 || ac > 4 ) {
			cerr << "Usage: ./rubik -astar/-greedy/-costuniform [command_list] [-r random_command_list_length]" << endl;
			exit (1);
		}
		int		searchType = checkSearchType( av[1] );
		if ( ac == 4 ) {
			if ( string(av[2]) != "-r" ) {
				throw runtime_error("Unknown argument");
			}
			int length = -1;
			try {
				length = stoi(av[3]);
			} catch (const exception& e) {
				cerr << "Error: " << e.what() << endl;
			}
			if ( length < 1 ) {
				throw range_error("Length of random command list must be a positive integer");
			}
			Solver s( length );
			s.solve( searchType );
		} else {
			Solver s( av[2] );
			s.solve( searchType );
		}
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return (0);
}

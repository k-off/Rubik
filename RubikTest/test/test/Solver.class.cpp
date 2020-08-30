/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Solver.class.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <pacovali@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 02:33:35 by pacovali      #+#    #+#                 */
/*   Updated: 2020/08/24 21:00:46 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Solver.class.hpp"

using namespace std;

Solver::Solver( const std::string& mix ) {
	vector<char>	commands;
	string			allowedChars = "FRUBLD2' ";

	for ( auto c = mix.begin(); c < mix.end(); c++ ) {
		if ( find(allowedChars.begin(), allowedChars.end(), *c) == allowedChars.end() ) {
			throw out_of_range("Forbidden character found");
		}
		while ( *c == ' ' ) {
			c++;
		}
		if ( c == mix.end() ) {
			break ;
		}
		char	current = *c;
		if ( find(allowedChars.begin() + 6, allowedChars.end(), current) != allowedChars.end() ) {
			throw logic_error("Command not well formatted");
		}
		commands.push_back(current);
		c++;
		if ( c == mix.end() ) {
			break ;
		} else if ( *c == '2' ) {
			commands.push_back(current);
			c++;
		} else if ( *c == '\'' ) {
			commands.push_back(current);
			commands.push_back(current);
			c++;
		}
		if ( *c != ' ' && c != mix.end() ) {
			throw logic_error("Command doesn't end with a space");
		}
	}
	if ( commands.size() < 1 ) {
		throw range_error("Command list is empty");
	}
	head_.setInitialState(commands);
}

Solver::Solver( const int& len ) {
	vector<char>	commands;
	vector<char>	allowed = {'F', 'R', 'U', 'B', 'L', 'D'};
	
	if ( len < 1 ) {
		throw range_error("Lenght of random command list must be positive");
	}
	srand((int)time(nullptr));
	cerr << "Random mix of length " << len << ": ";
	for ( int i = 0; i < len; i++ ) {
		commands.push_back(allowed[rand() % 6]);
		cerr << *(commands.end() - 1) << " ";
	}
	cerr << endl;
	head_.setInitialState(commands);
}

void	Solver::solve( const int& searchType ) {
	allStates_.insert( head_.getState() );
	openStates_.insert( {head_.getWeight() * (searchType & 1 ? 1 : 0) + head_.getCost() * (searchType & 2 ? 1 : 0), &head_} );
	__uint128_t cur_solution = solution;

	while ( openStates_.size() > 0 ) {
		auto begin = openStates_.begin();
		auto state = begin->second;
		if ( state->getState() == solution ) {
			printSolution( state );
			exit (0);
		}
		state->setChildren();
		auto newChildren = state->getChildren();
		for ( auto& child : *newChildren ) {
			if ( allStates_.count(child.getState()) < 1 ) {
				allStates_.insert( child.getState() );
				openStates_.insert( {child.getWeight() * (searchType & 1) + child.getCost() * (searchType & 2), &child} );
			}
		}
		openStates_.erase( begin );
	}
}

void	Solver::printSolution( Rubik *solution ) const {
	vector<pair<char, char>> commands;
	vector<char> mods = {'\0', '2', '\''};
	
	__uint128_t tmp_sol = (__uint128_t)solution;
	cout << "     ";
	for (int i = 0; i < 128; i++) {
			cout << (i % 6 ? '\0' : ' ') << ((uint8_t)tmp_sol & 1);
			tmp_sol >>= 1;
		}
	cout << endl;

	while ( solution->getParent() != nullptr ) {
		commands.insert( commands.begin(), {solution->getCommand(), solution->getCommandModifier()} );
		cout << "W: " << solution->getWeight();
		__uint128_t state = solution->getState();
		for (int i = 0; i < 128; i++) {
			cout << (i % 6 ? '\0' : ' ') << ((uint8_t)state & 1);
			state >>= 1;
		}
		cout << endl;
		solution = solution->getParent();
	}
	for ( auto c = commands.begin(); c < commands.end(); c++ ) {
		cout << c->first << c->second << ' ';
	}
	cout << endl;
}

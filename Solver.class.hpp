/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Solver.class.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <pacovali@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 02:33:40 by pacovali      #+#    #+#                 */
/*   Updated: 2020/08/15 02:33:41 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SOLVER_CLASS_HPP
# define __SOLVER_CLASS_HPP

# include "Rubik.class.hpp"

class Solver {
private:
	Rubik									head_;			// initial cube
	std::set<__uint128_t>					allStates_;		// all states ever generated
	std::set<std::pair<uint16_t, Rubik*>>	openStates_;	// all states which were not yet checked
public:
	Solver( const std::string& mix );						// initialize with a predefined initial mix
	Solver( const int& len );								// initialize with a length of random initial mix
	void	solve( const int& searchType );
	void	printSolution( Rubik *solution ) const;
};

#endif

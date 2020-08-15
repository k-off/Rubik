/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Rubik.class.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <pacovali@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 02:33:27 by pacovali      #+#    #+#                 */
/*   Updated: 2020/08/15 02:46:26 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RUBIK_CLASS_HPP
# define __RUBIK_CLASS_HPP

# include "header.h"

// Extract a single coordinate from state
# define COORDINATE 3

// Size of coordinate in bits
# define COORD_SIZE 2

// Size of node in bits
# define NODE_SIZE 6

// solution cube
const __uint128_t solution = ((__uint128_t)4646641668198692 << 60) | (__uint128_t)686272320752951945;

// helper constants to null all swapped nodes at once (see binary representation)
const __uint128_t null_front = ((__uint128_t)4398046507008 << 60) | (__uint128_t)1152640030703878143;
const __uint128_t null_right = ((__uint128_t)1152640030703878080 << 60) | (__uint128_t)18014329790267391;
const __uint128_t null_back = ((__uint128_t)1152921435887632383 << 60) | (__uint128_t)281474959933503;
const __uint128_t null_left = ((__uint128_t)18014398492704831 << 60) | (__uint128_t)1134911504143872000;
const __uint128_t null_upper = ((__uint128_t)1152921504606846975 << 60) | (__uint128_t)1152640029630136320;
const __uint128_t null_bottom = ((__uint128_t)4095 << 60) | (__uint128_t)1152921504606846975;

//swap node helper
const __uint128_t node = 63;

/**
 Commands - Front, Right, Up, Back, Left, Down
*/
enum Command {
	F = 'F', R = 'R', U = 'U', B = 'B', L = 'L', D = 'D',
};

class Rubik {
private:
	uint16_t					cost_;		//	how many steps from the initial state
	uint16_t					weight_;	//	how far is current state from solution; lighter - closer
	__uint128_t					state_;		//	current cube itself
	Rubik						*parent_;	//	pointer to the parent state
	std::vector<Rubik>			children_;	//	array of next states
	char						cmd_;		//	command which led to current state
	char						mod_;

	void						countWeight_( void );
	void						f_( void );
	void						r_( void );
	void						u_( void );
	void						b_( void );
	void						l_( void );
	void						d_( void );
	void						setVals_( int cmd, Rubik* parent, char mod, uint16_t cost);
public:
	Rubik( void );					//	generate initial state
	Rubik( const Rubik *parent );	//	generate child

	void						setInitialState( const std::vector<char>& mix );
	void						setChildren( void );		//	generate new states
	std::vector<Rubik>			*getChildren( void );
	const std::vector<Rubik>	*getChildren( void ) const;	//	get pointer to the vector of new states
	__uint128_t					getState( void ) const;
	uint16_t					getCost( void ) const;
	uint16_t					getWeight( void ) const;
	char						getCmd( void ) const;
	char						getMod( void ) const;
	Rubik						*getParent( void ) const;
};

#endif
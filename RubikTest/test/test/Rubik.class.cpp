/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Rubik.class.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <pacovali@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 02:33:21 by pacovali      #+#    #+#                 */
/*   Updated: 2020/08/24 21:02:28 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.class.hpp"

Rubik::Rubik( void ) {
	_cost = 0;
	_weight = 0;
	_state = solution;
	_parent = nullptr;
	_lastCommand = -1;
}

Rubik::Rubik( const Rubik *parent ) {
	_cost = parent->_cost + 1;
	_weight = 0;
	_state = parent->_state;
	_parent = (Rubik*)parent;
	_lastCommand = -1;
}

void						Rubik::_calculateWeight( void ) {
	__uint128_t current = _state;
	_weight = 0;
	for ( int offset = 0; offset < 120; offset += COORD_SIZE ) {
		_weight += abs(((uint8_t)(solution >> offset) & COORDINATE) - ((uint8_t)(current >> offset) & COORDINATE));
	}
}

void						Rubik::_front( void ) {
	_state = (_state & null_front) |
		 ((_state & (node << (NODE_SIZE * 19))) >> (NODE_SIZE * 12)) |
		 ((_state & (node << (NODE_SIZE * 18))) >> (NODE_SIZE * 7)) |
		 ((_state & (node << (NODE_SIZE * 17))) << (NODE_SIZE * 2)) |
		 ((_state & (node << (NODE_SIZE * 10))) << (NODE_SIZE * 8)) |
		 ((_state & (node << (NODE_SIZE * 5))) << (NODE_SIZE * 12)) |
		 ((_state & (node << (NODE_SIZE * 6))) << (NODE_SIZE * 4)) |
		 ((_state & (node << (NODE_SIZE * 7))) >> (NODE_SIZE * 2)) |
		 ((_state & (node << (NODE_SIZE * 11))) >> (NODE_SIZE * 5));
	_lastCommand = F;
}

void						Rubik::_right( void ) {
	_state = (_state & null_right) |
		 ((_state & (node << (NODE_SIZE * 17))) >> (NODE_SIZE * 12)) |
		 ((_state & (node << (NODE_SIZE * 16))) >> (NODE_SIZE * 6)) |
		 ((_state & (node << (NODE_SIZE * 15))) << (NODE_SIZE * 2)) |
		 ((_state & (node << (NODE_SIZE * 9))) << (NODE_SIZE * 7)) |
		 ((_state & (node << (NODE_SIZE * 3))) << (NODE_SIZE * 12)) |
		 ((_state & (node << (NODE_SIZE * 4))) << (NODE_SIZE * 5)) |
		 ((_state & (node << (NODE_SIZE * 5))) >> (NODE_SIZE * 2)) |
		 ((_state & (node << (NODE_SIZE * 10))) >> (NODE_SIZE * 6));
	_lastCommand = R;
}

void						Rubik::_up( void ) {
	_state = (_state & null_upper) |
		((_state & (node << (NODE_SIZE * 7))) >> (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 6))) >> (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 5))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 4))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 3))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 2))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 1))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 0))) << (NODE_SIZE * 2));
	_lastCommand = U;
}

void						Rubik::_back( void ) {
	_state = (_state & null_back) |
		((_state & (node << (NODE_SIZE * 15))) >> (NODE_SIZE * 12)) |
		((_state & (node << (NODE_SIZE * 14))) >> (NODE_SIZE * 5)) |
		((_state & (node << (NODE_SIZE * 13))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 8))) << (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 1))) << (NODE_SIZE * 12)) |
		((_state & (node << (NODE_SIZE * 2))) << (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 3))) >> (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 9))) >> (NODE_SIZE * 7));
	_lastCommand = B;
}

void						Rubik::_left( void ) {
	_state = (_state & null_left) |
		((_state & (node << (NODE_SIZE * 13))) >> (NODE_SIZE * 12)) |
		((_state & (node << (NODE_SIZE * 12))) >> (NODE_SIZE * 4)) |
		((_state & (node << (NODE_SIZE * 19))) >> (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 11))) << (NODE_SIZE * 1)) |
		((_state & (node << (NODE_SIZE * 7))) << (NODE_SIZE * 12)) |
		((_state & (node << (NODE_SIZE * 0))) << (NODE_SIZE * 11)) |
		((_state & (node << (NODE_SIZE * 1))) << (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 8))) >> (NODE_SIZE * 8));
	_lastCommand = L;
}

void						Rubik::_down( void ) {
	_state = (_state & null_bottom) |
		((_state & (node << (NODE_SIZE * 19))) >> (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 18))) >> (NODE_SIZE * 6)) |
		((_state & (node << (NODE_SIZE * 17))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 16))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 15))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 14))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 13))) << (NODE_SIZE * 2)) |
		((_state & (node << (NODE_SIZE * 12))) << (NODE_SIZE * 2));
	_lastCommand = D;
}

void						Rubik::setInitialState( const std::vector<char>& mix ) {
	for ( auto command : mix ) {
		if (command == F) {
			_front();
		} else if ( command == R ) {
			_right();
		} else if ( command == U ) {
			_up();
		} else if ( command == B ) {
			_back();
		} else if ( command == L ) {
			_left();
		} else if ( command == D ) {
			_down();
		}
	}
	_lastCommand = -1;
	_calculateWeight();
}

void						Rubik::_rotate( int command, Rubik* parent, char commandModifier, uint16_t cost) {
	if (command == F) {
		_front();
	} else if ( command == R ) {
		_right();
	} else if ( command == U ) {
		_up();
	} else if ( command == B ) {
		_back();
	} else if ( command == L ) {
		_left();
	} else if ( command == D ) {
		_down();
	}
	_calculateWeight();
	_parent = parent;
	_commandModifier = commandModifier;
	_cost = cost;
}

void						Rubik::setChildren( void ) {
	auto lastChild = _children.begin();
	std::vector<char> commandModifier = {'\0', '2', '\''};

	if ( this->_lastCommand != F ) {
		for (int i = 0; i < 3; i++) {
			_children.push_back( i ? &(*lastChild) : this );
			lastChild = _children.begin() + _children.size() - 1;
			lastChild->_rotate( F, this, commandModifier[i], _cost + 1);
		}
	}
	if ( this->_lastCommand != R ) {
		for (int i = 0; i < 3; i++) {
			_children.push_back( i ? &(*lastChild) : this );
			lastChild = _children.begin() + _children.size() - 1;
			lastChild->_rotate( R, this, commandModifier[i], _cost + 1);
		}
	}
	if ( this->_lastCommand != U ) {
		for (int i = 0; i < 3; i++) {
			_children.push_back( i ? &(*lastChild) : this );
			lastChild = _children.begin() + _children.size() - 1;
			lastChild->_rotate( U, this, commandModifier[i], _cost + 1);
		}
	}
	if ( this->_lastCommand != B ) {
		for (int i = 0; i < 3; i++) {
			_children.push_back( i ? &(*lastChild) : this );
			lastChild = _children.begin() + _children.size() - 1;
			lastChild->_rotate( B, this, commandModifier[i], _cost + 1);
		}
	}
	if ( this->_lastCommand != L ) {
		for (int i = 0; i < 3; i++) {
			_children.push_back( i ? &(*lastChild) : this );
			lastChild = _children.begin() + _children.size() - 1;
			lastChild->_rotate( L, this, commandModifier[i], _cost + 1);
		}
	}
	if ( this->_lastCommand != D ) {
		for (int i = 0; i < 3; i++) {
			_children.push_back( i ? &(*lastChild) : this );
			lastChild = _children.begin() + _children.size() - 1;
			lastChild->_rotate( D, this, commandModifier[i], _cost + 1);
		}
	}
}

std::vector<Rubik>			*Rubik::getChildren( void ) {
	return ( &_children );
}

const std::vector<Rubik>	*Rubik::getChildren( void ) const {
	return ( &_children );
}

__uint128_t					Rubik::getState( void ) const {
	return ( _state );
}

uint16_t					Rubik::getCost( void ) const {
	return ( _cost );
}

uint16_t					Rubik::getWeight( void ) const {
	return ( _weight );
}

char						Rubik::getCommand( void ) const {
	return ( _lastCommand );
}

char						Rubik::getCommandModifier( void ) const {
	return ( _commandModifier );
}

Rubik						*Rubik::getParent( void ) const {
	return (_parent);
}


// R F U B F B L F B L D F U L U F R B L B B B U R B
// B D R L B R D U D D D R R L U F R L F B D U B L U
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Rubik.class.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <pacovali@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/15 02:33:21 by pacovali      #+#    #+#                 */
/*   Updated: 2020/08/15 02:33:21 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.class.hpp"

Rubik::Rubik( void ) {
	cost_ = 0;
	weight_ = 0;
	state_ = solution;
	parent_ = nullptr;
	cmd_ = -1;
}

Rubik::Rubik( const Rubik *parent ) {
	cost_ = parent->cost_ + 1;
	weight_ = 0;
	state_ = parent->state_;
	parent_ = (Rubik*)parent;
	cmd_ = -1;
}

void						Rubik::countWeight_( void ) {
	__uint128_t current = state_;
	char	offset = 0;
	for ( int i = 0; i < 60; i++ ) {
		weight_ += abs(char((solution >> offset) & COORDINATE) - char((current >> offset) & COORDINATE));
		offset += COORD_SIZE;
	}
}

void						Rubik::f_( void ) {
	state_ = (state_ & null_front) |
		 ((state_ & (node << (NODE_SIZE * 19))) >> (NODE_SIZE * 12)) |
		 ((state_ & (node << (NODE_SIZE * 18))) >> (NODE_SIZE * 7)) |
		 ((state_ & (node << (NODE_SIZE * 17))) << (NODE_SIZE * 2)) |
		 ((state_ & (node << (NODE_SIZE * 10))) << (NODE_SIZE * 8)) |
		 ((state_ & (node << (NODE_SIZE * 5))) << (NODE_SIZE * 12)) |
		 ((state_ & (node << (NODE_SIZE * 6))) << (NODE_SIZE * 4)) |
		 ((state_ & (node << (NODE_SIZE * 7))) >> (NODE_SIZE * 2)) |
		 ((state_ & (node << (NODE_SIZE * 11))) >> (NODE_SIZE * 5));
	cmd_ = F;
}

void						Rubik::r_( void ) {
	state_ = (state_ & null_right) |
		 ((state_ & (node << (NODE_SIZE * 17))) >> (NODE_SIZE * 12)) |
		 ((state_ & (node << (NODE_SIZE * 16))) >> (NODE_SIZE * 6)) |
		 ((state_ & (node << (NODE_SIZE * 15))) << (NODE_SIZE * 2)) |
		 ((state_ & (node << (NODE_SIZE * 9))) << (NODE_SIZE * 7)) |
		 ((state_ & (node << (NODE_SIZE * 3))) << (NODE_SIZE * 12)) |
		 ((state_ & (node << (NODE_SIZE * 4))) << (NODE_SIZE * 5)) |
		 ((state_ & (node << (NODE_SIZE * 5))) >> (NODE_SIZE * 2)) |
		 ((state_ & (node << (NODE_SIZE * 10))) >> (NODE_SIZE * 6));
	cmd_ = R;
}

void						Rubik::u_( void ) {
	state_ = (state_ & null_upper) |
		((state_ & (node << (NODE_SIZE * 7))) >> (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 6))) >> (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 5))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 4))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 3))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 2))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 1))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 0))) << (NODE_SIZE * 2));
	cmd_ = U;
}

void						Rubik::b_( void ) {
	state_ = (state_ & null_back) |
		((state_ & (node << (NODE_SIZE * 15))) >> (NODE_SIZE * 12)) |
		((state_ & (node << (NODE_SIZE * 14))) >> (NODE_SIZE * 5)) |
		((state_ & (node << (NODE_SIZE * 13))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 8))) << (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 1))) << (NODE_SIZE * 12)) |
		((state_ & (node << (NODE_SIZE * 2))) << (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 3))) >> (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 9))) >> (NODE_SIZE * 7));
	cmd_ = B;
}

void						Rubik::l_( void ) {
	state_ = (state_ & null_left) |
		((state_ & (node << (NODE_SIZE * 13))) >> (NODE_SIZE * 12)) |
		((state_ & (node << (NODE_SIZE * 12))) >> (NODE_SIZE * 4)) |
		((state_ & (node << (NODE_SIZE * 19))) >> (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 11))) << (NODE_SIZE * 1)) |
		((state_ & (node << (NODE_SIZE * 7))) << (NODE_SIZE * 12)) |
		((state_ & (node << (NODE_SIZE * 0))) << (NODE_SIZE * 11)) |
		((state_ & (node << (NODE_SIZE * 1))) << (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 8))) >> (NODE_SIZE * 8));
	cmd_ = L;
}

void						Rubik::d_( void ) {
	state_ = (state_ & null_bottom) |
		((state_ & (node << (NODE_SIZE * 19))) >> (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 18))) >> (NODE_SIZE * 6)) |
		((state_ & (node << (NODE_SIZE * 17))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 16))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 15))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 14))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 13))) << (NODE_SIZE * 2)) |
		((state_ & (node << (NODE_SIZE * 12))) << (NODE_SIZE * 2));
	cmd_ = D;
}

void						Rubik::setInitialState( const std::vector<char>& mix ) {
	for ( auto i : mix ) {
		if (i == F) {
			f_();
		} else if ( i == R ) {
			r_();
		} else if ( i == U ) {
			u_();
		} else if ( i == B ) {
			b_();
		} else if ( i == L ) {
			l_();
		} else if ( i == D ) {
			d_();
		}
	}
	cmd_ = -1;
	countWeight_();
}

void						Rubik::setVals_( int cmd, Rubik* parent, char mod, uint16_t cost) {
	if (cmd == F) {
		f_();
	} else if ( cmd == R ) {
		r_();
	} else if ( cmd == U ) {
		u_();
	} else if ( cmd == B ) {
		b_();
	} else if ( cmd == L ) {
		l_();
	} else if ( cmd == D ) {
		d_();
	}
	countWeight_();
	parent_ = parent;
	mod_ = mod;
	cost_ = cost;
}

void						Rubik::setChildren( void ) {
	auto back = children_.begin();
	std::vector<char> mod = {'\0', '2', '\''};

	if ( this->cmd_ != F ) {
		for (int i = 0; i < 3; i++) {
			children_.push_back( i ? &(*back) : this );
			back = children_.begin() + children_.size() - 1;
			back->setVals_( F, this, mod[i], cost_ + 1);
		}
	}
	if ( this->cmd_ != R ) {
		for (int i = 0; i < 3; i++) {
			children_.push_back( i ? &(*back) : this );
			back = children_.begin() + children_.size() - 1;
			back->setVals_( R, this, mod[i], cost_ + 1);
		}
	}
	if ( this->cmd_ != U ) {
		for (int i = 0; i < 3; i++) {
			children_.push_back( i ? &(*back) : this );
			back = children_.begin() + children_.size() - 1;
			back->setVals_( U, this, mod[i], cost_ + 1);
		}
	}
	if ( this->cmd_ != B ) {
		for (int i = 0; i < 3; i++) {
			children_.push_back( i ? &(*back) : this );
			back = children_.begin() + children_.size() - 1;
			back->setVals_( B, this, mod[i], cost_ + 1);
		}
	}
	if ( this->cmd_ != L ) {
		for (int i = 0; i < 3; i++) {
			children_.push_back( i ? &(*back) : this );
			back = children_.begin() + children_.size() - 1;
			back->setVals_( L, this, mod[i], cost_ + 1);
		}
	}
	if ( this->cmd_ != D ) {
		for (int i = 0; i < 3; i++) {
			children_.push_back( i ? &(*back) : this );
			back = children_.begin() + children_.size() - 1;
			back->setVals_( D, this, mod[i], cost_ + 1);
		}
	}
}

std::vector<Rubik>			*Rubik::getChildren( void ) {
	return ( &children_ );
}

const std::vector<Rubik>	*Rubik::getChildren( void ) const {
	return ( &children_ );
}

__uint128_t					Rubik::getState( void ) const {
	return ( state_ );
}

uint16_t					Rubik::getCost( void ) const {
	return ( cost_ );
}

uint16_t					Rubik::getWeight( void ) const {
	return ( weight_ );
}

char						Rubik::getCmd( void ) const {
	return ( cmd_ );
}

char						Rubik::getMod( void ) const {
	return ( mod_ );
}

Rubik						*Rubik::getParent( void ) const {
	return (parent_);
}

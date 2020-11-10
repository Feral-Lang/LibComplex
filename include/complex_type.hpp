/*
	MIT License

	Copyright (c) 2020 Feral Language repositories

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so.
*/

#ifndef FERAL_LIB_COMPLEX_TYPE_HPP
#define FERAL_LIB_COMPLEX_TYPE_HPP

#include <mpc.h>
#include <feral/VM/VM.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////// Complex class ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class var_complex_t : public var_base_t
{
	mpc_t m_val;
public:
	var_complex_t( const mpc_t val, const size_t & src_id, const size_t & idx );
	var_complex_t( const mpz_t real, const mpz_t imag, const size_t & src_id, const size_t & idx );
	var_complex_t( const mpfr_t real, const mpfr_t imag, const size_t & src_id, const size_t & idx );
	var_complex_t( const mpz_t real, const mpfr_t imag, const size_t & src_id, const size_t & idx );
	var_complex_t( const mpfr_t real, const mpz_t imag, const size_t & src_id, const size_t & idx );
	var_complex_t( const int & real, const int & imag, const size_t & src_id, const size_t & idx );
	var_complex_t( const char * val, const size_t & src_id, const size_t & idx );
	~var_complex_t();

	var_base_t * copy( const size_t & src_id, const size_t & idx );
	void set( var_base_t * from );

	mpc_t & get();
};
#define COMPLEX( x ) static_cast< var_complex_t * >( x )

// Some extra functions for ease of dear life
int mpc_set_z_fr( mpc_ptr rop, mpz_srcptr re, mpfr_srcptr im, mpc_rnd_t rnd )
	MPC_SET_X_Y( z, fr, rop, re, im, rnd );
int mpc_set_fr_z( mpc_ptr rop, mpfr_srcptr re, mpz_srcptr im, mpc_rnd_t rnd )
	MPC_SET_X_Y( fr, z, rop, re, im, rnd );

#endif // FERAL_LIB_COMPLEX_TYPE_HPP
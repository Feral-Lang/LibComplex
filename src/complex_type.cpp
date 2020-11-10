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

#include "../include/complex_type.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////// VAR_COMPLEX //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var_complex_t::var_complex_t( const mpc_t val, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set( m_val, val, MPC_RNDND );
}
var_complex_t::var_complex_t( const mpz_t real, const mpz_t imag, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set_z_z( m_val, real, imag, MPC_RNDND );
}
var_complex_t::var_complex_t( const mpfr_t real, const mpfr_t imag, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set_fr_fr( m_val, real, imag, MPC_RNDND );
}
var_complex_t::var_complex_t( const mpz_t real, const mpfr_t imag, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set_z_fr( m_val, real, imag, MPC_RNDND );
}
var_complex_t::var_complex_t( const mpfr_t real, const mpz_t imag, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set_fr_z( m_val, real, imag, MPC_RNDND );
}
var_complex_t::var_complex_t( const int & real, const int & imag, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set_si_si( m_val, real, imag, MPC_RNDND );
}
var_complex_t::var_complex_t( const char * val, const size_t & src_id, const size_t & idx )
	: var_base_t( type_id< var_complex_t >(), src_id, idx, false, false )
{
	mpc_init2( m_val, 256 );
	mpc_set_str( m_val, val, 10, MPC_RNDND );
}
var_complex_t::~var_complex_t()
{
	mpc_clear( m_val );
}

var_base_t * var_complex_t::copy( const size_t & src_id, const size_t & idx ) { return new var_complex_t( m_val, src_id, idx ); }
mpc_t & var_complex_t::get() { return m_val; }
void var_complex_t::set( var_base_t * from )
{
	mpc_set( m_val, COMPLEX( from )->get(), MPC_RNDND );
}
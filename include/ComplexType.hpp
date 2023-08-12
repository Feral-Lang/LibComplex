#pragma once

#include <mpc.h>
#include <VM/Interpreter.hpp>

using namespace fer;

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Complex class ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

class VarComplex : public Var
{
	mpc_t val;

public:
	VarComplex(const ModuleLoc *loc, const mpc_t _val);
	VarComplex(const ModuleLoc *loc, const mpz_t real, const mpz_t imag);
	VarComplex(const ModuleLoc *loc, const mpfr_t real, const mpfr_t imag);
	VarComplex(const ModuleLoc *loc, const mpz_t real, const mpfr_t imag);
	VarComplex(const ModuleLoc *loc, const mpfr_t real, const mpz_t imag);
	VarComplex(const ModuleLoc *loc, int real, int imag);
	VarComplex(const ModuleLoc *loc, const char *val);
	~VarComplex();

	Var *copy(const ModuleLoc *loc);
	void set(Var *from);

	inline mpc_t &get() { return val; }
};

// Some extra functions for ease of dear life
int mpc_set_z_fr(mpc_ptr rop, mpz_srcptr re, mpfr_srcptr im, mpc_rnd_t rnd);
int mpc_set_fr_z(mpc_ptr rop, mpfr_srcptr re, mpz_srcptr im, mpc_rnd_t rnd);

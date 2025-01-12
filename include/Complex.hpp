#pragma once

#include <mpc.h>
#include <VM/Interpreter.hpp>

namespace fer
{

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Complex class ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

class VarComplex : public Var
{
	mpc_t val;

	Var *onCopy(Interpreter &vm, ModuleLoc loc) override;
	void onSet(Interpreter &vm, Var *from) override;

public:
	VarComplex(ModuleLoc loc, const mpc_t _val);
	VarComplex(ModuleLoc loc, const mpz_t real, const mpz_t imag);
	VarComplex(ModuleLoc loc, const mpfr_t real, const mpfr_t imag);
	VarComplex(ModuleLoc loc, const mpz_t real, const mpfr_t imag);
	VarComplex(ModuleLoc loc, const mpfr_t real, const mpz_t imag);
	VarComplex(ModuleLoc loc, long long real, long long imag);
	VarComplex(ModuleLoc loc, long long real, long double imag);
	VarComplex(ModuleLoc loc, long double real, long long imag);
	VarComplex(ModuleLoc loc, long double real, long double imag);
	VarComplex(ModuleLoc loc, const char *val);
	// doesn't initialize, must call init() functions with this
	VarComplex();
	~VarComplex();

	inline mpc_t &getVal() { return val; }
};

// Some extra functions for ease of dear life
int mpc_set_z_fr(mpc_ptr rop, mpz_srcptr re, mpfr_srcptr im, mpc_rnd_t rnd);
int mpc_set_fr_z(mpc_ptr rop, mpfr_srcptr re, mpz_srcptr im, mpc_rnd_t rnd);
int mpc_set_si_ld(mpc_ptr rop, long long re, long double im, mpc_rnd_t rnd);
int mpc_set_ld_si(mpc_ptr rop, long double re, long long im, mpc_rnd_t rnd);

} // namespace fer
#include "ComplexType.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// VAR_COMPLEX ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

VarComplex::VarComplex(ModuleLoc loc, const mpc_t _val)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set(val, _val, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, const mpz_t real, const mpz_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_z_z(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, const mpfr_t real, const mpfr_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_fr_fr(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, const mpz_t real, const mpfr_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_z_fr(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, const mpfr_t real, const mpz_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_fr_z(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, long long real, long long imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_si_si(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, long long real, long double imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_si_ld(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, long double real, long long imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_ld_si(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, long double real, long double imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_ld_ld(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(ModuleLoc loc, const char *_val)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_str(val, _val, 10, MPC_RNDND);
}
VarComplex::~VarComplex() { mpc_clear(val); }

Var *VarComplex::copy(ModuleLoc loc) { return new VarComplex(loc, val); }
void VarComplex::set(Var *from) { mpc_set(val, as<VarComplex>(from)->get(), MPC_RNDND); }

int mpc_set_z_fr(mpc_ptr rop, mpz_srcptr re, mpfr_srcptr im, mpc_rnd_t rnd)
MPC_SET_X_Y(z, fr, rop, re, im, rnd);
int mpc_set_fr_z(mpc_ptr rop, mpfr_srcptr re, mpz_srcptr im, mpc_rnd_t rnd)
MPC_SET_X_Y(fr, z, rop, re, im, rnd);
int mpc_set_si_ld(mpc_ptr rop, long long re, long double im, mpc_rnd_t rnd)
MPC_SET_X_Y(si, ld, rop, re, im, rnd);
int mpc_set_ld_si(mpc_ptr rop, long double re, long long im, mpc_rnd_t rnd)
MPC_SET_X_Y(ld, si, rop, re, im, rnd);
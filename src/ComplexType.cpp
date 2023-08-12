#include "ComplexType.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// VAR_COMPLEX ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

VarComplex::VarComplex(const ModuleLoc *loc, const mpc_t _val)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set(val, _val, MPC_RNDND);
}
VarComplex::VarComplex(const ModuleLoc *loc, const mpz_t real, const mpz_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_z_z(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(const ModuleLoc *loc, const mpfr_t real, const mpfr_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_fr_fr(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(const ModuleLoc *loc, const mpz_t real, const mpfr_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_z_fr(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(const ModuleLoc *loc, const mpfr_t real, const mpz_t imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_fr_z(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(const ModuleLoc *loc, int real, int imag)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_si_si(val, real, imag, MPC_RNDND);
}
VarComplex::VarComplex(const ModuleLoc *loc, const char *_val)
	: Var(loc, typeID<VarComplex>(), false, false)
{
	mpc_init2(val, 256);
	mpc_set_str(val, _val, 10, MPC_RNDND);
}
VarComplex::~VarComplex() { mpc_clear(val); }

Var *VarComplex::copy(const ModuleLoc *loc) { return new VarComplex(loc, val); }
void VarComplex::set(Var *from) { mpc_set(val, as<VarComplex>(from)->get(), MPC_RNDND); }

int mpc_set_z_fr(mpc_ptr rop, mpz_srcptr re, mpfr_srcptr im, mpc_rnd_t rnd)
MPC_SET_X_Y(z, fr, rop, re, im, rnd);
int mpc_set_fr_z(mpc_ptr rop, mpfr_srcptr re, mpz_srcptr im, mpc_rnd_t rnd)
MPC_SET_X_Y(fr, z, rop, re, im, rnd);
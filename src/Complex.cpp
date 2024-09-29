#include "ComplexType.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Functions ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

Var *complexNewNative(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		      const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>()) {
		vm.fail(loc, "argument 1 to complex.new() must be of type 'int' or 'flt', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	if(!args[2]->is<VarInt>() && !args[2]->is<VarFlt>()) {
		vm.fail(loc, "argument 2 to complex.new() must be of type 'int' or 'flt', found: ",
			vm.getTypeName(args[2]));
		return nullptr;
	}

	Var *a1		= args[1];
	Var *a2		= args[2];
	VarComplex *res = nullptr;

	if(a1->is<VarInt>()) {
		if(a2->is<VarInt>()) {
			res =
			vm.makeVar<VarComplex>(loc, as<VarInt>(a1)->get(), as<VarInt>(a2)->get());
		} else if(a2->is<VarFlt>()) {
			res =
			vm.makeVar<VarComplex>(loc, as<VarInt>(a1)->get(), as<VarFlt>(a2)->get());
		}
	} else if(a1->is<VarFlt>()) {
		if(a2->is<VarInt>()) {
			res =
			vm.makeVar<VarComplex>(loc, as<VarFlt>(a1)->get(), as<VarInt>(a2)->get());
		} else if(a2->is<VarFlt>()) {
			res =
			vm.makeVar<VarComplex>(loc, as<VarFlt>(a1)->get(), as<VarFlt>(a2)->get());
		}
	}

	return res;
}

#define LOGICC_FUNC(name, sym)                                               \
	Var *complex##name(Interpreter &vm, ModuleLoc loc, Span<Var *> args, \
			   const StringMap<AssnArgData> &assn_args)          \
	{                                                                    \
		if(args[1]->is<VarComplex>()) {                              \
			return mpc_cmp(as<VarComplex>(args[0])->get(),       \
				       as<VarComplex>(args[1])->get()) sym 0 \
			       ? vm.getTrue()                                \
			       : vm.getFalse();                              \
		}                                                            \
		return vm.getFalse();                                        \
	}

LOGICC_FUNC(Lt, <)
LOGICC_FUNC(Gt, >)
LOGICC_FUNC(Le, <=)
LOGICC_FUNC(Ge, >=)

Var *complexAdd(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base	= as<VarComplex>(args[0])->get();
	VarComplex *res = vm.makeVar<VarComplex>(loc, base);
	if(args[1]->is<VarInt>())
		mpc_add_si(res->get(), base, mpz_get_si(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_add_fr(res->get(), base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_add(res->get(), base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return res;
}

Var *complexSub(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base	= as<VarComplex>(args[0])->get();
	VarComplex *res = vm.makeVar<VarComplex>(loc, base);
	if(args[1]->is<VarInt>())
		mpc_sub_ui(res->get(), base, mpz_get_ui(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_sub_fr(res->get(), base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_sub(res->get(), base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return res;
}

Var *complexMul(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base	= as<VarComplex>(args[0])->get();
	VarComplex *res = vm.makeVar<VarComplex>(loc, base);
	if(args[1]->is<VarInt>())
		mpc_mul_si(res->get(), base, mpz_get_si(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_mul_fr(res->get(), base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_mul(res->get(), base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return res;
}

Var *complexDiv(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base	= as<VarComplex>(args[0])->get();
	VarComplex *res = vm.makeVar<VarComplex>(loc, base);
	if(args[1]->is<VarInt>())
		mpc_div_ui(res->get(), base, mpz_get_ui(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_div_fr(res->get(), base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_div(res->get(), base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return res;
}

Var *complexAddAssn(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		    const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base = as<VarComplex>(args[0])->get();
	if(args[1]->is<VarInt>())
		mpc_add_si(base, base, mpz_get_si(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_add_fr(base, base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_add(base, base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return args[0];
}

Var *complexSubAssn(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		    const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base = as<VarComplex>(args[0])->get();
	if(args[1]->is<VarInt>())
		mpc_sub_ui(base, base, mpz_get_ui(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_sub_fr(base, base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_sub(base, base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return args[0];
}

Var *complexMulAssn(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		    const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base = as<VarComplex>(args[0])->get();
	if(args[1]->is<VarInt>())
		mpc_mul_si(base, base, mpz_get_si(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_mul_fr(base, base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_mul(base, base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return args[0];
}

Var *complexDivAssn(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		    const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>() && !args[1]->is<VarComplex>()) {
		vm.fail(loc,
			"argument 1 to complex arithmetic must be of "
			"type 'int', 'flt', or "
			"'complex', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	mpc_t &base = as<VarComplex>(args[0])->get();
	if(args[1]->is<VarInt>())
		mpc_div_ui(base, base, mpz_get_ui(as<VarInt>(args[1])->get()), MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_div_fr(base, base, as<VarFlt>(args[1])->get(), MPC_RNDND);
	else if(args[1]->is<VarComplex>())
		mpc_div(base, base, as<VarComplex>(args[1])->get(), MPC_RNDND);
	return args[0];
}

Var *complexEq(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
	       const StringMap<AssnArgData> &assn_args)
{
	if(args[1]->is<VarComplex>()) {
		return mpc_cmp(as<VarComplex>(args[0])->get(), as<VarComplex>(args[1])->get()) == 0
		       ? vm.getTrue()
		       : vm.getFalse();
	}
	return vm.getFalse();
}

Var *complexNe(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
	       const StringMap<AssnArgData> &assn_args)
{
	if(args[1]->is<VarComplex>()) {
		return mpc_cmp(as<VarComplex>(args[0])->get(), as<VarComplex>(args[1])->get()) != 0
		       ? vm.getTrue()
		       : vm.getFalse();
	}
	return vm.getTrue();
}

Var *complexPreInc(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		   const StringMap<AssnArgData> &assn_args)
{
	mpc_add_ui(as<VarComplex>(args[0])->get(), as<VarComplex>(args[0])->get(), 1, MPC_RNDND);
	return args[0];
}

Var *complexPostInc(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		    const StringMap<AssnArgData> &assn_args)
{
	VarComplex *res = vm.makeVar<VarComplex>(loc, as<VarComplex>(args[0])->get());
	mpc_add_ui(as<VarComplex>(args[0])->get(), as<VarComplex>(args[0])->get(), 1, MPC_RNDND);
	return res;
}

Var *complexPreDec(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		   const StringMap<AssnArgData> &assn_args)
{
	mpc_sub_ui(as<VarComplex>(args[0])->get(), as<VarComplex>(args[0])->get(), 1, MPC_RNDND);
	return args[0];
}

Var *complexPostDec(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		    const StringMap<AssnArgData> &assn_args)
{
	VarComplex *res = vm.makeVar<VarComplex>(loc, as<VarComplex>(args[0])->get());
	mpc_sub_ui(as<VarComplex>(args[0])->get(), as<VarComplex>(args[0])->get(), 1, MPC_RNDND);
	return res;
}

Var *complexUSub(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		 const StringMap<AssnArgData> &assn_args)
{
	VarComplex *res = vm.makeVar<VarComplex>(loc, as<VarComplex>(args[0])->get());
	mpc_neg(res->get(), as<VarComplex>(args[0])->get(), MPC_RNDND);
	return res;
}

Var *complexPow(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>()) {
		vm.fail(loc, "power must be an 'int' or 'flt', found: ", vm.getTypeName(args[1]));
		return nullptr;
	}
	VarComplex *res = vm.makeVar<VarComplex>(loc, as<VarComplex>(args[0])->get());
	if(args[1]->is<VarInt>())
		mpc_pow_z(res->get(), as<VarComplex>(args[0])->get(), as<VarInt>(args[1])->get(),
			  MPC_RNDND);
	else if(args[1]->is<VarFlt>())
		mpc_pow_fr(res->get(), as<VarComplex>(args[0])->get(), as<VarFlt>(args[1])->get(),
			   MPC_RNDND);
	return res;
}

Var *complexAbs(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	VarFlt *res = vm.makeVar<VarFlt>(loc, 0.0);
	mpc_abs(res->get(), as<VarComplex>(args[0])->get(), mpfr_get_default_rounding_mode());
	return res;
}

Var *complexSet(Interpreter &vm, ModuleLoc loc, Span<Var *> args,
		const StringMap<AssnArgData> &assn_args)
{
	if(!args[1]->is<VarInt>() && !args[1]->is<VarFlt>()) {
		vm.fail(loc, "argument 1 to complex.new() must be of type 'int' or 'flt', found: ",
			vm.getTypeName(args[1]));
		return nullptr;
	}
	if(!args[2]->is<VarInt>() && !args[2]->is<VarFlt>()) {
		vm.fail(loc, "argument 2 to complex.new() must be of type 'int' or 'flt', found: ",
			vm.getTypeName(args[2]));
		return nullptr;
	}

	Var *a1		= args[1];
	Var *a2		= args[2];
	VarComplex *res = as<VarComplex>(args[0]);

	if(a1->is<VarInt>()) {
		if(a2->is<VarInt>()) {
			mpc_set_z_z(res->get(), as<VarInt>(a1)->get(), as<VarInt>(a2)->get(),
				    MPC_RNDND);
		} else if(a2->is<VarFlt>()) {
			mpc_set_z_fr(res->get(), as<VarInt>(a1)->get(), as<VarFlt>(a2)->get(),
				     MPC_RNDND);
		}
	} else if(a1->is<VarFlt>()) {
		if(a2->is<VarInt>()) {
			mpc_set_fr_z(res->get(), as<VarFlt>(a1)->get(), as<VarInt>(a2)->get(),
				     MPC_RNDND);
		} else if(a2->is<VarFlt>()) {
			mpc_set_fr_fr(res->get(), as<VarFlt>(a1)->get(), as<VarFlt>(a2)->get(),
				      MPC_RNDND);
		}
	}
	return args[0];
}

INIT_MODULE(Complex)
{
	VarModule *mod = vm.getCurrModule();

	mod->addNativeFn("newNative", complexNewNative, 2);

	// register the complex type (registerType)
	vm.registerType<VarComplex>(loc, "Complex");

	vm.addNativeTypeFn<VarComplex>(loc, "+", complexAdd, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "-", complexSub, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "*", complexMul, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "/", complexDiv, 1);

	vm.addNativeTypeFn<VarComplex>(loc, "+=", complexAddAssn, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "-=", complexSubAssn, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "*=", complexMulAssn, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "/=", complexDivAssn, 1);

	vm.addNativeTypeFn<VarComplex>(loc, "==", complexEq, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "!=", complexNe, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "<", complexLt, 1);
	vm.addNativeTypeFn<VarComplex>(loc, "<=", complexLe, 1);
	vm.addNativeTypeFn<VarComplex>(loc, ">", complexGt, 1);
	vm.addNativeTypeFn<VarComplex>(loc, ">=", complexGe, 1);

	vm.addNativeTypeFn<VarComplex>(loc, "++x", complexPreInc, 0);
	vm.addNativeTypeFn<VarComplex>(loc, "x++", complexPostInc, 0);
	vm.addNativeTypeFn<VarComplex>(loc, "--x", complexPreDec, 0);
	vm.addNativeTypeFn<VarComplex>(loc, "x--", complexPostDec, 0);

	vm.addNativeTypeFn<VarComplex>(loc, "u-", complexUSub, 0);

	vm.addNativeTypeFn<VarComplex>(loc, "**", complexPow, 1);

	vm.addNativeTypeFn<VarComplex>(loc, "abs", complexAbs, 0);
	vm.addNativeTypeFn<VarComplex>(loc, "set", complexSet, 2);

	return true;
}

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

#ifndef LIBRARY_CORE_FLT_HPP
#define LIBRARY_CORE_FLT_HPP

#include "../include/complex_type.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Functions ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

var_base_t *complex_new_native(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>()) {
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex.new() must be of type 'int' or 'flt', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	if(!fd.args[2]->istype<var_int_t>() && !fd.args[2]->istype<var_flt_t>()) {
		vm.fail(fd.src_id, fd.idx,
			"argument 2 to complex.new() must be of type 'int' or 'flt', found: %s",
			vm.type_name(fd.args[2]).c_str());
		return nullptr;
	}

	var_base_t *a1	   = fd.args[1];
	var_base_t *a2	   = fd.args[2];
	var_complex_t *res = nullptr;

	if(a1->istype<var_int_t>()) {
		if(a2->istype<var_int_t>()) {
			res = make<var_complex_t>(INT(a1)->get(), INT(a2)->get());
		} else if(a2->istype<var_flt_t>()) {
			res = make<var_complex_t>(INT(a1)->get(), FLT(a2)->get());
		}
	} else if(a1->istype<var_flt_t>()) {
		if(a2->istype<var_int_t>()) {
			res = make<var_complex_t>(FLT(a1)->get(), INT(a2)->get());
		} else if(a2->istype<var_flt_t>()) {
			res = make<var_complex_t>(FLT(a1)->get(), FLT(a2)->get());
		}
	}

	return res;
}

#define LOGICC_FUNC(name, sym)                                                                 \
	var_base_t *complex_##name(vm_state_t &vm, const fn_data_t &fd)                        \
	{                                                                                      \
		if(fd.args[1]->istype<var_complex_t>()) {                                      \
			return mpc_cmp(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[1])->get()) \
			       sym 0                                                           \
			       ? vm.tru                                                        \
			       : vm.fals;                                                      \
		}                                                                              \
		return vm.fals;                                                                \
	}

LOGICC_FUNC(lt, <)
LOGICC_FUNC(gt, >)
LOGICC_FUNC(le, <=)
LOGICC_FUNC(ge, >=)

var_base_t *complex_add(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base	   = COMPLEX(fd.args[0])->get();
	var_complex_t *res = make<var_complex_t>(base);
	if(fd.args[1]->istype<var_int_t>())
		mpc_add_si(res->get(), base, mpz_get_si(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_add_fr(res->get(), base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_add(res->get(), base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return res;
}

var_base_t *complex_sub(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base	   = COMPLEX(fd.args[0])->get();
	var_complex_t *res = make<var_complex_t>(base);
	if(fd.args[1]->istype<var_int_t>())
		mpc_sub_ui(res->get(), base, mpz_get_ui(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_sub_fr(res->get(), base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_sub(res->get(), base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return res;
}

var_base_t *complex_mul(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base	   = COMPLEX(fd.args[0])->get();
	var_complex_t *res = make<var_complex_t>(base);
	if(fd.args[1]->istype<var_int_t>())
		mpc_mul_si(res->get(), base, mpz_get_si(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_mul_fr(res->get(), base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_mul(res->get(), base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return res;
}

var_base_t *complex_div(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base	   = COMPLEX(fd.args[0])->get();
	var_complex_t *res = make<var_complex_t>(base);
	if(fd.args[1]->istype<var_int_t>())
		mpc_div_ui(res->get(), base, mpz_get_ui(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_div_fr(res->get(), base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_div(res->get(), base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return res;
}

var_base_t *complex_addassn(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base = COMPLEX(fd.args[0])->get();
	if(fd.args[1]->istype<var_int_t>())
		mpc_add_si(base, base, mpz_get_si(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_add_fr(base, base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_add(base, base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return fd.args[0];
}

var_base_t *complex_subassn(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base = COMPLEX(fd.args[0])->get();
	if(fd.args[1]->istype<var_int_t>())
		mpc_sub_ui(base, base, mpz_get_ui(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_sub_fr(base, base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_sub(base, base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return fd.args[0];
}

var_base_t *complex_mulassn(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base = COMPLEX(fd.args[0])->get();
	if(fd.args[1]->istype<var_int_t>())
		mpc_mul_si(base, base, mpz_get_si(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_mul_fr(base, base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_mul(base, base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return fd.args[0];
}

var_base_t *complex_divassn(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>() &&
	   !fd.args[1]->istype<var_complex_t>())
	{
		vm.fail(fd.src_id, fd.idx,
			"argument 1 to complex arithmetic must be of type 'int', 'flt', or "
			"'complex', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	mpc_t &base = COMPLEX(fd.args[0])->get();
	if(fd.args[1]->istype<var_int_t>())
		mpc_div_ui(base, base, mpz_get_ui(INT(fd.args[1])->get()), MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_div_fr(base, base, FLT(fd.args[1])->get(), MPC_RNDND);
	else if(fd.args[1]->istype<var_complex_t>())
		mpc_div(base, base, COMPLEX(fd.args[1])->get(), MPC_RNDND);
	return fd.args[0];
}

var_base_t *complex_eq(vm_state_t &vm, const fn_data_t &fd)
{
	if(fd.args[1]->istype<var_complex_t>()) {
		return mpc_cmp(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[1])->get()) == 0
		       ? vm.tru
		       : vm.fals;
	}
	return vm.fals;
}

var_base_t *complex_ne(vm_state_t &vm, const fn_data_t &fd)
{
	if(fd.args[1]->istype<var_complex_t>()) {
		return mpc_cmp(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[1])->get()) != 0
		       ? vm.tru
		       : vm.fals;
	}
	return vm.tru;
}

var_base_t *complex_preinc(vm_state_t &vm, const fn_data_t &fd)
{
	mpc_add_ui(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[0])->get(), 1, MPC_RNDND);
	return fd.args[0];
}

var_base_t *complex_postinc(vm_state_t &vm, const fn_data_t &fd)
{
	var_complex_t *res = make<var_complex_t>(COMPLEX(fd.args[0])->get());
	mpc_add_ui(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[0])->get(), 1, MPC_RNDND);
	return res;
}

var_base_t *complex_predec(vm_state_t &vm, const fn_data_t &fd)
{
	mpc_sub_ui(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[0])->get(), 1, MPC_RNDND);
	return fd.args[0];
}

var_base_t *complex_postdec(vm_state_t &vm, const fn_data_t &fd)
{
	var_complex_t *res = make<var_complex_t>(COMPLEX(fd.args[0])->get());
	mpc_sub_ui(COMPLEX(fd.args[0])->get(), COMPLEX(fd.args[0])->get(), 1, MPC_RNDND);
	return res;
}

var_base_t *complex_usub(vm_state_t &vm, const fn_data_t &fd)
{
	var_complex_t *res = make<var_complex_t>(COMPLEX(fd.args[0])->get());
	mpc_neg(res->get(), COMPLEX(fd.args[0])->get(), MPC_RNDND);
	return res;
}

var_base_t *complex_pow(vm_state_t &vm, const fn_data_t &fd)
{
	if(!fd.args[1]->istype<var_int_t>() && !fd.args[1]->istype<var_flt_t>()) {
		vm.fail(fd.src_id, fd.idx, "power must be an 'int' or 'flt', found: %s",
			vm.type_name(fd.args[1]).c_str());
		return nullptr;
	}
	var_complex_t *res = make<var_complex_t>(COMPLEX(fd.args[0])->get());
	if(fd.args[1]->istype<var_int_t>())
		mpc_pow_z(res->get(), COMPLEX(fd.args[0])->get(), INT(fd.args[1])->get(),
			  MPC_RNDND);
	else if(fd.args[1]->istype<var_flt_t>())
		mpc_pow_fr(res->get(), COMPLEX(fd.args[0])->get(), FLT(fd.args[1])->get(),
			   MPC_RNDND);
	return res;
}

var_base_t *complex_abs(vm_state_t &vm, const fn_data_t &fd)
{
	var_flt_t *res = make<var_flt_t>(0.0);
	mpc_abs(res->get(), COMPLEX(fd.args[0])->get(), mpfr_get_default_rounding_mode());
	return res;
}

INIT_MODULE(complex)
{
	var_src_t *src = vm.current_source();

	src->add_native_fn("new_native", complex_new_native, 2);

	// register the complex type (register_type)
	vm.register_type<var_complex_t>("complex", src_id, idx);

	vm.add_native_typefn<var_complex_t>("+", complex_add, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("-", complex_sub, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("*", complex_mul, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("/", complex_div, 1, src_id, idx);

	vm.add_native_typefn<var_complex_t>("+=", complex_addassn, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("-=", complex_subassn, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("*=", complex_mulassn, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("/=", complex_divassn, 1, src_id, idx);

	vm.add_native_typefn<var_complex_t>("==", complex_eq, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("!=", complex_ne, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("<", complex_lt, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>("<=", complex_le, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>(">", complex_gt, 1, src_id, idx);
	vm.add_native_typefn<var_complex_t>(">=", complex_ge, 1, src_id, idx);

	vm.add_native_typefn<var_complex_t>("++x", complex_preinc, 0, src_id, idx);
	vm.add_native_typefn<var_complex_t>("x++", complex_postinc, 0, src_id, idx);
	vm.add_native_typefn<var_complex_t>("--x", complex_predec, 0, src_id, idx);
	vm.add_native_typefn<var_complex_t>("x--", complex_postdec, 0, src_id, idx);

	vm.add_native_typefn<var_complex_t>("u-", complex_usub, 0, src_id, idx);

	vm.add_native_typefn<var_complex_t>("**", complex_pow, 1, src_id, idx);

	vm.add_native_typefn<var_complex_t>("abs", complex_abs, 0, src_id, idx);

	return true;
}

#endif // LIBRARY_CORE_FLT_HPP
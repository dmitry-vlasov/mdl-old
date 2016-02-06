/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unit_DIR.hpp                    */
/* Description:     pair of iterators for the directed unification algorithm */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/mdl_expression_iterator.hpp"

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class T_1, class T_2, int P, int K>
class Unit : public
	iterator :: modifier :: Pair
	<
		Substirator<T_1, T_2, P>,
		Substirator<T_2, T_1, P>
	> {
public :
	typedef T_1 Term_1_;
	typedef T_2 Term_2_;
	enum {
		policy_ = P
	};
	enum {
		kind_ = K
	};
	typedef
		typename Term_1_ :: const_Iterator_
		Iterator_1_;
	typedef
		typename Term_2_ :: const_Iterator_
		Iterator_2_;
	typedef
		Substirator<Term_1_, Term_2_, policy_>
		Substirator_1_;
	typedef
		Substirator<Term_2_, Term_1_, policy_>
		Substirator_2_;
	typedef
		typename iterator :: modifier :: Pair<Substirator_1_, Substirator_2_>
		Pair_;
	typedef
		typename Substirator_1_ :: Substitution_
		Substitution_1_;
	typedef
		typename Substirator_2_ :: Substitution_
		Substitution_2_;

	typedef Unit Unit_;
	typedef
		Unit<Term_2_, Term_1_, policy_, kind_>
		InverseUnit_;

	enum Replaceable_ {
		NONE    = 0,
		DIRECT  = 1,
		INVERSE = 2,
		BOTH    = 3
	};

	Unit
	(
		const Iterator_1_,
		const Iterator_2_,
		const Substitution_1_* const = NULL,
		const Substitution_2_* const = NULL,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	);
	Unit
	(
		const Substirator_1_,
		const Substirator_2_,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	);
	Unit (const Unit&);
	Unit ();

	InverseUnit_ inverse() const;

	Iterator_2_ follow (bool&) const;

	bool isReacheable() const;
	bool isReplaceable() const;
	bool isFixed() const;
	Replaceable_ getReplaceability() const;

	template<class A>
	void cloneSubstitution();

	bool newSubstitution (const Term_2_* const);

	void operator = (const Unit_);

	Substirator_1_ getSource() const;
	Substirator_2_ getTarget() const;

	Substirator_1_& source();
	Substirator_2_& target();

	void show (String&) const;
	void dump() const;
	void verifyIntegrity() const;

private :
	typedef
		List<allocator :: Stack>
		_List;
	typedef
		Substitution<typename _List :: Term_>
		_Substitution;

	bool checkResult
	(
		_List*&, _List*&,
		const _Substitution*&,
		const _Substitution*&
	) const;
	void verificationFail
	(
		const _List*, const _List*,
		const _Substitution*,
		const _Substitution*
	) const;
	template<class T, class S>
	void show
	(
		String&,
		const T*,
		const S*,
		const char*
	) const;

	bool checkTermTypes (const Term_2_* const) const;

	index :: Step level_1_;
	index :: Step level_2_;
};

	template<class T_1, class T_2, int P, int K>
	String&
	operator << (String&, const Unit<T_1, T_2, P, K>&);
}
}
}
}



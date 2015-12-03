/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unit_SYM.hpp                    */
/* Description:     pair of iterators for the symmetric unification algorithm*/
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_UNIT_SYM_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_UNIT_SYM_HPP_

#include "mdl/expression/iterator/mdl_expression_iterator.hpp"

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class T_1, class T_2, int K>
class Unit<T_1, T_2, policy :: SYMMETRIC, K> : public
	iterator :: modifier :: Pair
	<
		typename T_1 :: const_Iterator_,
		typename T_2 :: const_Iterator_
	> {
public :
	typedef T_1 Term_1_;
	typedef T_2 Term_2_;
	enum {
		policy_ = policy :: SYMMETRIC
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
		typename iterator :: modifier :: Pair<Iterator_1_, Iterator_2_>
		Pair_;
	typedef
		List<allocator :: Stack>
		List_;
	typedef
		typename List_ :: Term_ :: Substitution_
		Substitution_;
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
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP,
		const Substitution_* = NULL
	);
	Unit (const Unit&);
	Unit ();

	void operator ++ ();

	InverseUnit_ inverse() const;

	bool isReacheable() const;
	bool isReplaceable() const;
	bool isFixed() const;
	Replaceable_ getReplaceability() const;

	template<class A>
	void cloneSubstitution();

	const Substitution_* findSubstitution() const;
	bool newSubstitution (const Term_2_* const);
	template<class A>
	const typename List<A> :: Substitution_* getSubstitution() const;
	template<class A>
	const typename List<A> :: Substitution_* getSourceSubstitution() const;
	template<class A>
	const typename List<A> :: Substitution_* getTargetSubstitution() const;

	void operator = (const Unit_&);

	Iterator_1_ getSource() const;
	Iterator_2_ getTarget() const;

	Iterator_1_& source();
	Iterator_2_& target();

	void show (String&) const;
	void dump() const;
	void verifyIntegrity() const;

private :
	bool checkResult
	(
		List_*&, List_*&,
		const Substitution_*&
	) const;
	void showVerification
	(
		String&,
		const List_*, const List_*,
		const Substitution_*
	) const;
	void verificationFail
	(
		const List_*, const List_*,
		const Substitution_*
	) const;
	template<class T1, class T2>
	void show
	(
		String&,
		const T1*,
		const T2*,
		const Substitution_*,
		const char*
	) const;

	bool checkTermTypes (const Term_2_* const) const;
	bool checkTermVariables (const Term_2_* const) const;

	const Substitution_* substitution_;
	index :: Step level_1_;
	index :: Step level_2_;
};

	template<class T_1, class T_2, int K>
	String&
	operator << (String&, const Unit<T_1, T_2, policy :: SYMMETRIC, K>&);
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_UNIT_SYM_HPP_*/

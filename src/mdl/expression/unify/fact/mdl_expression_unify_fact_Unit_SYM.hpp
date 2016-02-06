/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Unit_SYM.hpp                   */
/* Description:     pair of iterators for the symmetric unification algorithm*/
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
namespace fact {

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
	typedef Unit Unit_;
	typedef
		Unit<Term_2_, Term_1_, policy_, kind_>
		InverseUnit_;

	Unit
	(
		const Iterator_1_,
		const Iterator_2_,
		value :: Integer& minDifference_1,
		value :: Integer& minDifference_2,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	);
	Unit
	(
		const Iterator_1_,
		const Iterator_2_,
		value :: Integer& minDifference_1,
		value :: Integer& minDifference_2,
		const index :: Step,
		const index :: Step,
		const value :: Integer,
		const value :: Integer
	);
	Unit (const Unit&);

	InverseUnit_ inverse() const;

	void updateMinDifference() const;
	value :: Integer getSourceDifference() const;
	value :: Integer getTargetDifference() const;

	/*static value :: Integer getMinSourceDifference();
	static value :: Integer getMinTargetDifference();
	static value :: Integer getMinDifference();*/

	bool isReacheable() const;
	bool isFixed() const;
	bool shift (const Term_1_* const, const Term_2_* const);

	Iterator_1_ getSource() const;
	Iterator_2_ getTarget() const;
	Iterator_1_& source();
	Iterator_2_& target();

	void show (String&) const;
	void show (std :: ostream&) const;
	void show() const;

private :
	template<class, class>
	friend class Result;
	template<class, class, int, int>
	friend class Unit;

	template<class T1, class T2>
	void show
	(
		String&,
		const T1*,
		const T2*,
		const char*
	) const;

	bool checkTermTypes
	(
		const Term_1_* const,
		const Term_2_* const
	) const;
	//static void swapMinDifference();

	const index :: Step level_1_;
	const index :: Step level_2_;

	value :: Integer difference_1_;
	value :: Integer difference_2_;

	value :: Integer& minDifference_1_;
	value :: Integer& minDifference_2_;
};

	template<class T_1, class T_2, int K>
	String&
	operator << (String&, const Unit<T_1, T_2, policy :: SYMMETRIC, K>&);
	template<class T_1, class T_2, int K>
	std :: ostream&
	operator << (std :: ostream&, const Unit<T_1, T_2, policy :: SYMMETRIC, K>&);
}
}
}
}



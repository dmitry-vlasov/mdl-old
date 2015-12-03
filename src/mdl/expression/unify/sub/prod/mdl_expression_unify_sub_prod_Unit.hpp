/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Unit.hpp                   */
/* Description:     unit testing template class for vector unifier           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_PROD_UNIT_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_PROD_UNIT_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

template<class E, class S, int P, int K>
class Unit {
public :
	typedef E Expression_;
	typedef S Substiunit_;
	enum { policy_ = P };
	enum { kind_ = K };
	typedef
		typename Expression_ :: Term_
		Term_;

	static bool admit
	(
		const Term_* const,
		const Term_* const
	);
	static const Substiunit_* check
	(
		const Term_* const,
		const Term_* const
	);

private :
	template<class, class, int, int>
	friend class Unit;

	static const Substiunit_* make
	(
		const Term_* const,
		const Term_* const
	);
};

template<class E, class S, int K>
class Unit<E, S, policy :: DIRECT, K> {
public :
	typedef E Expression_;
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef S Substiunit_;
	enum { policy_ = policy :: DIRECT };
	enum { kind_ = K };

	static bool admit
	(
		const Term_* const,
		const Term_* const
	);
	static const Substiunit_* check
	(
		const Term_* const,
		const Term_* const
	);

private :
	template<class, class, int, int>
	friend class Unit;

	static const Substiunit_* make
	(
		const Term_* const,
		const Term_* const
	);
};

template<class E, class S, int K>
class Unit<E, S, policy :: INVERSE, K> {
public :
	typedef E Expression_;
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef S Substiunit_;
	enum { policy_ = policy :: INVERSE };
	enum { kind_ = K };

	static bool admit
	(
		const Term_* const,
		const Term_* const
	);
	static const Substiunit_* check
	(
		const Term_* const,
		const Term_* const
	);

private :
	template<class, class, int, int>
	friend class Unit;

	static const Substiunit_* make
	(
		const Term_* const,
		const Term_* const
	);
};

}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_PROD_UNIT_HPP_*/

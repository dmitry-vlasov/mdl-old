/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Policy_DIR.hpp                  */
/* Description:     direct unification policy                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_POLICY_DIR_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_POLICY_DIR_HPP_

#include "mdl/expression/unify/mdl_expression_unify.dpp"

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class U>
class Policy<U, policy :: DIRECT, direction :: DIRECT> {
public :
	enum { policy_ = policy :: DIRECT };
	enum { direction_ = direction :: DIRECT };
	typedef U MainUnifier_;
	typedef U Unifier_;
	typedef
		typename Unifier_ :: Result_
		Result_;
	typedef
		typename Unifier_ :: Unit_
		Unit_;
	typedef
		typename Unit_ :: InverseUnit_
		InverseUnit_;
	typedef
		Unifier<InverseUnit_, typename Unifier_ :: Allocator_, policy_>
		InverseUnifier_;

	inline static Result_
	unifyNext (Unit_ unit) {
		return Unifier_ :: unifyNext (unit);
	}
	inline static Result_
	unifyThis (Unit_ unit) {
		return Unifier_ :: tryUnit (unit);
	}
};

template<class U>
class Policy<U, policy :: DIRECT, direction :: INVERSE> {
public :
	enum { policy_ = policy :: DIRECT };
	enum { direction_ = direction :: INVERSE };
	typedef U MainUnifier_;
	typedef U InverseUnifier_;
	typedef
		typename InverseUnifier_ :: Result_
		Result_;
	typedef
		typename InverseUnifier_ :: Unit_
		InverseUnit_;
	typedef
		typename InverseUnit_ :: InverseUnit_
		Unit_;
	typedef
		Unifier<InverseUnit_, typename InverseUnifier_ :: Allocator_, policy_>
		Unifier_;

	inline static Result_
	unifyNext (Unit_) {
		return Result_();
	}
	inline static Result_
	unifyThis (Unit_) {
		return Result_();
	}
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_POLICY_DIR_HPP_*/

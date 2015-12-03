/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Replacer_SYM.hpp                */
/* Description:     symmetric unification variable substitution algorithm    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_REPLACER_SYM_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_REPLACER_SYM_HPP_

#include "mdl/expression/unify/exp/mdl_expression_unify_exp.dpp"

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class U, int D>
class Replacer<U, policy :: SYMMETRIC, D> {
public :
	enum { policy_ = policy :: SYMMETRIC };
	enum { direction_ = D };
	typedef
		Policy<U, policy_, direction_>
		Policy_;
	typedef
		typename Policy_ :: Result_
		Result_;
	typedef
		typename Policy_ :: Unit_
		Unit_;
	typedef
		typename Unit_ :: Substitution_
		Substitution_;
	typedef
		typename Unit_ :: Iterator_2_
		Target_;
	typedef
		typename Target_ :: Node_
		Node_;
	typedef
		typename Node_ :: Terms_
		Terms_;
	typedef
		typename Node_ :: Term_
		Term_;

	static Result_ tryReplace (Unit_);

private :
	static Result_ tryUsed (Unit_, const Substitution_*);
	static Result_ tryNew (Unit_);
	static Result_ tryTerm (Unit_, const Term_*);
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_REPLACER_SYM_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Replacer_DIR.hpp                */
/* Description:     directed unification variable substitution algorithm     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/unify/exp/mdl_expression_unify_exp.dpp"

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class U, int P, int D>
class Replacer {
public :
	enum { policy_ = P };
	enum { direction_ = D };
	typedef
		Policy<U, policy_, direction_>
		Policy_;
	typedef
		typename Policy_ :: Unifier_
		Unifier_;
	typedef
		typename Policy_ :: Result_
		Result_;
	typedef
		typename Policy_ :: Unit_
		Unit_;
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
	static Result_ tryUsed (Unit_, Target_);
	static Result_ tryNew (Unit_, Target_);
	static Result_ tryTerm (Unit_, const Term_*);
};

}
}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Replacer_SYM.hpp               */
/* Description:     symmetric unification variable substitution algorithm    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/unify/fact/mdl_expression_unify_fact.dpp"

namespace mdl {
namespace expression {
namespace unify {
namespace fact {

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
		typename Unit_ :: Iterator_1_
		Source_;
	typedef
		typename Source_ :: Node_
		SourceNode_;
	typedef
		typename SourceNode_ :: Terms_
		SourceTerms_;
	typedef
		typename SourceNode_ :: Term_
		SourceTerm_;

	typedef
		typename Unit_ :: Iterator_2_
		Target_;
	typedef
		typename Target_ :: Node_
		TargetNode_;
	typedef
		typename TargetNode_ :: Terms_
		TargetTerms_;
	typedef
		typename TargetNode_ :: Term_
		TargetTerm_;

	static Result_ tryReplace (Unit_);

private :
	static Result_ tryTerm (Unit_, const SourceTerm_*, const TargetTerm_*);
};

}
}
}
}



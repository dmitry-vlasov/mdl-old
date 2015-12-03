/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Result.hpp                      */
/* Description:     unification result class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_RESULT_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_RESULT_HPP_

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class U, class A>
class Result : public list :: List<U, storage :: ByValue, A> {
public :
	typedef U Unit_;
	typedef A Allocator_;
	typedef
		typename list :: List
		<
			Unit_,
			storage :: ByValue,
			Allocator_
		>
		List_;
	typedef
		typename List_ :: Node_
		Node_;

	Result ();
	Result (const Result&);
	Result (Unit_);

	void show (String&) const;
	void dump () const;

	#ifdef DEBUG
	bool correct_;
	#endif
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_RESULT_HPP_*/

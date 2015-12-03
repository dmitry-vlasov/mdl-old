/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unify.hpp                       */
/* Description:     wrapper for the Unifier class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_UNIFY_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_UNIFY_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template
<
	class T_1,
	class T_2,
	int P = policy :: DIRECT,
	int T = kind :: COMMON,
	class A = allocator :: Heap
>
class Unify : public Unifier<Unit<T_1, T_2, P, T>, A, P> {
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_UNIFY_HPP_*/

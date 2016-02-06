/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Unify.hpp                      */
/* Description:     wrapper for the Unifier class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace unify {
namespace fact {

template
<
	class T_1,
	class T_2,
	int P = policy :: SYMMETRIC,
	int T = kind :: COMMON,
	class A = allocator :: Heap
>
class Unify : public Unifier<Unit<T_1, T_2, P, T>, A, P> {
};

}
}
}
}



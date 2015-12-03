/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Simify.hpp                         */
/* Description:     wrapper for Simifier class. Static class                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SIMIFY_SIMIFY_HPP_
#define MDL_EXPRESSION_SIMIFY_SIMIFY_HPP_

namespace mdl {
namespace expression {
namespace simify {

template
<
	class T_1,
	class T_2,
	class A = allocator :: Heap
>
class Simify : public Simifier<Unit<T_1, T_2>, A> {
};

}
}
}

#endif /*MDL_EXPRESSION_SIMIFY_SIMIFY_HPP_*/

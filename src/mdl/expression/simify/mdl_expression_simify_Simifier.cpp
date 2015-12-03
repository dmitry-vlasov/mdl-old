/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Simifier.cpp                       */
/* Description:     main simification algorithm. Static class                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SIMIFY_SIMIFIER_CPP_
#define MDL_EXPRESSION_SIMIFY_SIMIFIER_CPP_

namespace mdl {
namespace expression {
namespace simify {

	/****************************
	 *		Private members
	 ****************************/

	template<class U, class A>
	typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: simifyNode (Unit_ unit)
	{
		Similarity_ result;
		while (unit != NULL) {
			if (unit.isReacheable()) {
				result += DirectSimifier_ :: tryReplaceable (unit);
				result += InverseSimifier_ :: tryReplaceable (unit.inverse()).inverse();
				result += tryFixed (unit);
			}
			+ unit;
		}
		return result;
	}
}
}
}

#endif /*MDL_EXPRESSION_SIMIFY_SIMIFIER_CPP_*/

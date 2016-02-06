/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Result.ipp                     */
/* Description:     unification result class                                 */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class A>
	inline
	Result<U, A> :: Result () :
	List_() {
	}
	template<class U, class A>
	inline
	Result<U, A> :: Result (const Result& result) :
	List_(result) {
	}
	template<class U, class A>
	inline
	Result<U, A> :: Result (const Unit_ unit) :
	List_()
	{
		List_ :: addLast (unit);
		unit.updateMinDifference();
	}

using manipulator :: endLine;

	template<class U, class A>
	void
	Result<U, A> :: show (String& string) const
	{
		const Node_* node = List_ :: getFirst();
		while (node != NULL) {
			Unit_& unit = node->getReference();
			string << unit << endLine;
			node = node->getNext();
		}
	}
	template<class U, class A>
	void
	Result<U, A> :: show (std :: ostream& os) const
	{
		value :: Integer counter = 0;
		const Node_* node = List_ :: getFirst();
		while (node != NULL) {
			const Unit_& unit = node->getReference();
			os << "unit " << ++ counter << ":" << std :: endl;
			os << unit << std :: endl;
			node = node->getNext();
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class U, class A>
	inline std :: ostream&
	operator << (std :: ostream& os, const Result<U, A> result) {
		result.show (os);
		return os;
	}
}
}
}
}



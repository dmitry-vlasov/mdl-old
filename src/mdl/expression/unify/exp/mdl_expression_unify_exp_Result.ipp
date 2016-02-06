/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Result.ipp                      */
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
namespace exp {

	/****************************
	 *		Public members
	 ****************************/

#ifndef DEBUG
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
	Result<U, A> :: Result (Unit_ unit) :
	List_() {
		List_ :: addLast (unit);
	}

using manipulator :: endLine;

	template<class U, class A>
	void
	Result<U, A> :: show (String& string) const
	{
		int counter = 0;
		string << "unification result:" << endLine;
		string << "-------------------" << endLine;
		const Node_* node = List_ :: getFirst();
		while (node != NULL) {
			Unit_ unit = node->getValue();
			string << "item " << (counter ++) << " = " << endLine;
			unit.show (string);
			string << endLine;
			node = node->getNext();
		}
		string << endLine;
	}

	template<class U, class A>
	void
	Result<U, A> :: dump() const
	{
		String string (1024);
		show (string);
		std :: cout << string << std :: flush;
	}

#endif /*RELEASE*/

#ifdef DEBUG
	template<class U, class A>
	inline
	Result<U, A> :: Result () :
	List_(),
	correct_ (true) {
	}
	template<class U, class A>
	inline
	Result<U, A> :: Result (const Result& result) :
	List_(result),
	correct_ (result.correct_) {
	}
	template<class U, class A>
	inline
	Result<U, A> :: Result (const Unit_ unit) :
	List_(),
	correct_ (true) {
		try {
			unit.verifyIntegrity();
		} catch (Error* error) {
			correct_ = false;
			//std :: cout << error->message() << std :: endl;
			throw error;
		}
		List_ :: addLast (unit);
	}
#endif /*DEBUG*/

}
}
}
}



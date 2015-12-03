/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_Linear.ipp                     */
/* Description:     node container for terms: linear node                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_TERMS_LINEAR_IPP_
#define MDL_EXPRESSION_NODE_TERMS_LINEAR_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace terms {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	inline
	Linear<T, A> :: Linear() :
	initial_ (),
	terminal_ () {
	}
	template<class T, class A>
	inline
	Linear<T, A> :: ~ Linear() {
	}

	template<class T, class A>
	template<class P>
	inline void
	Linear<T, A> :: cloneContents (P* pool) const
	{
		initial_.cloneContents (pool);
		terminal_.cloneContents (pool);
	}

	template<class T, class A>
	inline bool
	Linear<T, A> :: isEmpty() const
	{
		bool result = true;
		result = result && initial_.isEmpty();
		result = result && terminal_.isEmpty();
		return result;
	}

	template<class T, class A>
	inline typename Linear<T, A> :: Initial_&
	Linear<T, A> :: initial() {
		return initial_;
	}
	template<class T, class A>
	inline typename Linear<T, A> :: Terminal_&
	Linear<T, A> :: terminal() {
		return terminal_;
	}
	template<class T, class A>
	inline const typename Linear<T, A> :: Initial_&
	Linear<T, A> :: getInitial() const {
		return initial_;
	}
	template<class T, class A>
	inline const typename Linear<T, A> :: Terminal_&
	Linear<T, A> :: getTerminal() const {
		return terminal_;
	}

	template<class T, class A>
	inline void
	Linear<T, A> :: operator = (const Linear& linear)
	{
		initial_ = linear.initial_;
		terminal_ = linear.terminal_;
	}

	template<class T, class A>
	template<class T1, class A1>
	inline bool
	Linear<T, A> :: coinside
	(
		const Branching<T1, A1>& branching,
		const Term_* term0,
		const T1* term1
	) const
	{
		bool result = true;
		result = result &&
			(
				initial_.template subset<T1, A1> (branching.getInitial(), term0, term1)
			);
		result = result &&
			(
				terminal_.template subset<T1, A1> (branching.getTerminal(), term0, term1)
			);
		return result;
	}
	template<class T, class A>
	template<class T1, class A1>
	inline bool
	Linear<T, A> :: coinside
	(
		const Linear<T1, A1>& linear,
		const Term_* term0,
		const T1* term1
	) const
	{
		bool result = true;
		result = result &&
			(
				initial_.coinside (linear.getInitial(), term0, term1)
			);
		result = result &&
			(
				terminal_.coinside (linear.getTerminal(), term0, term1)
			);
		return result;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class T, class A>
	void
	Linear<T, A> :: showAll (String& string) const
	{
		string << tab << "initial:" << endLine;
		initial_.showAll (string);
		string << endLine;
		string << tab << "terminal:" << endLine;
		terminal_.showAll (string);
	}
	template<class T, class A>
	void
	Linear<T, A> :: showTypes (String& string, bool initial) const
	{
		if (initial) {
			initial_.showTypes (string);
		} else {
			terminal_.showTypes (string);
		}
	}

	// object :: Object implementation
	template<class T, class A>
	inline void
	Linear<T, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class A>
	inline Size_t
	Linear<T, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += initial_.getVolume();
		volume += terminal_.getVolume();
		return volume;
	}
	template<class T, class A>
	inline Size_t
	Linear<T, A> :: getSizeOf() const {
		return sizeof (Linear);
	}
	template<class T, class A>
	void
	Linear<T, A> :: show (String& string) const
	{
		if (!initial_.isEmpty()) {
			string << tab << "initial:" << endLine;
			if (initial_.isEmpty()) {
				string << tab << "empty";
			} else {
				initial_.show (string);
			}
			string << endLine;
		}
		if (!terminal_.isEmpty()) {
			string << tab << "terminal:" << endLine;
			if (terminal_.isEmpty()) {
				string << tab << "empty";
			} else {
				terminal_.show (string);
			}
		}
	}
	template<class T, class A>
	void
	Linear<T, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template<class T, class A>
	String&
	operator << (String& string, const Linear<T, A>& linear)
	{
		linear.show (string);
		string << endLine;
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_TERMS_LINEAR_IPP_*/

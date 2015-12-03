/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_Branching.ipp                  */
/* Description:     node container for terms: branching node                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_TERMS_BRANCHING_IPP_
#define MDL_EXPRESSION_NODE_TERMS_BRANCHING_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace terms {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	inline
	Branching<T, A> :: Branching() :
	initial_ (),
	terminal_ () {
	}
	template<class T, class A>
	inline
	Branching<T, A> :: ~ Branching() {
	}

	template<class T, class A>
	template<class P>
	inline void
	Branching<T, A> :: cloneContents (P* pool) const
	{
		initial_.cloneContents (pool);
		terminal_.cloneContents (pool);
	}

	template<class T, class A>
	inline bool
	Branching<T, A> :: isEmpty() const
	{
		bool result = true;
		result = result && initial_.isEmpty();
		result = result && terminal_.isEmpty();
		return result;
	}

	template<class T, class A>
	inline typename Branching<T, A> :: Initial_&
	Branching<T, A> :: initial() {
		return initial_;
	}
	template<class T, class A>
	inline typename Branching<T, A> :: Terminal_&
	Branching<T, A> :: terminal() {
		return terminal_;
	}
	template<class T, class A>
	inline const typename Branching<T, A> :: Initial_&
	Branching<T, A> :: getInitial() const {
		return initial_;
	}
	template<class T, class A>
	inline const typename Branching<T, A> :: Terminal_&
	Branching<T, A> :: getTerminal() const {
		return terminal_;
	}

	template<class T, class A>
	inline void
	Branching<T, A> :: operator = (const Branching& branching)
	{
		initial_ = branching.initial_;
		terminal_ = branching.terminal_;
	}

	template<class T, class A>
	template<class T1, class A1>
	bool
	Branching<T, A> :: coinside
	(
		const Branching<T1, A1>& branching,
		const Term_* term0,
		const T1* term1
	) const
	{
		bool result = true;
		result = result &&
			(
				initial_.coinside (branching.getInitial(), term0, term1)
			);
		result = result &&
			(
				terminal_.coinside (branching.getTerminal(), term0, term1)
			);
		return result;
	}
	template<class T, class A>
	template<class T1, class A1>
	inline bool
	Branching<T, A> :: coinside
	(
		const Linear<T1, A1>& linear,
		const Term_* term0,
		const T1* term1
	) const
	{
		bool result = true;
		result = result &&
			(
				linear.getInitial().template
					subset<Term_, Allocator_> (initial_, term1, term0)
			);
		result = result &&
			(
				linear.getTerminal().template
					subset<Term_, Allocator_> (terminal_, term1, term0)
			);
		return result;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class T, class A>
	void
	Branching<T, A> :: showAll (String& string) const
	{
		string << tab << "initial:" << endLine;
		initial_.showAll (string);
		string << endLine;
		string << tab << "terminal:" << endLine;
		terminal_.showAll (string);
	}
	template<class T, class A>
	void
	Branching<T, A> :: showTypes (String& string, bool initial) const
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
	Branching<T, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class A>
	inline Size_t
	Branching<T, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += initial_.getVolume();
		volume += terminal_.getVolume();
		return volume;
	}
	template<class T, class A>
	inline Size_t
	Branching<T, A> :: getSizeOf() const {
		return sizeof (Branching);
	}
	template<class T, class A>
	void
	Branching<T, A> :: show (String& string) const
	{
		if (!initial_.isEmpty()) {
			string << tab << "initial:" << endLine;
			initial_.show (string);
			string << endLine;
		}
		if (!terminal_.isEmpty()) {
			string << tab << "terminal:" << endLine;
			terminal_.show (string);
		}
	}
	template<class T, class A>
	void
	Branching<T, A> :: dump() const
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
	operator << (String& string, const Branching<T, A>& branching)
	{
		branching.show (string);
		string << endLine;
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_TERMS_BRANCHING_IPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Trace.ipp               */
/* Description:     modifier for traceable iterator                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_TRACE_IPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_TRACE_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I>
	inline
	Trace<I> :: Trace () :
	Iterator_ (),
	back_ () {
	}
	template<class I>
	inline
	Trace<I> :: Trace (const Iterator_& iterator) :
	Iterator_ (iterator),
	back_ (iterator) {
	}
	template<class I>
	inline
	Trace<I> :: Trace (const Trace& trace) :
	Iterator_ (trace),
	back_ (trace.back_) {
	}

	template<class I>
	inline bool
	Trace<I> :: operator == (const Node_* node) const {
		return Iterator_ :: operator == (node);
	}
	template<class I>
	bool
	Trace<I> :: operator != (const Node_* node) const {
		return Iterator_ :: operator != (node);
	}
	template<class I>
	void
	Trace<I> :: operator = (const Node_* node) {
		Iterator_ :: operator = (node);
	}

	template<class I>
	inline void
	Trace<I> :: operator = (const Trace& trace) {
		Iterator_ :: operator = (trace);
		back_ = trace.back_;
	}
	template<class I>
	inline bool
	Trace<I> :: operator == (const Trace& trace) const {
		return
			(Iterator_ :: operator == (trace)) &&
			(back_ == trace.back_);
	}
	template<class I>
	inline bool
	Trace<I> :: operator != (const Trace& trace) const {
		return !(operator == (trace));
	}

	template<class I>
	inline void
	Trace<I> :: operator ++ () {
		back_ = *this;
		Iterator_ :: operator ++ ();
	}
	template<class I>
	inline void
	Trace<I> :: operator -- () {
		back_ = *this;
		Iterator_ :: operator -- ();
	}
	template<class I>
	inline void
	Trace<I> :: operator + () {
		back_ = *this;
		Iterator_ :: operator + ();
	}
	template<class I>
	inline void
	Trace<I> :: operator - () {
		back_ = *this;
		Iterator_ :: operator - ();
	}

	template<class I>
	inline void
	Trace<I> :: shiftBack() {
		*this = back_;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_TRACE_IPP_*/

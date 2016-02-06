/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Memory.ipp              */
/* Description:     memory modifier for recallable iterator                  */
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
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I>
	inline
	Memory<I> :: Memory () :
	Iterator_(),
	back_ () {
	}
	template<class I>
	inline
	Memory<I> :: Memory (const Iterator_& iterator) :
	Iterator_(iterator),
	back_ (iterator) {
	}
	template<class I>
	inline
	Memory<I> :: Memory (const Memory& memory) :
	Iterator_(memory),
	back_ (memory.back_) {
	}

	template<class I>
	inline bool
	Memory<I> :: operator == (const Node_* node) const {
		return Iterator_ :: operator == (node);
	}
	template<class I>
	bool
	Memory<I> :: operator != (const Node_* node) const {
		return Iterator_ :: operator != (node);
	}
	template<class I>
	void
	Memory<I> :: operator = (const Node_* node) {
		Iterator_ :: operator = (node);
	}

	template<class I>
	inline void
	Memory<I> :: operator = (const Memory& memory) {
		Iterator_:: operator = (memory);
		back_ = memory.back_;
	}
	template<class I>
	inline bool
	Memory<I> :: operator == (const Memory& memory) const {
		return (Iterator_:: operator == (memory)) && (back_ == memory.back_);
	}
	template<class I>
	inline bool
	Memory<I> :: operator != (const Memory& memory) const {
		return !(operator == (memory));
	}

	template<class I>
	inline void
	Memory<I> :: remember() {
		back_ = *this;
	}
	template<class I>
	inline void
	Memory<I> :: recall() {
		*this = back_;
	}
}
}
}
}



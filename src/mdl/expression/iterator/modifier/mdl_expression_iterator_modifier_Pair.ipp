/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Pair.ipp                */
/* Description:     modifier for iterator decart product                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_PAIR_IPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_PAIR_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I_1, class I_2>
	inline
	Pair<I_1, I_2> :: Pair () :
	iterator_1_ (),
	iterator_2_ () {
	}
	template<class I_1, class I_2>
	inline
	Pair<I_1, I_2> :: Pair
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2
	) :
	iterator_1_ (iterator_1),
	iterator_2_ (iterator_2) {
	}
	template<class I_1, class I_2>
	inline
	Pair<I_1, I_2> :: Pair (const Pair& pair) :
	iterator_1_ (pair.iterator_1_),
	iterator_2_ (pair.iterator_2_) {
	}

	template<class I_1, class I_2>
	inline typename Pair<I_1, I_2> :: InversePair_
	Pair<I_1, I_2> :: inverse() const {
		return InversePair_ (iterator_2_, iterator_1_);
	}

	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: operator == (const Node_1_* const pointer) const {
		return (iterator_1_ == pointer);
	}
	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: operator != (const Node_1_* const pointer) const {
		return !(operator == (pointer));
	}
	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: operator == (const Pair& pair) const {
		return
			(iterator_1_ == pair.iterator_1_) &&
			(iterator_2_ == pair.iterator_2_);
	}
	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: operator != (const Pair& pair) const {
		return !(operator == (pair));
	}
	template<class I_1, class I_2>
	inline void
	Pair<I_1, I_2> :: operator = (const Pair& pair) {
		iterator_1_ = pair.iterator_1_;
		iterator_2_ = pair.iterator_2_;
	}

	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: isFinal() const {
		return
			iterator_1_.template isTerminal<direction :: RIGHT>() &&
			iterator_2_.template isTerminal<direction :: RIGHT>();
	}
	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: isTerminal() const {
		return
			iterator_1_.template isTerminal<direction :: RIGHT>() ||
			iterator_2_.template isTerminal<direction :: RIGHT>();
	}
	template<class I_1, class I_2>
	inline bool
	Pair<I_1, I_2> :: isEqual() const
	{
		const Symbol& symbol_1 = *iterator_1_;
		const Symbol& symbol_2 = *iterator_2_;
		return (symbol_1 == symbol_2);
	}


	template<class I_1, class I_2>
	inline void
	Pair<I_1, I_2> :: operator ++ ()
	{
		++ iterator_1_;
		++ iterator_2_;

		if (iterator_1_ != NULL) {
			iterator_1_.remember();
		}
		if (iterator_2_ != NULL) {
			iterator_2_.remember();
		}
	}
	template<class I_1, class I_2>
	inline void
	Pair<I_1, I_2> :: operator -- ()
	{
		-- iterator_1_;
		-- iterator_2_;

		if (iterator_1_ != NULL) {
			iterator_1_.remember();
		}
		if (iterator_2_ != NULL) {
			iterator_2_.remember();
		}
	}

	template<class I_1, class I_2>
	inline void
	Pair<I_1, I_2> :: operator + ()
	{
		if (iterator_2_.template isTerminal<direction :: UP>()) {
			+ iterator_1_;
			if (iterator_1_ != NULL) {
				iterator_2_.recall();
			}
		} else {
			+ iterator_2_;
		}
	}
	template<class I_1, class I_2>
	inline void
	Pair<I_1, I_2> :: operator - ()
	{
		if (iterator_2_.template isTerminal<direction :: DOWN>()) {
			- iterator_1_;
			if (iterator_1_ != NULL) {
				iterator_2_.recall();
			}
		} else {
			- iterator_2_;
		}
	}

	template<class I_1, class I_2>
	inline void
	Pair<I_1, I_2> :: recall()
	{
		iterator_1_.recall();
		iterator_2_.recall();
	}

	template<class I_1, class I_2>
	inline typename Pair<I_1, I_2> :: Iterator_1_
	Pair<I_1, I_2> :: getFirst() const {
		return iterator_1_;
	}
	template<class I_1, class I_2>
	inline typename Pair<I_1, I_2> :: Iterator_2_
	Pair<I_1, I_2> :: getSecond() const {
		return iterator_2_;
	}

	template<class I_1, class I_2>
	inline typename Pair<I_1, I_2> :: Iterator_1_&
	Pair<I_1, I_2> :: first() {
		return iterator_1_;
	}
	template<class I_1, class I_2>
	inline typename Pair<I_1, I_2> :: Iterator_2_&
	Pair<I_1, I_2> :: second() {
		return iterator_2_;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_PAIR_IPP_*/

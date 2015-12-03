/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Array.ipp               */
/* Description:     modifier for iterator decart product                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_ARRAY_IPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_ARRAY_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I, class A>
	inline
	Array<I, A> :: Array (const index :: Arity dimension) :
	dimension_ (dimension),
	array_ (dimension_) {
	}
	template<class I, class A>
	inline
	Array<I, A> :: Array
	(
		const index :: Arity dimension, const Iterator_ array[]
	) :
	dimension_ (dimension),
	array_ (dimension, array)
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			array_[i].remember();
		}
	}
	template<class I, class A>
	inline
	Array<I, A> :: Array (const Array& a) :
	dimension_ (a.dimension_),
	array_ (a.array_)
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			array_[i].remember();
		}
	}

	template<class I, class A>
	index :: Arity
	Array<I, A> :: getDimension() const {
		return dimension_;
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: skip (const index :: Arity i) const {
		return array_[i]->isLambda();
	}

	template<class I, class A>
	inline bool
	Array<I, A> :: operator == (const Array& a) const
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			if (array_[i] != a.array_ [i]) {
				return false;
			}
		}
		return true;
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: operator != (const Array& pair) const {
		return !(operator == (pair));
	}
	template<class I, class A>
	inline void
	Array<I, A> :: operator = (const Array& a)
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			array_.getReference (i) = a.array_ [i];
		}
	}

	template<class I, class A>
	inline bool
	Array<I, A> :: isNull() const
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			if (!array_[i].isNull()) {
				return false;
			}
		}
		return true;
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: isLambda() const
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			if (!array_[i]->isLambda()) {
				return false;
			}
		}
		return true;
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: isFinal() const
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			if (skip (i)) {
				continue;
			}
			if (!array_[i].template isTerminal<direction :: RIGHT>()) {
				return false;
			}
		}
		return true;
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: isTerminal() const
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			if (skip (i)) {
				continue;
			}
			if (array_[i].template isTerminal<direction :: RIGHT>()) {
				return true;
			}
		}
		return false;
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: isReplaceable (const index :: Arity i) const {
		return array_[i]->isReplaceable();
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: isFixed (const index :: Arity i) const {
		return array_[i]->isFixed();
	}
	template<class I, class A>
	inline bool
	Array<I, A> :: isEqual() const
	{
		for (index :: Arity i = 1; i < dimension_; ++ i) {
			if (*array_[0] != *array_ [i]) {
				return false;
			}
		}
		return true;
	}

	template<class I, class A>
	inline void
	Array<I, A> :: operator ++ ()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			++ array_[i];
			if (!array_[i].isNull()) {
				array_ [i].remember();
			}
		}
	}
	template<class I, class A>
	inline void
	Array<I, A> :: operator -- ()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			-- array_[i];
			if (!array_[i].isNull()) {
				array_ [i].remember();
			}
		}
	}

	template<class I, class A>
	inline void
	Array<I, A> :: operator + () {
		increment();
	}
	template<class I, class A>
	inline void
	Array<I, A> :: operator - () {
		decrement();
	}

	template<class I, class A>
	inline void
	Array<I, A> :: recall()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			array_[i].recall();
		}
	}

	template<class I, class A>
	inline typename Array<I, A> :: Iterator_
	Array<I, A> :: getIterator (const index :: Arity i) const {
		return array_ [i];
	}
	template<class I, class A>
	inline typename Array<I, A> :: Iterator_&
	Array<I, A> :: iterator (const index :: Arity i) {
		return array_.getReference (i);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class I, class A>
	void
	Array<I, A> :: increment (const index :: Arity i)
	{
		if (i == dimension_) {
			setNull();
			return;
		}
		if (!array_[i].template isTerminal<direction :: UP>()) {
			+ array_ [i];
		} else {
			array_ [i].recall();
			increment (i + 1);
		}
	}
	template<class I, class A>
	void
	Array<I, A> :: decrement (const index :: Arity i)
	{
		if (i == dimension_) {
			setNull();
			return;
		}
		if (!array_[i].template isTerminal<direction :: DOWN>()) {
			- array_ [i];
		} else {
			array_[i].recall();
			decrement (i + 1);
		}
	}
	template<class I, class A>
	void
	Array<I, A> :: setNull()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			array_[i].setNull();
		}
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_ARRAY_IPP_*/

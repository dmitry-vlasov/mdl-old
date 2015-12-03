/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Array.hpp               */
/* Description:     modifier for iterator decart product                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_ARRAY_HPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_ARRAY_HPP_

#include "mdl/expression/iterator/modifier/mdl_expression_iterator_modifier_Memory.hpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

template<class I, class A = allocator :: Stack>
class Array {
public :
	typedef I Iterator_;
	typedef A Allocator_;
	typedef
		typename Iterator_ :: Node_
		Node_;

	Array (const index :: Arity);
	Array (const index :: Arity, const Iterator_[]);
	Array (const Array&);

	index :: Arity getDimension() const;
	bool skip (const index :: Arity) const;

	bool operator == (const Array&) const;
	bool operator != (const Array&) const;
	void operator = (const Array&);

	bool isNull() const;
	bool isLambda() const;
	bool isFinal() const;
	bool isTerminal() const;
	bool isReplaceable (const index :: Arity) const;
	bool isFixed (const index :: Arity) const;
	bool isEqual() const;

	void operator ++ ();
	void operator -- ();

	void operator + ();
	void operator - ();

	void recall();

	Iterator_ getIterator (const index :: Arity) const;
	Iterator_& iterator (const index :: Arity);

protected :
	typedef
		Memory<Iterator_>
		_Iterator_;
	typedef
		array :: Array
		<
			_Iterator_,
			storage :: ByValue,
			Allocator_
		>
		Array_;
	const index :: Arity dimension_;
	Array_ array_;

private :
	void increment (const index :: Arity = 0);
	void decrement (const index :: Arity = 0);
	void setNull();
};

}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_ARRAY_HPP_*/

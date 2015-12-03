/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Array.ipp                                 */
/* Description:     array expression                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ARRAY_IPP_
#define MDL_EXPRESSION_ARRAY_IPP_

#include "mdl/auxiliary/mdl_auxiliary.hpp"

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Array<A> :: Array
	(
		const value :: Literal* literalArray,
		const index :: Literal size,
		const bool isReplaceable
	) :
	Expression_ (),
	array_ (size)
	{
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			array_[i].setLiteral (literalArray [i]);
			array_[i].setReplaceable (isReplaceable);
		}
	}
	template<class A>
	Array<A> :: Array
	(
		const vector :: value :: Literal& literalVector,
		const bool isReplaceable
	) :
	Expression_ (),
	array_ (literalVector.getSize())
	{
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			const value :: Literal
				literal = literalVector.getValue (i);
			array_[i].setLiteral (literal);
			array_[i].setReplaceable (isReplaceable);
		}
	}
	template<class A>
	Array<A> :: Array (const Array& array, const bool isReplaceable) :
	Expression_ (),
	array_ (array.getSize())
	{
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			array_[i] = array [i];
			array_[i].setReplaceable (isReplaceable);
		}
		Memory :: stack().push();
		Pool<>* pool = new Pool<>();
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			Node_* object = &const_cast<Array&>(array).array_[i];
			Node_* clone = &array_[i];
			pool->add (object, clone);
		}
		clone (pool);
		Memory :: stack().pop();
		#ifdef DEBUG
		Expression_ :: verifyIntegrity();
		#endif /*DEBUG*/
		//std :: cout << "******* term ******" << std :: endl;
		//std :: cout << *this << std :: endl;
		//std :: cout << getVolume() << std :: endl;
		//std :: cout << "sizeof (Term_) = " << sizeof (Term_) << std :: endl;
	}
	template<class A>
	template<class E>
	Array<A> :: Array (const E* const expression) :
	Expression_ (),
	array_ (expression->getLength())
	{
		typedef E Expression;
		typedef
			Builder
			<
				Array,
				typename Expression :: Term_
			>
			Builder;
		Builder builder (expression->getTerm());
		builder.build (this);
		#ifdef DEBUG
		Expression_ :: verifyIntegrity();
		#endif
	}
	template<class A>
	inline
	Array<A> :: ~ Array() {
	}

	template<class A>
	template<class T>
	const typename Array<A> :: Term_*
	Array<A> :: createTerm (const T* term)
	{
		typedef T Term;
		const index :: Literal
			size = term->getLength();
		Array array (size);
		return Builder<Array, Term> :: build (term, &array);
	}
	template<class A>
	template<class T>
	typename Array<A> :: Array*
	Array<A> :: createArray (const T* term)
	{
		typedef T Term;
		const index :: Literal
			size = term->getLength();
		Array* array = new Array (size);
		Builder<Array, Term> :: build (term, array);
		return array;
	}

	template<class A>
	inline const typename Array<A> :: Node_&
	Array<A> :: operator [] (const index :: Literal i) const {
		return array_[i];
	}
	template<class A>
	inline const Symbol&
	Array<A> :: getSymbol (const index :: Literal i) const {
		return array_[i];
	}
	template<class A>
	inline index :: Literal
	Array<A> :: getSize() const {
		return array_.getSize();
	}

	template<class A>
	bool
	Array<A> :: isEqual (const Array* expression) const
	{
		if (array_.getSize() != expression->getSize()) {
			return false;
		}
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			if (array_[i] != expression->getSymbol (i)) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	inline bool
	Array<A> :: operator == (const Array& expression) const {
		return isEqual (&expression);
	}
	template<class A>
	inline bool
	Array<A> :: operator != (const Array& expression) const {
		return !(operator == (expression));
	}
	template<class A>
	bool
	Array<A> :: isPrimitive() const
	{
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			const Term_* term = array_[i].getTerms().getInitial().getTerm();
			if ((term != NULL) && (term != getTerm()) && !(term->isVariable())) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	inline bool
	Array<A> :: isSingleton() const {
		return (array_.getSize() == 1);
	}
	template<class A>
	inline bool
	Array<A> :: isVariable() const {
		return isSingleton() && (array_ [0].isVariable());
	}
	template<class A>
	inline bool
	Array<A> :: isConstant() const {
		return isSingleton() && (array_ [0].isConstant());
	}
	template<class A>
	inline bool
	Array<A> :: isEmpty() const {
		return (array_.getSize() == 0);
	}
	template<class A>
	inline bool
	Array<A> :: isNull() const {
		return false;
	}

	template<class A>
	inline typename Array<A> :: const_Iterator_
	Array<A> :: getBegin() const {
		return const_Iterator_ (&array_.getFirstReference());
	}
	template<class A>
	inline typename Array<A> :: const_Iterator_
	Array<A> :: getEnd() const {
		return const_Iterator_ (&array_.getLastReference());
	}
	template<class A>
	inline typename Array<A> :: Iterator_
	Array<A> :: getBegin() {
		return Iterator_ (&array_.getFirstReference());
	}
	template<class A>
	inline typename Array<A> :: Iterator_
	Array<A> :: getEnd() {
		return Iterator_ (&array_.getLastReference());
	}
	template<class A>
	inline const typename Array<A> :: Term_*
	Array<A> :: getTerm() const {
		return array_[0].getTerms().getInitial().getTerm();
	}
	template<class A>
	inline typename Array<A> :: Term_*
	Array<A> :: getTerm() {
		return const_cast<Term_*>(array_[0].getTerms().getInitial().getTerm());
	}

using manipulator :: endLine;
using manipulator :: tab;

	template<class A>
	void
	Array<A> :: build (const object :: Typing* variables, const bool makeFixed)
	{
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			array_[i].build (variables, makeFixed);
		}
	}
	template<class A>
	void
	Array<A> :: parse (const mdl :: Type* type)
	{
		if (Config :: shallowParsing()) {
			return;
		}
		Memory :: stack().push();
		Parser parser (this);
		if (Config :: checkUnambiguity()) {
			parser.proceed (type, true, true);
		} else {
			if (!parser.proceed (type, false)) {
				parser.proceed (type, true);
			}
		}
		typedef
			pool :: Binary
			<
				const Term_, const Substitution_,
				allocator :: Heap,
				allocator :: Stack
			>
			Pool;
		clone (new Pool());
		//Expression_ :: verifyIntegrity();
		Memory :: stack().pop();
		#ifdef DEBUG
		Expression_ :: verifyIntegrity();
		#endif
	}
	template<class A>
	void
	Array<A> :: create (const mdl :: Rule* rule)
	{
		const Term_*
			term = Term_ :: template create<allocator :: Heap>
				(getBegin(), getEnd(), rule->getType(), rule);
		term->addSelf (true);
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			if (!array_[i].isConstant()) {
				const Term_*
					varTerm = Term_ :: template create<allocator :: Heap>
						(Iterator_ (&array_[i]));
				varTerm->addSelf (true);
			}
		}
		#ifdef DEBUG
		Expression_ :: verifyIntegrity();
		#endif
	}

using manipulator :: space;

	template<class A>
	void
	Array<A> :: write (String& string) const
	{
		if (getTerm() != NULL) {
			Expression_ :: write (string);
		} else {
			for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
				string << array_[i].getString() << space;
			}
		}
	}
	template<class A>
	void
	Array<A> :: write (String& string, const Indent indent) const
	{
		if (getTerm() != NULL) {
			Expression_ :: write (string, indent);
		} else {
			for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
				string << array_[i].getString() << space;
			}
		}
	}

	// object :: Object interface
	template<class A>
	void
	Array<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Array<A> :: getVolume() const
	{
		if (getTerm() == NULL) {
			return array_.getVolume();
		} else {
			Size_t volume = 0;
			volume += Expression_ :: getVolume();
			volume += sizeof (Node_);
			return volume;
		}
	}
	template<class A>
	Size_t
	Array<A> :: getSizeOf() const {
		return sizeof (Array);
	}
	template<class A>
	void
	Array<A> :: show (String& string) const
	{
		getVolume();
		if (getTerm() != NULL) {
			Expression_ :: show (string);
		} else {
			for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
				string << static_cast<const Symbol&>(array_[i]) << space;
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	inline
	Array<A> :: Array (const index :: Literal size) :
	Expression_ (),
	array_ (size) {
	}
	template<class A>
	template<class P>
	inline void
	Array<A> :: clone (P* pool)
	{
		#ifdef DEBUG
		Expression_ :: verifyIntegrity();
		#endif
		for (index :: Literal i = 0; i < array_.getSize(); ++ i) {
			array_[i].cloneContents (pool);
		}
		#ifdef DEBUG
		Expression_ :: verifyIntegrity();
		#endif
	}
}
}

#endif /*MDL_EXPRESSION_ARRAY_IPP_*/

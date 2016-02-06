/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Unit.ipp                   */
/* Description:     array of iterators for the unification algorithm         */
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
namespace sub {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class C, class A>
	inline
	Unit<C, A> :: Unit
	(
		const index :: Arity dimension,
		const Matrix_& matrix
	) :
	Array_ (dimension),
	substitution_ (NULL),
	data_ (NULL),
	matrix_ (matrix),
	index_ (0),
	prev_ (NULL)
	{
		const Vector_* const
			vector = matrix_.getValue (index_);
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			Cell_* const cell = vector->getValue (i);
			Array_ :: iterator (i) = cell->getBegin();
		}
	}
	template<class C, class A>
	inline
	Unit<C, A> :: Unit (const Unit& unit) :
	Array_ (unit),
	substitution_ (unit.substitution_),
	data_ (unit.data_),
	matrix_ (unit.matrix_),
	index_ (unit.index_),
	prev_ (unit.prev_) {
	}

using manipulator :: endLine;

	template<class C, class A>
	inline void
	Unit<C, A> :: operator + ()
	{
		Array_ :: operator + ();
		if (!Array_ :: isNull()) {
			intersectData (false);
		}
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: operator ++ ()
	{
		Array_ :: operator ++ ();
		if (!Array_ :: isNull()) {
			intersectData (true);
		}
	}
	template<class C, class A>
	inline value :: Integer
	Unit<C, A> :: getComplexity() const
	{
		value :: Integer complexity = 0;
		const Unit* unit = this;
		while (unit != NULL) {
			const value :: Integer
				unitLength = unit->getUnitLength (substitution_);
			complexity = (complexity < unitLength) ? unitLength : complexity;
			unit = unit->prev_;
		}
		return complexity;
	}

	template<class C, class A>
	inline value :: Integer
	Unit<C, A> :: getIndex() const {
		return index_;
	}
	template<class C, class A>
	inline const typename Unit<C, A> :: Substitution_*
	Unit<C, A> :: findSubstitution (const index :: Arity i) const
	{
		const Symbol&
			variable = *(Array_ :: getIterator (i));
		return substitution_->find (variable);
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: newSubstitution (Substitution_* delta)
	{
		if (substitution_ != NULL) {
			substitution_ = new Substitution_ (substitution_);
		}
		if (delta != NULL) {
			delta = delta->compose (substitution_, false);
			substitution_ = const_cast<Substitution_*>(substitution_)->compose (delta);
		}
	}
	template<class C, class A>
	inline const typename Unit<C, A> :: Substitution_*
	Unit<C, A> :: getSubstitution() const {
		return substitution_;
	}
	template<class C, class A>
	inline typename Unit<C, A> :: Substitution_*&
	Unit<C, A> :: substitution() {
		return const_cast<Substitution_*&>(substitution_);
	}

	template<class C, class A>
	inline index :: Arity
	Unit<C, A> :: getVariable() const
	{
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (Array_ :: skip (i)) {
				continue;
			}
			const Symbol symbol = *Array_ :: getIterator (i);
			if (symbol.isReplaceable()) {
				return i;
			}
		}
		return index :: undefined :: ARITY;
	}
	template<class C, class A>
	inline index :: Arity
	Unit<C, A> :: getTerm (const index :: Arity i) const
	{
		const Symbol variable = *Array_ :: getIterator (i);
		for (index :: Arity j = 0; j < Array_ :: getDimension(); ++ j) {
			if (Array_ :: skip (j)) {
				continue;
			}
			const Symbol symbol = *Array_ :: getIterator (j);
			if (symbol != variable) {
				return j;
			}
		}
		return index :: undefined :: ARITY;
	}
	template<class C, class A>
	bool
	Unit<C, A> :: findVarTermPair (index :: Arity& varIndex, index :: Arity& termIndex) const
	{
		for (varIndex = 0; varIndex < Array_ :: getDimension(); ++ varIndex) {
			if (Array_ :: skip (varIndex)) {
				continue;
			}
			const Symbol variable = *Array_ :: getIterator (varIndex);
			if (!variable.isReplaceable()) {
				continue;
			}
			for (termIndex = 0; termIndex < Array_ :: getDimension(); ++ termIndex) {
				if (Array_ :: skip (termIndex)) {
					continue;
				}
				const Symbol symbol = *Array_ :: getIterator (termIndex);
				if (symbol == variable) {
					continue;
				}
				if (symbol.getType()->isSuper (variable.getType())) {
					return true;
				}
			}
		}
		varIndex  = index :: undefined :: ARITY;
		termIndex = index :: undefined :: ARITY;
		return false;
	}

	template<class C, class A>
	inline bool
	Unit<C, A> :: isVarTermPair
	(
		const index :: Arity varIndex,
		const index :: Arity termIndex
	) const
	{
		const Symbol
			varSymbol = *Array_ :: getIterator (varIndex);
		if (!varSymbol.isReplaceable()) {
			return false;
		}
		const Symbol
			termSymbol = *Array_ :: getIterator (termIndex);
		if (termSymbol == varSymbol) {
			return false;
		}
		return true;
	}

	template<class C, class A>
	inline bool
	Unit<C, A> :: fixedAreEqual() const
	{
		Symbol firstFixed;
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (Array_ :: skip (i)) {
				continue;
			}
			const Symbol symbol = *Array_ :: getIterator (i);
			if (symbol.isFixed()) {
				if (firstFixed.isUndefined()) {
					firstFixed = symbol;
				}
				if (firstFixed != symbol) {
					return false;
				}
			}
		}
		return true;
	}
	template<class C, class A>
	inline bool
	Unit<C, A> :: allAreEqual() const
	{
		Symbol first;
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (Array_ :: skip (i)) {
				continue;
			}
			const Symbol symbol = *Array_ :: getIterator (i);
			if (first.isUndefined()) {
				first = symbol;
			}
			if (first != symbol) {
				return false;
			}
		}
		return true;
	}
	template<class C, class A>
	inline bool
	Unit<C, A> :: checkTermType
	(
		const index :: Arity i,  // varIndex
		const index :: Arity j,  // termIndex
		const Term_* const term
	) const
	{
		if (Array_ :: getIterator (j) != term->getBegin()) {
			return false;
		}
		const mdl :: Type* const
			varType = Array_ :: getIterator (i)->getType();
		const mdl :: Type* const
			termType = term->getType();
		return termType->isSuper (varType);
	}
	template<class C, class A>
	inline bool
	Unit<C, A> :: checkTermAccessible (const index :: Arity j, const Term_* const term) const
	{
		const Container_& containerNode = data_->getReference (j);
		const Container_& containerTerm = term->getEnd()->getData().getContainer();
		return !containerNode.isDisjointed (containerTerm);
	}
	template<class C, class A>
	inline bool
	Unit<C, A> :: checkTermVariables (const index :: Arity i, const Term_* const term) const
	{
		const Symbol& variable = *(Array_ :: getIterator (i));
		const Iterator_ begin = term->getBegin();
		const Iterator_ end = term->getEnd();
		Iterator_ iterator = end;

		while (true) {
			const Symbol& symbol = *iterator;
			if (symbol == variable) {
				return false;
			}
			const Substitution_* sub = substitution_->find (symbol);
			if (sub != NULL) {
				const typename Substitution_ :: Term_* term = sub->getTerm();
				if (term->contains (variable)) {
					return false;
				}
			}
			if (iterator == begin) {
				break;
			}
			-- iterator;
		}
		return true;
	}

	template<class C, class A>
	inline void
	Unit<C, A> :: initData()
	{
		data_ = new Data_ (Array_ :: getDimension());
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			const Iterator_ iterator = Array_ :: getIterator (i);
			const Container_& container = iterator->getData().getContainer();
			data_->getReference (i).copy (container);
		}
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: intersectData (const bool shift)
	{
		if (data_ == NULL || ((data_->prev_ == NULL) && !shift)) {
			initData();
			return;
		}
		const Data_* data = shift ? data_ : data_->prev_;
		data_ = new Data_ (Array_ :: getDimension(), data);
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			const Iterator_ iterator = Array_ :: getIterator (i);
			data_->getReference (i).copy (data->getReference (i));
			#ifdef DEBUG
			if (!data_->getReference (i).verify (true)) {
				std :: cout << "data set at substitution unification is bad" << std :: endl;
			}
			if (!iterator->getData().getContainer().verify (true)) {
				std :: cout << "data set at substitution unification is bad" << std :: endl;
			}
			#endif
			data_->getReference (i).intersect (iterator->getData().getContainer());
		}
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: intersectData (const index :: Arity j, const Term_* term)
	{
		if (data_->prev_ != NULL) {
			const Data_* data = data_;
			data_ = new Data_ (Array_ :: getDimension(), data_->prev_);
			for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
				data_->getReference (i).copy (data->getReference (i));
			}
		} else {
			data_ = new Data_ (Array_ :: getDimension());
			for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
				const Iterator_ iterator = Array_ :: getIterator (i);
				data_->getReference (i).copy (iterator->getData().getContainer());
			}
		}
		data_->getReference (j).intersect (term->getEnd()->getData().getContainer());
	}
	template<class C, class A>
	inline bool
	Unit<C, A> :: isGood()
	{
		if (!isNonempty()) {
			return false;
		}
		return true;
	}
	template<class C, class A>
	inline bool
	Unit<C, A> :: isNonempty()
	{
		if (data_ == NULL) {
			initData();
		}
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (data_->getReference (i).isEmpty()) {
				return false;
			}
		}
		return true;
	}

	/*template<class C, class A>
	inline typename Unit<C, A> :: Evidence_*
	Unit<C, A> :: getValue (const index :: Arity i) const
	{
		const Container_& container = data_->getReference (i);
		value :: Integer minCardinality = value :: undefined :: INTEGER;
		value :: Integer minIndex = 0;
		for (value :: Integer j = 0; j < container.getSize(); ++ j) {
			Evidence_* const
				evidence = container.getValue (j);
			if (evidence->getCardinality() < minCardinality) {
				minCardinality = evidence->getCardinality();
				minIndex = j;
			}
		}
		return data_->getReference (i).getValue (minIndex);
	}*/
	template<class C, class A>
	inline typename Unit<C, A> :: Container_&
	Unit<C, A> :: getValues (const index :: Arity i) const {
		return data_->getReference (i);
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: insert (const index :: Arity i, const Term_* insertion)
	{
		const Iterator_ iterator = Array_ :: getIterator (i);
		const Container_& container = data_->getReference (i);
		Term_* const term = const_cast<Term_*>(insertion);
		const typename Term_ :: Iterator_ begin = term->getBegin();
		const typename Term_ :: Iterator_ end = term->getEnd();
		typename Term_ :: Iterator_ iter = end;
		while (true) {
			iter->getData().container().copy (container);
			if (iter == begin) {
				break;
			}
			-- iter;
		}
		Array_ :: iterator (i) = insertion->getBegin();
	}

	template<class C, class A>
	inline bool
	Unit<C, A> :: isLastColumn() const {
		return (index_ + 1 == matrix_.getSize());
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: shiftColumn (const Unit* prev)
	{
		prev_ = prev;
		++ index_;
		const Vector_* const
			vector = matrix_.getValue (index_);
		newSubstitution();
		for (index :: Arity i = 0; i < vector->getSize(); ++ i) {
			Cell_* const cell = vector->getValue (i);
			Array_ :: iterator (i) = cell->getBegin();
		}
		intersectData (true);
	}

using manipulator :: endLine;
using manipulator :: iterate;
using manipulator :: tab;
using manipulator :: space;

	template<class C, class A>
	inline void
	Unit<C, A> :: show (String& string) const
	{
		string << endLine;
		/*string << "unit, index = " << index_ << " : " << endLine;
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			string << i << " = ";
			Array_ :: getIterator (i)->showBack (string);
			string << endLine;
		}
		//string << endLine;*/
		if (substitution_ != NULL) {
			string << "substitution: " << *substitution_ << endLine;
		} else {
			string << "substitution: NULL" << endLine;
		}
		string << endLine;
		string << "index =  " << index_ << endLine;
		//string << "length =  " << getLength() << endLine;
		string << "nodes: (data = " << data_ << ")" << endLine;
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			string << tab << i << space << ":" << space;
			string << " -- ";
			if (Array_ :: getIterator (i) != NULL) {
				Array_ :: getIterator (i)->show (string);
			} else {
				string << "NULL";
			}
			string << " --  ";
			if (Array_ :: getIterator (i) != NULL) {
				Array_ :: getIterator (i)->showBack (string);
			} else {
				string << "NULL";
			}
			if (data_ != NULL) {
				string << tab;
				/*if (getValue (i).isNew()) {
					string << "new" << space;
				} else {
					string << "old" << space;
				}*/
				//string << "evidence = " << getValue (i).getEvidence() << space;
				string << "data = " << data_->getValue (i) << space;
			}
			string << endLine;
		}
		string << endLine;
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: showUnit (String& string) const
	{
		if (prev_ != NULL) {
			prev_->showUnit (string);
		}
		string << "-------------------------------------" << endLine;
		string << "index: " << index_ << endLine;
		string << "branch: "; showBranch (string); string << endLine;
		if (substitution_ != NULL) {
			string << "substitution: " << *substitution_ << endLine;
		} else {
			string << "substitution: NULL" << endLine;
		}
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: showBranch (String& string) const
	{
		Iterator_ iterator;
		for (index :: Arity k = 0; k < Array_ :: getDimension(); ++ k) {
			if (Array_ :: skip (k)) {
				if (k == Array_ :: getDimension() - 1) {
					string << "<Lambda> ";
				}
				continue;
			}
			iterator = Array_ :: getIterator (k);
			break;
		}
		iterator->showBack (string);
	}

	template<class C, class A>
	inline void
	Unit<C, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 256
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: verifyIntegrity() const
	{
		Expression_* expressions [Array_ :: getDimension()];
		const Substitution_*
			substitution = substitution_->template createList<allocator :: Stack>();
		bool success = true;

		Memory :: stack().push();
		try {
			success = checkResult (expressions, substitution);
		} catch (Error* error) {
			success = false;
			delete error;
		}
		Memory :: stack().pop();

		if (!success) {
			Memory :: stack().push();
			success = checkResult (expressions, substitution);
			Memory :: stack().pop();
			verificationFail (expressions, substitution);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class C, class A>
	inline value :: Integer
	Unit<C, A> :: getUnitLength (const Substitution_* substitution) const
	{
		Iterator_ iterator;
		for (index :: Arity k = 0; k < Array_ :: getDimension(); ++ k) {
			if (Array_ :: skip (k)) {
				if (k == Array_ :: getDimension() - 1) {
					return 0;
				}
				continue;
			}
			iterator = Array_ :: getIterator (k);
			break;
		}
		value :: Integer
			length = 0;
		while (iterator != NULL) {
			const Symbol& symbol = *iterator;
			const Substitution_* sub = substitution->find (symbol);
			++ length;
			if (sub != NULL) {
				const typename Substitution_ :: Term_* term = sub->getTerm();
				const index :: Literal
					subLength = term->getLength();
				length += subLength - 1;
			}
			-- iterator;
		}
		return length;
	}
	template<class C, class A>
	inline value :: Integer
	Unit<C, A> :: getComplexity
	(
		const index :: Arity i,  // varIndex
		const Term_* const term
	) const
	{
		const Symbol&
			variable = *Array_ :: getIterator (i);
		const value :: Integer
			insertionLength = getSubstitutedLength (term);
		value :: Integer
			complexity = getUnitLength (i, insertionLength, substitution_);
		const Unit* unit = prev_;
		while (unit != NULL) {
			const value :: Integer
				unitLength = unit->getUnitLength (variable, insertionLength, substitution_);
			complexity = (complexity < unitLength) ? unitLength : complexity;
			unit = unit->prev_;
		}
		return complexity;
	}
	template<class C, class A>
	inline value :: Integer
	Unit<C, A> :: getUnitLength
	(
		const index :: Arity i,
		const value :: Integer insertionLength,
		const Substitution_* substitution
	) const
	{
		Iterator_
			iterator = Array_ :: getIterator (i);
		const Symbol&
			variable = *Array_ :: getIterator (i);
		value :: Integer length = 0;
		while (iterator != NULL) {
			const Symbol& symbol = *iterator;
			const Substitution_* sub = substitution->find (symbol);
			++ length;
			if (sub != NULL) {
				const typename Substitution_ :: Term_* term = sub->getTerm();
				const index :: Literal
					subLength = getSubstitutedLength (variable, insertionLength, term);
				length += subLength - 1;
			} else if (symbol == variable) {
				length += insertionLength - 1;
			}
			-- iterator;
		}
		return length;
	}
	template<class C, class A>
	inline value :: Integer
	Unit<C, A> :: getUnitLength
	(
		const Symbol& variable,
		const value :: Integer insertionLength,
		const Substitution_* substitution
	) const
	{
		Iterator_ iterator;
		for (index :: Arity k = 0; k < Array_ :: getDimension(); ++ k) {
			if (Array_ :: skip (k)) {
				continue;
			}
			iterator = Array_ :: getIterator (k);
			break;
		}
		value :: Integer length = 0;
		while (iterator != NULL) {
			const Symbol& symbol = *iterator;
			const Substitution_* sub = substitution->find (symbol);
			++ length;
			if (sub != NULL) {
				const typename Substitution_ :: Term_* term = sub->getTerm();
				const index :: Literal
					subLength = getSubstitutedLength (variable, insertionLength, term);
				length += subLength - 1;
			} else if (symbol == variable) {
				length += insertionLength - 1;
			}
			-- iterator;
		}
		return length;
	}
	template<class C, class A>
	inline index :: Literal
	Unit<C, A> :: getSubstitutedLength (const Term_* const term) const
	{
		value :: Integer length = 0;
		typedef
			typename Term_ :: const_Iterator_
			const_Iterator;
		const const_Iterator begin = term->getBegin();
		const const_Iterator end = term->getEnd();
		const_Iterator iterator = end;
		while (true) {
			const Symbol& symbol = *iterator;
			++ length;
			const Substitution_* sub = substitution_->find (symbol);
			if (sub != NULL) {
				length += sub->getTerm()->getLength() - 1;
			}
			if (iterator == begin) {
				break;
			}
			-- iterator;
		}
 		return length;
	}
	template<class C, class A>
	inline index :: Literal
	Unit<C, A> :: getSubstitutedLength
	(
		const Symbol& variable,
		const index :: Literal insertionLength,
		const typename Substitution_ :: Term_* const term
	) const
	{
		value :: Integer length = 0;
		typedef
			typename Substitution_ :: Term_ :: const_Iterator_
			const_Iterator;

		const const_Iterator begin = term->getBegin();
		const const_Iterator end = term->getEnd();
		const_Iterator iterator = end;
		while (true) {
			const Symbol& symbol = *iterator;
			++ length;
			if (symbol == variable) {
				length += insertionLength - 1;
			}
			if (iterator == begin) {
				break;
			}
			-- iterator;
		}
		return length;
	}

	template<class C, class A>
	inline bool
	Unit<C, A> :: checkResult
	(
		Expression_** expressions,
		const Substitution_* substitution
	) const
	{
		if (Array_ :: isNull ()) {
			return true;
		}
		bool result = true;
		Expression_* firstExpession = NULL;

		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (Array_ :: skip (i)) {
				continue;
			}
			const Term_* const
				term = Array_ :: getIterator (i)->getTerms().getTerminal().getLast()->getValue();

			Expression_*& currentExpression = expressions [i];
			currentExpression = Expression_ :: createList (term);

			currentExpression->verifyIntegrity();
			currentExpression->execute (substitution);
			currentExpression->verifyIntegrity();

			if (firstExpession == NULL) {
				firstExpession = currentExpression;
			} else {
				result &=
				(
					firstExpession->template
						coinsides<node :: List, allocator :: Stack> (*currentExpression)
				);
			}
		}
		return result;
	}
	template<class C, class A>
	inline void
	Unit<C, A> :: verificationFail
	(
		Expression_** expressions,
		const Substitution_* substitution
	) const
	{
		Mode mode;
		//mode << Mode :: SHOW_REPLACEABILITY;
		Error* error = new Error (Error :: SEMANTIC);
		error->message() << mode << "unification error" << endLine;
		error->message() << "=================" << endLine;
		error->message() << "substitution:" << endLine;
		if (substitution != NULL) {
			error->message() << tab << *substitution;
		} else {
			error->message() << tab << "NULL" << endLine;
		}
		error->message() << endLine;
		error->message() << "original expressions:" << endLine;
		error->message() << "--------------------:" << endLine;
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (Array_ :: skip (i)) {
				error->message() << "term " << i << " = " << "skip" << endLine;
				continue;
			}
			const Term_* const
				term = Array_ :: getIterator (i)->getTerms().getTerminal().getLast()->getValue();
			error->message() << "term " << i << " = " << *term << endLine;
		}
		error->message() << endLine;
		error->message() << "obtained expressions:" << endLine;
		error->message() << "--------------------:" << endLine;
		for (index :: Arity i = 0; i < Array_ :: getDimension(); ++ i) {
			if (Array_ :: skip (i)) {
				error->message() << "term " << i << " = " << "skip" << endLine;
				continue;
			}
			error->message() << "term " << i << " = " << *expressions [i] << endLine;
		}
		error->message() << iterate << 5 << endLine;
		throw error;
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class C, class A>
	String&
	operator << (String& string, const Unit<C, A>& unit)
	{
		unit.show (string);
		return string;
	}
	template<class C, class A>
	std :: ostream&
	operator << (std :: ostream& os, const Unit<C, A>& unit)
	{
		static String* string = NULL;
		if (string == NULL) {
			string = new String (1024);
		} else {
			string->clear();
		}
		unit.show (*string);
		return os << *string;
	}
}
}
}
}
}



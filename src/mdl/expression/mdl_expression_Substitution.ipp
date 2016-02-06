/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Substitution.ipp                          */
/* Description:     substitution expression class                            */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	template<class A>
	inline typename Substitution<T> :: template Alternative<A> :: Result_*
	Substitution<T> :: castAway()
	{
		typedef A Allocator;
		typedef
			typename Alternative<Allocator> :: Result_
			Alternative;
		return reinterpret_cast<Alternative*>(this);
	}
	template<class T>
	template<class A>
	inline const typename Substitution<T> :: template Alternative<A> :: Result_*
	Substitution<T> :: castAway() const
	{
		typedef A Allocator;
		typedef
			typename Alternative<Allocator> :: Result_
			Alternative;
		return reinterpret_cast<const Alternative*>(this);
	}

	template<class T>
	template<class A>
	inline Substitution<T>*
	Substitution<T> :: create
	(
		const Symbol& variable ,
		const Term_* term,
		const Substitution* next,
		const bool ownsTerm
	)
	{
		typedef A Allocator;
		typedef
			typename Alternative<Allocator> :: Result_
			Result;
		Result* const result = new Result
		(
			variable,
			term->castAway<Allocator>(),
			next->castAway<Allocator>(),
			ownsTerm
		);
		return result->castAway<Allocator_>();
	}
	template<class T>
	inline Substitution<T>*
	Substitution<T> :: create (const Substitution* substitution) {
		return (substitution == NULL) ? NULL : new Substitution (substitution);
	}
	template<class T>
	template<class T1>
	inline Substitution<T>*
	Substitution<T> :: create (const Substitution<T1>* substitution) {
		return (substitution == NULL) ? NULL : new Substitution (substitution);
	}

	template<class T>
	template<class A>
	inline const Substitution<T>*
	Substitution<T> :: clone() const
	{
		typedef A Allocator;
		Memory :: stack().push();
		Pool<Allocator>* const
			pool = new Pool<Allocator>();
		const Substitution*
			result = clone<Pool<Allocator> > (pool);
		Memory :: stack().pop();
		return result;
	}
	template<class T>
	template<class P>
	inline const Substitution<T>*
	Substitution<T> :: clone (P* pool) const {
		return pool->clone (this);
	}
	template<class T>
	template<class A>
	inline Substitution<T>*
	Substitution<T> :: cloneSelf () const
	{
		typedef A Allocator;
		if (this == NULL) {
			return NULL;
		}
		return create<Allocator>(unit_.variable_, unit_.term_, next_);
	}
	template<class T>
	template<class P>
	inline void
	Substitution<T> :: cloneContents (P* pool) const
	{
		unit_.term_ = pool->clone (unit_.term_);
		next_= pool->clone (next_);
	}

	template<class T>
	template<class A>
	const Substitution<Term<typename node :: List<A> > >*
	Substitution<T> :: createList() const
	{
		if (this == NULL) {
			return NULL;
		}
		typedef A Allocator;
		typedef
			Substitution<Term<typename node :: List<A> > >
			Substitution_;
		return Substitution_ :: template create<Allocator>
		(
			unit_.variable_,
			unit_.term_->template createList<Allocator>(),
			next_->template createList<Allocator>(),
			true
		);
	}

	template<class T>
	inline
	Substitution<T> :: Substitution
	(
		const Symbol& variable,
		const Term_* term,
		const Substitution* const next,
		const bool ownsTerm
	) :
	unit_ (variable, term, ownsTerm),
	next_ (next)
	{
		#ifdef DEBUG
		//verifyIntegrity();
		#endif
	}
	template<class T>
	Substitution<T> :: Substitution (const Substitution* const substitution) :
	unit_
	(
		substitution->getVariable(),
		List<Allocator_> :: createTerm (substitution->getTerm()),
		true
	),
	next_ (create (substitution->getNext()))
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
	}
	template<class T>
	template<class T1>
	Substitution<T> :: Substitution (const Substitution<T1>* const substitution) :
	unit_
	(
		substitution->getVariable(),
		List<Allocator_> :: template createTerm<T1> (substitution->getTerm()),
		true
	),
	next_ (create (substitution->getNext()))
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
	}
	template<class T>
	Substitution<T> :: ~ Substitution()
	{
		if (next_ != NULL) {
			delete next_;
			next_ = NULL;
		}
	}

	template<class T>
	bool
	Substitution<T> :: coinsides (const const_Iterator_ begin, const const_Iterator_ end) const
	{
		const_Iterator_ it_1 = getEnd();
		const_Iterator_ it_2 = end;

		while (true) {
			if (*it_1 != *it_2) {
				return false;
			}
			if (it_1 == getBegin()) {
				return (it_2 == begin);
			}
			if (it_2 == begin) {
				return (it_1 == getBegin());
			}
			-- it_1;
			-- it_2;
		}
	}

	template<class T>
	inline typename Substitution<T> :: const_Iterator_
	Substitution<T> :: follow (const const_Iterator_ iterator) const {
		return follow (getEnd(), iterator);
	}

	template<class T>
	const Substitution<T>*
	Substitution<T> :: find (const Symbol& variable) const
	{
		const Substitution* substitution = this;
		while (substitution != NULL) {
			if (substitution->unit_.variable_ == variable) {
				return substitution;
			}
			substitution = substitution->next_;
		}
		return NULL;
	}
	template<class T>
	const Substitution<T>*
	Substitution<T> :: findTerm (const Symbol& variable) const
	{
		const Substitution* substitution = this;
		while (substitution != NULL) {
			const Term_* const
				term = substitution->unit_.term_;
			if ((term->isVariable()) && (term->contains (variable))) {
				return substitution;
			}
			substitution = substitution->next_;
		}
		return NULL;
	}
	template<class T>
	const Substitution<T>*
	Substitution<T> :: find (const value :: Literal variable) const
	{
		const Substitution* substitution = this;
		while (substitution != NULL) {
			if (substitution->unit_.variable_.getLiteral() == variable) {
				return substitution;
			}
			substitution = substitution->next_;
		}
		return NULL;
	}

	template<class T>
	inline const typename Substitution<T> :: Term_*
	Substitution<T> :: getTerm () const {
		return unit_.term_;
	}
	template<class T>
	inline typename Substitution<T> :: Term_*
	Substitution<T> :: term() {
		return const_cast<Term_*>(unit_.term_);
	}
	template<class T>
	inline const Symbol&
	Substitution<T> :: getVariable() const {
		return unit_.variable_;
	}
	template<class T>
	inline const Substitution<T>*
	Substitution<T> :: getNext() const {
		return next_;
	}
	template<class T>
	inline void
	Substitution<T> :: setNext (const Substitution* next) const {
		next_ = next;
	}
	template<class T>
	inline Substitution<T>*
	Substitution<T> :: next() const {
		return const_cast<Substitution*> (next_);
	}

	template<class T>
	inline value :: Integer
	Substitution<T> :: getLength() const {
		return unit_.getLength();
	}
	template<class T>
	value :: Integer
	Substitution<T> :: getSymbolVolume() const
	{
		value :: Integer volume = 0;
		const Substitution* substitution = this;
		while (substitution != NULL) {
			volume += substitution->unit_.getTerm()->getSymbolVolume();
			substitution = substitution->getNext();
		}
		return volume;
	}
	template<class T>
	value :: Integer
	Substitution<T> :: getComplexity() const
	{
		value :: Integer maxComplexity = 0;
		const Substitution* substitution = this;
		while (substitution != NULL) {
			const value :: Integer
				complexity = substitution->unit_.getTerm()->getComplexity();
			if (maxComplexity < complexity) {
				maxComplexity = complexity;
			}
			substitution = substitution->getNext();
		}
		return maxComplexity;
	}
	template<class T>
	inline value :: Integer
	Substitution<T> :: getCardinality() const
	{
		value :: Integer cardinality = 0;
		const Substitution* substitution = this;
		while (substitution != NULL) {
			++ cardinality;
			substitution = substitution->getNext();
		}
		return cardinality;
	}

	template<class T>
	inline bool
	Substitution<T> :: isTrivial() const
	{
		if (this == NULL) {
			return true;
		}
		return unit_.isTrivial();
	}

	template<class T>
	inline Substitution<T>*
	Substitution<T> :: compose
	(
		const Substitution* const delta,
		const bool join
	)
	{
		Substitution* applied = apply (delta);
		#ifdef DEBUG
		verifyIntegrity();
		delta->verifyIntegrity();
		#endif
		Substitution* result = NULL;
		if (join) {
			result = applied->add (delta);
		} else {
			result = applied;
		}
		#ifdef DEBUG
		verifyIntegrity();
		delta->verifyIntegrity();
		#endif
		return result;
	}
	template<class T>
	inline Substitution<T>*
	Substitution<T> :: unite (const Substitution* const theta) {
		return add (theta);
	}
	template<class T>
	inline Substitution<T>*
	Substitution<T> :: join (const Substitution* const substitution)
	{
		if (this == NULL) {
			return const_cast<Substitution*>(substitution);
		}
		const Substitution* theta = this;
		while (theta != NULL) {
			const Substitution* next = theta->next_;
			if (next == NULL) {
				theta->next_ = substitution;
			}
			theta = next;
		}
		return this;
	}
	template<class T>
	inline bool
	Substitution<T> :: isComposableWith (const Substitution* const substitution) const
	{
		const Substitution* theta = this;
		while (theta != NULL) {
			const Term_* term = theta->getTerm();
			const Substitution* tau = substitution;
			while (tau != NULL) {
				const Symbol& variable = tau->getVariable();
				if (term->contains (variable)) {
					return true;
				}
				tau = tau->getNext();
			}
			theta = theta->getNext();
		}
		return false;
	}
	template<class T>
	template<class I>
	inline Substitution<T>*
	Substitution<T> :: restrictTo (const I end)
	{
		typedef I Iterator;
		Substitution* theta = this;
		Substitution* prev = NULL;
		Substitution* next = NULL;
		Substitution* result = NULL;

		while (theta != NULL) {
			const Symbol&
				variable = theta->unit_.variable_;
			bool contains = false;
			Iterator iterator (end);
			while (!iterator.isNull()) {
				if (variable == *iterator) {
					contains = true;
					break;
				}
				-- iterator;
			}
			if (contains) {
				if (prev != NULL) {
					prev->next_ = theta;
				} else {
					result = theta;
				}
				prev = theta;
			}
			next = theta->next();
			if (!contains) {
				//theta->next_ = NULL;
				//theta->commitSuicide();
			}
			theta = next;
			if (prev != NULL) {
				prev->next_ = NULL;
			}
		}
		return result;
	}
	template<class T>
	inline Substitution<T>*
	Substitution<T> :: inverse() const
	{
		Substitution* result = Substitution :: create (this);
		result->inverse();
		return result;
	}
	template<class T>
	inline bool
	Substitution<T> :: operator == (const Substitution& substitution) const
	{
		if (unit_ != substitution.unit_) {
			return false;
		}
		if (next_ != NULL) {
			if (substitution.next_ == NULL) {
				return false;
			} else {
				return (*next_ == *substitution.next_);
			}
		} else {
			if (substitution.next_ == NULL) {
				return true;
			} else {
				return false;
			}
		}
	}
	template<class T>
	inline bool
	Substitution<T> :: operator != (const Substitution& substitution) const {
		return !(operator == (substitution));
	}

	template<class T>
	inline bool
	Substitution<T> :: isEqual (const Substitution* substitution) const
	{
		if ((this == NULL) && (substitution == NULL)) {
			return true;
		}
		if (!isLessGeneral<unify :: kind :: PLAIN>(substitution)) {
			return false;
		}
		if (!isMoreGeneral<unify :: kind :: PLAIN>(substitution)) {
			return false;
		}
		return true;
	}
	template<class T>
	template<int K>
	inline bool
	Substitution<T> :: isLessGeneral (const Substitution* substitution) const
	{
		if (this == NULL) {
			return false;
		}
		if (!substitution->domainsSubset (this)) {
			return false;
		}
		enum {
			kind = K
		};
		typedef
			List<allocator :: Stack>
			StackExpression;
		typedef
			typename StackExpression :: Term_
			StackTerm;
		typedef
			Substitution <StackTerm>
			StackSubstitution;
		typedef
			vector :: Vector
			<
				const StackSubstitution*,
				storage :: ByValue,
				allocator :: Stack
			>
			Substivector;
		typedef
			substitution :: prod :: Unify
			<
				prover :: template Types<typename allocator :: Stack>,
				unify :: policy :: DIRECT,
				kind,
				allocator :: Stack
			>
			PairUnifier;
		bool result = false;
		/*Memory :: stack().push();
		Substivector substitutionPair (2);
		substitutionPair.add (substitution->castAway<allocator :: Stack>());
		substitutionPair.add (this->castAway<allocator :: Stack>());
		PairUnifier pairUnifier (substitutionPair, NULL);
		result = pairUnifier.unify();
		Memory :: stack().pop();*/
		return result;
	}
	template<class T>
	template<int K>
	inline bool
	Substitution<T> :: isMoreGeneral (const Substitution* substitution) const
	{
		enum {
			kind = K
		};
		return substitution->isLessGeneral<kind> (this);
	}
	template<class T>
	inline bool
	Substitution<T> :: domainsAreEqual (const Substitution* substitution) const
	{
		if (!this->domainsSubset (substitution)) {
			return false;
		}
		if (!substitution->domainsSubset (this)) {
			return false;
		}
		return true;
	}
	template<class T>
	inline bool
	Substitution<T> :: domainsSubset (const Substitution* substitution) const
	{
		const Substitution* sub = this;
		while (sub != NULL) {
			const Symbol& variable = sub->getVariable();
			if (substitution->find (variable) == NULL) {
				return false;
			}
			sub = sub->getNext();
		}
		return true;
	}

	template<class T>
	inline bool
	Substitution<T> :: isIdentical (const Substitution* substitution) const
	{
		if (!this->inside (substitution)) {
			return false;
		}
		if (!substitution->inside (this)) {
			return false;
		}
		return true;
	}
	template<class T>
	inline bool
	Substitution<T> :: inside (const Substitution* substitution) const
	{
		if (substitution == NULL) {
			return (this == NULL);
		}
		const Substitution* sub = this;
		while (sub != NULL) {
			if (!substitution->includes (sub->unit_)) {
				return false;
			}
			sub = sub->getNext();
		}
		return true;
	}
	template<class T>
	inline bool
	Substitution<T> :: includes (const Substiunit_& unit) const
	{
		const Substitution* sub = this;
		while (sub != NULL) {
			if (sub->unit_.isEqual (unit)) {
				return true;
			}
			sub = sub->getNext();
		}
		return false;
	}

	template<class T>
	inline bool
	Substitution<T> :: unifyCommonVariables
	(
		Substitution*& th,
		Substitution*& dl
	)
	{
		bool iterate = true;
		while (iterate) {
			if (!unifyCommonVariable (th, dl, iterate)) {
				return false;
			}
		}
		return true;
	}
	template<class T>
	inline bool
	Substitution<T> :: compositionClosure
	(
		const value :: Integer boundary,
		Substitution*& substitution
	)
	{
		if ((substitution == NULL) || (boundary == 0)) {
			return true;
		}
		Substitution*
			sb = Substitution :: create (substitution);
		for (value :: Integer i = 0; i < boundary; ++ i) {
			if (substitution->isComposableWith (sb)) {
				substitution = substitution->compose (sb, false);
			} else {
				return true;
			}
		}
		return false;
	}

	template<class T>
	inline void
	Substitution<T> :: verifyIntegrity() const
	{
		if (this == NULL) {
			return;
		}
		unit_.verifyIntegrity();
		next_->verifyIntegrity();
		const Substitution* const
			substitution = next_->find (unit_.getVariable());
		if (substitution != NULL) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "inconsistent substitution:" << endLine;
			error->message() << *this << endLine;
			throw error;
		}
	}

	template<class T>
	void
	Substitution<T> :: inverse()
	{
		Substitution* sub = this;
		while (sub != NULL) {
			sub->unit_.inverse();
			sub = sub->next();
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class T>
	inline void
	Substitution<T> :: commitSuicide() {
		delete this;
	}
	template<class T>
	Size_t
	Substitution<T> :: getVolume() const
	{
		Size_t volume = 0;
		volume += unit_.getVolume();
		if (next_ != NULL) {
			volume += next_->getVolume();
			volume += next_->getSizeOf();
		}
		return volume;
	}
	template<class T>
	inline Size_t
	Substitution<T> :: getSizeOf() const {
		return sizeof (Substitution);
	}
	template<class T>
	void
	Substitution<T> :: show (String& string) const
	{
		const bool oneLine = true; //(getSymbolVolume() < Config :: multylineMaxWidth());
		if (oneLine) {
			string << '{' << space;
		} else {
			string << endLine << '{' << endLine;
		}
		const Substitution*
			substitution = this;
		while (substitution != NULL) {
			substitution->unit_.show (string);
			substitution = substitution->getNext();
			if (substitution != NULL) {
				string << ',' << space;
			}
			if (!oneLine) {
				string << endLine;
			}
		}
		if (oneLine) {
			string << '}' << space;
		} else {
			string << '}' << endLine;
		}
	}
	template<class T>
	void
	Substitution<T> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	typename Substitution<T> :: const_Iterator_
	Substitution<T> :: follow (const_Iterator_ x, const_Iterator_ y) const
	{
		if (x != getBegin()) {
			const_Iterator_ x_prev = x;
			-- x_prev;
			const_Iterator_ y_curr = follow (x_prev, y);
			if (y_curr == NULL) {
				return const_Iterator_();
			}
			++ y_curr;
			return match (x, y_curr);
		} else {
			return match (x, y);
		}
	}
	template<class T>
	typename Substitution<T> :: const_Iterator_
	Substitution<T> :: match (const const_Iterator_ x, const_Iterator_ y) const
	{
		while (y != NULL) {
			if (*x == *y) {
				break;
			}
			+ y;
		}
		return y;
	}

	template<class T>
	inline typename Substitution<T> :: const_Iterator_
	Substitution<T> :: getBegin() const {
		return unit_.term_->getBegin();
	}
	template<class T>
	inline typename Substitution<T> :: const_Iterator_
	Substitution<T> :: getEnd() const {
		return unit_.term_->getEnd();
	}

	// composition  routines
	template<class T>
	Substitution<T>*
	Substitution<T> :: apply (const Substitution* const delta)
	{
		Substitution* theta = this;
		while (theta != NULL) {
			theta->unit_.term_ = theta->term()->execute (delta);
			theta = theta->next();
		}
		#ifdef DEBUG
		delta->verifyIntegrity();
		verifyIntegrity();
		#endif
		Substitution* result = removeTrivial();
		#ifdef DEBUG
		delta->verifyIntegrity();
		verifyIntegrity();
		#endif
		return result;
	}
	template<class T>
	Substitution<T>*
	Substitution<T> :: removeTrivial()
	{
		Substitution* theta = this;
		Substitution* prev = NULL;
		Substitution* next = NULL;
		Substitution* result = NULL;
		while (theta != NULL) {
			if (!theta->isTrivial()) {
				if (prev != NULL) {
					prev->next_ = theta;
				} else {
					result = theta;
				}
				prev = theta;
			}
			next = theta->next();
			if (theta->isTrivial()) {
				theta->next_ = NULL;
				theta->commitSuicide();
			}
			theta = next;
			if (prev != NULL) {
				prev->next_ = NULL;
			}
		}
		return result;
	}
	template<class T>
	Substitution<T>*
	Substitution<T> :: add (const Substitution* const delta)
	{
		const Substitution* theta = delta;
		Substitution* result = this;
		while (theta != NULL) {
			if (!theta->isTrivial()) {
				result = addUnit (result, theta->unit_);
			}
			theta = theta->getNext();
		}
		#ifdef DEBUG
		delta->verifyIntegrity();
		verifyIntegrity();
		#endif
		return result;
	}
	template<class T>
	Substitution<T>*
	Substitution<T> :: addUnit
	(
		Substitution* const substitution,
		const Substiunit_& pair
	)
	{
		#ifdef DEBUG
		substitution->verifyIntegrity();
		#endif
		const Substitution*
			sub = find (pair.variable_);
		if (sub != NULL) {
			#ifdef DEBUG
			if (!sub->unit_.isEqualLiteraly (pair)) {
				/*Error* error = new Error (Error :: SEMANTIC);
				error->message() << "incorrect adding substitution:" << endLine;
				error->message() << sub->unit_ << " != " << pair << endLine;
				error->message() << "substitution = " << *this << endLine;
				throw error;*/
			}
			#endif
			return substitution;
		} else {
			#ifdef DEBUG
			pair.term_->verifyIntegrity();
			#endif
			const Term_*
				term = pair.ownsTerm_ ?
					pair.term_->template createList<Allocator_>() :
					pair.term_;
			#ifdef DEBUG
			pair.term_->verifyIntegrity();
			term->verifyIntegrity();
			#endif
			Substitution*
				result = new Substitution
			(
				pair.variable_,
				term,
				substitution,
				pair.ownsTerm_
			);
			#ifdef DEBUG
			substitution->verifyIntegrity();
			result->verifyIntegrity();
			#endif
			return result;
		}
	}

	// common variable unification routines
	template<class T>
	inline bool
	Substitution<T> :: unifyCommonVariable
	(
		Substitution*& th,
		Substitution*& dl,
		bool& iterate
	)
	{
		const Substitution* delta = dl;
		while (delta != NULL) {
			const Symbol& var1 = delta->getVariable();
			const Substitution* theta = th;
			while (theta != NULL) {
				const Symbol& var2 = theta->getVariable();
				if (var1 == var2) {
					typedef List<allocator :: Stack> Expression;
					const Term_* const
						term1 = Expression :: createTerm (delta->getTerm());
					const Term_* const
						term2 = Expression :: createTerm (theta->getTerm());
					if (*term1 != *term2) {
						return unifyCommonPair (th, dl, term1, term2);
					}
				}
				theta = theta->getNext();
			}
			delta = delta->getNext();
		}
		iterate = false;
		return true;
	}
	template<class T>
	inline bool
	Substitution<T> :: unifyCommonPair
	(
		Substitution*& th,
		Substitution*& dl,
		const Term_* term1,
		const Term_* term2
	)
	{
		typedef List<allocator :: Stack> Expression;
		const Expression* const
			expression1 = new Expression (term1);
		const Expression* const
			expression2 = new Expression (term2);
		const Substitution* substitution = NULL;

		const bool
			success = expression1->unifySymmetric (expression2, substitution);

		if (success) {
			th = th->compose (substitution);
			dl = dl->compose (substitution, false);
		}
		return success;
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T>
	String&
	operator << (String& string, const Substitution<T>& substitution)
	{
		substitution.show (string);
		return string;
	}
	template<class T>
	std :: ostream&
	operator << (std :: ostream& os, const Substitution<T>& substitution)
	{
		String* string = new String (1024);
		os << (*string << substitution);
		string->commitSuicide();
		return os;
	}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unit_SYM.ipp                    */
/* Description:     pair of iterators for the symmetric unification algorithm*/
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_UNIT_SYM_IPP_
#define MDL_EXPRESSION_UNIFY_EXP_UNIT_SYM_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2, int K>
	inline
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Unit
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2,
		const index :: Step level_1,
		const index :: Step level_2,
		const Substitution_* substitution
	) :
	Pair_ (iterator_1, iterator_2),
	substitution_ (substitution),
	level_1_ (level_1),
	level_2_ (level_2) {
	}
	template<class T_1, class T_2, int K>
	inline
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Unit (const Unit& unit) :
	Pair_ (unit),
	substitution_ (unit.substitution_),
	level_1_ (unit.level_1_),
	level_2_ (unit.level_2_) {
	}
	template<class T_1, class T_2, int K>
	inline
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Unit () :
	Pair_ (),
	substitution_ (NULL),
	level_1_ (index :: undefined :: STEP),
	level_2_ (index :: undefined :: STEP) {
	}

	template<class T_1, class T_2, int K>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: operator ++ () {
		Pair_ :: operator ++ ();
	}

	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: InverseUnit_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: inverse () const
	{
		InverseUnit_ inverseUnit
		(
			Pair_ :: getSecond(),
			Pair_ :: getFirst(),
			level_2_,
			level_1_,
			substitution_
		);
		return inverseUnit;
	}

	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: isReacheable() const
	{
		return
			Pair_ :: getFirst()->isReacheable (level_1_) &&
			Pair_ :: getSecond()->isReacheable (level_2_);
	}
	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: isReplaceable() const {
		return Pair_ :: getFirst()->isReplaceable();
	}
	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: isFixed() const
	{
		return
			Pair_ :: getFirst()->isFixed() &&
			Pair_ :: getSecond()->isFixed();
	}
	template<class T_1, class T_2, int K>
	typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Replaceable_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getReplaceability() const
	{
		const bool firstIsReplaceable = Pair_ :: getFirst()->isReplaceable();
		const bool secondIsReplaceable = Pair_ :: getSecond()->isReplaceable();
		if (firstIsReplaceable && secondIsReplaceable) {
			return BOTH;
		} else if (firstIsReplaceable && !secondIsReplaceable) {
			return DIRECT;
		} if (!firstIsReplaceable && secondIsReplaceable) {
			return INVERSE;
		} else {
			return NONE;
		}
	}

	template<class T_1, class T_2, int K>
	template<class A>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: cloneSubstitution()
	{
		typedef A Allocator;
		if (substitution_ != NULL) {
			substitution_ = substitution_->template clone<Allocator>();
		}
	}

	template<class T_1, class T_2, int K>
	inline const typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Substitution_*
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: findSubstitution() const
	{
		const Symbol&
			variable = *(Pair_ :: getFirst());
		return substitution_->find (variable);
	}
	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: newSubstitution (const Term_2_* const term)
	{
		if ((static_cast<kind :: Type>(kind_) == kind :: PLAIN) &&
			(!term->isReplaceable())) {
			return false;
		}
		if (!checkTermTypes (term)) {
			return false;
		}
		if (!checkTermVariables (term)) {
			return false;
		}
		Pair_ :: second() = term->getEnd();

		if (!isReacheable()) {
			return false;
		}

		const typename List_ :: Term_* const
			listTerm = List_ :: createTerm<Term_2_> (term);

		const Symbol&
			variable = *Pair_ :: first();
		Substitution_*
			delta = Substitution_ :: template
				create<allocator :: Stack>(variable, listTerm, NULL, true);

		if (substitution_ != NULL) {
			substitution_ = new Substitution_ (substitution_);
		}
		delta = delta->compose (substitution_);
		substitution_ = const_cast<Substitution_*>(substitution_)->compose (delta);
		return true;
	}
	template<class T_1, class T_2, int K>
	template<class A>
	inline const typename List<A> :: Substitution_*
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getSubstitution() const
	{
		typedef A Allocator;
		if (substitution_ == NULL) {
			return NULL;
		}
		return substitution_->createList<Allocator>();
	}
	template<class T_1, class T_2, int K>
	template<class A>
	inline const typename List<A> :: Substitution_*
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getSourceSubstitution() const
	{
		typedef A Allocator;
		if (substitution_ == NULL) {
			return NULL;
		}
		Substitution_*
			substitution = new Substitution_ (substitution_);
		substitution = substitution->template restrictTo<Iterator_1_> (Pair_ :: getFirst());
		return substitution->createList<Allocator>();
	}
	template<class T_1, class T_2, int K>
	template<class A>
	inline const typename List<A> :: Substitution_*
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getTargetSubstitution() const
	{
		typedef A Allocator;
		if (substitution_ == NULL) {
			return NULL;
		}
		Substitution_*
			substitution = new Substitution_ (substitution_);
		substitution = substitution->template restrictTo<Iterator_2_> (Pair_ :: getSecond());
		return substitution->createList<Allocator>();
	}

	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: operator = (const Unit_& unit)
	{
		Pair_ :: operator = (unit);
		substitution_  = unit.substitution_;
		level_1_ = unit.level_1_;
		level_2_ = unit.level_2_;
	}

	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_1_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getSource() const {
		return Pair_ :: getFirst();
	}
	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_2_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getTarget() const {
		return Pair_ :: getSecond();
	}
		template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_1_&
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: source() {
		return Pair_ :: first();

	}
	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_2_&
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: target() {
		return Pair_ :: second();
	}

using manipulator :: endLine;
using manipulator :: iterate;

	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: show (String& string) const
	{
		string << "source node: " << endLine;
		Pair_ :: getFirst().show (string);
		Pair_ :: getFirst()->showBack (string);
		string << endLine;

		string << "target node: " << endLine;
		Pair_ :: getSecond().show (string);
		Pair_ :: getSecond()->showBack (string);
		string << endLine;

		string << "substitution: " << endLine;
		string << *substitution_ << endLine;
		string << endLine;
	}

	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: dump() const
	{
		String string (1024);
		show (string);
		std :: cout << string << std :: flush;
	}
	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: verifyIntegrity() const
	{
		List_* expression_1 = NULL;
		List_* expression_2 = NULL;
		const Substitution_* substitution = NULL;
		bool success = true;

		Memory :: stack().push();
		try {
			success = checkResult (expression_1, expression_2, substitution);
		} catch (Error* error) {
			success = false;
			delete error;
		}
		Memory :: stack().pop();

		if (!success) {
			Memory :: stack().push();
			success = checkResult (expression_1, expression_2, substitution);
			Memory :: stack().pop();
			verificationFail (expression_1, expression_2, substitution);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T_1, class T_2, int K>
	bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: checkResult
	(
		List_*& expression_1,
		List_*& expression_2,
		const Substitution_*& substitution
	) const
	{
		const Term_1_* const
			term_1 = getSource()->getTerms().getTerminal().getLast()->getValue();
		const Term_2_* const
			term_2 = getTarget()->getTerms().getTerminal().getLast()->getValue();

		expression_1 = List_ :: createList (term_1);
		expression_2 = List_ :: createList (term_2);
		substitution = substitution_->template createList<allocator :: Stack>();

		expression_1->verifyIntegrity();
		expression_2->verifyIntegrity();

		expression_1->execute (substitution);
		expression_2->execute (substitution);

		expression_1->verifyIntegrity();
		expression_2->verifyIntegrity();

		const bool result =
		(
			expression_1->template
				coinsides<node :: List, allocator :: Stack> (*expression_2)
		);
		return result;
	}
	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: showVerification
	(
		String& string,
		const List_* expression_1,
		const List_* expression_2,
		const Substitution_* substitution
	) const
	{
		const Term_1_* const
			term_1 = getSource()->getTerms().getTerminal().getLast()->getValue();
		const Term_2_* const
			term_2 = getTarget()->getTerms().getTerminal().getLast()->getValue();

		string << "-----------------" << endLine;
		//show (string, term_1, substitution_1, "(1)");
		//show (string, term_2, substitution_2, "(2)");
		show (string, term_1, expression_1, substitution, "1");
		show (string, term_2, expression_2, substitution, "2");
		string << "-----------------" << endLine;
		string << iterate << 5 << endLine;
	}
	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: verificationFail
	(
		const List_* expression_1,
		const List_* expression_2,
		const Substitution_* substitution
	) const
	{
		Mode mode;
		//mode << Mode :: SHOW_REPLACEABILITY;
		Error* error = new Error (Error :: SEMANTIC);
		error->message() << mode << "symmetric unification error" << endLine;
		showVerification (error->message(), expression_1, expression_2, substitution);
		error->message() << iterate << 5 << endLine;
		throw error;
	}
	template<class T_1, class T_2, int K>
	template<class T1, class T2>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: show
	(
		String& string,
		const T1* term,
		const T2* expression,
		const Substitution_* substitution,
		const char* label
	) const
	{
		string << "term " << label << ":" << endLine;
		string << *term << endLine;
		string << "substitution " << label << ":" << endLine;
		if (substitution != NULL) {
			string << *substitution;
		} else {
			string << tab << "NULL" << endLine;
		}
		string << "result " << label << ":" << endLine;
		string << *expression << endLine;
		//string << "subterms " << label << ":" << endLine;
		//expression->showTerms (string); string << endLine;
		string << endLine;
		//string << iterate << 5 << endLine;
	}

	template<class T_1, class T_2, int K>
	bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: checkTermTypes (const Term_2_* const term) const
	{
		if (Pair_ :: getSecond() != term->getBegin()) {
			return false;
		}
		const mdl :: Type* const
			varType = Pair_ :: getFirst()->getType();
		const mdl :: Type* const
			termType = term->getType();
		return termType->isSuper (varType);
	}
	template<class T_1, class T_2, int K>
	bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: checkTermVariables (const Term_2_* const term) const
	{
		const Symbol variable = *(Pair_ :: getFirst());
		Iterator_2_ iterator = term->getEnd();
		while (true) {
			const Symbol symbol = *iterator;
			if (symbol == variable) {
				return false;
			}
			const Substitution_* const
				substitution = substitution_->find (symbol);
			if (substitution != NULL) {
				if (substitution->getTerm()->contains (variable)) {
					return false;
				}
			}
			if (iterator == term->getBegin()) {
				break;
			}
			-- iterator;
		}
		return true;
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T_1, class T_2, int K>
	String&
	operator << (String& string, const Unit<T_1, T_2, policy :: SYMMETRIC, K>& unit)
	{
		unit.show (string);
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_UNIT_SYM_IPP_*/

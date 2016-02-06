/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unit_DIR.ipp                    */
/* Description:     pair of iterators for the directed unification algorithm */
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
namespace exp {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2, int P, int K>
	inline
	Unit<T_1, T_2, P, K> :: Unit
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2,
		const Substitution_1_* const substitution_1,
		const Substitution_2_* const substitution_2,
		const index :: Step level_1,
		const index :: Step level_2
	) :
	Pair_
	(
		Substirator_1_ (iterator_1, substitution_1),
		Substirator_2_ (iterator_2, substitution_2)
	),
	level_1_ (level_1),
	level_2_ (level_2) {
	}
	template<class T_1, class T_2, int P, int K>
	inline
	Unit<T_1, T_2, P, K> :: Unit
	(
		const Substirator_1_ iterator_1,
		const Substirator_2_ iterator_2,
		const index :: Step level_1,
		const index :: Step level_2
	) :
	Pair_ (iterator_1, iterator_2),
	level_1_ (level_1),
	level_2_ (level_2) {
	}
	template<class T_1, class T_2, int P, int K>
	inline
	Unit<T_1, T_2, P, K> :: Unit (const Unit& unit) :
	Pair_ (unit),
	level_1_ (unit.level_1_),
	level_2_ (unit.level_2_) {
	}
	template<class T_1, class T_2, int P, int K>
	inline
	Unit<T_1, T_2, P, K> :: Unit () :
	Pair_ (),
	level_1_ (index :: undefined :: STEP),
	level_2_ (index :: undefined :: STEP) {
	}

	template<class T_1, class T_2, int P, int K>
	inline typename Unit<T_1, T_2, P, K> :: InverseUnit_
	Unit<T_1, T_2, P, K> :: inverse () const
	{
		return InverseUnit_
		(
			Pair_ :: getSecond(),
			Pair_ :: getFirst(),
			level_2_,
			level_1_
		);
	}

	template<class T_1, class T_2, int P, int K>
	inline typename Unit<T_1, T_2, P, K> :: Iterator_2_
	Unit<T_1, T_2, P, K> :: follow (bool& substituted) const
	{
		Substirator_1_ source = Pair_ :: getFirst();
		Substirator_2_ target = Pair_ :: getSecond();
		return source.follow (target, substituted);
	}
	template<class T_1, class T_2, int P, int K>
	inline bool
	Unit<T_1, T_2, P, K> :: isReacheable() const
	{
		return
			Pair_ :: getFirst()->isReacheable (level_1_) &&
			Pair_ :: getSecond()->isReacheable (level_2_);
	}
	template<class T_1, class T_2, int P, int K>
	inline bool
	Unit<T_1, T_2, P, K> :: isReplaceable() const {
		return Pair_ :: getFirst()->isReplaceable();
	}
	template<class T_1, class T_2, int P, int K>
	inline bool
	Unit<T_1, T_2, P, K> :: isFixed() const
	{
		return
			Pair_ :: getFirst()->isFixed() &&
			Pair_ :: getSecond()->isFixed();
	}
	template<class T_1, class T_2, int P, int K>
	typename Unit<T_1, T_2, P, K> :: Replaceable_
	Unit<T_1, T_2, P, K> :: getReplaceability() const
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

	template<class T_1, class T_2, int P, int K>
	template<class A>
	inline void
	Unit<T_1, T_2, P, K> :: cloneSubstitution()
	{
		typedef A Allocator;
		Pair_ :: first().cloneSubstitution<Allocator>();
		Pair_ :: second().cloneSubstitution<Allocator>();
	}

	template<class T_1, class T_2, int P, int K>
	inline bool
	Unit<T_1, T_2, P, K> :: newSubstitution (const Term_2_* term)
	{
		if ((static_cast<kind :: Type>(kind_) == kind :: PLAIN) &&
			(!term->isReplaceable())) {
			return false;
		}
		if (!checkTermTypes (term)) {
			return false;
		}
		const Substitution_1_* const
			next = Pair_ :: first().getSubstitution();
		const Substitution_1_* const
			delta = Pair_ :: first().newSubstitution (term);
		Pair_ :: second() = term->getEnd();
		delta->setNext (next);
		return true;
	}

	template<class T_1, class T_2, int P, int K>
	void
	Unit<T_1, T_2, P, K> :: operator = (const Unit_ unit)
	{
		Pair_ :: operator = (unit);
		level_1_ = unit.level_1_;
		level_2_ = unit.level_2_;
	}

	template<class T_1, class T_2, int P, int K>
	inline typename Unit<T_1, T_2, P, K> :: Substirator_1_
	Unit<T_1, T_2, P, K> :: getSource() const {
		return Pair_ :: getFirst();
	}
	template<class T_1, class T_2, int P, int K>
	inline typename Unit<T_1, T_2, P, K> :: Substirator_2_
	Unit<T_1, T_2, P, K> :: getTarget() const {
		return Pair_ :: getSecond();
	}
		template<class T_1, class T_2, int P, int K>
	inline typename Unit<T_1, T_2, P, K> :: Substirator_1_&
	Unit<T_1, T_2, P, K> :: source() {
		return Pair_ :: first();
	}
	template<class T_1, class T_2, int P, int K>
	inline typename Unit<T_1, T_2, P, K> :: Substirator_2_&
	Unit<T_1, T_2, P, K> :: target() {
		return Pair_ :: second();
	}

using manipulator :: endLine;
using manipulator :: iterate;

	template<class T_1, class T_2, int P, int K>
	void
	Unit<T_1, T_2, P, K> :: show (String& string) const
	{
		string << "source node: " << endLine;
		Pair_ :: getFirst().show (string);
		string << endLine;

		string << "target node: " << endLine;
		Pair_ :: getSecond().show (string);
		string << endLine;
	}

	template<class T_1, class T_2, int P, int K>
	void
	Unit<T_1, T_2, P, K> :: dump() const
	{
		String string (1024);
		show (string);
		std :: cout << string << std :: flush;
	}
	template<class T_1, class T_2, int P, int K>
	void
	Unit<T_1, T_2, P, K> :: verifyIntegrity() const
	{
		_List* expression_1 = NULL;
		_List* expression_2 = NULL;
		const _Substitution* sub_1 = NULL;
		const _Substitution* sub_2 = NULL;
		bool success = true;

		Memory :: stack().push();
		try {
			success = checkResult (expression_1, expression_2, sub_1, sub_2);
		} catch (Error* error) {
			success = false;
			delete error;
		}
		Memory :: stack().pop();
		if (!success) {
			verificationFail (expression_1, expression_2, sub_1, sub_2);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T_1, class T_2, int P, int K>
	bool
	Unit<T_1, T_2, P, K> :: checkResult
	(
		_List*& expression_1,
		_List*& expression_2,
		const _Substitution*& sub_1,
		const _Substitution*& sub_2
	) const
	{
		const Term_1_* const
			term_1 = getSource()->getTerms().getTerminal().getLast()->getValue();
		const Term_2_* const
			term_2 = getTarget()->getTerms().getTerminal().getLast()->getValue();
		const Substitution_1_* const
			substitution_1 = getSource().getSubstitution();
		const Substitution_2_* const
			substitution_2 = getTarget().getSubstitution();

		expression_1 = _List :: createList (term_1);
		expression_2 = _List :: createList (term_2);
		sub_1 = substitution_1->template createList<allocator :: Stack>();
		sub_2 = substitution_2->template createList<allocator :: Stack>();

		expression_1->execute (sub_1);
		expression_2->execute (sub_2);

		const bool result =
		(
			expression_1->template
				coinsides<node :: List, allocator :: Stack> (*expression_2)
		);
		return result;
	}
	template<class T_1, class T_2, int P, int K>
	void
	Unit<T_1, T_2, P, K> :: verificationFail
	(
		const _List* expression_1,
		const _List* expression_2,
		const _Substitution* sub_1,
		const _Substitution* sub_2
	) const
	{
		const Term_1_* const
			term_1 = getSource()->getTerms().getTerminal().getLast()->getValue();
		const Term_2_* const
			term_2 = getTarget()->getTerms().getTerminal().getLast()->getValue();
		const Substitution_1_* const
			substitution_1 = getSource().getSubstitution();
		const Substitution_2_* const
			substitution_2 = getTarget().getSubstitution();

		Error* error = new Error (Error :: SEMANTIC);
		error->message() << "directed unification error" << endLine;
		error->message() << "-----------------" << endLine;
		show (error->message(), term_1, substitution_1, "(1)");
		show (error->message(), term_2, substitution_2, "(2)");
		show (error->message(), expression_1, sub_1, "1");
		show (error->message(), expression_2, sub_2, "2");
		throw error;
	}
	template<class T_1, class T_2, int P, int K>
	template<class T, class S>
	void
	Unit<T_1, T_2, P, K> :: show
	(
		String& string,
		const T* term,
		const S* substitution,
		const char* label
	) const
	{
		string << "term " << label << ":" << endLine;
		string << *term << endLine;
		string << "subterms " << label << ":" << endLine;
		term->showTerms (string); string << endLine;
		string << "substitution " << label << ":" << endLine;
		if (substitution != NULL) {
			string << *substitution << endLine;
		} else {
			string << tab << "NULL" << endLine;
		}
		string << iterate << 5 << endLine;
	}

	template<class T_1, class T_2, int P, int K>
	bool
	Unit<T_1, T_2, P, K> :: checkTermTypes (const Term_2_* const term) const
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

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T_1, class T_2, int P, int K>
	String&
	operator << (String& string, const Unit<T_1, T_2, P, K>& unit)
	{
		unit.show (string);
		return string;
	}
}
}
}
}



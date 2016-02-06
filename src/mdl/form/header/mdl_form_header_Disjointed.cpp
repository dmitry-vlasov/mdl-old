/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Disjointed.cpp                           */
/* Description:     disjointed variable restriction                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Disjointed :: Disjointed
	(
		const vector :: value :: Literal& literalVector,
		mdl :: Theory* theory
	) :
	literalVector_ (literalVector) {
	}
	inline
	Disjointed :: Disjointed
	(
		value :: Literal x,
		value :: Literal y,
		mdl :: Theory* theory
	) :
	literalVector_ (2)
	{
		literalVector_.add (x);
		literalVector_.add (y);
	}
	Disjointed :: ~ Disjointed() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// mdl :: header :: Disjointed implementation
	bool
	Disjointed :: noRestriction() const {
		return (literalVector_.getSize() < 2);
	}
	void
	Disjointed :: check
	(
		const array :: Substitution* substitution,
		const mdl :: Assertion* theorem
	) const
	{
		if (literalVector_.getSize() < 2) {
			return;
		}
		for (index :: Arity i = 0; i < literalVector_.getSize() - 1; ++ i) {
			const value :: Literal x = literalVector_.getValue (i);
			for (index :: Arity j = i + 1; j < literalVector_.getSize(); ++ j) {
				const value :: Literal y = literalVector_.getValue (j);

				try {
					checkPair (substitution, theorem, x, y);
				} catch (Error* error) {
					error->message() << tab << "disjoined pair: ";
					error->message() << Table :: literals()->get (x) << " and ";
					error->message() << Table :: literals()->get (y) << endLine;
					throw error;
				}
			}
		}
	}
	bool
	Disjointed :: check
	(
		const list :: Substitution* substitution,
		const mdl :: Assertion* theorem
	) const
	{
		if (literalVector_.getSize() < 2) {
			return true;
		}
		for (index :: Arity i = 0; i < literalVector_.getSize() - 1; ++ i) {
			const value :: Literal x = literalVector_.getValue (i);
			for (index :: Arity j = i + 1; j < literalVector_.getSize(); ++ j) {
				const value :: Literal y = literalVector_.getValue (j);

				if (!checkPair (substitution, theorem, x, y)) {
					return false;
				}
			}
		}
		return true;
	}
	bool
	Disjointed :: contains (const value :: Literal literal_1) const
	{
		for (index :: Arity i = 0; i < literalVector_.getSize(); i ++) {
			const value :: Literal literal_2 = literalVector_.getValue (i);
			if (literal_2 == literal_1) {
				return true;
			}
		}
		return false;
	}

	bool
	Disjointed :: isMoreRestrictive (const mdl :: header :: Disjointed* disjointed) const {
		return disjointed->isLessRestrictive (this);
	}
	bool
	Disjointed :: isLessRestrictive (const mdl :: header :: Disjointed* disjointed) const
	{
		for (index :: Arity i = 0; i < literalVector_.getSize(); i ++) {
			const value :: Literal literal = literalVector_.getValue (i);
			if (!disjointed->contains (literal)) {
				return false;
			}
		}
		return true;
	}

	// object :: Writable implementation
	void
	Disjointed :: translate (String& string) const
	{
		if (literalVector_.getSize() < 2) {
			return;
		}
		string << :: smm :: Token :: disjointed_<< space;
		for (index :: Arity i = 0; i < literalVector_.getSize(); i ++) {
			const value :: Literal literal = literalVector_.getValue (i);
			string << Table :: literals()->get (literal) << space;
		}
		string << :: smm :: Token :: end_ << space;
	}
	void
	Disjointed :: replicate (String& string) const
	{
		for (index :: Arity i = 0; i < literalVector_.getSize(); i ++) {
			const value :: Literal literal = literalVector_.getValue (i);
			string << Table :: literals()->get (literal);
			if (i != literalVector_.getSize() - 1) {
				string << space;
			}
		}
	}

	// object :: Object implementation
	void
	Disjointed :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjointed :: getVolume() const {
		return literalVector_.getVolume();
	}
	Size_t
	Disjointed :: getSizeOf() const {
		return sizeof (Disjointed);
	}

	/****************************
	 *		Private members
	 ****************************/

	// verification routines
	void
	Disjointed :: checkPair
	(
		const array :: Substitution* substitution,
		const mdl :: Assertion* theorem,
		const value :: Literal x,
		const value :: Literal y
	) const
	{
		const array :: Substitution*
			xImage = substitution->find (x);
		if (xImage == NULL) {
			return;
		}
		const array :: Substitution*
			yImage = substitution->find (y);
		if (yImage == NULL) {
			return;
		}
		try {
			checkTerms (xImage->getTerm(), yImage->getTerm(), theorem);
		} catch (Error* error) {
			error->message() << tab << "substitution 1: " << endLine;
			error->message() << *xImage << endLine;
			error->message() << tab << "substitution 2: " << endLine;
			error->message() << *yImage << endLine;
			throw error;
		}
	}
	void
	Disjointed :: checkTerms
	(
		const array :: Term* xTerm,
		const array :: Term* yTerm,
		const mdl :: Assertion* theorem
	) const
	{
		typedef
			array :: Term :: const_Iterator_
			const_Iterator;
		const_Iterator i = xTerm->getBegin();
		while (true) {
			const_Iterator j = yTerm->getBegin();
			while (true) {
				if ((i->isVariable()) && (j->isVariable())) {
					checkSymbols (*i, *j, xTerm, yTerm, theorem);
				}
				if (j == yTerm->getEnd()) {
					break;
				}
				++ j;
			}
			if (i == xTerm->getEnd()) {
				break;
			}
			++ i;
		}
	}
	void
	Disjointed :: checkSymbols
	(
		const Symbol& symbol_1,
		const Symbol& symbol_2,
		const array :: Term* xTerm,
		const array :: Term* yTerm,
		const mdl :: Assertion* theorem
	) const
	{
		if (symbol_1 == symbol_2) {
			Error* error = new Error (Error :: DISJOINTEDS);
			error->message() << "disjointed variables violation." << endLine;
			error->message() << "variable " << symbol_1 << " is common for:" << endLine;
			error->message() << tab << "term 1: " << *xTerm << endLine;
			error->message() << tab << "term 2: " << *yTerm << endLine;
			error->message() << endLine;
			throw error;
		}
		if (!Config :: translate()) {
			const mdl :: Variables* const
				variables = theorem->getVariables();
			if (!variables->contain (symbol_1) || !variables->contain (symbol_2)) {
				return;
			}
		}
		if (!theorem->getDisjointeds()->check (symbol_1, symbol_2)) {
			Error* error = new Error (Error :: DISJOINTEDS);
			error->message() << "disjointed variables violation." << endLine;
			error->message() << "variables " << symbol_1 << " and " << symbol_2 << " are not inherently disjointed ";
			error->message() << "in theorem ";
			theorem->replicateName (error->message());
			error->message() << endLine;
			error->message() << *theorem << endLine;
			error->message() << endLine;
			throw error;
		}
	}

	// prover routines
	bool
	Disjointed :: checkPair
	(
		const list :: Substitution* substitution,
		const mdl :: Assertion* theorem,
		const value :: Literal x,
		const value :: Literal y
	) const
	{
		const list :: Substitution*
			xImage = substitution->find (x);
		if (xImage == NULL) {
			return true;
		}
		const list :: Substitution*
			yImage = substitution->find (y);
		if (yImage == NULL) {
			return true;
		}
		return checkTerms<list :: Term>
		(
			theorem,
			xImage->getTerm(),
			yImage->getTerm()
		);
	}
	template<class T>
	bool
	Disjointed :: checkTerms
	(
		const mdl :: Assertion* theorem,
		const T* xTerm,
		const T* yTerm
	) const
	{
		typedef T Term;
		typedef
			typename Term :: const_Iterator_
			const_Iterator;
		const_Iterator i = xTerm->getBegin();
		while (true) {
			const_Iterator j = yTerm->getBegin();
			while (true) {
				if ((i->isVariable()) && (j->isVariable())) {
					if (!checkSymbols (theorem, *i, *j)) {
						return false;
					}
				}
				if (j == yTerm->getEnd()) {
					break;
				}
				++ j;
			}
			if (i == xTerm->getEnd()) {
				break;
			}
			++ i;
		}
		return true;
	}
	bool
	Disjointed :: checkSymbols
	(
		const mdl :: Assertion* theorem,
		const Symbol& symbol_1,
		const Symbol& symbol_2
	) const
	{
		if (symbol_1 == symbol_2) {
			return false;
		}
		if (!Config :: translate()) {
			const mdl :: Variables*
				variables = theorem->getVariables();
			if (!variables->contain (symbol_1) || !variables->contain (symbol_2)) {
				return true;
			}
		}
		return theorem->getDisjointeds()->check (symbol_1, symbol_2);
	}
}
}
}



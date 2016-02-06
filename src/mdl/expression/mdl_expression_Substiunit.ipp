/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Substiunit.ipp                            */
/* Description:     substitution unit class                                  */
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
	inline
	Substiunit<T> :: Substiunit() :
	variable_ (),
	term_ (NULL),
	ownsTerm_ (false) {
	}
	template<class T>
	inline
	Substiunit<T> :: Substiunit
	(
		const Symbol& variable,
		const Term_* term,
		const bool ownsTerm
	) :
	variable_ (variable),
	term_ (term),
	ownsTerm_ (ownsTerm) {
	}
	template<class T>
	inline
	Substiunit<T> :: ~ Substiunit()
	{
		if (ownsTerm_ && (term_ != NULL)) {
			term_->deleteNodes();
			term_ = NULL;
		}
	}

	template<class T>
	void
	Substiunit<T> :: inverse()
	{
		if (!term_->isVariable()) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "impossible to inverse:" << endLine;
			error->message() << *this << endLine;
			throw error;
		}
		typedef
			typename Iterator_ :: Node_
			Node_;
		const Symbol
			inverseVariable = Symbol (*term_->getBegin());
		Node_*
			inverseVarNode = new Node_ (variable_);
		const Iterator_
			iterator (inverseVarNode);
		const Term_*
			inverseTerm = new Term_ (iterator, variable_.getType());
		inverseVarNode->terms().initial().addFirst (inverseTerm);
		inverseVarNode->terms().terminal().addFirst (inverseTerm);
		variable_ = inverseVariable;
		if (ownsTerm_) {
			term_->deleteNodes();
		}
		term_ = inverseTerm;
		ownsTerm_ = true;
	}

	template<class T>
	inline bool
	Substiunit<T> :: isUndefined() const {
		return (variable_.isUndefined() || (term_ == NULL));
	}
	template<class T>
	inline bool
	Substiunit<T> :: isTrivial() const {
		return term_->isSymbol (variable_);
	}
	template<class T>
	inline bool
	Substiunit<T> :: isGoodMgu() const
	{
		if (isUndefined()) {
			return false;
		}
		if (!variable_.isReplaceable()) {
			return false;
		}
		const mdl :: Type* const
			varType = variable_.getType();
		const mdl :: Type* const
			termType = term_->getType();
		if (!termType->isSuper (varType)) {
			return false;
		}
		return !(term_->contains (variable_));
	}
	template<class T>
	inline bool
	Substiunit<T> :: isEqualLiteraly (const Substiunit& unit) const
	{
		const bool varsAreTheSame = variable_.isEqualLiteraly (unit.variable_);
		const bool termsAreTheSame = term_->isEqualLiteraly (*unit.term_);
		return (varsAreTheSame && termsAreTheSame);
	}
	template<class T>
	inline bool
	Substiunit<T> :: operator == (const Substiunit& unit) const
	{
		const bool varsAreTheSame = (variable_ == unit.variable_);
		const bool termsAreTheSame = (*term_ == *unit.term_);
		return (varsAreTheSame && termsAreTheSame);
	}
	template<class T>
	inline bool
	Substiunit<T> :: operator != (const Substiunit& unit) const {
		return !(operator == (unit));
	}
	template<class T>
	inline void
	Substiunit<T> :: operator = (const Substiunit& unit)
	{
		const_cast<Symbol&>(variable_) = unit.variable_;
		term_ = unit.term_;
		const_cast<bool&>(ownsTerm_) = unit.ownsTerm_;
	}
	template<class T>
	inline bool
	Substiunit<T> :: isEqual (const Substiunit& unit) const
	{
		return
			(variable_ == unit.variable_) &&
			(*term_ == *unit.term_);
	}

	template<class T>
	inline value :: Integer
	Substiunit<T> :: getLength() const {
		return term_->getLength();
	}
	template<class T>
	inline const Symbol&
	Substiunit<T> :: getVariable() const {
		return variable_;
	}
	template<class T>
	inline const typename Substiunit<T> :: Term_*
	Substiunit<T> :: getTerm() const {
		return term_;
	}

	template<class T>
	inline void
	Substiunit<T> :: verifyIntegrity() const
	{
		if (term_ == NULL) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "null term in substitution unit.";
			throw error;
		}
		term_->verifyIntegrity();
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: endLine;

	// object :: Object implementation
	template<class T>
	inline void
	Substiunit<T> :: commitSuicide() {
		delete this;
	}
	template<class T>
	inline Size_t
	Substiunit<T> :: getVolume() const
	{
		Size_t volume = 0;
		if (ownsTerm_) {
			volume += term_->getExpressionVolume();
		}
		return volume;
	}
	template<class T>
	inline Size_t
	Substiunit<T> :: getSizeOf() const {
		return sizeof (Substiunit);
	}
	template<class T>
	void
	Substiunit<T> :: show (String& string) const
	{
		variable_.show (string);
		string << " / ";
		if (Config :: expressionsMultyline()) {
			const value :: Integer length = getLength();
			if (getLength() >= Config :: multylineMaxWidth()) {
				string << endLine;
			}
			String reversed (256);
			term_->writeMultylineBackward (reversed, Indent(), 0);
			reversed.reverse();
			string << reversed;
		} else {
			const value :: Integer length = getLength();
			Symbol buffer [length];

			const_Iterator_ iterator = term_->getEnd();
			for (value :: Integer i = 0; i < length; ++ i) {
				buffer [i] = *iterator;
				-- iterator;
			}
			for (value :: Integer i = 0; i < length; ++ i) {
				buffer [length - i - 1].show (string);
				string << space;
			}
		}
	}
	template<class T>
	void
	Substiunit<T> :: dump() const
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
	inline
	Substiunit<T> :: Substiunit (const Substiunit& unit) :
	variable_ (unit.variable_),
	term_ (unit.term_),
	ownsTerm_ (unit.ownsTerm_) {
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T>
	String&
	operator << (String& string, const Substiunit<T>& substiunit)
	{
		substiunit.show (string);
		return string;
	}
	template<class T>
	std :: ostream&
	operator << (std :: ostream& os, const Substiunit<T>& substiunit)
	{
		String* string = new String (1024);
		os << (*string << substiunit);
		string->commitSuicide();
		return os;
	}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Symbol.ipp                                */
/* Description:     expression symbol                                        */
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

	inline
	Symbol :: Symbol() :
	literal_ (value :: undefined :: LITERAL),
	isReplaceable_ (false),
	type_ (NULL) {
	}
	inline
	Symbol :: Symbol (const value :: Literal literal) :
	literal_ (literal),
	isReplaceable_ (false),
	type_ (NULL) {
	}
	inline
	Symbol :: Symbol (const Symbol& symbol) :
	literal_ (symbol.literal_),
	isReplaceable_ (symbol.isReplaceable_),
	type_ (symbol.type_){
	}
	inline
	Symbol :: ~ Symbol() {
	}

	inline value :: Literal
	Symbol :: getLiteral() const {
		return literal_;
	}
	inline value :: Literal
	Symbol :: getLambda() {
		return lambda_;
	}
	inline const mdl :: Type*
	Symbol :: getType() const {
		return type_;
	}

	inline bool
	Symbol :: isLambda() const {
		return (literal_ == lambda_);
	}
	inline bool
	Symbol :: isReplaceable() const {
		return isReplaceable_;
	}
	inline bool
	Symbol :: isFixed() const {
		return !isReplaceable_;
	}
	inline bool
	Symbol :: isUndefined() const {
		return (literal_ == value :: undefined :: LITERAL);
	}
	inline bool
	Symbol :: isConstant() const {
		return (type_ == NULL);
	}
	inline bool
	Symbol :: isVariable() const {
		return !isConstant();
	}
	inline bool
	Symbol :: isEqualLiteraly (const char* string) const
	{
		const value :: Literal
			literal =  Table :: literals()->find (string);
		return (literal_ == literal);
	}
	inline bool
	Symbol :: isEqualLiteraly (const value :: Literal literal) const {
		return (literal_ == literal);
	}
	inline bool
	Symbol :: isEqualLiteraly (const Symbol& symbol) const {
		return (literal_ == symbol.literal_);
	}

	inline bool
	Symbol :: operator == (const Symbol& symbol) const
	{
		bool result = true;
		result = result && (literal_ == symbol.literal_);
		result = result && (isReplaceable_ == symbol.isReplaceable_);
		result = result && (type_ == symbol.type_);
		return result;
	}
	inline bool
	Symbol :: operator != (const Symbol& symbol) const {
		return !operator == (symbol);
	}
	inline void
	Symbol :: operator = (const Symbol& symbol)
	{
		literal_ = symbol.literal_;
		isReplaceable_ = symbol.isReplaceable_;
		type_ = symbol.type_;
	}

	inline void
	Symbol :: setLambda() {
		literal_ = lambda_;
	}
	inline void
	Symbol :: setLiteral (const value :: Literal literal) {
		literal_ = literal;
	}
	inline void
	Symbol :: setType (mdl :: Type* type) {
		type_ = type;
	}
	inline void
	Symbol :: setReplaceable (const bool isReplaceable) {
		isReplaceable_ = isReplaceable;
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	String&
	operator << (String& string, const Symbol& symbol)
	{
		symbol.write (string);
		return string;
	}
	std :: ostream&
	operator << (std :: ostream& os, const Symbol& symbol)
	{
		String string (64);
		return os << (string << symbol);
	}

	bool
	operator < (const Symbol& s_1, const Symbol& s_2)
	{
		if (s_1.literal_ < s_2.literal_) {
			return true;
		} else if (s_1.literal_ > s_2.literal_) {
			return false;
		} else {
			if (s_1.isReplaceable_ < s_2.isReplaceable_) {
				return true;
			} else if (s_1.isReplaceable_ > s_2.isReplaceable_) {
				return false;
			} else {
				if (s_1.type_ < s_2.type_) {
					return true;
				} else if (s_1.type_ > s_2.type_) {
					return false;
				} else {
					return false;
				}
			}
		}
	}
	inline bool
	operator <= (const Symbol& s_1, const Symbol& s_2) {
		return operator < (s_1, s_2) || (s_1 == s_2);
	}
	inline bool
	operator > (const Symbol& s_1, const Symbol& s_2) {
		return operator < (s_2, s_1);
	}
	inline bool
	operator >= (const Symbol& s_1, const Symbol& s_2) {
		return operator <= (s_2, s_1);
	}
}
}



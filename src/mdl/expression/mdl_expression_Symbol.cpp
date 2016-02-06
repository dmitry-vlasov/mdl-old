/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Symbol.cpp                                */
/* Description:     expression symbol                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/auxiliary/mdl_auxiliary.hpp"
#include "mdl/math/mdl_math.hpp"
#include "mdl/expression/mdl_expression_Symbol.hpp"
#include "mdl/expression/mdl_expression_Mode.hpp"

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: space;
using manipulator :: underline;

	inline const String&
	Symbol :: getString () const {
		return Table :: literals()->get (literal_);
	}

	void
	Symbol :: build (const object :: Typing* typing, bool makeFixed)
	{
		type_ = typing->getType (literal_);
		if (type_ == NULL && !(Math :: constants()->contain (literal_))) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "literal \"" << Table :: literals()->get (literal_) << "\"" << space;
			error->message() << "is not declared." << endLine;
			throw error;
		}
		if (type_ == NULL || makeFixed) {
			isReplaceable_ = false;
		}
	}
	void
	Symbol :: write (String& string) const
	{
		if (isUndefined()) {
			string << "<undefined>";
		} else if (isLambda()) {
			string << "<lambda>";
		} else {
			if (Config :: translate()) {
				string << *Table :: literals()->getAscii (literal_);
			} else {
				string << Table :: literals()->get (literal_);
			}
		}
	}
	void
	Symbol :: writeReversed (String& string) const
	{
		String symbol (32);
		write (symbol);
		symbol.reverse();
		string << symbol;
	}

	// object :: Object implementation
	inline void
	Symbol :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Symbol :: getVolume () const {
		return 0;
	}
	inline Size_t
	Symbol :: getSizeOf () const {
		return sizeof (Symbol);
	}
	void
	Symbol :: show (String& string) const
	{
		Mode mode (string);
		if (literal_ == value :: undefined :: LITERAL) {
			string << "<undefined>";
		} else if (literal_ == lambda_) {
			string << "<lambda>";
		} else {
			string << Table :: literals()->get (literal_);
		}
		if (type_ != NULL) {
			if (mode.getValue (Mode :: SHOW_REPLACEABILITY)) {
				if (!isReplaceable_) {
					if (literal_ == value :: undefined :: LITERAL) {
						string << "#";
					} else {
						string << Table :: literals()->get (literal_);
					}
				}
			}
			if (mode.getValue (Mode :: SHOW_TYPE)) {
				string << underline;
				type_->replicateName (string);
			}
		}
	}
	void
	Symbol :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 16
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string << std :: flush;
	}

	/*************************************
	 *		Static private attributes
	 *************************************/

	const value :: Literal
		Symbol :: lambda_ = value :: undefined :: LITERAL - 1;
}
}



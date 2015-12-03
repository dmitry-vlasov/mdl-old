/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Constants.cpp                                    */
/* Description:     global metamath constants container                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MATH_CONSTANTS_CPP_
#define MM_MATH_CONSTANTS_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "math/mm_math.hpp"

namespace mm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	Constants :: Constants() :
	constantSet_ (INITIAL_CONSTANTS_CAPACITY),
	constantCount_ (0),

	// base alphabet symbols
	turnstile_ (value :: undefined :: LITERAL),
	openBracket_ (value :: undefined :: LITERAL),
	closeBracket_ (value :: undefined :: LITERAL),
	openBrace_ (value :: undefined :: LITERAL),
	closeBrace_ (value :: undefined :: LITERAL),
	equality_ (value :: undefined :: LITERAL),
	equivalence_ (value :: undefined :: LITERAL),

	// base type symbols
	wff_ (value :: undefined :: LITERAL),
	set_ (value :: undefined :: LITERAL),
	class_ (value :: undefined :: LITERAL) {
	}
	Constants :: ~ Constants() {
	}

	void
	Constants :: add (const mm :: source :: Constants* const constants)
	{
		constants->addTo (constantSet_);
		initConstants();
		++ constantCount_;
	}
	bool
	Constants :: contain (const value :: Literal symb)
	{
		const index :: Literal
			index = constantSet_.find (symb);
		return (index != index :: undefined :: LITERAL);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Constants :: commitSuicide() {
		delete this;
	}
	Size_t
	Constants :: getVolume() const {
		return constantSet_.getVolume();
	}
	Size_t
	Constants :: getSizeOf() const {
		return sizeof (Constants);
	}
	void
	Constants :: show (String& string) const
	{
		string << tab << "constants   " << tab;
		string << '-' << space << constantCount_ << endLine;
	}

	/*********************************
	 *		Private members
	 *********************************/

	void
	Constants :: initConstants ()
	{
		if (turnstile_ == value :: undefined :: LITERAL) {
			turnstile_ = Table :: literals()->find ("|-");
		}
		if (openBracket_ == value :: undefined :: LITERAL) {
			openBracket_ = Table :: literals()->find ("(");
		}
		if (closeBracket_ == value :: undefined :: LITERAL) {
			closeBracket_ = Table :: literals()->find (")");
		}
		if (openBrace_ == value :: undefined :: LITERAL) {
			openBrace_ = Table :: literals()->find ("{");
		}
		if (closeBrace_ == value :: undefined :: LITERAL) {
			closeBrace_ = Table :: literals()->find ("}");
		}
		if (equality_ == value :: undefined :: LITERAL) {
			equality_ = Table :: literals()->find ("=");
		}
		if (equivalence_ == value :: undefined :: LITERAL) {
			equivalence_ = Table :: literals()->find ("<->");
		}

		if (wff_ == value :: undefined :: LITERAL) {
			wff_ = Table :: literals()->find ("wff");
		}
		if (set_ == value :: undefined :: LITERAL) {
			set_ = Table :: literals()->find ("set");
		}
		if (class_ == value :: undefined :: LITERAL) {
			class_ = Table :: literals()->find ("class");
		}
	}
}
}

#endif /*MM_MATH_CONSTANTS_CPP_*/

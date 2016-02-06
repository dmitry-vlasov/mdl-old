/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Comments.cpp                                    */
/* Description:     comment holder class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/auxiliary/mdl_auxiliary.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "smm/lexer/smm_lexer_Token.hpp"

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	Comments :: Comments (const Lexer :: Comments_& comments, const bool multyLine) :
	vector_ (comments.getSize()),
	multyLine_ (multyLine)
	{
		for (Index_ i = 0; i < comments.getSize(); ++ i) {
			String* comment = new String (*comments.get (i));
			vector_.add (comment);
		}
	}
	Comments :: Comments (const char* commentText, const bool multyLine) :
	vector_ (INITIAL_VECTOR_CAPACITY),
	multyLine_ (multyLine)
	{
		String* comment = new String (commentText);
		vector_.add (comment);
	}
	Comments :: Comments (const bool multyLine) :
	vector_ (INITIAL_VECTOR_CAPACITY),
	multyLine_ (multyLine) {
	}
	Comments :: ~ Comments() {
	}

using manipulator :: endLine;
using manipulator :: space;

	// object :: Writable implementation
	void
	Comments :: translate (String& string) const
	{
		for (Index_ i = 0; i < vector_.getSize(); ++ i) {
			string << smm :: Token :: commentBegin_ << space;
			string << *vector_.getValue (i) << space;
			string << smm :: Token :: commentEnd_;
			if (multyLine_) {
				string << endLine;
			} else {
				string << space;
			}
		}
	}
	void
	Comments :: replicate (String& string) const
	{
		if (Config :: hideComments()) {
			return;
		}
		for (Index_ i = 0; i < vector_.getSize(); ++ i) {
			string << mdl :: Token :: commentBegin_;
			string << *vector_.getValue (i);
			string << mdl :: Token :: commentEnd_;
			if (multyLine_) {
				string << endLine;
			} else {
				string << space;
			}
		}
	}

	// object :: Object implementation
	void
	Comments :: commitSuicide() {
		delete this;
	}
	Size_t
	Comments :: getVolume() const {
		return vector_.getVolume();
	}
	Size_t
	Comments :: getSizeOf() const {
		return sizeof (Comments);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}



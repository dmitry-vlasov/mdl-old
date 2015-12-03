/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Comments.cpp                                  */
/* Description:     comment holder class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_COMMENTS_CPP_
#define DEL_SOURCE_COMMENTS_CPP_

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Comments :: Comments (const Lexer :: Comments_& comments, const bool multyLine) :
	vector_ (comments.getSize()),
	multyLine_ (multyLine)
	{
		for (Index_ i = 0; i < comments.getSize(); ++ i) {
			const String* comment = new String (*comments.get (i));
			vector_.add (comment);
		}
	}
	Comments :: ~ Comments() {
	}

using manipulator :: endLine;
using manipulator :: space;

	// object :: Writable implementation
	void
	Comments :: translate (String& string) const {
		replicate (string);
	}
	void
	Comments :: replicate (String& string) const
	{
		if (Config :: removeComments()) {
			return;
		}
		for (Index_ i = 0; i < vector_.getSize(); ++ i) {
			string << del :: Token :: commentBegin_;
			string << *vector_.getValue (i);
			string << del :: Token :: commentEnd_;
			if (multyLine_) {
				string << endLine;
			} else {
				string << space;
			}
		}
		string << endLine;
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

#endif /*DEL_SOURCE_COMMENTS_CPP_*/

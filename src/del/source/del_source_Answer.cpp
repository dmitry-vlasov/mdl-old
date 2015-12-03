/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Answer.cpp                                    */
/* Description:     answer                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_ANSWER_CPP_
#define DEL_SOURCE_ANSWER_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source_Answer.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Answer :: Answer
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory name,
		const bool isPositive,
		const del :: Formula* formula
	) :
	location_ (location),
	comments_ (comments),
	formula_ (formula),
	name_ (name),
	isPositive_ (isPositive),
	theory_ (Math :: theories()->get (name_)) {
	}
	Answer :: ~ Answer()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (formula_);
	}

	// del :: Answer implementation
	bool
	Answer :: isPositive() const {
		return isPositive_;
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Answer :: replicate (String& string) const
	{
		string << location_.getIndent();
		string << Token :: solution_ << space;
		string << Table :: theories()->get (name_) << space;
		string << (isPositive_? Token :: models_ : Token :: does_not_model_) << space;
		formula_->replicate (string);
		string << space << Token :: assertion_ << endLine;
	}
	void
	Answer :: translate (String& string) const {
		replicate (string);
	}
	void
	Answer :: write (String& string) const
	{
		if (Config :: removeComments()) {
			string << "/****************************************/" << endLine;
			string << "/*         answer to the question       */" << endLine;
			string << "/****************************************/" << endLine;
			string << endLine;
		}
		theory_->replicate (string);
		replicate (string);
		string << endLine << endLine;
	}

	// object :: Object implementation
	void
	Answer :: commitSuicide() {
		delete this;
	}
	Size_t
	Answer :: getSizeOf() const {
		return sizeof (Answer);
	}
	Size_t
	Answer :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (formula_);
		return volume;
	}
}
}

#endif /*DEL_SOURCE_ANSWER_CPP_*/

/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Minimization.cpp                              */
/* Description:     answer                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_MINIMIZATION_CPP_
#define DEL_SOURCE_MINIMIZATION_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source_Minimization.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Minimization :: Minimization
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory theoryName,
		const value :: Theory minimizedTheoryName
	) :
	location_ (location),
	comments_ (comments),
	theoryName_ (theoryName),
	minimizedTheoryName_ (minimizedTheoryName),
	theory_ (Math :: theories()->get (theoryName_)),
	minimizedTheory_ (Math :: theories()->get (minimizedTheoryName_)) {
	}
	inline
	Minimization :: Minimization
	(
		const value :: Theory theoryName,
		const value :: Theory minimizedTheoryName
	) :
	location_ (),
	comments_ (NULL),
	theoryName_ (theoryName),
	minimizedTheoryName_ (minimizedTheoryName),
	theory_ (Math :: theories()->get (theoryName_)),
	minimizedTheory_ (Math :: theories()->get (minimizedTheoryName_)) {
	}
	Minimization :: ~ Minimization() {
		deleteAggregateObject (comments_);
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// del :: Minimization implementation
	bool
	Minimization :: checkCorrectness() const {
		return true;
	}
	void
	Minimization :: replicateCompletely (String& string) const
	{
		string << "/****************************************/" << endLine;
		string << "/*            minimization              */" << endLine;
		string << "/****************************************/" << endLine;
		string << endLine;
		string << "// Original theory:" << endLine;
		theory_->replicate (string);
		string << endLine;
		string << "// Minimized theory:" << endLine;
		minimizedTheory_->replicate (string);
		string << endLine;
		string << "// Minimization:" << endLine;
		replicate (string);
	}

	// object :: Writable implementation
	void
	Minimization :: replicate (String& string) const
	{
		if (comments_ != NULL) {
			comments_->replicate (string);
		}
		string << location_.getIndent();
		string << Token :: minimizationOf_ << space;
		string << Table :: theories()->get (theoryName_) << space;
		string << Token :: equality_ << space;
		string << Table :: theories()->get (minimizedTheoryName_) << endLine;
		string << endLine;
		string << endLine;
	}
	void
	Minimization :: translate (String& string) const {
		replicate (string);
	}
	void
	Minimization :: write (String& string) const
	{
		if (Config :: removeComments()) {
			string << "/****************************************/" << endLine;
			string << "/*            minimization              */" << endLine;
			string << "/****************************************/" << endLine;
			string << endLine;
		}
		theory_->replicate (string);
		minimizedTheory_->replicate (string);
		replicate (string);
		string << endLine;
		string << endLine;
	}

	// object :: Object implementation
	void
	Minimization :: commitSuicide() {
		delete this;
	}
	Size_t
	Minimization :: getSizeOf() const {
		return sizeof (Minimization);
	}
	Size_t
	Minimization :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/
}
}

#endif /*DEL_SOURCE_MINIMIZATION_CPP_*/

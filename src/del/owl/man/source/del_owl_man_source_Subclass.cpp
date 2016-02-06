/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Subclass.cpp                          */
/* Description:     manchester OWL subclass source                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.hpp"

namespace del {
namespace owl {
namespace man {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Subclass :: Subclass (const Location& location, const Class* clas) :
	location_ (location),
	class_ (clas),
	terms_ () {
		Class :: lastItem_ = this;
	}
	inline
	Subclass :: Subclass (const Class* clas) :
	location_ (),
	class_ (clas),
	terms_ () {
		Class :: lastItem_ = this;
	}
	Subclass :: ~ Subclass() {
	}

	void
	Subclass :: addToTheory (del :: Theory* theory) const
	{
		const value :: Variable name = class_->getName();
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* term_1 = new del :: source :: term :: Variable (name);
			const del :: Term* term_2 = terms_.getValue (i)->clone();
			const del :: Formula* const
				formula = new del :: source :: formula :: Subset (Location(), term_1, term_2);
			theory->addFormula (formula);
		}
	}
	void
	Subclass :: addTerm (const del :: Term* term) {
		terms_.add (term);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Subclass :: translate (String& string) const
	{
		const value :: Variable name = class_->getName();
		const String& nameString = Table :: variables()->get (name);
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* term = terms_.getValue (i);
			string << tab << nameString << space << del :: Token :: subset_ << space;
			term->replicate (string);
			if (Class :: lastItem_ == this) {
				string << endLine;
			} else {
				string << "," << endLine;
			}
		}
	}
	void
	Subclass :: replicate (String& string) const
	{
		if (location_.getIndent().isEmpty()) {
			const_cast<Location&>(location_).indent().incTabs();
		}
		string << location_.getIndent();
		string << Token :: subclass_of_ << endLine;
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* term = terms_.getValue (i);
			string << location_.getIndent() << tab << *term;
			if (i < terms_.getSize() - 1) {
				string << "," << endLine;
			} else {
				string << endLine;
			}
		}
	}

	// object :: Object implementation
	void
	Subclass :: commitSuicide() {
		delete this;
	}
	Size_t
	Subclass :: getVolume() const {
		return terms_.getVolume();
	}
	Size_t
	Subclass :: getSizeOf() const {
		return sizeof (Subclass);
	}
}
}
}
}



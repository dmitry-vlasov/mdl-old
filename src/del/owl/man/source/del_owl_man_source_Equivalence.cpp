/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Equivalence.cpp                       */
/* Description:     manchester OWL equivalence source                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_EQUIVALENCE_CPP_
#define DEL_OWL_MAN_SOURCE_EQUIVALENCE_CPP_

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
	Equivalence :: Equivalence (const Location& location, const Class* clas) :
	location_ (location),
	class_ (clas),
	terms_ () {
		Class :: lastItem_ = this;
	}
	inline
	Equivalence :: Equivalence (const Class* clas) :
	location_ (),
	class_ (clas),
	terms_ () {
		Class :: lastItem_ = this;
	}
	Equivalence :: ~ Equivalence() {
	}

	void
	Equivalence :: addToTheory (del :: Theory* theory) const
	{
		const value :: Variable name = class_->getName();
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* term_1 = new del :: source :: term :: Variable (name);
			const del :: Term* term_2 = terms_.getValue (i)->clone();
			const del :: Formula* const
				formula = new del :: source :: formula :: Identity (Location(), term_1, term_2);
			theory->addFormula (formula);
		}
	}
	void
	Equivalence :: addTerm (const del :: Term* term) {
		terms_.add (term);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Equivalence :: translate (String& string) const
	{
		const value :: Variable name = class_->getName();
		const String& nameString = Table :: variables()->get (name);
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* term = terms_.getValue (i);
			string << tab << nameString << space << del :: Token :: equal_ << space;
			term->replicate (string);
			if (Class :: lastItem_ == this) {
				string << endLine;
			} else {
				string << "," << endLine;
			}
		}
	}
	void
	Equivalence :: replicate (String& string) const
	{
		if (location_.getIndent().isEmpty()) {
			const_cast<Location&>(location_).indent().incTabs();
		}
		string << location_.getIndent();
		string << Token :: equivalent_to_ << endLine;
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
	Equivalence :: commitSuicide() {
		delete this;
	}
	Size_t
	Equivalence :: getVolume() const {
		return terms_.getVolume();
	}
	Size_t
	Equivalence :: getSizeOf() const {
		return sizeof (Equivalence);
	}
}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_EQUIVALENCE_CPP_*/

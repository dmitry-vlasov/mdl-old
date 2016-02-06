/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Ontology.cpp                          */
/* Description:     manchester OWL ontology source                           */
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
	Ontology :: Ontology (const Location& location, const String& contents) :
	location_ (location),
	contents_ (contents) {
	}
	inline
	Ontology :: Ontology (const String& contents) :
	location_ (),
	contents_ (contents) {
	}
	Ontology :: ~ Ontology() {
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Ontology :: translate (String& string) const
	{
		if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << del :: Token :: commentBegin_;
		string << Token :: ontology_ << space;
		string << contents_ ;
		string << del :: Token :: commentEnd_ << endLine;
	}
	void
	Ontology :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: ontology_ << space;
		string << contents_ << endLine;
		string << endLine;
	}

	// object :: Object implementation
	void
	Ontology :: commitSuicide() {
		delete this;
	}
	Size_t
	Ontology :: getVolume() const {
		return contents_.getVolume();
	}
	Size_t
	Ontology :: getSizeOf() const {
		return sizeof (Ontology);
	}
}
}
}
}



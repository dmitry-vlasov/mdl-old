/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Ontology.cpp                          */
/* Description:     manchester OWL ontology parser                           */
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
#include "del/owl/man/parser/del_owl_man_parser.hpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Ontology :: Ontology() :
	location_ (),
	contents_ (INITIAL_CONTENTS_CAPACITY) {
	}
	Ontology :: ~ Ontology() {
	}

	const source :: Ontology*
	Ontology :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: LEFT_ANGLE>();
		lexer->scan<Token :: NAME>();
		contents_.copy (lexer->getToken());
		lexer->scan<Token :: RIGHT_ANGLE>();
		return new source :: Ontology (location_, contents_);
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
	void
	Ontology :: show (String&) const {
	}
}
}
}
}



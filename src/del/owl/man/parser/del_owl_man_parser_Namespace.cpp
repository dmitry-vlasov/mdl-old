/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Namespace.cpp                         */
/* Description:     manchester OWL namespace parser                          */
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
	Namespace :: Namespace() :
	location_ (),
	name_ (INITIAL_NAME_CAPACITY),
	contents_ (INITIAL_CONTENTS_CAPACITY) {
	}
	Namespace :: ~ Namespace() {
	}

	const source :: Namespace*
	Namespace :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: NAME>();
		const String& name = lexer->getToken();
		name_.copy (name);
		lexer->scan<Token :: LEFT_ANGLE>();
		lexer->scan<Token :: NAME>();
		const String& contents = lexer->getToken();
		contents_.copy (contents);
		lexer->scan<Token :: RIGHT_ANGLE>();

		return new source :: Namespace (location_, name_, contents_);
	}

	// object :: Object implementation
	void
	Namespace :: commitSuicide() {
		delete this;
	}
	Size_t
	Namespace :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += contents_.getVolume();
		return volume;
	}
	Size_t
	Namespace :: getSizeOf() const {
		return sizeof (Namespace);
	}
	void
	Namespace :: show (String&) const {
	}
}
}
}
}



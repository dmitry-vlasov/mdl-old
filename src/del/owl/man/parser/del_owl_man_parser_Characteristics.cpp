/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Characteristics.cpp                   */
/* Description:     manchester OWL characteristics parser                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_CHARACTERISTICS_CPP_
#define DEL_OWL_MAN_PARSER_CHARACTERISTICS_CPP_

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
	Characteristics :: Characteristics() :
	location_ () {
	}
	Characteristics :: ~ Characteristics() {
	}

	void
	Characteristics :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: COLON>();
		lexer->scan<Token :: NAME>();
	}

	// object :: Object implementation
	void
	Characteristics :: commitSuicide() {
		delete this;
	}
	Size_t
	Characteristics :: getVolume() const {
		return 0;
	}
	Size_t
	Characteristics :: getSizeOf() const {
		return sizeof (Characteristics);
	}
	void
	Characteristics :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_CHARACTERISTICS_CPP_*/

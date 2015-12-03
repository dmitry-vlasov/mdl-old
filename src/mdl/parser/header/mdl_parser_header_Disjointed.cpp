/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Disjointed.cpp                         */
/* Description:     disjointed parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_DISJOINTED_CPP_
#define MDL_PARSER_HEADER_DISJOINTED_CPP_

namespace mdl {
namespace parser {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Disjointed :: Disjointed() :
	literalVector_ (INITIAL_LITERAL_VECTOR_CAPACITY) {
	}
	Disjointed :: ~ Disjointed() {
	}

	mdl :: header :: Disjointed*
	Disjointed :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		literalVector_.clear();

		while (true) {
			lexer->scan
			<
				Token :: NAME,
				Token :: CLOSE_BRACKET,
				Token :: COMMA
			>();
			switch (lexer->getTokenType()) {
			case Token :: NAME : {
				const value :: Literal
					literal = Table :: literals()->add (lexer->getToken());
				literalVector_.add (literal);
				break;
			}
			case Token :: CLOSE_BRACKET :
				return new form :: header :: Disjointed (literalVector_, theory);
			case Token :: COMMA :
				return new form :: header :: Disjointed (literalVector_, theory);
			default :
				return NULL;
			}
		}
	}

	// object :: Object implementation
	void
	Disjointed :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjointed :: getVolume() const {
		return literalVector_.getVolume();
	}
	Size_t
	Disjointed :: getSizeOf() const {
		return sizeof (Disjointed);
	}
	void
	Disjointed :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_HEADER_DISJOINTED_CPP_*/

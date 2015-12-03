/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Variable.cpp                            */
/* Description:     proof variable declaration parser                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_VARIABLE_CPP_
#define MDL_PARSER_PROOF_VARIABLE_CPP_

namespace mdl {
namespace parser {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variable :: Variable() :
	variableParser_ (new parser :: header :: Variable()),
	location_ (),
	comments_ (NULL),
	variable_ (NULL) {
	}
	Variable :: ~ Variable() {
		deleteAggregateObject (variableParser_);
	}

	mdl :: proof :: Variable*
	Variable :: parse
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line
	)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		location_ = lexer->getLocation();
		variable_ = variableParser_->parse<form :: proof :: Variable :: Declaration> (lexer, theory, create);
		lexer->scan<Token :: SEMICOLON> ();
		comments_ =
			(lexer->comments().isEmpty() || !create) ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		if (create) {
			return new form :: proof :: Variable (line, location_, comments_, variable_, theory);
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Variable :: commitSuicide() {
		delete this;
	}
	Size_t
	Variable :: getVolume() const {
		return getAggregateVolume (variableParser_);
	}
	Size_t
	Variable :: getSizeOf() const {
		return sizeof (Variable);
	}
	void
	Variable :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_PROOF_VARIABLE_CPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Variable.cpp                           */
/* Description:     variable declaration parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace parser {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variable :: Variable() :
	location_ (),
	identificatorParser_ (new parser :: Identificator()),
	literal_ (value :: undefined :: LITERAL),
	type_ (NULL) {
	}
	Variable :: ~ Variable() {
		deleteAggregateObject (identificatorParser_);
	}

	template<class I>
	mdl :: header :: Variable*
	Variable :: parse (Lexer* lexer, mdl :: Theory* theory, const bool create)
	{
		typedef I Implementation;
		location_ = lexer->getLocation();
		literal_ = lexer->scanLiteralName();
		lexer->scan <Token :: COLON>();
		type_ = identificatorParser_->parse (lexer, create);
		if (create) {
			return new Implementation (location_, literal_, type_, theory);
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
	Variable :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (identificatorParser_);
		return volume;
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



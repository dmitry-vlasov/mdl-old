/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Line.cpp                               */
/* Description:     line parser                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_LINE_CPP_
#define MDL_PARSER_HEADER_LINE_CPP_

namespace mdl {
namespace parser {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	Line :: Line() :
	identificatorParser_ (new parser :: Identificator()),
	expressionParser_ (new parser :: Expression()),
	location_ (),
	index_ (index :: undefined :: ARITY),
	type_ (NULL),
	expression_ (NULL) {
	}
	Line :: ~ Line()
	{
		deleteAggregateObject (identificatorParser_);
		deleteAggregateObject (expressionParser_);
	}

	template<class T, class TF, Token :: Type token>
	T*
	Line :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		if (lexer->scan<Token :: NUMBER, Token :: COLON>() == Token :: NUMBER) {
			index_ = lexer->getToken().getIntegerValue<index :: Arity>();
			lexer->scan<Token :: COLON>();
		} else {
			index_ = 1;
		}
		type_ = identificatorParser_->parse (lexer);
		lexer->scan<Token :: EQUALITY>();

		lexer->template scan<token> ();
		expression_ = expressionParser_->parse (lexer);
		return new TF (location_, index_ - 1, type_, expression_, theory);
	}

	// object :: Object implementation
	void
	Line :: commitSuicide() {
		delete this;
	}
	Size_t
	Line :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (identificatorParser_);
		volume += getAggregateVolume (expressionParser_);
		return volume;
	}
	Size_t
	Line :: getSizeOf() const {
		return sizeof (Line);
	}
	void
	Line :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_HEADER_LINE_CPP_*/

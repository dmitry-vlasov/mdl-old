/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Type.cpp                                */
/* Description:     type parser                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_TYPE_CPP_
#define MDL_PARSER_BLOCK_TYPE_CPP_

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Type :: Type() :
	identificatorParser_ (new parser :: Identificator()),
	location_(),
	comments_ (NULL),
	name_ (value :: undefined :: NAME),
	superTypes_ (INITIAL_SUPER_TYPES_CAPACITY) {
	}
	Type :: ~ Type() {
		deleteAggregateObject (identificatorParser_);
	}

	mdl :: Type*
	Type :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		superTypes_.clear();
		location_ = lexer->getLocation();
		name_ = lexer->scanName();
		if (lexer->scan<Token :: SEMICOLON, Token :: COLON>() == Token :: COLON) {
			while (true) {
				mdl :: Identificator* superType = identificatorParser_->parse (lexer);
				superTypes_.add (superType);
				if (lexer->scan<Token :: SEMICOLON, Token :: COMMA>() == Token :: SEMICOLON) {
					break;
				}
			}
		}
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		return new form :: Type
		(
			location_,
			comments_,
			name_,
			superTypes_,
			theory
		);
	}

	// object :: Object implementation
	void
	Type :: commitSuicide() {
		delete this;
	}
	Size_t
	Type :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (identificatorParser_);
		volume += superTypes_.getVolume();
		return volume;
	}
	Size_t
	Type :: getSizeOf() const {
		return sizeof (Type);
	}
	void
	Type :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_BLOCK_TYPE_CPP_*/

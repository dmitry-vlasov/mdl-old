/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Proof.cpp                               */
/* Description:     proof parser                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

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
	Proof :: Proof (const bool local) :
	local_ (local),
	identificatorParser_ (new parser :: Identificator()),
	proofParser_ (new parser :: proof :: Proof()),

	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: NAME),
	theorem_ (NULL),
	proof_ (NULL) {
	}
	Proof :: ~ Proof()
	{
		deleteAggregateObject (identificatorParser_);
		deleteAggregateObject (proofParser_);
	}

	mdl :: Proof*
	Proof :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		location_ = lexer->getLocation();
		if (!local_) {
			lexer->comments().clear();
			if (lexer->scan<Token :: NAME, Token :: OF>() == Token :: NAME) {
				name_ = Table :: names()->add (lexer->getToken());
				lexer->scan <Token :: OF>();
			} else {
				name_ = Table :: defaultName();
			}
			theorem_ = identificatorParser_->parse (lexer);
			comments_ =
				(lexer->comments().isEmpty() || !create) ?
				NULL :
				new form :: Comments (lexer->comments(), false);
			lexer->comments().clear();
		}
		lexer->scan <Token :: OPEN_BRACE>();
		proof_ = proofParser_->parse (lexer, theory);
		if (local_) {
			return proof_;
		} else {
			return new form :: Proof
			(
				location_,
				comments_,
				name_,
				theorem_,
				proof_,
				theory
			);
		}
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (identificatorParser_);
		volume += getAggregateVolume (proofParser_);
		return volume;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
	void
	Proof :: show (String&) const {
	}
}
}
}



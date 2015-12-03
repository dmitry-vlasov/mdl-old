/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Link.cpp                                */
/* Description:     proof link parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_LINK_CPP_
#define MDL_PARSER_PROOF_LINK_CPP_

namespace mdl {
namespace parser {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Link :: Link() :
	location_ (),
	identificatorParser_ (new parser :: Identificator()),
	referencesParser_ (new parser :: proof :: References()),
	
	kind_ (Token :: UNKNOWN),
	inference_ (NULL),
	proposition_ (index :: undefined :: ARITY),
	references_ (NULL) {
	}
	Link :: ~ Link()
	{
		deleteAggregateObject (identificatorParser_);
		deleteAggregateObject (referencesParser_);
	}

	mdl :: proof :: Link*
	proof :: Link :: parse (Lexer* lexer, mdl :: Theory* theory, const bool parseIdentificator)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		kind_ = lexer->getTokenType();
		if (parseIdentificator) {
			location_ = lexer->getLocation();;
			inference_ = identificatorParser_->parse (lexer, create);
			if (lexer->scan<Token :: OPEN_BRACKET, Token :: COLON>() == Token :: COLON) {
				proposition_ =	lexer->scanNumber<index :: Arity>();
				lexer->scan<Token :: OPEN_BRACKET>();
			} else {
				proposition_ = 1;
			}
		} else {
			inference_ = NULL;
			proposition_ = index :: undefined :: ARITY;
			lexer->scan<Token :: OPEN_BRACKET>();
		}
		references_ = referencesParser_->parse (lexer, theory);
		if (create) {
			return new form :: proof :: Link
			(
				location_,
				kind_,
				inference_,
				proposition_,
				references_,
				theory
			);
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Link :: commitSuicide() {
		delete this;
	}
	Size_t
	Link :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (identificatorParser_);
		volume += getAggregateVolume (referencesParser_);
		return volume;
	}
	Size_t
	Link :: getSizeOf() const {
		return sizeof (Link);
	}
	void
	Link :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_PROOF_LINK_CPP_*/

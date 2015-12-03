/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_References.cpp                          */
/* Description:     proof reference vector parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_REFERENCES_CPP_
#define MDL_PARSER_PROOF_REFERENCES_CPP_

namespace mdl {
namespace parser {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	References :: References() :
	referenceParser_ (new parser :: proof :: Reference()),
	referenceVector_ (INITIAL_REFERENCE_VECTOR_CAPACITY) {	
	}
	References :: ~ References() {
		deleteAggregateObject (referenceParser_);
	}

	mdl :: proof :: References*
	References :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		referenceVector_.clear();

		while (true) {
			lexer->scan
			<
				Token :: HYP,
				Token :: PROP,
				Token :: STEP,
				Token :: CLOSE_BRACKET
			>();
			if (lexer->getTokenType() == Token :: CLOSE_BRACKET) {
				break;
			}
			mdl :: proof :: Reference*
				reference = referenceParser_->parse (lexer, theory);
			if (create) {
				referenceVector_.add (reference);
			}
			if (lexer->scan<Token :: COMMA, Token :: CLOSE_BRACKET>() == Token :: CLOSE_BRACKET) {
				break;
			}
		} 
		if (create) {
			return new form :: proof :: References (referenceVector_, theory);
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	References :: commitSuicide() {
		delete this;
	}
	Size_t
	References :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (referenceParser_);
		volume += referenceVector_.getVolume ();
		return volume;
	}
	Size_t
	References :: getSizeOf() const {
		return sizeof (References);
	}
	void
	References :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_PROOF_REFERENCES_CPP_*/

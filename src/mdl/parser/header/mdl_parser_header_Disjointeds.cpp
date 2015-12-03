/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Disjointeds.cpp                        */
/* Description:     disjointeds parser                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_DISJOINTEDS_CPP_
#define MDL_PARSER_HEADER_DISJOINTEDS_CPP_

namespace mdl {
namespace parser {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Disjointeds :: Disjointeds() :
	disjointedParser_ (new parser :: header :: Disjointed()),
	disjointedVector_ (INITIAL_DISJOINTED_VECTOR_CAPACITY) {
	}
	Disjointeds :: ~ Disjointeds() {
		deleteAggregateObject (disjointedParser_);
	}

	mdl :: Disjointeds*
	Disjointeds :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		disjointedVector_.clear();
		lexer->scan <Token :: OPEN_BRACKET>();
		while (lexer->getTokenType() != Token :: CLOSE_BRACKET) {
			disjointedVector_.add (disjointedParser_->parse (lexer, theory));
		}
		return new form :: Disjointeds (disjointedVector_, theory);
	}

	// object :: Object implementation
	void
	Disjointeds :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjointeds :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (disjointedParser_);
		volume += disjointedVector_.getVolume();
		return volume;
	}
	Size_t
	Disjointeds :: getSizeOf() const {
		return sizeof (Disjointeds);
	}
	void
	Disjointeds :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_HEADER_DISJOINTEDS_CPP_*/

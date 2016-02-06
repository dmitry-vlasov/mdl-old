/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Reference.cpp                           */
/* Description:     proof reference parser                                   */
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
namespace proof {

	/****************************
	 *		Public members
	 ****************************/
	
	inline
	Reference :: Reference() :
	location_ (),
	kind_ (value :: undefined :: KIND),
	index_ (index :: undefined :: STEP) {
	}
	Reference :: ~ Reference() {
	}

	mdl :: proof :: Reference*
	Reference :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		kind_ = lexer->getTokenType();
		index_ = lexer->scanNumber<index :: Step>() - 1;
		if (!Config :: shallowParsing() || lexer->isTop()) {
			return new form :: proof :: Reference (location_, kind_, index_, NULL, theory);
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Reference :: commitSuicide() {
		delete this;
	}
	Size_t
	Reference :: getVolume() const {
		return location_.getVolume();
	}
	Size_t
	Reference :: getSizeOf() const {
		return sizeof (Reference);
	}
	void
	Reference :: show (String&) const {
	}
}
}
}



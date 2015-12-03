/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       mm_parser_Inclusion.cpp                                  */
/* Description:     inclusion parser                                         */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_INCLUDE_CPP_
#define SMM_PARSER_INCLUDE_CPP_

#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Inclusion :: Inclusion() :
	path_ (INITIAL_PATH_CAPACITY),
	location_ () {
	}
	Inclusion :: ~ Inclusion() {
	}

	const smm :: Inclusion*
	Inclusion :: parse (Lexer* const lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: PATH>();
		path_ = lexer->getToken();
		lexer->scan<Token :: INCLUSION_END>();
		return  new source :: Inclusion (location_, path_);

		/*if (!Table :: files()->contains (path_)) {
			Table :: files()->add (path_);
			if (source_ == NULL) {
					source_ = new parser :: Source (false);
			}
			const source :: Inclusion* const
			inclusion = new source :: Inclusion (location_, path_);
			mmBlock = source_->parse (include, mmBlock);
		}
		break;


		if (sourceParser_ == NULL) {
			sourceParser_ = new parser :: Source ();
		}

		source->addComponent (inclusion);
		sourceParser_->parse (source, inclusion);*/
	}

	// object :: Object implementation
	void
	Inclusion :: commitSuicide() {
		delete this;
	}
	Size_t
	Inclusion :: getVolume() const
	{
		Size_t volume = 0;
		volume += path_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Inclusion :: getSizeOf() const {
		return sizeof (Inclusion);
	}
	void
	Inclusion :: show (String&) const {
	}
}
}

#endif /*SMM_PARSER_INCLUDE_CPP_*/

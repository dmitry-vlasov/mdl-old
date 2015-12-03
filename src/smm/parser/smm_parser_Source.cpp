/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Source.cpp                                    */
/* Description:     smm source parser                                        */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_SOURCE_CPP_
#define SMM_PARSER_SOURCE_CPP_

#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source() :
	lexer_(NULL),
	location_ (),
	constantsParser_ (new Constant_()),
	assertionParser_ (new parser :: Assertion()),
	inclusionParser_ (new parser :: Inclusion()),
	sourceParser_ (NULL),
	source_ (NULL) {
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (constantsParser_);
		deleteAggregateObject (assertionParser_);
		deleteAggregateObject (inclusionParser_);
		deleteAggregateObject (sourceParser_);
		deleteAggregateObject (lexer_);
	}

	inline const smm :: Source*
	Source :: parse (const String& path)
	{
		source_ = new source :: Source();
		Table :: files()->add (path);
		open (path);
		parseContents();
		close (path);
		return source_;
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (constantsParser_);
		volume += getAggregateVolume (assertionParser_);
		volume += getAggregateVolume (inclusionParser_);
		volume += getAggregateVolume (sourceParser_);
		volume += getAggregateVolume (lexer_);
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	void
	Source :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Source :: parseContents()
	{
		while (true) {
			location_ = lexer_->getLocation();
			switch (lexer_->scan()) {
			case Token :: CONSTANT : {
				const Expression*
					literals = constantsParser_->parse (lexer_);
				const smm :: Constants*
					constants = new source :: Constants (location_, literals);
				source_->addComponent (constants);
				break;
			}
			case Token :: BLOCK_BEGIN : {
				const smm :: Assertion*
					assertion = assertionParser_->parse (lexer_);
				source_->addComponent (assertion);
				break;
			}
			case Token :: INCLUSION_BEGIN : {
				const smm :: Inclusion* const
					inclusion = inclusionParser_->parse (lexer_);
				const String& path = inclusion->getPath();
				source_->addComponent (inclusion);
				if (!Table :: files()->contains (path)) {
					Table :: files()->add (path);
					if (sourceParser_ == NULL) {
						sourceParser_ = new parser :: Source();
					}
					const smm :: Source*
						includedSource = sourceParser_->parse (path);
					source_->addComponent (includedSource);
				}
				break;
			}
			case Token :: EOF_ :
				return;
			default :
				Error* error = new Error (location_, Error :: PARSER);
				error->message() << "unexpected token: " << lexer_->getToken () << space;
				error->message() << "should be one of : $c, ${, $[, EOF" << endLine;
				throw error;
			}
		}
	}

	void
	Source :: open (const String& path)
	{
		if (lexer_ != NULL) {
			lexer_->open (path);
		} else {
			lexer_ = new Lexer (path);
			lexer_->open();
		}
	}
	void
	Source :: close (const String& path)
	{
		if (lexer_ == NULL) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "attempt to close non opened " << path << endLine;
			throw error;
		}
		if (lexer_->getTokenType() != Token :: EOF_) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "unexpected token: "<< lexer_->getToken() << endLine;
			error->message() << "EOF expected in file " << path << endLine;
			throw error;
		}
		lexer_->close();
	}
}
}

#endif /*SMM_PARSER_SOURCE_CPP_*/

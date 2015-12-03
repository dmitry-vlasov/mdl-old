/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Source.cpp                                    */
/* Description:     source parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_SOURCE_CPP_
#define DEL_PARSER_SOURCE_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source () :
	lexer_ (NULL),
	assertionParser_ (new parser :: Assertion()),
	theoryParser_ (new parser :: Theory()),
	questionParser_ (new parser :: Question()),
	answerParser_ (new parser :: Answer()),
	signatureParser_ (new parser :: Signature()),
	decomposeParser_ (new parser :: Decompose()),
	decompositionParser_ (new parser :: Decomposition()),
	minimizeParser_ (new parser :: Minimize()),
	minimizationParser_ (new parser :: Minimization()) {
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (assertionParser_);
		deleteAggregateObject (theoryParser_);
		deleteAggregateObject (questionParser_);
		deleteAggregateObject (answerParser_);
		deleteAggregateObject (signatureParser_);
		deleteAggregateObject (decomposeParser_);
		deleteAggregateObject (decompositionParser_);
		deleteAggregateObject (minimizeParser_);
		deleteAggregateObject (minimizationParser_);
	}

	const del :: Source*
	Source :: parse (const del :: Path& path)
	{
		open (path);
		lexer_->scanComments();
		const del :: Comments* comments =
			lexer_->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer_->comments());

		lexer_->comments().clear();
		del :: Source* const source =
			(Config :: getTarget().isUndefined()) ?
			new source :: Source (lexer_, comments, path) :
			new source :: Source (lexer_, comments, path, Config :: getTarget());

		while (true) {
			lexer_->scan
			<
				Token :: ASSERT,
				Token :: THEORY,
				Token :: DOES,
				Token :: SOLUTION,
				Token :: SIGNATURE,
				Token :: DECOMPOSE,
				Token :: DECOMPOSITION_OF,
				Token :: MINIMIZE,
				Token :: MINIMIZATION_OF,
				Token :: EOF_
			>();
			switch (lexer_->getTokenType()) {
			case Token :: ASSERT : {
				const del :: Assertion* const
					assertion = assertionParser_->parse (lexer_);
				source->addAssertion (assertion);
				break;
			}
			case Token :: THEORY : {
				const del :: Theory* const
					theory = theoryParser_->parse (lexer_);
				source->addTheory (theory);
				break;
			}
			case Token :: DOES : {
				const del :: Question* const
					question = questionParser_->parse (lexer_);
				source->addQuestion (question);
				break;
			}
			case Token :: SOLUTION : {
				const del :: Answer* const
					answer = answerParser_->parse (lexer_);
				source->addAnswer (answer);
				break;
			}
			case Token :: SIGNATURE : {
				const del :: Signature* const
					signature = signatureParser_->parse (lexer_);
				source->addSignature (signature);
				break;
			}
			case Token :: DECOMPOSE : {
				const del :: Decompose* const
					decompose = decomposeParser_->parse (lexer_);
				source->addDecompose (decompose);
				break;
			}
			case Token :: DECOMPOSITION_OF : {
				const del :: Decomposition* const
					decomposition = decompositionParser_->parse (lexer_);
				source->addDecomposition (decomposition);
				break;
			}
			case Token :: MINIMIZE : {
				const del :: Minimize* const
					minimize = minimizeParser_->parse (lexer_);
				source->addMinimize (minimize);
				break;
			}
			case Token :: MINIMIZATION_OF : {
				const del :: Minimization* const
					minimization = minimizationParser_->parse (lexer_);
				source->addMinimization (minimization);
				break;
			}
			case Token :: EOF_ : {
				lexer_->getLocation();
				goto end;
			}
			default :
				return NULL;
			}
		}
		end :
		comments =
			lexer_->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer_->comments());
		source->addComments (comments);
		lexer_->comments().clear();
		close (path);
		return source;
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
		volume += getAggregateVolume (assertionParser_);
		volume += getAggregateVolume (theoryParser_);
		volume += getAggregateVolume (questionParser_);
		volume += getAggregateVolume (answerParser_);
		volume += getAggregateVolume (signatureParser_);
		volume += getAggregateVolume (decomposeParser_);
		volume += getAggregateVolume (decompositionParser_);
		volume += getAggregateVolume (minimizeParser_);
		volume += getAggregateVolume (minimizationParser_);
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

using manipulator :: endLine;

	void
	Source :: open (const Path& path)
	{
		const String& file = path.getString();
		lexer_ = new Lexer (file);
		lexer_->open();
	}
	void
	Source :: close (const Path& path)
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

#endif /*DEL_PARSER_SOURCE_CPP_*/

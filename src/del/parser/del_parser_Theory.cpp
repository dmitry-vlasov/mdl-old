/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Theory.cpp                                    */
/* Description:     theory contents parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_THEORY_CPP_
#define DEL_PARSER_THEORY_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Theory :: Theory() :
	formulaParser_ (new parser :: Formula()),
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: THEORY),
	theory_ (NULL) {
	}
	Theory :: ~ Theory() {
		deleteAggregateObject (formulaParser_);
	}

	const del :: Theory*
	Theory :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		name_ = lexer->scanTheoryName (true);
		lexer->scan<Token :: EQUALITY>();

		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		lexer->scan
		<
			Token :: OPEN_BRACE,
			Token :: OPEN_BRACKET,
			Token :: FILE
		>();
		switch (lexer->getTokenType()) {
		case Token :: OPEN_BRACE :
			theory_ = new source :: Theory (location_, comments_, name_);
			parseSet (lexer);
			break;
		case Token :: OPEN_BRACKET :
			theory_ = new source :: Theory (location_, comments_, name_);
			parseTerm (lexer);
			break;
		case Token :: FILE :
			parseFile (lexer);
			break;
		default : break;
		}
		lexer->comments().clear();
		return theory_;
	}

	// object :: Object implementation
	void
	Theory :: commitSuicide() {
		delete this;
	}
	Size_t
	Theory :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (formulaParser_);
		return volume;
	}
	Size_t
	Theory :: getSizeOf() const {
		return sizeof (Theory);
	}
	void
	Theory :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Theory :: parseSet (Lexer* lexer)
	{
		while (true) {
			const del :: Formula*
				formula = formulaParser_->parse (lexer);
			if (formula != NULL) {
				theory_->addFormula (formula);
				if (lexer->scan<Token :: COMMA, Token :: CLOSE_BRACE>() == Token :: CLOSE_BRACE) {
					break;
				}
			} else {
				break;
			}
		}
	}
	void
	Theory :: parseTerm (Lexer* lexer)
	{
		while (true) {
			if (lexer->scan<Token :: COPY, Token :: NAME>() == Token :: COPY) {
				lexer->scan<Token :: OPEN_BRACKET>();
				const value :: Theory
					th = lexer->scanTheoryName();
				const del :: Theory*
					theory = Math :: theories()->get (th);
				lexer->scan<Token :: COMMA>();
				const value :: Signature
					signature = lexer->scanSignatureName();
				lexer->scan<Token :: CLOSE_BRACKET>();
				del :: Theory*
					theoryDelta = theory->clone();
				const del :: Signature* const
					sign = Math :: signatures()->get (signature);
				del :: Expansion* const
					expansion = new source :: Expansion<> (sign);
				theoryDelta->makeDeltaCopy (expansion);
				theory_->unite (theoryDelta);
				theoryDelta->commitSuicide();
				expansion->commitSuicide();
			} else {
				const String& name = lexer->getToken();
				const value :: Theory th = Table :: theories()->find (name);
				const del :: Theory* theory = Math :: theories()->get (th);
				theory_->unite (theory);
			}
			if (lexer->scan<Token :: CLOSE_BRACKET, Token :: UNION>() == Token :: CLOSE_BRACKET) {
				break;
			}
		}
	}
	void
	Theory :: parseFile (Lexer* lexer)
	{
		const String& file = lexer->scanPath();
		const Path path (file);
		if (path.extensionIs ("man")) {
			if (Del :: del()->owlMan() != NULL) {
				Error* error = new Error (Error :: INPUT);
				error->message() << "only one import from file is allowed."<< endLine;
				throw error;
			}
			owl :: man :: Owl* owl = new owl :: man :: Owl (file);
			owl->read();
			theory_ = const_cast<del :: Theory*>(owl->getSource()->createTheory());
			theory_->setName (name_);
			Math :: theories()->add (theory_);
			Del :: del()->owlMan() = owl;
		} else if (path.extensionIs ("owl")) {
			if (Del :: del()->owlFunc() != NULL) {
				Error* error = new Error (Error :: INPUT);
				error->message() << "only one import from file is allowed."<< endLine;
				throw error;
			}
			owl :: func :: Owl* owl = new owl :: func :: Owl (file);
			owl->read();
			theory_ = const_cast<del :: Theory*>(owl->getSource()->createTheory());
			theory_->setName (name_);
			Math :: theories()->add (theory_);
			Del :: del()->owlFunc() = owl;
		} else {
			Error* error = new Error (Error :: INPUT);
			error->message() << "import from " << path.getExtension() << " is not supported." << endLine;
			throw error;
		}
	}
}
}

#endif /*DEL_PARSER_THEORY_CPP_*/

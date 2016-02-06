/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Corrector.cpp                               */
/* Description:     corrector for math.mm syntax irregularities              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <iostream>

#include "mm/lexer/mm_lexer.hpp"
#include "mm/auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	const vector :: Literal*
	Corrector :: Grammar :: getExpression (const String& token)
	{
		const index :: Assertion
			index = correctionLabels_->find (token);
		if (index == index :: undefined :: ASSERTION) {
			return NULL;
		}
		return expressionVector_->getValue (index);
	}
	void
	Corrector :: Grammar :: release()
	{
		deleteAggregateObject (expressionVector_);
		deleteAggregateObject (correctionLabels_);
		deleteAggregateObject (path_);
		deleteAggregateObject (lexer_);
	}

	// nstd :: Static implementation
	void
	Corrector :: Grammar :: initRaw()
	{
		if (Config :: useGrammarCorrection()) {
			expressionVector_ = new ExpressionVector_ (INITIAL_EXPRESSIONS_VECTOR_CAPACITY);
			correctionLabels_ = new CorrectionLabels_ ();
			path_ =  new Path (*Config :: getGrammarCorrectionSource());
			lexer_ = new Lexer (path_->getString());
			run();
		}
	}
	void
	Corrector :: Grammar :: showRaw (String&) {
	}
	Size_t
	Corrector :: Grammar :: getRawVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (expressionVector_);
		result += getAggregateVolume (correctionLabels_);
		result += getAggregateVolume (path_);
		result += getAggregateVolume (lexer_);
		return result;
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: endLine;

	bool
	Corrector :: Grammar :: run()
	{
		try {
			open();
			parse();
			close();
		} catch (Error* error) {
			std :: cout << error->message() << std :: endl;
			delete error;
			return false;
		} catch (std :: exception& e) {
			std :: cout << "exception: " << e.what() << std :: endl;
			return false;
		}
		return true;
	}
	void
	Corrector :: Grammar :: parse()
	{
		while (lexer_->scan<Token :: IDENTIFICATOR, Token :: EOF_> () != Token :: EOF_) {
			const String&
				name = lexer_->getToken();
			correctionLabels_->add (name);
			lexer_->scan<Token :: AXIOMATIC, Token :: ESSENTIAL> ();

			vector :: Literal*
				expression = expressionVector_->push();

			while (lexer_->scan<Token :: LITERAL, Token :: END>() != Token :: END) {
				const String&
					token = lexer_->getToken();
				const value :: Literal
					literal = Table :: literals()->add (token);
				expression->add (literal);
			}
		}
	}
	void
	Corrector :: Grammar :: open() {
		lexer_->open ();
	}
	void
	Corrector :: Grammar :: close() {
		lexer_->close ();
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	Corrector :: Grammar :: ExpressionVector_*
		Corrector :: Grammar :: expressionVector_ = NULL;
	Corrector :: Grammar :: CorrectionLabels_*
		Corrector :: Grammar :: correctionLabels_ = NULL;
	Path*
		Corrector :: Grammar :: path_ = NULL;
	Lexer*
		Corrector :: Grammar :: lexer_ = NULL;
}
}



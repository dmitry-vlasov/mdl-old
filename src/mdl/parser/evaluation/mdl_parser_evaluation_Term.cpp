/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_evaluation_Term.cpp                           */
/* Description:     evaluation term parser                                   */
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
namespace evaluation {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Term :: Term() :
	termParser_ (NULL),
	caseParser_ (NULL),
	location_ (),
	parameter_ (0),
	parameterVector_ (INITIAL_PARAMETER_VECTOR_CAPACITY),
	subtermVector_ (INITIAL_TERM_VECTOR_CAPACITY) {
	}
	Term :: ~ Term()
	{
		deleteAggregateObject (termParser_);
		deleteAggregateObject (caseParser_);
	}

	mdl :: evaluation :: Term*
	Term :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		const Token :: Type
			tokenType = lexer->scan
			<
				Token :: SUM,
				Token :: MULT,
				Token :: LEXP,
				Token :: CONST,
				Token :: SUB_CPLX,
				Token :: EXP_CPLX,
				Token :: EXP_AVG,
				Token :: EXP_SIM,
				Token :: EXP_EQ,
				Token :: EXP_DISP,
				Token :: FORKING,
				Token :: WEIGHTED_SUM,
				Token :: BARRIER,
				Token :: CLOSE_BRACKET
			>();
		switch (tokenType) {
		case Token :: SUM :
		case Token :: MULT :
			return parseSimpleOperation (tokenType, lexer, theory);
		case Token :: LEXP :
			return parseLexpOperation (tokenType, lexer, theory);
		case Token :: CONST :
		case Token :: SUB_CPLX :
		case Token :: EXP_CPLX :
		case Token :: EXP_AVG :
		case Token :: EXP_SIM :
		case Token :: EXP_EQ :
		case Token :: EXP_DISP :
		case Token :: FORKING :
			return parseConstOperation (tokenType, lexer, theory);
		case Token :: WEIGHTED_SUM :
		case Token :: BARRIER :
			return parseComplexOperation (tokenType, lexer, theory);
		case Token :: CLOSE_BRACKET :
		default :
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Term :: commitSuicide() {
		delete this;
	}
	Size_t
	Term :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (termParser_);
		volume += getAggregateVolume (caseParser_);
		volume += parameterVector_.getVolume();
		volume += subtermVector_.getVolume();
		return volume;
	}
	Size_t
	Term :: getSizeOf() const {
		return sizeof (Term);
	}
	void
	Term :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	mdl :: evaluation :: Term*
	Term :: parseSimpleOperation
	(
		const Token :: Type tokenType,
		Lexer* lexer,
		mdl :: Theory* theory
	)
	{
		if (termParser_ == NULL) {
			termParser_ = new parser :: evaluation :: Term();
		}
		lexer->scan<Token :: OPEN_SQ_BRACKET>();
		parameter_ = lexer->scanReal();
		lexer->scan<Token :: CLOSE_SQ_BRACKET>();
		lexer->scan<Token :: OPEN_BRACKET>();
		subtermVector_.clear();
		while (true) {
			mdl :: evaluation :: Term*
				subterm = termParser_->parse (lexer, theory);
			if (subterm != NULL) {
				subtermVector_.add (subterm);
			} else {
				break;
			}
		}
		switch (tokenType) {
		case Token :: SUM :
			return new form :: evaluation :: term :: Sum (location_, parameter_, subtermVector_, theory);
		case Token :: MULT :
			return new form :: evaluation :: term :: Mult (location_, parameter_, subtermVector_, theory);
		default :
			return NULL;
		}
	}
	mdl :: evaluation :: Term*
	Term :: parseComplexOperation
	(
		const Token :: Type tokenType,
		Lexer* lexer,
		mdl :: Theory* theory
	)
	{
		if (termParser_ == NULL) {
			termParser_ = new parser :: evaluation :: Term();
		}
		parameterVector_.clear();
		if (tokenType == Token :: WEIGHTED_SUM) {
			lexer->scan<Token :: OPEN_SQ_BRACKET>();
			while (true) {
				parameter_ = lexer->scanReal();
				parameterVector_.add (parameter_);
				if (lexer->scan<Token :: COMMA, Token :: CLOSE_SQ_BRACKET>() == Token :: CLOSE_SQ_BRACKET) {
					break;
				}
			}
		}
		lexer->scan<Token :: OPEN_BRACKET>();
		subtermVector_.clear();
		while (true) {
			mdl :: evaluation :: Term*
				subterm = termParser_->parse (lexer, theory);
			if (subterm != NULL) {
				subtermVector_.add (subterm);
			} else {
				break;
			}
		}
		switch (tokenType) {
		case Token :: WEIGHTED_SUM :
			return new form :: evaluation :: term :: WeightedSum (location_, parameterVector_, subtermVector_, theory);
		case Token :: BARRIER :
			if (subtermVector_.getSize() != 3) {
				Error* error = new Error (location_, Error :: PARSER, "wrong barrier evaluation function arity.");
				throw error;
			}
			if (parameterVector_.getSize() > 0) {
				Error* error = new Error (Error :: PARSER, "barrier evaluation function has no parameters.");
				throw error;
			}
			return new form :: evaluation :: term :: Barrier (location_, parameterVector_, subtermVector_, theory);
		default :
			return NULL;
		}
	}
	mdl :: evaluation :: Term*
	Term :: parseLexpOperation
	(
		const Token :: Type tokenType,
		Lexer* lexer,
		mdl :: Theory* theory
	)
	{
		if (caseParser_ == NULL) {
			caseParser_ = new parser :: evaluation :: Case();
		}
		form :: evaluation :: term :: Lexp*
			lexp = new form :: evaluation :: term :: Lexp (location_, theory);
		lexer->scan<Token :: OPEN_SQ_BRACKET>();
		bool firstPass = true;
		while (true) {
			bool sign = false;
			mdl :: evaluation :: Case*
				_case = caseParser_->parse (lexer, sign, firstPass, theory);
			if (_case != NULL) {
				lexp->addCase (_case);
			} else {
				if (firstPass) {
					lexp->setConst (sign);
				}
				break;
			}
			firstPass = false;
		}
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: CLOSE_BRACKET>();
		return lexp;
	}
	mdl :: evaluation :: Term*
	Term :: parseConstOperation
	(
		const Token :: Type tokenType,
		Lexer* lexer,
		mdl :: Theory* theory
	)
	{
		if (lexer->scan<Token :: OPEN_SQ_BRACKET, Token :: OPEN_BRACKET>() == Token :: OPEN_SQ_BRACKET) {
			parameter_ = lexer->scanReal();
			lexer->scan<Token :: CLOSE_SQ_BRACKET>();
			lexer->scan<Token :: OPEN_BRACKET>();
		}
		lexer->scan<Token :: CLOSE_BRACKET>();
		switch (tokenType) {
		case Token :: CONST :
			return new form :: evaluation :: term :: Const (location_, parameter_, theory);
		case Token :: SUB_CPLX :
			return new form :: evaluation :: term :: SubCplx (location_, theory);
		case Token :: EXP_CPLX :
			return new form :: evaluation :: term :: ExpCplx (location_, theory);
		case Token :: EXP_AVG :
			return new form :: evaluation :: term :: ExpAvg (location_, theory);
		case Token :: EXP_SIM :
			return new form :: evaluation :: term :: ExpSim (location_, theory);
		case Token :: EXP_EQ :
			return new form :: evaluation :: term :: ExpEq (location_, theory);
		case Token :: EXP_DISP :
			return new form :: evaluation :: term :: ExpDisp (location_, theory);
		case Token :: FORKING :
			return new form :: evaluation :: term :: Forking (location_, theory);
		default :
			return NULL;
		}
	}
}
}
}



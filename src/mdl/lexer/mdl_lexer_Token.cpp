/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Token.cpp                                      */
/* Description:     mdl tokens                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace lexer {

	/********************************
	 *		Public static attributes
	 ********************************/

	const Token Token :: unknown_ (UNKNOWN, "unknown");
	const Token Token :: import_ (IMPORT, "import");
	const Token Token :: theory_ (THEORY, "theory");

	const Token Token :: constant_ (CONSTANT, "constant");
	const Token Token :: type_ (TYPE, "type");
	const Token Token :: rule_ (RULE, "rule");
	const Token Token :: axiom_ (AXIOM, "axiom");
	const Token Token :: definition_ (DEFINITION, "definition");
	const Token Token :: theorem_ (THEOREM, "theorem");
	const Token Token :: problem_ (PROBLEM, "problem");
	const Token Token :: proof_ (PROOF, "proof");

	const Token Token :: term_ (TERM, "term");
	const Token Token :: hyp_ (HYP, "hyp");
	const Token Token :: prop_ (PROP, "prop");
	const Token Token :: disjointed_ (DISJOINTED, "disjointed");
	const Token Token :: defiendum_ (DEFIENDUM, "defiendum");
	const Token Token :: definiens_ (DEFINIENS, "definiens");

	const Token Token :: variable_ (VARIABLE, "var");
	const Token Token :: claim_ (CLAIM, "claim");
	const Token Token :: notation_ (NOTATION, "notation");
	const Token Token :: step_ (STEP, "step");
	const Token Token :: qed_ (QED, "qed");
	const Token Token :: abbreviation_ (ABBREVIATION, "abbreviation");
	const Token Token :: meaning_ (MEANING, "meaning");

	const Token Token :: openBrace_ (OPEN_BRACE, "{");
	const Token Token :: closeBrace_ (CLOSE_BRACE, "}");
	const Token Token :: openBracket_ (OPEN_BRACKET, "(");
	const Token Token :: closeBracket_ (CLOSE_BRACKET, ")");

	const Token Token :: horisontalBar_ (HORISONTAL_BAR, "-----------------");
	const Token Token :: turnstile_ (TURNSTILE, "|-");

	const Token Token :: sharp_ (SHARP, "#");
	const Token Token :: semicolon_ (SEMICOLON, ";");
	const Token Token :: colon_ (COLON, ":");
	const Token Token :: comma_ (COMMA, ",");
	const Token Token :: dot_ (DOT, ".");
	const Token Token :: equality_ (EQUALITY, "=");
	const Token Token :: question_ (QUESTION, "?");
	const Token Token :: exclamation_ (EXCLAMATION, "!");
	const Token Token :: upArrow_ (UP_ARROW, "^");
	const Token Token :: ast_ (AST, "*");;

	const Token Token :: name_ (NAME, "<name> ([^ \\t\\n\\r\\f:;.])+");
	const Token Token :: literal_ (LITERAL, "<literal> ([^ \\t\\n\\r\\f:;.])+");
	const Token Token :: number_ (NUMBER, "<number> ([0-9])+");

	const Token Token :: contents_ (CONTENTS, "contents");
	const Token Token :: of_ (OF, "of");
	const Token Token :: commentBegin_ (COMMENT_BEGIN, "/*");
	const Token Token :: commentEnd_ (COMMENT_END, "*/");
	const Token Token :: lineComment_ (LINE_COMMENT, "//");

	const Token Token :: symbol_ (SYMBOL, "symbol");
	const Token Token :: ascii_ (ASCII, "ascii");
	const Token Token :: latex_ (LATEX, "latex");

	const Token Token :: evaluation_ (EVALUATION, "evaluation");
	const Token Token :: openSqBracket_ (OPEN_SQ_BRACKET, "[");
	const Token Token :: closeSqBracket_ (CLOSE_SQ_BRACKET, "]");
	const Token Token :: plus_ (PLUS, "+");
	const Token Token :: minus_ (MINUS, "-");
	const Token Token :: sum_ (SUM, "sum");
	const Token Token :: mult_ (MULT, "mult");
	const Token Token :: const_ (CONST, "const");
	const Token Token :: lexp_ (LEXP, "lexp");
	const Token Token :: subCplx_ (SUB_CPLX, "sub_cplx");
	const Token Token :: expCplx_ (EXP_CPLX, "exp_cplx");
	const Token Token :: expAvg_ (EXP_AVG, "exp_avg");
	const Token Token :: expSim_ (EXP_SIM, "exp_sim");
	const Token Token :: expEq_ (EXP_EQ, "exp_eq");
	const Token Token :: expDisp_ (EXP_DISP, "exp_disp");
	const Token Token :: forking_ (FORKING, "forking");
	const Token Token :: realNumber_ (REAL_NUMBER, "3.149215");
	const Token Token :: weightedSum_ (WEIGHTED_SUM, "w_sum");
	const Token Token :: barrier_ (BARRIER, "barrier");

	const Token Token :: eof_ (EOF_, "eof");

	const Token Token :: tokens_[NUMBER_OF_TOKENS] =
	{
		unknown_,       import_,       theory_,
		constant_,      type_,         rule_,
		axiom_,         definition_,   theorem_,
		defiendum_,     problem_,      proof_,
		term_,          hyp_,          prop_,
		definiens_,     disjointed_,   step_,
		variable_,      claim_,        notation_,
		abbreviation_,	meaning_,      closeBracket_,
		openBrace_,     closeBrace_,   openBracket_,
		horisontalBar_, turnstile_,    qed_,
		sharp_,         semicolon_,    colon_,       comma_,
		equality_,      question_,     exclamation_, upArrow_,
		name_,          literal_,      number_,      contents_,
		eof_,           of_,           ast_,         dot_,
		commentBegin_,  commentEnd_,   lineComment_,
		symbol_,        ascii_,        latex_,
		evaluation_,    openSqBracket_,closeSqBracket_,
		plus_,          minus_,        sum_,
		mult_,          const_,        lexp_,
		subCplx_,       expCplx_,      expAvg_,
		expSim_,        expEq_,        expDisp_,
		forking_,       realNumber_,   weightedSum_,
		barrier_
	};

	/****************************
	 *		Public members
	 ****************************/

	const char*
	Token :: getString (const Type type)
	{
		for (int i = 0 ; i < NUMBER_OF_TOKENS; i ++) {
			if (tokens_[i].getType() == type) {
				return tokens_[i].getString();
			}
		}
		return unknown_.getString();
	}

	// nstd :: Object implementation
	void
	Token :: commitSuicide() {
		delete this;
	}
	nstd :: Size_t
	Token :: getSizeOf() const {
		return sizeof (Token);
	}
	nstd :: Size_t
	Token :: getVolume() const {
		return 0;
	}
	void
	Token :: show (nstd :: String<>& string) const {
		string << getString();
	}
}
}



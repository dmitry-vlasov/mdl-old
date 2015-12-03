/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Token.cpp                                      */
/* Description:     del tokens                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_LEXER_TOKEN_CPP_
#define DEL_LEXER_TOKEN_CPP_

namespace del {
namespace lexer {

	/********************************
	 *		Public static attributes
	 ********************************/

	const Token Token :: unknown_ (UNKNOWN, "unknown");
	const Token Token :: subset_ (SUBSET, "\u2291");
	const Token Token :: intersect_ (INTERSECT, "\u2293");
	const Token Token :: exists_ (EXISTS, "\u2203");
	const Token Token :: equal_ (EQUAL, "\u2261");
	const Token Token :: top_ (TOP, "\u22A4");
	const Token Token :: models_ (MODELS, "\u22A8");
	const Token Token :: does_not_model_ (DOES_NOT_MODEL, "\u22AD");
	const Token Token :: dot_ (DOT, ".");

	const Token Token :: theory_ (THEORY, "theory");
	const Token Token :: does_ (DOES, "does");
	const Token Token :: solution_ (SOLUTION, "solution");
	const Token Token :: equality_ (EQUALITY, "=");
	const Token Token :: question_ (QUESTION, "?");
	const Token Token :: assertion_ (ASSERTION, "!");
	const Token Token :: comma_ (COMMA, ",");

	const Token Token :: openBrace_ (OPEN_BRACE, "{");
	const Token Token :: closeBrace_ (CLOSE_BRACE, "}");
	const Token Token :: openBracket_ (OPEN_BRACKET, "(");
	const Token Token :: closeBracket_ (CLOSE_BRACKET, ")");

	const Token Token :: name_ (NAME, "<name> ([^ \\t\\n\\r\\f:;.])+");
	const Token Token :: path_ (NAME, "<path to a file>");

	const Token Token :: commentBegin_ (COMMENT_BEGIN, "/*");
	const Token Token :: commentEnd_ (COMMENT_END, "*/");
	const Token Token :: lineComment_ (LINE_COMMENT, "//");

	const Token Token :: signature_ (SIGNATURE, "signature");
	const Token Token :: concept_ (CONCEPT, "concept");
	const Token Token :: relation_ (RELATION, "relation");
	const Token Token :: copy_ (COPY, "copy");
	const Token Token :: decompose_ (DECOMPOSE, "decompose");
	const Token Token :: decompositionOf_ (DECOMPOSITION_OF, "decomposition_of");
	const Token Token :: union_ (UNION, "\u2294");
	const Token Token :: assert_ (ASSERT, "assert");
	const Token Token :: concepts_ (CONCEPTS, "concepts");
	const Token Token :: relations_ (RELATIONS, "relations");
	const Token Token :: file_ (FILE, "file:");
	const Token Token :: minimize_ (MINIMIZE, "minimize");
	const Token Token :: minimizationOf_ (MINIMIZATION_OF, "minimization_of");

	const Token Token :: eof_ (EOF_, "eof");

	const Token Token :: tokens_[NUMBER_OF_TOKENS] =
	{
		unknown_,        subset_,          intersect_,
		exists_,         equal_,           top_,
		models_,         does_not_model_,  dot_,
		theory_,         does_,            solution_,
		equality_,       question_,        assertion_,
		comma_,          openBrace_,       closeBrace_,
		closeBracket_,   openBracket_,     name_,            path_,
		commentBegin_,   commentEnd_,      lineComment_,
		signature_,      concept_,         relation_,
		copy_,           decompose_,       decompositionOf_,
		union_,          assert_,          concepts_,
		relations_,      file_,            minimize_,
		minimizationOf_, eof_
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

#endif /*DEL_LEXER_TOKEN_CPP_*/

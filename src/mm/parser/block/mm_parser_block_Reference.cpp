/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Reference.cpp                            */
/* Description:     reference in proof parser                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_REFERENCE_CPP_
#define MM_PARSER_BLOCK_REFERENCE_CPP_

#include "mm/auxiliary/mm_auxiliary.hpp"
#include "mm/lexer/mm_lexer.hpp"
#include "mm/ast/mm_ast.hpp"
#include "mm/parser/mm_parser.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Reference :: Reference() :
	location_ () {
	}
	Reference :: ~ Reference() {
	}

using manipulator :: endLine;

	const mm :: source :: Reference*
	Reference :: parse (Lexer* const lexer, const mm :: source :: Block* const block)
	{
		location_ = lexer->getLocation();
		const String&
			token = lexer->getToken();
		const mm :: source :: Reference*
			reference = NULL;

		reference = createAssertionReference (token);
		if (reference != NULL) {
			return reference;
		}
		reference = createHypothesisReference (token, block);
		if (reference != NULL) {
			return reference;
		}
		Error* error = new Error (location_, Error :: SEMANTIC);
		error->message() << "unknown label: " << token << " in proof." << endLine;
		throw error;
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

	/****************************
	 *		Public members
	 ****************************/

	const mm :: source :: Reference*
	Reference :: createAssertionReference (const String& token) const
	{
		const index :: Assertion
			assertionIndex = Table :: assertionLabels()->find (token);

		if (assertionIndex != index :: undefined :: ASSERTION) {
			const mm :: source :: Assertion* const
				assertion = Math :: assertions()->get (assertionIndex);
			return new ast :: source :: reference :: Assertion (location_, assertion);
		}
		return NULL;
	}
	const mm :: source :: Reference*
	Reference :: createHypothesisReference (const String& token, const mm :: source :: Block* const block) const
	{
		const index :: Assertion
			hypothesisLabel = Table :: hypothesisLabels()->find (token);

		if (hypothesisLabel != index :: undefined :: ASSERTION) {
			const mm :: source :: Hypothesis*
				hypothesis = block->getHypothesis ();
			while (hypothesis != NULL) {
				if (hypothesis->getLabel() == hypothesisLabel) {
					break;
				}
				hypothesis = hypothesis->getPrevious();
			}
			if (hypothesis != NULL) {
				return new ast :: source :: reference :: Hypothesis (location_, hypothesis);
			}
		}
		return NULL;
	}
}
}
}

#endif /*MM_PARSER_BLOCK_REFERENCE_CPP_*/

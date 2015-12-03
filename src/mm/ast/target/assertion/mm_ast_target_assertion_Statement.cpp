#ifndef MM_AST_TARGET_ASSERTION_STATEMENT_CPP_
#define MM_AST_TARGET_ASSERTION_STATEMENT_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

	/****************************
	 *		Public members
	 ****************************/

	Statement :: Statement
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjoineds,
		const mm :: target :: Comments* const comments
	) :
	Assertion (label, variables, disjoineds, comments) {
	}
	Statement :: ~ Statement() {
	}

	// target :: Statement implementation
	void
	Statement :: addHypothesis (const object :: Targetive* const hypothesis) {
		hypotheses_.addLast (hypothesis);
	}
	void
	Statement :: addProposition (const object :: Targetive* const proposition) {
		propositions_.addLast (proposition);
	}

	// object :: Referable implementation
	void
	Statement :: writeReference (String& string) const {
		Assertion :: writeReference (string);
	}

	// object :: Targetive implementation
	void
	Statement :: complete (mm :: target :: Block* const block) const
	{
		Assertion :: complete (block);
		const Hypotheses_ :: Node_* hyp = hypotheses_.getFirst();
		while (hyp != NULL) {
			hyp->getValue()->complete (block);
			hyp = hyp->getNext();
		}
		const Propositions_ :: Node_* prop = hypotheses_.getFirst();
		while (prop != NULL) {
			prop->getValue()->complete (block);
			prop = prop->getNext();
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Statement :: write (String& string) const
	{
		Assertion :: write (string);
		string << tab << mdl :: Token :: openBrace_ << endLine;
		writeBody (string);
		string << tab << mdl :: Token :: closeBrace_ << endLine;
	}

	// object :: Object implementation
	Size_t
	Statement :: getVolume() const
	{
		Size_t volume = 0;
		volume += Assertion :: getVolume();
		volume += hypotheses_.getVolume();
		volume += propositions_.getVolume();
		return volume;
	}
	Size_t
	Statement :: getSizeOf() const {
		return sizeof (Statement);
	}

	/****************************
	 *		Protected members
	 ****************************/

	void
	Statement :: writeBody (String& string) const
	{
		if (!hypotheses_.isEmpty()) {
			writeHypotheses (string);
			string << tab << tab << mdl :: Token :: horisontalBar_ << endLine;
		}
		writePropositions (string);
	}
	void
	Statement :: writeHypotheses (String& string) const
	{
		const Hypotheses_ :: Node_*
			node = hypotheses_.getFirst();
		const mm :: object :: Targetive*
			hypothesis = NULL;
		while (node != NULL) {
			hypothesis = node->getValue();
			hypothesis->write (string);
			node = node->getNext();
		}
	}
	void
	Statement :: writePropositions (String& string) const
	{
		const Propositions_ :: Node_*
			node = propositions_.getFirst();
		const mm :: object :: Targetive*
			proposition = NULL;
		while (node != NULL) {
			proposition = node->getValue();
			proposition->write (string);
			node = node->getNext();
		}
	}
}
}
}
}

#endif /*MM_AST_TARGET_ASSERTION_STATEMENT_CPP_*/


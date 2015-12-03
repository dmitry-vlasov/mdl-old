#ifndef MM_AST_TARGET_ASSERTION_RULE_CPP_
#define MM_AST_TARGET_ASSERTION_RULE_CPP_

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

	inline
	Rule :: Rule
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjoineds,
		const mm :: target :: Comments* const comments
	) :
	Assertion (label, variables, disjoineds, comments) {
	}
	Rule :: ~ Rule() {
		deleteAggregateObject (term_);
	}

	// target :: Syntactic implementation
	void
	Rule :: addTerm (const mm :: target :: Term* const term) {
		term_ = term;
	}

	// object :: Referable implementation
	void
	Rule :: writeReference (String& string) const
	{
		string << mdl :: Token :: rule_ << space;
		string << Table :: assertionLabels()->get(label_) << space;
	}
	void
	Rule :: writeIdentificator (String& string) const {
		string << Table :: assertionLabels()->get(label_) << space;
	}

	// object :: Targetive implementation
	void
	Rule :: complete (mm :: target :: Block* const block) const
	{
		Assertion :: complete (block);
		term_->complete (block);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Rule :: write (String& string) const
	{
		Assertion :: write (string);
		string << tab << mdl :: Token :: openBrace_ << endLine;
		term_->write (string);
		string << tab << mdl :: Token :: closeBrace_ << endLine;
		string << endLine;
	}

	// object :: Object implementation
	void
	Rule :: commitSuicide() {
		delete this;
	}
	Size_t
	Rule :: getVolume() const
	{
		Size_t volume = 0;
		volume += Assertion :: getVolume();
		volume += getAggregateVolume (term_);
		return volume;
	}
	Size_t
	Rule :: getSizeOf() const {
		return sizeof (Rule);
	}
}
}
}
}

#endif /*MM_AST_TARGET_ASSERTION_RULE_CPP_*/

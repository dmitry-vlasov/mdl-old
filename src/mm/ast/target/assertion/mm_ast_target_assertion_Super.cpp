/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_assertion_Super.cpp                        */
/* Description:     mdl supertype declaration                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_ASSERTION_SUPER_CPP_
#define MM_AST_TARGET_ASSERTION_SUPER_CPP_

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
	Super :: Super
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjoineds,
		const mm :: target :: Comments* const comments
	) :
	Assertion (label, variables, disjoineds, comments) {
	}
	Super :: ~ Super() {
		deleteAggregateObject (term_);
	}

	// target :: Syntactic implementation
	void
	Super :: addTerm (const mm :: target :: Term* const term) {
		term_ = term;
	}

	// object :: Referable implementation
	void
	Super :: writeReference (String&) const {
	}
	void
	Super :: writeIdentificator (String&) const {
	}

	// object :: Targetive implementation
	void
	Super :: complete (mm :: target :: Block* const block) const
	{
		Assertion :: complete (block);
		term_->complete (block);

		const mm :: target :: Type* const
			superiorType = findSuperiorType (block);
		mm :: target :: Type* const
			inferiorType = findInferiorType (block);

		inferiorType->setSuper (superiorType);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Super :: write (String& string) const {
	}

	// object :: Object implementation
	void
	Super :: commitSuicide() {
		delete this;
	}
	Size_t
	Super :: getVolume() const
	{
		Size_t volume = 0;
		volume += Assertion :: getVolume();
		volume += getAggregateVolume (term_);
		return volume;
	}
	Size_t
	Super :: getSizeOf() const {
		return sizeof (Super);
	}

	/****************************
	 *		Private members
	 ****************************/

	const mm :: target :: Type*
	Super :: findSuperiorType (const mm :: target :: Block* const block) const
	{
		const Symbol&
			superior = term_->getType();
		const mm :: target :: Type* const
			superiorType = block->getType (superior);
		return superiorType;
	}
	mm :: target :: Type*
	Super :: findInferiorType (const mm :: target :: Block* const block) const
	{
		const Symbol&
			variable = term_->getFirstSymbol ();
		const mm :: target :: Type* const
			inferiorType = variables_->getType (variable);
		return const_cast<mm :: target :: Type* const>(inferiorType);
	}
}
}
}
}

#endif /*MM_AST_TARGET_ASSERTION_SUPER_CPP_*/

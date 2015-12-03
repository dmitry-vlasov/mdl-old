/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Assertion.ipp                              */
/* Description:     metamath assertion                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_ASSERTION_IPP_
#define MM_AST_SOURCE_ASSERTION_IPP_

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Protected members
	 ****************************/

	inline bool
	Assertion :: isStatement () const {
		return proposition_->isStatement();
	}
	inline bool
	Assertion :: isDefinition () const {
		return Table :: assertionLabels()->isDefinition (label_);
	}
	inline bool
	Assertion :: isSuperType () const
	{
		return
			proposition_->isTerm() &&
			proposition_->isTrivial();
	}

	inline const mm :: target :: Variables*
	Assertion :: translateVariables () const {
		return translateVariables (hypothesis_);
	}
	inline const mm :: target :: Disjoineds*
	Assertion :: translateDisjoineds (const bool axiomatic) const
	{
		computeDisjoineds();
		return translateDisjoineds (disjoined_, axiomatic);
	}
	inline void
	Assertion :: translateHypothesis (mm :: target :: Statement* const statement) const {
		translateHypothesis (statement, hypothesis_);
	}


	/****************************
	 *		Private members
	 ****************************/

	inline void
	Assertion :: initStatic () const
	{
		if (substitution_ == NULL) {
			substitution_ = new Substitution();
			localStack_ = new Stack (INITIAL_LOCAL_STACK_CAPACITY);
			arguments_ = new vector :: target :: Step (INITIAL_ARGUMENTS_CAPACITY);
		}
	}
}
}
}

#endif /*MM_AST_SOURCE_ASSERTION_IPP_*/

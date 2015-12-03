/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Proof.cpp                                  */
/* Description:     mdl proof                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_PROOF_CPP_
#define MM_AST_TARGET_PROOF_CPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof (const mm :: target :: Comments* comments) :
	comments_ (comments),
	theorem_ (NULL),
	stepList_ (),
	stepCount_ (0) {
	}
	Proof :: ~ Proof() {
		deleteAggregateObject (comments_);
	}

	// target :: Proof implementation
	void
	Proof :: setTheorem (const mm :: target :: Theorem* theorem) {
		theorem_ = theorem;
	}
	void
	Proof :: addStep (const mm :: target :: Step* const step)
	{
		step->incIndex (stepCount_);
		stepList_.addLast (step);
	}
	void
	Proof :: finalize()
	{
		const mm :: target :: Step* const
			qed = new target :: step :: Qed (stepCount_);
		stepList_.addLast (qed);
	}

	// object :: Targetive implementation
	void
	Proof :: complete (mm :: target :: Block* const block) const
	{
		const list :: target :: Step :: Node_*
			node = stepList_.getFirst();
		const mm :: target :: Step*
			step = NULL;
		while (node != NULL) {
			step = node->getValue();
			step->complete (block);
			node = node->getNext();
		}
	}

	// object :: Writable implementation
	void
	Proof :: write (String& string) const
	{
		string << tab;
		comments_->write (string);
		string << endLine;

		string << tab << mdl :: Token :: proof_ << space;
		string << mdl :: Token :: of_ << space;
		theorem_->writeIdentificator (string);
		string << mdl :: Token :: openBrace_ << endLine;
		const list :: target :: Step :: Node_*
			node = stepList_.getFirst();
		const mm :: target :: Step*
			step = NULL;
		while (node != NULL) {
			step = node->getValue();
			if (Config :: removeProofs()) {
				if (node->getNext() == NULL) {
					step->write (string);
				} else if (node->getNext()->getNext() == NULL) {
					step->write (string);
				}
			} else {
				step->write (string);
			}
			node = node->getNext();
		}
		string << tab << mdl :: Token :: closeBrace_ << endLine;
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		volume += stepList_.getVolume();
		volume += getAggregateVolume (comments_);
		return volume;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
}
}
}

#endif /* MM_AST_TARGET_PROOF_CPP_ */

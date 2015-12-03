/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_assertion_Theorem.hpp                      */
/* Description:     mdl theorem                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_ASSERTION_THEOREM_HPP_
#define MM_AST_TARGET_ASSERTION_THEOREM_HPP_

#include "ast/target/assertion/mm_ast_target_assertion_Statement.hpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

class Theorem :
	public mm :: target :: Theorem,
	public Statement,
	public Scalar<Theorem> {
public :
	Theorem
	(
		const value :: Label,
		const mm :: target :: Variables* const,
		const mm :: target :: Disjoineds* const,
		const mm :: target :: Comments* const
	);
	virtual ~ Theorem();

	// target :: Theorem interface
	virtual void addProof (const mm :: target :: Proof* const);

	// target :: Statement interface
	virtual void addHypothesis (const object :: Targetive* const);
	virtual void addProposition (const object :: Targetive* const);

	// object :: Referable interface
	virtual void writeReference (String&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const mm :: target :: Proof* proof_;
};

}
}
}
}

#endif /*MM_AST_TARGET_ASSERTION_THEOREM_HPP_*/
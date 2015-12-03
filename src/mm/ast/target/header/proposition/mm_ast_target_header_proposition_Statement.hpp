/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_proposition_Statement.hpp           */
/* Description:     mdl statement proposition                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_PROPOSITION_STATEMENT_HPP_
#define MM_AST_TARGET_HEADER_STATEMENT_STATEMENT_HPP_

#include "ast/target/header/proposition/mm_ast_target_header_proposition_Proposition.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {
namespace proposition {

class Statement :
	public Proposition,
	public Scalar<Statement> {
public :
	Statement
	(
		const mm :: Expression* const,
		const index :: Arity = index :: undefined :: ARITY
	);
	virtual ~ Statement();

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
	// target :: Proposition interface
	virtual void writeBody (String&) const;
};

}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_PROPOSITION_STATEMENT_HPP_ */

/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_proposition_Definition.hpp          */
/* Description:     mdl definition proposition                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_PROPOSITION_DEFINITION_HPP_
#define MM_AST_TARGET_HEADER_DEFINITION_DEFINITION_HPP_

#include "ast/target/header/proposition/mm_ast_target_header_proposition_Proposition.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {
namespace proposition {

class Definition :
	public Proposition,
	public Scalar<Definition> {
public :
	Definition
	(
		const mm :: Expression* const,
		const index :: Arity = index :: undefined :: ARITY
	);
	virtual ~ Definition();

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

#endif /* MM_AST_TARGET_HEADER_PROPOSITION_DEFINITION_HPP_ */

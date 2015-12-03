/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Hypothesis.hpp                      */
/* Description:     mdl hypothesis                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_HYPOTHESIS_HPP_
#define MM_AST_TARGET_HEADER_HYPOTHESIS_HPP_

#include "ast/target/header/mm_ast_target_header_Line.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

class Hypothesis :
	public Line,
	public Scalar<Hypothesis> {
public :
	Hypothesis
	(
		const mm :: Expression* const,
		const index :: Arity = index :: undefined :: ARITY
	);
	virtual ~ Hypothesis();

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
};

}
}
}
}

#endif /* MM_AST_TARGET_HEADER_HYPOTHESIS_HPP_ */

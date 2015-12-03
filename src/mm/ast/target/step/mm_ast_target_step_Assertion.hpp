/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Assertion.hpp                         */
/* Description:     mdl assertion proof step                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_STEP_ASSERTION_HPP_
#define MM_AST_TARGET_STEP_ASSERTION_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {
namespace step {

class Assertion :
	public mm :: target :: Step,
	public Scalar<Assertion> {
public :
	Assertion
	(
		const object :: Referable* const,
		const vector :: target :: Step* const,
		const Expression* const
	);
	virtual ~ Assertion();

	// target :: Step interface
	virtual void incIndex (index :: Step&) const;

	// object :: Referable interface
	virtual void writeReference (String&) const;
	virtual void writeIdentificator (String&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	void writeHeader (String&) const;
	void writeArguments (String&) const;
	void writeExpression (String&) const;

	mutable index :: Step index_;
	const object :: Referable* const assertion_;
	const vector :: target :: Step arguments_;
	const Expression expression_;
};

}
}
}
}

#endif /* MM_AST_TARGET_STEP_ASSERTION_HPP_ */

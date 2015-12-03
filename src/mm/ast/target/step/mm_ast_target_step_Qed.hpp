/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Qed.hpp                               */
/* Description:     mdl q.e.d. proof node                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_STEP_QED_HPP_
#define MM_AST_TARGET_STEP_QED_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {
namespace step {

class Qed :
	public mm :: target :: Step,
	public Scalar<Qed> {
public :
	Qed (const index :: Step);
	virtual ~ Qed();

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
	const index :: Step index_;
};

}
}
}
}

#endif /* MM_AST_TARGET_STEP_QED_HPP_ */

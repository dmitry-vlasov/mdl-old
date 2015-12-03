/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Proof.hpp                                  */
/* Description:     mdl proof                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_PROOF_HPP_
#define MM_AST_TARGET_PROOF_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {

class Proof :
	public mm :: target :: Proof,
	public Scalar<Proof> {
public :
	Proof (const mm :: target :: Comments*);
	virtual ~ Proof();

	// target :: Proof interface
	virtual void setTheorem (const mm :: target :: Theorem*);
	virtual void addStep (const mm :: target :: Step* const);
	virtual void finalize();

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const mm :: target :: Comments* comments_;
	const mm :: target :: Theorem* theorem_;

	list :: target :: Step stepList_;
	index :: Step stepCount_;
};

}
}
}

#endif /* MM_AST_TARGET_PROOF_HPP_ */

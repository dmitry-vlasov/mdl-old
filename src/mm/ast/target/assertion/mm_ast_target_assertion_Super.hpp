/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_assertion_Super.hpp                        */
/* Description:     mdl supertype declaration                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"
#include "ast/target/assertion/mm_ast_target_assertion_Assertion.hpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

class Super :
	public mm :: target :: Syntactic,
	public Assertion,
	public Scalar<Super> {
public :
	Super
	(
		const value :: Label,
		const mm :: target :: Variables* const,
		const mm :: target :: Disjoineds* const,
		const mm :: target :: Comments* const
	);
	virtual ~ Super();

	// target :: Syntactic interface
	virtual void addTerm (const mm :: target :: Term* const);

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
	const mm :: target :: Type* findSuperiorType (const mm :: target :: Block* const) const;
	mm :: target :: Type* findInferiorType (const mm :: target :: Block* const) const;

	const mm :: target :: Term* term_;
};

}
}
}
}



/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Declaration.hpp                       */
/* Description:     mdl variable declaration in proof                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {
namespace step {

class Declaration :
	public mm :: target :: Step,
	public Scalar<Declaration> {
public :
	Declaration (const mm :: target :: Typing* const);
	virtual ~ Declaration();

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
	const mm :: target :: Typing* const variable_;
};

}
}
}
}



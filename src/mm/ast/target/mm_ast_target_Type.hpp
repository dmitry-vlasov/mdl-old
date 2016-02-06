/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Type.hpp                                   */
/* Description:     mdl type declaration                                     */
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

class Type :
	public mm :: target :: Type,
	public Scalar<Type> {
public :
	Type (const Symbol&, mm :: target :: Block* const);
	virtual ~ Type();

	// target :: Type interface
	virtual const Symbol& getSymbol() const;
	virtual void setSuper (const mm :: target :: Type* const) const;

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
	mutable bool declared_;
	const Symbol symbol_;
	mutable const mm :: target :: Type* super_;
};

}
}
}



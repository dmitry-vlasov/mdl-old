/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Variables.hpp                       */
/* Description:     mdl variables declarations                               */
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
namespace header {

class Variables :
	public mm :: target :: Variables,
	public Scalar<Variables> {
public :
	Variables ();
	virtual ~ Variables();

	// target :: Variables interface
	virtual void addVariable (const mm :: target :: Typing* const);

	// target :: Typing interface
	virtual const mm :: target :: Type* getType (const Symbol&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		list :: target :: Typing
		Variables_;
	Variables_ variables_;
};

}
}
}
}



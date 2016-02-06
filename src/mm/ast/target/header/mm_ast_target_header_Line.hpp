/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Line.hpp                            */
/* Description:     mdl header line general class                            */
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

class Line : public mm :: object :: Targetive {
public :
	Line
	(
		const mm :: Expression* const,
		const index :: Arity = index :: undefined :: ARITY
	);
	virtual ~ Line();

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const = 0;

	// object :: Writable interface
	virtual void write (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	index :: Literal firstInsideIndex() const;
	index :: Literal lastInsideIndex() const;
	bool expressionInBrackets() const;
	void countDepth (const Symbol&, int&, int&) const;
	bool findTermType (const Symbol&, String&) const;

	const mm :: Expression* const expression_;
	const index :: Arity index_;

};

}
}
}
}



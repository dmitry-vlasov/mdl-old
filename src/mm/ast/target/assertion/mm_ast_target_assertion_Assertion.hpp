/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_target_assertion_Assertion.hpp                    */
/* Description:     mdl assertion base class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"
#include "ast/mm_ast.dpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

class Assertion : virtual public mm :: object :: Referable {
public :
	Assertion
	(
		const value :: Label,
		const mm :: target :: Variables* const,
		const mm :: target :: Disjoineds* const,
		const mm :: target :: Comments* const
	);
	virtual ~ Assertion();

	// object :: Referable interface
	virtual void writeReference (String&) const;
	virtual void writeIdentificator (String&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	const value :: Label label_;
	const mm :: target :: Variables* const variables_;
	const mm :: target :: Disjoineds* const disjoineds_;
	const mm :: target :: Comments* const comments_;
};

}
}
}
}



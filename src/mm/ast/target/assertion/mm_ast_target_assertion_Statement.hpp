/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_assertion_Statement.hpp                    */
/* Description:     mdl statement base class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "ast/target/assertion/mm_ast_target_assertion_Statement.hpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

class Statement :
	virtual public mm :: target :: Statement,
	public Assertion {
public :
	Statement
	(
		const value :: Label,
		const mm :: target :: Variables* const,
		const mm :: target :: Disjoineds* const,
		const mm :: target :: Comments* const
	);
	virtual ~ Statement();

	// target :: Statement interface
	virtual void addHypothesis (const object :: Targetive* const);
	virtual void addProposition (const object :: Targetive* const);

	// object :: Referable interface
	virtual void writeReference (String&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	void writeBody (String&) const;
	void writeHypotheses (String&) const;
	void writePropositions (String&) const;

	typedef list :: object :: Targetive Hypotheses_;
	typedef list :: object :: Targetive Propositions_;
	Hypotheses_ hypotheses_;
	Propositions_ propositions_;
};

}
}
}
}



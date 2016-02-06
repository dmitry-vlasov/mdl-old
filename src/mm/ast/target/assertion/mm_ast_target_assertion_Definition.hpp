/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_target_assertion_Definition.hpp                   */
/* Description:     mdl definition                                           */
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

class Definition :
	public mm :: target :: Definition,
	public ast :: target :: assertion :: Statement,
	public Scalar<Definition> {
public :
	Definition
	(
		const value :: Label,
		const mm :: target :: Variables* const,
		const mm :: target :: Disjoineds* const,
		const mm :: target :: Comments* const
	);
	virtual ~ Definition();

	// target :: Definition interface
	virtual void addDefiendum (const object :: Targetive* const);
	virtual void addDefiniens (const object :: Targetive* const);

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
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const object :: Targetive* defiendum_;
	const object :: Targetive* definiens_;
};

}
}
}
}



/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Provable.hpp                               */
/* Description:     metamath provable assertion                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_PROVABLE_HPP_
#define MM_AST_SOURCE_PROVABLE_HPP_

#include "ast/source/mm_ast_source_Assertion.hpp"

namespace mm {
namespace ast {
namespace source {

class Provable :
	public Assertion,
	public Scalar<Provable> {
public :
	Provable
	(
		const Location&,
		const value :: Label,
		const vector :: Literal&,
		const mm :: source :: Proof* const,
		mm :: source :: Block* const,
		const mm :: source :: Comments*
	);
	virtual ~ Provable();

	// source :: Assertion interface
	virtual void applyCheck (Stack* const) const;
	virtual const mm :: target :: Step* applyTranslate (Stack* const) const;
	virtual bool areDisjoined (const value :: Literal, const value :: Literal) const;
	virtual void checkDisjoined (const mm :: source :: Assertion* const) const;
	virtual bool newVariable (const value :: Literal) const;

	virtual bool isAxiomatic() const;
	virtual bool isProvable() const;
	virtual bool isVerified() const;

	// object :: Expressive interface
	virtual bool isEqual (const Expression* const) const;
	virtual void assignTo (const Expression* const);

	// object :: Labeled interface
	virtual value :: Label getLabel() const;

	// object :: Verifiable interface
	virtual void check() const;

	// object :: Translatable interface
	virtual const object :: Targetive* translate() const;
	virtual bool isBlock() const;
	virtual bool isDisjoined() const;
	virtual bool isFloating() const;
	virtual bool isEssential() const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	void checkProposition() const;
	mutable bool isVerified_;
	const mm :: source :: Proof* const proof_;

	mutable const mm :: target :: Theorem* theorem_;
};

}
}
}

#endif /*MM_AST_SOURCE_PROVABLE_HPP_*/

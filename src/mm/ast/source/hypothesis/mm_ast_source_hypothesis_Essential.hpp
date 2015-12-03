/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_hypothesis_Essential.hpp                   */
/* Description:     essential metamath hypothesis                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_HYPOTHESIS_ESSENTIAL_HPP_
#define MM_AST_SOURCE_HYPOTHESIS_ESSENTIAL_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {
namespace hypothesis {

class Essential :
	public mm :: source :: Hypothesis,
	public Scalar<Essential> {
public :
	Essential
	(
		const Location&,
		const value :: Label,
		const vector :: Literal&,
		mm :: source :: Block* const
	);
	virtual ~ Essential();

	// source :: Hypothesis interface
	virtual bool isRelevant (const vector :: Literal&) const;
	virtual void checkFloating (const Expression*, Substitution* const) const;
	virtual void checkEssential (const stack :: Line*, const Substitution* const) const;
	virtual void collectEssentialVariables (vector :: Literal&) const;
	virtual void pushSelf (mm :: Stack* const, const stack :: Line* const = NULL) const;
	virtual const mm :: target :: Step* needDeclaration
	(
		const mm :: source :: Assertion* const,
		const mm :: source :: Proof* const
	) const;
	virtual const mm :: source :: Hypothesis* getPrevious() const;

	// object :: Expressive interface
	virtual bool isEqual (const Expression* const) const;
	virtual void assignTo (const Expression* const);

	// object :: Labeled interface
	virtual value :: Label getLabel() const;

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
	void getIndex () const;

	const Location location_;
	const value :: Label label_;
	const mm :: Expression* expression_;
	const mm :: source :: Hypothesis* const previous_;
	const index :: Arity index_;

	const mm :: target :: Step* step_;
	const mm :: object :: Referable* hypothesis_;
};

}
}
}
}

#endif /*MM_AST_SOURCE_HYPOTHESIS_ESSENTIAL_HPP_*/

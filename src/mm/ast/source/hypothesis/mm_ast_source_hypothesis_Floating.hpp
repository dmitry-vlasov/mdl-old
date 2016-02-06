/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_hypothesis_Floating.hpp                    */
/* Description:     floating metamath hypothesis                             */
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
namespace source {
namespace hypothesis {

class Floating :
	public mm :: source :: Hypothesis,
	public Scalar<Floating> {
public :
	Floating
	(
		const Location&,
		const value :: Label,
		const value :: Literal,
		const value :: Literal,
		mm :: source :: Block* const
	);
	virtual ~ Floating();

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
	void checkSemanticCorrectness (const mm :: source :: Block* const) const;

	const Location location_;
	const value :: Label label_;
	const Symbol type_;
	const Symbol variable_;
	const mm :: source :: Hypothesis* const previous_;
};

}
}
}
}



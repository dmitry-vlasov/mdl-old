/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Block.hpp                                  */
/* Description:     metamath block                                           */
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

class Block :
	public mm :: source :: Block,
	public Scalar<Block> {
public :
	Block
	(
		const Location&,
		const mm :: source :: Source* const
	);
	Block
	(
		const Location&,
		mm :: source :: Block* const,
		mm :: source :: Block* const,
		const mm :: source :: Source* const = NULL
	);
	virtual ~ Block();

	// source :: Block interface
	virtual const mm :: source :: Source* getSource() const;
	virtual const mm :: source :: Constants* getConstants() const;
	virtual const mm :: source :: Variables* getVariables() const;
	virtual const mm :: source :: Disjoined* getDisjoined() const;
	virtual const mm :: source :: Hypothesis* getHypothesis() const;

	virtual void pushConstants (const mm :: source :: Constants* const);
	virtual void pushVariables (const mm :: source :: Variables* const);
	virtual void pushDisjoined (const mm :: source :: Disjoined* const);
	virtual void pushHypothesis (const mm :: source :: Hypothesis* const);
	virtual void pushAssertion (const mm :: source :: Assertion* const);
	virtual void pushBlock (const mm :: source :: Block* const);
	virtual void pushSource (const mm :: source :: Source* const);
	virtual void pushInclude (const mm :: source :: Include* const);

	virtual void translateTo (mm :: target :: Block* const) const;

	// object :: Verifiable interface
	virtual void check() const;

	// object :: Translatable interface
	virtual const object :: Targetive* translate () const;
	virtual bool isBlock() const;
	virtual bool isDisjoined() const;
	virtual bool isFloating() const;
	virtual bool isEssential() const;

	// object :: Writable interface
	virtual void write (String&) const;
	virtual void write (Output&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const mm :: source :: Source* const source_;
	const mm :: source :: Block* const parent_;
	const mm :: source :: Block* const sibling_;

	const mm :: source :: Constants* constants_;
	const mm :: source :: Variables* variables_;
	const mm :: source :: Disjoined* disjoined_;
	const mm :: source :: Hypothesis* hypothesis_;

	list :: object :: Translatable includeList_;
	list :: object :: Translatable componentList_;
	list :: object :: Verifiable verifiableList_;
};

}
}
}



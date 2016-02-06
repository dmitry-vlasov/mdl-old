/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Block.hpp                                  */
/* Description:     mdl theory contents                                      */
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

class Block :
	public mm :: target :: Block,
	public Scalar<Block> {
public :
	Block (const mm :: object :: Referable* const);
	virtual ~ Block();

	//static list :: target :: Type& typeList();

	// target :: Block interface
	virtual void addInclude (const object :: Targetive* const);
	virtual void addComponent (const object :: Targetive* const);
	virtual void addType (const mm :: target :: Type* const);
	virtual const mm :: target :: Type* getType (const Symbol&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;
	virtual void write (Output&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class auxiliary :: Volume;

	void writeHeader (String&) const;
	void writeEnding (String&) const;
	bool noWritableContent() const;
	void writeTo (String&) const;
	void writeInclusions() const;

	const mm :: object :: Referable* const theory_;
	list :: object :: Writable includeList_;
	list :: object :: Writable componentList_;

	static bool staticVolumeCounted_;
	static list :: target :: Type* typeList_;
};

}
}
}



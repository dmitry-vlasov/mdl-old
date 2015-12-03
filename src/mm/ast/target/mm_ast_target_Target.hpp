/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Target.hpp                                 */
/* Description:     mdl target - top AST node                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_TARGET_HPP_
#define MM_AST_TARGET_TARGET_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {

class Target :
	public mm :: target :: Target,
	public Scalar<Target> {
public :
	enum {
		COMMENT_HEADER_WIDTH = 79,
		COMMENT_HEADER_INDENT = 14
	};

	Target (const bool, const mm :: source :: Include* const);
	virtual ~ Target();

	// target :: Target interface
	virtual void addBlock (const object :: Targetive* const);
	virtual const mm :: object :: Referable* getTheory() const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;
	virtual void write() const;
	virtual bool nothingToWrite() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	void writeHeader (String&) const;

	const bool isTop_;
	const mm :: target :: Import* const import_;
	const mm :: object :: Referable* const theory_;
	const mm :: object :: Targetive* block_;
	const Path* path_;
	Output* output_;
};

}
}
}

#endif /* MM_AST_TARGET_TARGET_HPP_ */

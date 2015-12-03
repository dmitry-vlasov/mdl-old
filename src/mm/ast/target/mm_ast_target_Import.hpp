/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Import.hpp                                 */
/* Description:     mdl import                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_IMPORT_HPP_
#define MM_AST_TARGET_IMPORT_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {

class Import :
	public mm :: target :: Import,
	public Scalar<Import> {
public :
	Import (const mm :: source :: Include* const);
	virtual ~ Import();

	// target :: Import interface
	virtual const Path& getPath() const;
	virtual void writeDescription (String&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	Path path_;
};

}
}
}

#endif /* MM_AST_TARGET_IMPORT_HPP_ */

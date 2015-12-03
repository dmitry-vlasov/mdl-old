/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_target_Comments.hpp                               */
/* Description:     Russell comments                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_COMMENTS_HPP_
#define MM_AST_TARGET_COMMENTS_HPP_

#include "interface/mm_interface.hpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace ast {
namespace target {

class Comments :
	public mm :: target :: Comments,
	public Scalar<Comments> {
public :
	Comments (const mm :: source :: Comments*, const bool = false);
	virtual ~ Comments();

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		Lexer :: Comments_ :: Comment_
		Comment_;
	typedef
		Lexer :: Comments_ :: Index_
		Index_;
	const bool date_;
	const mm :: source :: Comments* comments_;
};

}
}
}

#endif /* MM_AST_TARGET_COMMENTS_HPP_ */

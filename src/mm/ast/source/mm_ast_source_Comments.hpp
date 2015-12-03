/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Comments.hpp                               */
/* Description:     metamath comments                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_COMMENTS_HPP_
#define MM_AST_SOURCE_COMMENTS_HPP_

#include "mm/interface/mm_interface.hpp"
#include "mm/lexer/mm_lexer.hpp"

namespace mm {
namespace ast {
namespace source {

class Comments :
	public mm :: source :: Comments,
	public Scalar<Comments> {
public :
	typedef
		Lexer :: Comments_ :: Comment_
		Comment_;
	typedef
		Lexer :: Comments_ :: Index_
		Index_;

	Comments (const Lexer :: Comments_&, const bool = false);
	virtual ~ Comments();

	// source :: Comments interface
	virtual Index_ getSize() const;
	virtual const String* getString (const Index_) const;
	virtual bool isDate (const Index_) const;

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
	typedef
		Vector
		<
			const String,
			storage :: ByPointer,
			allocator :: Heap
		>
		Vector_;
	Vector_ vector_;
	const bool date_;
};

}
}
}

#endif /* MM_AST_SOURCE_COMMENTS_HPP_ */

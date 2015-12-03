/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_term_Term.hpp                       */
/* Description:     abstract mdl term class                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_TERM_TERM_HPP_
#define MM_AST_TARGET_HEADER_TERM_TERM_HPP_

#include "ast/target/header/mm_ast_target_header_Line.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {
namespace term {

class Term :
	public mm :: target :: Term,
	public Line {
public :
	Term
	(
		const mm :: Expression* const,
		const index :: Arity = index :: undefined :: ARITY
	);
	virtual ~ Term();

	// target :: Term interface
	virtual const Symbol& getType() const;
	virtual const Symbol& getFirstSymbol() const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	// target :: Term interface
	virtual void writeHeader (String&) const = 0;
	virtual void writeType (String&) const = 0;
	virtual void writeBody (String&) const = 0;
};

}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_TERM_TERM_HPP_ */

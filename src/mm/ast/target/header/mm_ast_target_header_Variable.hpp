/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Variable.hpp                        */
/* Description:     mdl variable declaration                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_VARIABLE_HPP_
#define MM_AST_TARGET_HEADER_VARIABLE_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

class Variable :
	public mm :: target :: Typing,
	public Scalar<Variable> {
public :
	Variable (const Symbol&, const Symbol&);
	virtual ~ Variable();

	// target :: Typing interface
	virtual const mm :: target :: Type* getType (const Symbol&) const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Symbol variableSymbol_;
	const Symbol typeSymbol_;
	mutable const mm :: target :: Type* type_;
};

}
}
}
}

#endif /* MM_AST_TARGET_HEADER_VARIABLE_HPP_ */

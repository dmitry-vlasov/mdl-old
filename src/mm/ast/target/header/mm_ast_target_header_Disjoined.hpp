/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Disjoined.hpp                       */
/* Description:     mdl disjoined variables restriction                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_DISJOINED_HPP_
#define MM_AST_TARGET_HEADER_DISJOINED_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

class Disjoined :
	public mm :: target :: Disjoined,
	public Scalar<Disjoined> {
public :
	Disjoined (const vector :: Literal* const);
	virtual ~ Disjoined();

	// target :: Disjointed interface
	virtual bool isEmpty() const;

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const vector :: Literal* const variables_;
};

}
}
}
}

#endif /* MM_AST_TARGET_HEADER_DISJOINED_HPP_ */

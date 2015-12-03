/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_reference_Assertion.hpp                    */
/* Description:     proof reference to assertion                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_REFERENCE_ASSERTION_HPP_
#define MM_AST_SOURCE_REFERENCE_ASSERTION_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {
namespace reference {

class Assertion :
	public mm :: source :: Reference,
	public Scalar<Assertion> {
public :
	Assertion
	(
		const Location&,
		const mm :: source :: Assertion* const
	);
	virtual ~ Assertion();

	// source :: Reference interface
	virtual void operateCheck
	(
		Stack* const,
		const mm :: source :: Assertion* const
	) const;
	virtual const mm :: target :: Step* operateTranslate
	(
		Stack* const,
		const mm :: source :: Assertion* const,
		const mm :: source :: Proof* const
	) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const mm :: source :: Assertion* const assertion_;
};

}
}
}
}

#endif /* MM_AST_SOURCE_REFERENCE_ASSERTION_HPP_ */

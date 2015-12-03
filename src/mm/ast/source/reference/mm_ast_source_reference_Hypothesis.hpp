/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_reference_Hypothesis.hpp                   */
/* Description:     proof reference to hypothesis                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_REFERENCE_HYPOTHESIS_HPP_
#define MM_AST_SOURCE_REFERENCE_HYPOTHESIS_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {
namespace reference {

class Hypothesis :
	public mm :: source :: Reference,
	public Scalar<Hypothesis> {
public :
	Hypothesis
	(
		const Location&,
		const mm :: source :: Hypothesis* const
	);
	virtual ~ Hypothesis();

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
	const mm :: source :: Hypothesis* const hypothesis_;
};

}
}
}
}

#endif /* MM_AST_SOURCE_REFERENCE_HYPOTHESIS_HPP_ */

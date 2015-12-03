/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Variables.hpp                              */
/* Description:     metamath variables                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_VARIABLES_HPP_
#define MM_AST_SOURCE_VARIABLES_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {

class Variables :
	public mm :: source :: Variables,
	public Scalar<Variables> {
public :
	Variables
	(
		const Location&,
		const vector :: Literal&,
		mm :: source :: Block* const
	);
	virtual ~ Variables();

	// source :: Variables interface
	virtual bool isVariable (const value :: Literal) const;
	virtual const mm :: source :: Variables* getPrevious() const;

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
	void checkSemanticCorrectness (const mm :: source :: Block* const) const;

	const Location location_;
	const vector :: Literal variables_;
	const mm :: source :: Variables* const previous_;
};

}
}
}

#endif /*MM_AST_SOURCE_VARIABLES_HPP_*/

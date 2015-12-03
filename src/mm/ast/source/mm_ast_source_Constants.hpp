/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Constants.hpp                              */
/* Description:     metamath constants                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_CONSTANTS_HPP_
#define MM_AST_SOURCE_CONSTANTS_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {

class Constants :
	public mm :: source :: Constants,
	public Scalar<Constants> {
public :
	Constants
	(
		const Location&,
		const mm :: source :: Comments*,
		const vector :: Literal&,
		mm :: source :: Block* const
	);
	virtual ~ Constants();

	// source :: Constants interface
	virtual bool isConstant (const value :: Literal) const;
	virtual const mm :: source :: Constants* getPrevious () const;
	virtual void addTo (vector :: Literal&) const;

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
	const mm :: source :: Comments* const comments_;
	const vector :: Literal constants_;
	const mm :: source :: Constants* const previous_;
};

}
}
}

#endif /*MM_AST_SOURCE_CONSTANTS_HPP_*/

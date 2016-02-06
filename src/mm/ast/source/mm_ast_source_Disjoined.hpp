/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Disjoined.hpp                              */
/* Description:     metamath disjoined variables                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {

class Disjoined :
	public mm :: source :: Disjoined,
	public Scalar<Disjoined> {
public :
	Disjoined
	(
		const Location&,
		const vector :: Literal&,
		mm :: source :: Block* const
	);
	Disjoined (const mm :: source ::Disjoined*, const vector :: Literal&);
	virtual ~ Disjoined();

	// source :: Disjointed interface
	virtual bool areDisjoined (const value :: Literal, const value :: Literal) const;
	virtual const mm :: source :: Disjoined* getPrevious() const;

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
	void checkSemanticCorrectnes (const mm :: source :: Block* const) const;

	const Location location_;
	const vector :: Literal variables_;
	const mm :: source :: Disjoined* const previous_;
};

}
}
}



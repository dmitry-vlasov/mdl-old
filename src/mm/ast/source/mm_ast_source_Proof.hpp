/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Proof.hpp                                  */
/* Description:     metamath proof                                           */
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

class Proof :
	public mm :: source :: Proof,
	public Scalar<Proof> {
public :
	Proof (const Location&);
	virtual ~ Proof();

	// source :: Proof interface
	virtual void setAssertion (const mm :: source :: Assertion* const);
	virtual void addReference (const mm :: source :: Reference* const);
	virtual const Expression* getFinalExpression() const;
	virtual bool newVariable (const value :: Literal) const;
	virtual void addComments (const mm :: source :: Comments*);

	// object :: Verifiable interface
	virtual void check() const;

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
	void initStatic() const;
	void showStack (Error*) const;

	const Location location_;
	const mm :: source :: Comments* comments_;
	const mm :: source :: Assertion* assertion_;
	list :: source :: Reference referenceList_;

	mutable mm :: target :: Proof* proof_;
	mutable vector :: Literal variables_;

	static bool staticVolumeCounted_;
	static mm :: Stack* stack_;
	enum {
		INITIAL_STACK_CAPACITY = 1024
	};
	friend class auxiliary :: Volume;
};

}
}
}



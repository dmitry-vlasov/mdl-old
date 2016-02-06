/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Assertion.hpp                              */
/* Description:     metamath assertion                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"
#include "ast/mm_ast.dpp"

namespace mm {
namespace ast {
namespace source {

class Assertion : public mm :: source :: Assertion {
public :
	Assertion
	(
		const Location&,
		const value :: Label,
		const vector :: Literal&,
		mm :: source :: Block* const,
		const mm :: source :: Comments*
	);
	virtual ~ Assertion();

	// source :: Assertion interface
	virtual void applyCheck (Stack* const) const;
	virtual const mm :: target :: Step* applyTranslate (Stack* const) const;
	virtual bool areDisjoined (const value :: Literal, const value :: Literal) const;
	virtual void checkDisjoined (const mm :: source :: Assertion* const) const;
	virtual bool newVariable (const value :: Literal) const;

	virtual bool isAxiomatic() const = 0;
	virtual bool isProvable() const = 0;
	virtual bool isVerified() const = 0;

	// object :: Expressive interface
	virtual bool isEqual (const Expression* const) const;
	virtual void assignTo (const Expression* const);

	// object :: Labeled interface
	virtual value :: Label getLabel() const;

	// object :: Verifiable interface
	virtual void check() const = 0;

	// object :: Translatable interface
	virtual const object :: Targetive* translate() const = 0;
	virtual bool isBlock() const;
	virtual bool isDisjoined() const;
	virtual bool isFloating() const;
	virtual bool isEssential() const;

	// object :: Writable interface
	virtual void write (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	// translator part
	bool isStatement () const;
	bool isDefinition () const;
	bool isSuperType () const;

	const mm :: target :: Variables* translateVariables() const;
	const mm :: target :: Disjoineds* translateDisjoineds (const bool) const;
	void translateDefinition (mm :: target :: Statement* const) const;
	void translateHypothesis (mm :: target :: Statement* const) const;
	void translateProposition (mm :: target :: Statement* const) const;
	void translateTerm (mm :: target :: Syntactic* const) const;

	const Location location_;
	const value :: Label label_;
	mutable const mm :: source :: Disjoined* disjoined_;
	const mm :: source :: Hypothesis* const hypothesis_;
	const mm :: source :: Comments* const comments_;
	const mm :: Expression* proposition_;

private :
	void initStatic() const;

	// checker part
	void computeVariables();
	void computeDisjoineds() const;
	void unify (Stack* const, const mm :: source :: Hypothesis* const) const;
	void checkHypothesis (const mm :: source :: Hypothesis* const, const bool) const;
	stack :: Line* pushPropositionCheck (Stack* const) const;
	const mm :: target :: Step* pushPropositionTranslate (Stack* const) const;

	vector :: Literal variables_;

	static bool staticVolumeCounted_;
	static mm :: Substitution* substitution_;
	static mm :: Stack* localStack_;
	enum {
		INITIAL_LOCAL_STACK_CAPACITY = 32,
		INITIAL_ARGUMENTS_CAPACITY = 32
	};

	// translator part
	mm :: target :: Variables* translateVariables (const mm :: source :: Hypothesis* const) const;
	mm :: target :: Disjoineds* translateDisjoineds
	(
		const mm :: source :: Disjoined* const,
		const bool
	) const;
	void translateHypothesis (mm :: target :: Statement* const, const mm :: source :: Hypothesis* const) const;

	static vector :: target :: Step* arguments_;
	mutable const mm :: target :: Statement* statement_;
	friend class auxiliary :: Volume;
};

}
}
}

#include "ast/source/mm_ast_source_Assertion.ipp"



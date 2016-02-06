/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_function_Function.hpp                */
/* Description:     evaluation function for proposition                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace function {

class Function : public mdl :: evaluation :: Function {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	Function
	(
		index :: Arity index,
		const mdl :: Proposition*,
		mdl :: Evaluation*
	);
	Function
	(
		const Location&,
		index :: Arity index,
		Term_* term,
		mdl :: Theory*
	);
	virtual ~ Function();

	void setEvaluation (mdl :: Evaluation*);
	void setAssertion (const mdl :: Assertion*);

	// evaluation :: Function interface
	virtual Term_* getTerm();
	virtual const Term_* getTerm() const;
	virtual mdl :: Evaluation* getEvaluation();
	virtual const mdl :: Evaluation* getEvaluation() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	const Location location_;
	index :: Arity index_;
	Term_* term_;

	mdl :: Evaluation*  evaluation_;
	const form :: header :: statement :: Proposition* proposition_;
};

}
}
}
}



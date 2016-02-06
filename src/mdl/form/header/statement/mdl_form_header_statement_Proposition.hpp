/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Proposition.hpp                */
/* Description:     proposition statement class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/header/statement/mdl_form_header_statement_Statement.hpp"

namespace mdl {
namespace form {
namespace header {
namespace statement {

class Proposition :
	virtual public mdl :: Proposition,
	public Statement,
	public Line :: Counter {
public :
	Proposition
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Proposition();

	void addEvaluationFunction (mdl :: evaluation :: Function*);
	void replaceEvaluationFunction (const index :: Arity, mdl :: evaluation :: Function*);

	// mdl :: Proposition interface
	virtual const Location& getLocation() const;
	virtual index :: Assertion getSourceIndex() const;
	virtual index :: Assertion getTargetIndex() const;

	virtual void incRate (const bool sign = true);
	virtual value :: Integer getRate (const bool sign = true) const;

	virtual mdl :: statement :: Experience* getExperience();
	virtual mdl :: evaluation :: Function* getEvaluation (const value :: Name);
	virtual const mdl :: statement :: Experience* getExperience() const;
	virtual const mdl :: evaluation :: Function* getEvaluation (const value :: Name) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		mdl :: vector :: Vector
		<
			mdl :: evaluation :: Function*,
			storage :: ByValue,
			allocator :: Heap
		>
		FunctionVector_;

	enum {
		INITIAL_FUNCTION_VECTOR_CAPACITY = 4
	};

	mdl :: evaluation :: Function* getFunction (const value :: Name);
	const mdl :: evaluation :: Function* getFunction (const value :: Name) const;

	statement :: Experience* experience_;
	index :: Assertion sourceIndex_;
	FunctionVector_ functionVector_;
	value :: Integer positiveRate_;
	value :: Integer negativeRate_;

	static index :: Assertion counter_;
};

}
}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Assertion.hpp                        */
/* Description:     assertion abstract interface                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace block {

class Assertion : virtual public object :: Identifiable {
public :
	enum Kind {
		AXIOM,
		DEFINITION,
		PROBLEM,
		THEOREM
	};

	virtual void addEvaluation (Evaluation*) = 0;
	virtual Kind getKind() const = 0;
	virtual index :: Assertion getIndex() const = 0;
	virtual index :: Arity getHypArity() const = 0;
	virtual index :: Arity getPropArity() const = 0;

	virtual Variables* getVariables() = 0;
	virtual Disjointeds* getDisjointeds() = 0;
	virtual Hypothesis* getHypothesis (const index :: Arity) = 0;
	virtual Proposition* getProposition (const index :: Arity) = 0;
	virtual Evaluation* getEvaluation (const value :: Name) = 0;

	virtual const Variables* getVariables() const = 0;
	virtual const Disjointeds* getDisjointeds() const = 0;
	virtual const Hypothesis* getHypothesis (const index :: Arity) const = 0;
	virtual const Proposition* getProposition (const index :: Arity) const = 0;
	virtual const Evaluation* getEvaluation (const value :: Name) const = 0;
};

	/*bool operator < (const Assertion&, const Assertion&);
	bool operator <= (const Assertion&, const Assertion&);
	bool operator > (const Assertion&, const Assertion&);
	bool operator >= (const Assertion&, const Assertion&);
	bool operator == (const Assertion&, const Assertion&);*/
}
}
}



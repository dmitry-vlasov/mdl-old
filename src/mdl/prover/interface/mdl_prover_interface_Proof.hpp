/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Proof.hpp                           */
/* Description:     interface for proof in prover                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Proof : public object :: Object {
public :
	typedef A Allocator_;
	typedef Base<Allocator_> Base_;
	typedef Node<Allocator_> Node_;
	typedef Proof<Allocator_> Proof_;
	typedef Evidence<Allocator_> Evidence_;
	typedef
		typename Base_ :: Expression_
		Expression_;
	typedef
		typename Base_ :: Substitution_
		Substitution_;

	enum Kind {
		HYP,
		PROP,
		REF,
		TOP
	};

	virtual index :: Arity getUpArity() const = 0;
	virtual Proof* getUp (const index :: Arity) = 0;
	virtual const Proof* getUp (const index :: Arity) const = 0;
	virtual void checkValidity() = 0;

	virtual Proof_* makeCopy() const = 0;
	virtual Kind getKind() const = 0;
	virtual bool isIdentical (const Proof_*) const = 0;
	virtual bool isValid() const = 0;
	virtual void resetCompilation() = 0;
	virtual void verifyIntegrity() = 0;
	virtual const Evidence_* getEvidence() const = 0;
	virtual index :: Step getDepth() const = 0;
	virtual value :: Integer getCardinality() const = 0;
	virtual mdl :: proof :: Step* compileStep (mdl :: proof :: Question*) = 0;
	virtual void compileClaim (mdl :: proof :: Claim*) = 0;
	virtual mdl :: proof :: Reference* getReference() = 0;
	virtual mdl :: proof :: Step* getStep() = 0;
	virtual const mdl :: proof :: Reference* getReference() const = 0;
	virtual const mdl :: proof :: Step* getStep() const = 0;

	virtual void showAsTerm(String&) const = 0;

	Proof* findInvalidProof();
};

	template<class A>
	bool operator == (const Proof<A>&, const Proof<A>&);
}
}
}



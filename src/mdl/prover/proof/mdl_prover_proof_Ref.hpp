/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_proof_Ref.hpp                                 */
/* Description:     reference proof element                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_PROOF_REF_HPP_
#define MDL_PROVER_PROOF_REF_HPP_

#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace proof {

template<class A>
class Ref :
	public Proof<A>,
	public Scalar<Ref<A>, A> {
public :
	typedef A Allocator_;
	typedef Types<Allocator_> Types_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Types_ :: Substitution_
		Substitution_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Proof_
		Proof_;
	typedef
		typename Types_ :: Premise_
		Premise_;

	Ref (const Ref&);
	Ref
	(
		Evidence_*,
		Substitution_*,
		Proof_*
	);
	virtual ~ Ref();

	// prover :: Proof interface
	virtual index :: Arity getUpArity() const;
	virtual Proof_* getUp (const index :: Arity);
	virtual const Proof_* getUp (const index :: Arity) const;
	virtual void checkValidity();
	virtual Proof_* makeCopy() const;
	virtual typename Proof_ :: Kind getKind() const;
	virtual bool isIdentical (const Proof_*) const;
	virtual bool isValid() const;
	virtual void resetCompilation();
	virtual void verifyIntegrity();
	virtual const Evidence_* getEvidence() const;
	virtual index :: Step getDepth() const;
	virtual value :: Integer getCardinality() const;
	virtual mdl :: proof :: Step* compileStep (mdl :: proof :: Question*);
	virtual void compileClaim (mdl :: proof :: Claim*);
	virtual mdl :: proof :: Reference* getReference();
	virtual mdl :: proof :: Step* getStep();
	virtual const mdl :: proof :: Reference* getReference() const;
	virtual const mdl :: proof :: Step* getStep() const;
	virtual void showAsTerm(String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Prop;

	Evidence_* evidence_;
	Substitution_* substitution_;
	Proof_* up_;
	mdl :: proof :: Reference* reference_;
};

}
}
}

#endif /*MDL_PROVER_PROOF_REF_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_redundant_Hypotheses.hpp                    */
/* Description:     remove redundant hypotheses                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_REFACTOR_REDUNDANT_HYPOTHESES_HPP_
#define MDL_REFACTOR_REDUNDANT_HYPOTHESES_HPP_

namespace mdl {
namespace refactor {
namespace redundant {

class Hypotheses :
	public object :: Object,
	public Scalar<Hypotheses> {
public :
	typedef
		mdl :: form :: block :: Theorem
		Theorem_;

	Hypotheses (Format&);
	virtual ~ Hypotheses();

	void refactor (mdl :: Source*);
	bool removeUnusedHypothesis (mdl :: Theorem*);
	bool removeDuplicateHypothesis (mdl :: Theorem*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :

	typedef
		mdl :: form :: proof :: References
		References_;
	typedef
		mdl :: form :: proof :: Reference
		Reference_;

	void collectUsedHypotheses (const mdl :: Theorem*, bool used[]);
	void collectUsedHypotheses (const mdl :: Proof*, bool used[]);
	bool findUnusedHypothesis (bool used[], const index :: Arity arity, index :: Arity& unused) const;
	void removeUnusedHypothesisFromTheorem (Theorem_*, const index :: Arity unused);
	void removeUnusedHypothesisFromReferences (Theorem_*, const index :: Arity unused);
	void removeUnusedHypothesisFromReferences (mdl :: Proof*, const index :: Arity unused);

	bool findDuplicateHypotheses (const mdl :: Theorem*, index :: Arity&, index :: Arity&);
	void removeDuplicateHypothesisFromTheorem (Theorem_*, const index :: Arity duplicate);
	void removeDuplicateHypothesisFromReferences (Theorem_*, const index :: Arity original, const index :: Arity duplicate);
	void removeDuplicateHypothesisFromReferences (mdl :: Proof*, const index :: Arity original, const index :: Arity duplicate);

	void removeHypothesisFromOtherTheorems (const mdl :: Assertion*, const index :: Arity);
	void removeHypothesisFromProof (mdl :: Proof*, const mdl :: Assertion*, const index :: Arity);

	Format format_;
	Format subFormat_;
};

}
}
}

#endif /*MDL_REFACTOR_REDUNDANT_HYPOTHESES_HPP_*/

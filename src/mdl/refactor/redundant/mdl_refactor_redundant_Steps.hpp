/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_redundant_Steps.hpp                         */
/* Description:     remove redundant proof steps                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace refactor {
namespace redundant {

class Steps :
	public object :: Object,
	public Scalar<Steps> {
public :
	Steps (Format&);
	virtual ~ Steps();

	void refactor (mdl :: Source*);

	bool removeUnusedSteps (mdl :: Proof*);
	bool removeDuplicateSteps (mdl :: Proof*);
	bool removeUnusedSteps (mdl :: Theorem*);
	bool removeDuplicateSteps (mdl :: Theorem*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		mdl :: form :: proof :: Proof
		Proof_;
	typedef
		mdl :: form :: block :: Proof
		BlockProof_;
	typedef
		mdl :: form :: proof :: Step
		Step_;
	typedef
		mdl :: form :: proof :: Qed
		Qed_;
	typedef
		mdl :: form :: proof :: References
		References_;
	typedef
		mdl :: form :: proof :: Reference
		Reference_;

	void collectUsedSteps_plain (const mdl :: Proof*, bool used[]);
	void collectUsedSteps_tree (const mdl :: Proof*, bool used[]);
	void collectUsedSteps_step (const mdl :: proof :: Step*, bool used[]);

	bool findUnusedStep (bool used[], const index :: Step length, index :: Step& unused) const;
	void removeUnusedStepFromProof (Proof_*, const index :: Step unused);
	void removeUnusedStepFromReferences (mdl :: Proof*, const index :: Step unused);
	void removeUnusedStepFromQed (mdl :: Proof*, const index :: Step unused);

	bool findDuplicateSteps (const mdl :: Proof*, index :: Step&, index :: Step&);
	void removeDuplicateStepFromProof (Proof_*, const index :: Step duplicate);
	void removeDuplicateStepFromReferences (mdl :: Proof*, const index :: Step original, const index :: Step duplicate);
	void removeDuplicateStepFromQed (mdl :: Proof* proof, const index :: Step original, const index :: Step duplicate);

	Format format_;
	Format subFormat_;
};

}
}
}



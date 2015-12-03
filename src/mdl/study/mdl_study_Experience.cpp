/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_Expreience.cpp                                 */
/* Description:     collecting experience of proposition usage               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_EXPERIENCE_CPP_
#define MDL_STUDY_EXPERIENCE_CPP_

namespace mdl {
namespace study {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Experience :: Experience
	(
		Format& supFormat,
		Sample* sample
	) :
	format_ (supFormat),
	subFormat_ (format_),
	message_ (INITIAL_MESSAGE_CAPACITY),
	sample_ (sample)
	{
		subFormat_.setVerbosity (Config :: VERBOSE_SILENT);
		//subFormat_.setVerbosity (format_.getVerbosity());
	}
	Experience :: ~ Experience() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;
using manipulator :: iterate;

	bool
	Experience :: collect()
	{
		static bool done = false;
		if (done) {
			return false;
		} else {
			format_.message() << "experience collection";
			format_.showStart();
			processMath();
			format_.showFinal();
			done = true;
			return true;
		}
	}

	// object :: Object implementation
	void
	Experience :: commitSuicide() {
		delete this;
	}
	Size_t
	Experience :: getVolume() const
	{
		Size_t volume = 0;
		volume += message_.getVolume();
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		return volume;
	}
	Size_t
	Experience :: getSizeOf() const {
		return sizeof (Experience);
	}
	void
	Experience :: show (String& string) const {
		//showExperience (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Experience :: processMath()
	{
		for (value :: Integer i = 0; i < Math :: proofs()->getSize(); ++ i) {
			mdl :: Proof*
				proof = Math :: proofs()->get (i);
			const value :: Name
				theoremName = proof->getScope()->getAssertion()->getName();
			if (Config :: excludeAssertion() == theoremName) {
				continue;
			}
			/*message_ << "proof of ";
			proof->getScope()->getAssertion()->replicateName (message_);
			message_ << " assertion";
			subFormat_.showStart (message_);
			message_.clear();*/
			processProof (proof);
			//subFormat_.showFinal();
		}
		showExperience();
	}
	void
	Experience :: processProof (const Proof* proof) const
	{
		for (value :: Integer i = 0; i < proof->getLength(); ++ i) {
			const proof :: Step*
				step = proof->getStep (i);
			const proof :: Claim*
				claim = dynamic_cast<const proof :: Claim*>(step);
			if (claim != NULL) {
				const Proof* subproof = claim->getProof();
				processProof (subproof);
				continue;
			}
			const proof :: Assertion*
				assertion = dynamic_cast<const proof :: Assertion*>(step);
			if (assertion != NULL) {
				const_cast<proof :: Assertion*>(assertion)->collectExperience();
				continue;
			}
		}
	}
	void
	Experience :: showExperience()
	{
		for (value :: Integer i = 0; i < Math :: assertions()->getSize(); ++ i) {
			const mdl :: Assertion*
				assertion = Math :: assertions()->get (i);
			for (value :: Integer j = 0; j < assertion->getPropArity(); ++ j) {
				const mdl :: Proposition*
					proposition = assertion->getProposition (j);
				const mdl :: statement :: Experience*
					experience = proposition->getExperience();
				subFormat_.message() << i << " - " << *experience;
				subFormat_.showStart();
				message_.clear();
				subFormat_.showFinal();
			}
		}
	}
}
}

#endif /*MDL_STUDY_EXPERIENCE_CPP_*/

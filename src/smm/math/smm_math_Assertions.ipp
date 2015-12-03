/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Assertions.ipp                                  */
/* Description:     global smm assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_MATH_ASSERTIONS_IPP_
#define SMM_MATH_ASSERTIONS_IPP_

namespace smm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline index :: Assertion
	Assertions :: add (const smm :: Assertion* const assertion)
	{
		if (assertion->getProof() == NULL) {
			++ axiomaticCount_;
		} else {
			++ provableCount_;
		}
		const index :: Assertion
			index = assertionVector_.getSize();
		assertionVector_.add (assertion);
		return index;
	}
	inline const smm :: Assertion*
	Assertions :: get (const index :: Assertion index) const {
		return assertionVector_.getValue (index);
	}
}
}

#endif /*SMM_MATH_ASSERTIONS_IPP_*/

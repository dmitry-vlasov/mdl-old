/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Assertions.ipp                                   */
/* Description:     global metamath assertions container                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MATH_ASSERTIONS_IPP_
#define MM_MATH_ASSERTIONS_IPP_

namespace mm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline void
	Assertions :: add (const mm :: source :: Assertion* const assertion)
	{
		if (assertion->isAxiomatic()) {
			++ axiomaticCount_;
		}
		if (assertion->isProvable()) {
			++ provableCount_;
		}
		assertionVector_.add (assertion);
	}
	inline const mm :: source :: Assertion*
	Assertions :: get (const index :: Assertion index) const {
		return assertionVector_.getValue (index);
	}
}
}

#endif /*MM_MATH_ASSERTIONS_IPP_*/

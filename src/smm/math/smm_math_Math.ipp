/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Math.ipp                                        */
/* Description:     static container for global smm structures               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_MATH_MATH_IPP_
#define SMM_MATH_MATH_IPP_

namespace smm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline Assertions*
	Math :: assertions() {
		return assertions_;
	}
	inline Constants*
	Math :: constants() {
		return constants_;
	}
	inline void
	Math :: release()
	{
		deleteAggregateObject (assertions_);
		deleteAggregateObject (constants_);
	}
}
}

#endif /*SMM_MATH_MATH_IPP_*/

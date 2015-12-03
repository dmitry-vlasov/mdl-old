/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Signatures.ipp                                  */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MATH_SIGNATURES_IPP_
#define DEL_MATH_SIGNATURES_IPP_

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline index :: Signature
	Signatures :: add (const del :: Signature* const signature)
	{
		const index :: Signature
			index = signatureVector_.getSize();
		signatureVector_.add (signature);
		return index;
	}
	inline const del :: Signature*
	Signatures :: get (const index :: Signature index) const
	{
		if (index < signatureVector_.getSize()) {
			return signatureVector_.getValue (index);
		} else {
			return NULL;
		}
	}
}
}

#endif /*DEL_MATH_SIGNATURES_IPP_*/

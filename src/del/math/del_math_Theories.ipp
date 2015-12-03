/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Theories.ipp                                    */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MATH_THEORIES_IPP_
#define DEL_MATH_THEORIES_IPP_

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline index :: Theory
	Theories :: add (const del :: Theory* const theory)
	{
		const index :: Theory
			index = theoryVector_.getSize();
		theoryVector_.add (theory);
		return index;
	}
	inline const del :: Theory*
	Theories :: get (const index :: Theory index) const
	{
		if (index < theoryVector_.getSize()) {
			return theoryVector_.getValue (index);
		} else {
			return NULL;
		}
	}
}
}

#endif /*DEL_MATH_THEORIES_IPP_*/

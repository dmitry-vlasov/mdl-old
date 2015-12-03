/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Source.ipp                                      */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MATH_SOURCE_IPP_
#define DEL_MATH_SOURCE_IPP_

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline void
	Source :: add (del :: Source* const source) {
		source_ = source;
	}
	inline del :: Source*
	Source :: get() const {
		return source_;
	}
}
}

#endif /*DEL_MATH_SOURCE_IPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Mode.ipp                                  */
/* Description:     class for the expression show mode                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_MODE_IPP_
#define MDL_EXPRESSION_MODE_IPP_

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Mode :: Mode () :
	mdl :: Mode () {
	}
	inline
	Mode :: Mode (const String& string) :
	mdl :: Mode (string) {
	}
	inline
	Mode :: Mode (const Mode& mode) :
	mdl :: Mode (mode) {
	}
}
}

#endif /*MDL_EXPRESSION_MODE_IPP_*/

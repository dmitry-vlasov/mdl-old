/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Config.ipp                                  */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_CONFIG_IPP_
#define MM_AUXILIARY_CONFIG_IPP_

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline const char*
	Config :: metamathExtension() {
		return "mm";
	}
}
}

#endif /*MM_AUXILIARY_CONFIG_IPP_*/

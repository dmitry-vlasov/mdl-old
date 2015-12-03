/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Config.ipp                                 */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_AUXILIARY_CONFIG_IPP_
#define SMM_AUXILIARY_CONFIG_IPP_

namespace smm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline const char*
	Config :: smmExtension() {
		return "smm";
	}
}
}

#endif /*SMM_AUXILIARY_CONFIG_IPP_*/

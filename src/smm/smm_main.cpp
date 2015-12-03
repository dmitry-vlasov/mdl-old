/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_main.cpp                                             */
/* Description:     main function for smm                                    */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#include "smm/smm.hpp"
#include "smm/smm.cpp"

using smm :: Config;
using smm :: Smm;
using smm :: Memory;

int main (const int argCount, const char* argValue[])
{
	if (!Config :: proceed (argCount, argValue)) {
		if (Config :: error()) {
			return Smm :: INIT_ERROR;
		} else {
			return Smm :: SUCCESS;
		}
	}
	if (Smm :: initMemory() != Smm :: SUCCESS) {
		return Smm :: INIT_ERROR;
	}

	Smm* const smm = new Smm ();

	if (Config :: verbose()) {
		smm->showStart();
	}

	smm->run();

	if (Config :: verbose()) {
		smm->showFinal();
	}

	Smm :: Status_
		status = smm->getStatus();

	if (Config :: verbose () || (status != Smm :: SUCCESS)) {
		std :: cout << *smm;
	}
	if (Config :: cleanMemory()) {
		smm->commitSuicide();
		if (status == Smm :: SUCCESS) {
			status = Smm :: releaseMemory();
		} else {
			Smm :: releaseMemory();
		}
	}
	return status;
}

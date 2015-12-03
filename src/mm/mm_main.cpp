/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_main.cpp                                              */
/* Description:     main function for mm                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#include "mm.hpp"
#include "mm.cpp"

using mm :: Config;
using mm :: Mm;
using mm :: Memory;

int main (const int argCount, const char* argValue[])
{
	if (!Config :: proceed (argCount, argValue)) {
		if (Config :: error()) {
			return Mm :: INIT_ERROR;
		} else {
			return Mm :: SUCCESS;
		}
	}
	if (Mm :: initMemory() != Mm :: SUCCESS) {
		return Mm :: INIT_ERROR;
	}
	Mm* const mm = new Mm ();

	if (Config :: verbose()) {
		mm->showStart();
	}

	mm->run();

	if (Config :: verbose()) {
		mm->showFinal();
	}

	Mm :: Status_
		status = mm->getStatus();
	if (Config :: verbose () || (status != Mm :: SUCCESS)) {
		std :: cout << *mm;
	}
	if (Config :: cleanMemory()) {
		mm->commitSuicide();
		if (status == Mm :: SUCCESS) {
			status = Mm :: releaseMemory();
		} else {
			Mm :: releaseMemory();
		}
	}
	return status;
}

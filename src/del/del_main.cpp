/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_main.cpp                                             */
/* Description:     main function for del                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#include "del/del.dpp"
#include "del/del.hpp"
#include "del/del.cpp"

using del :: Config;
using del :: Memory;
using del :: Size_t;
using del :: Path;
using del :: Del;

int main (const int argCount, const char* argValue[])
{
	if (!Config :: proceed (argCount, argValue)) {
		if (Config :: error()) {
			return Del :: INIT_ERROR;
		} else {
			return Del :: SUCCESS;
		}
	}
	if (Del :: initMemory() != Del :: SUCCESS) {
		return Del :: INIT_ERROR;
	}

	Del* const del = new Del();

	del->run();

	Del :: Status_
		status = del->getStatus();

	if (Config :: verbose () || (status != Del :: SUCCESS)) {
		std :: cout << *del;
	}
	if (Config :: cleanMemory()) {
		del->commitSuicide();
		if (status == Del :: SUCCESS) {
			status = Del :: releaseMemory();
		} else {
			Del :: releaseMemory();
		}
	}
	return status;
}

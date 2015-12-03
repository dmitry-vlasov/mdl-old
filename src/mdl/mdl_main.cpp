/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_main.cpp                                             */
/* Description:     main function for mdl                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#include "mdl/mdl.dpp"
#include "mdl/mdl.hpp"
#include "mdl/mdl.cpp"

using mdl :: Config;
using mdl :: Memory;
using mdl :: Size_t;
using mdl :: Path;
using mdl :: Engine;
using mdl :: Console;
using mdl :: Server;
using mdl :: showInfo;

int main (const int argCount, const char* argValue[])
{
	if (!Config :: proceed (argCount, argValue)) {
		if (Config :: error()) {
			return Engine :: INIT_ERROR;
		} else {
			return Engine :: SUCCESS;
		}
	}
	if (Engine :: initMemory() != Engine :: SUCCESS) {
		return Engine :: INIT_ERROR;
	}

	Engine* const engine = new Engine();

	Engine :: Status_ status = Engine :: SUCCESS;
	if (Config :: runOnefold()) {
		if (Config :: verbose()) {
			engine->showStart();
		}
		engine->run();
		Engine :: Status_
		status = engine->getStatus();
		if (Config :: verbose () || (status != Engine :: SUCCESS)) {
			engine->showFinal();
		}
	} else if (Config :: runConsole()) {
		Console* console = new Console (engine);
		console->run();
		status = engine->getStatus();
		console->commitSuicide();
	} else if (Config :: runServer()) {
		Server* server = new Server (engine);
		server->run();
		status = engine->getStatus();
		server->commitSuicide();
	}

	if (Config :: cleanMemory()) {
		engine->commitSuicide();
		if (status == Engine :: SUCCESS) {
			status = Engine :: releaseMemory();
		} else {
			Engine :: releaseMemory();
		}
	}
	return status;
}

/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_Smm.cpp                                              */
/* Description:     smm verifier                                             */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <exception>

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/math/smm_math.hpp"
#include "smm/parser/smm_parser.hpp"
#include "smm/smm_Smm.hpp"

namespace smm {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

	Smm :: Smm() :
	file_ (Config :: getSource().getString()),
	path_ (new Path (file_)),
	parser_ (NULL),
	source_ (NULL),
	timers_ (),
	volume_ (this),
	status_ (SUCCESS)
	{
		parser_ = new parser :: Source ();
		Math :: init();
		Table :: init();
	}
	Smm :: ~ Smm()
	{
		Table :: release();
		Math :: release();
		deleteAggregateObject (source_);
		deleteAggregateObject (parser_);
		deleteAggregateObject (path_);
		Config :: release();
		object :: Object :: release();
	}

using std :: endl;
using std :: cout;

	void
	Smm :: run ()
	{
		try {
			process();
		} catch (const Error* error) {
			timers_.stopAll();
			cout << *error << endl;
			status_ = static_cast<Status_>(error->getType());
			delete error;
		} catch (const OutOfMemory& error) {
			timers_.stopAll();
			cout << error << endl;
			Memory :: show (cout);
		} catch (const std :: exception& e) {
			timers_.stopAll();
			cout << "exception: " << e.what() << endl;
			status_ = GENERAL_FAILURE;
		} catch (...) {
			timers_.stopAll();
			cout << "exception." << endl;
			status_ = GENERAL_FAILURE;
		}
	}

	Smm :: Status_
	Smm :: getStatus() const {
		return status_;
	}

	void
	Smm :: showStart() const
	{
		std :: cout << "verifying file " << *path_ << " ... ";
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
		} else {
			std :: cout << std :: flush;
		}
	}
	void
	Smm :: showFinal() const
	{
		std :: cout << "is ";
		if (status_ == SUCCESS) {
			std :: cout << "done ";
		} else {
			std :: cout << "not done ";
		}
		std :: cout << "in " << timers_.total() << std :: endl;
		try {
			if (Config :: showTimings()) {
				std :: cout << std :: endl;
				std :: cout << timers_;
			}
			if (Config :: showMath()) {
				std :: cout << std :: endl;
				Math :: show (std :: cout);
			}
			if (Config :: showVolume() || Config :: showMemory()) {
				std :: cout << std :: endl;
				std :: cout << volume_;
			}
		} catch (const Error* error) {
			std :: cout << *error << std :: endl;
			delete error;
		} catch (const OutOfMemory& error) {
			std :: cout << error << std :: endl;
		} catch (const std :: exception& e) {
			std :: cout << "exception: " << e.what() << std :: endl;
		} catch (...) {
			std :: cout << "exception." << endl;
		}
	}

	Smm :: Status_
	Smm :: initMemory()
	{
		Status_ status = SUCCESS;
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "initializing ... " << std :: flush;
		}
		try {
			Memory :: standard().create();
			Memory :: heap().create();
		} catch (OutOfMemory&) {
			status = Smm :: INIT_ERROR;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << ((status == SUCCESS) ? "done." : "failed.") << std :: endl;
		}
		return status;
	}
	Smm :: Status_
	Smm :: releaseMemory()
	{
		bool success = true;
		if (Config :: verbosity() >= Config :: VERBOSE_MED) {
			std :: cout << "releasing ... " << std :: flush;
		}
		try {
			Memory :: heap().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			std :: cout << std :: endl << chars :: TAB <<exception.what() << ": ";
			std :: cout << exception.getLeak() << " bytes are lost ";
			success = false;
		} catch (std :: exception& exception) {
			std :: cout << exception.what() << std :: endl;
			success = false;
		} catch (...) {
			success = false;
		}
		if (Config :: verbosity() >= Config :: VERBOSE_MED) {
			std :: cout << (success ? "done." : "failed.") << std :: endl;
		}
		return (success ? SUCCESS : RELEASE_ERROR);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Smm :: commitSuicide() {
		delete this;
	}
	Size_t
	Smm :: getVolume() const
	{
		Size_t volume = 0;
		volume += file_.getVolume();
		volume += getAggregateVolume (path_);
		volume += getAggregateVolume (parser_);
		volume += getAggregateVolume (source_);
		volume += timers_.getVolume();
		volume += volume_.getVolume();
		return volume;
	}
	Size_t
	Smm :: getSizeOf() const {
		return sizeof (Smm);
	}
	void
	Smm :: show (String& string) const
	{
		/*if (path_ != NULL) {
			string << "file" << space;
			string << *path_ << space;
			string << "is verified in" << space << timers_.total() << endLine;
		}
		if (Config :: showTimings()) {
			timers_.show (string);
			string << endLine;
		}
		if (Config :: showMath()) {
			Math :: show (string);
			string << endLine;
		}
		if (Config :: showVolume() || Config :: showMemory()) {
			volume_.show (string);
			string << endLine;
		}*/
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Smm :: process ()
	{
		timers_.total().start();
		read();
		verify();
		timers_.total().stop();
	}
	void
	Smm :: read ()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "reading ... " << std :: flush;
		}
		timers_.read().start ();
		source_ = parser_->parse (path_->getString());
		timers_.read().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.read() << std :: endl;
		}
	}
	void
	Smm :: verify ()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "verifying ... " << std :: flush;
		}
		timers_.verify().start();
		source_->verify();
		timers_.verify().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.verify() << std :: endl;
		}
	}
}



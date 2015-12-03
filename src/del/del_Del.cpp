/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_Del.cpp                                              */
/* Description:     del translator/prover                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_DEL_CPP_
#define DEL_DEL_CPP_

#include <exception>

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/math/del_math.hpp"
#include "del/parser/del_parser.hpp"
#include "del/del_Del.hpp"

namespace del {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

	Del :: Del() :
	file_ (Config :: getSource().getString()),
	path_ (new Path (file_)),
	parser_ (new parser :: Source ()),
	source_ (NULL),
	owlMan_ (NULL),
	owlFunc_ (NULL),
	log_ (new Log()),
	timers_ (),
	volume_ (this),
	statistics_ (),
	status_ (SUCCESS)
	{
		Object :: init();
		Math :: init();
		Table :: init();
		srand (system :: getClock());

		if (Config :: getLog().isUndefined()) {
			log_->init ("del.log");
		} else {
			log_->init (Config :: getLog().getString());
		}
	}
	Del :: ~ Del()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "deleting ... " << std :: flush;
		}
		Timers :: release().start(); {
			deleteAggregateObject (source_);
			deleteAggregateObject (parser_);
			deleteAggregateObject (path_);
			deleteAggregateObject (owlMan_);
			deleteAggregateObject (owlFunc_);
			deleteAggregateObject (log_);
			del_ = NULL;
		}
		Timers :: release().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << Timers :: release() << std :: endl;
		}
	}

using std :: endl;
using std :: cout;

	void
	Del :: run()
	{
		if (del_ != NULL) {
			cout << "del already is initialized." << endl;
			status_ = GENERAL_FAILURE;
			return;
		}
		del_ = this;
		try {
			timers_.total().start();
			proceed();
			timers_.total().stop();
		} catch (const Error* error) {
			timers_.stopAll();
			cout << *error << endl;
			status_ = static_cast<Status_>(error->getType());
			delete error;
		} catch (const OutOfMemory& error) {
			timers_.stopAll();
			cout << error << endl;
			Memory :: show (cout);
			status_ = OUT_OF_MEMORY;
		} catch (const std :: exception& exception) {
			timers_.stopAll();
			cout << exception.what() << endl;
			status_ = GENERAL_FAILURE;
		} catch (...) {
			timers_.stopAll();
			cout << "exception." << endl;
			status_ = GENERAL_FAILURE;
		}
	}

	Del :: Status_
	Del :: getStatus() const {
		return status_;
	}
	const Timers&
	Del :: getTimers() const {
		return timers_;
	}
	Timers&
	Del :: timers() {
		return timers_;
	}

	Del*
	Del :: del() {
		return del_;
	}
	const Del*
	Del :: getDel() {
		return del_;
	}
	Del :: Status_
	Del :: initMemory()
	{
		Status_ status = SUCCESS;
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "initializing ... " << std :: flush;
		}
		Timers :: init().start();
		try {
			const Size_t
				stackVolume = Config :: getStackVolume();
			Memory :: standard().create();
			Memory :: heap().create();
			Memory :: pile().create (stackVolume);
		} catch (OutOfMemory&) {
			status = Del :: INIT_ERROR;
		}
		Timers :: init().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << ((status == SUCCESS) ? "done in " : "failed in ") << Timers :: init() << std :: endl;
		}
		return status;
	}
	Del :: Status_
	Del :: releaseMemory()
	{
		bool success = true;
		if (Config :: verbosity() >= Config :: VERBOSE_MED) {
			std :: cout << "releasing ... " << std :: flush;
		}
		Math :: release();
		Table :: release();
		Config :: release();
		Object :: release();

		success &= releaseHeap();
		success &= releaseStack();
		success &= releaseStandard();

		if (Config :: verbosity() >= Config :: VERBOSE_MED) {
			std :: cout << (success ? "done." : "failed.") << std :: endl;
		}
		return (success ? SUCCESS : RELEASE_ERROR);
	}
	inline void
	Del :: showMemory()
	{
		if (del_ != NULL) {
			cout << del_->volume_ << endl;
		}
	}
	inline Volume&
	Del :: volume() {
		return del_->volume_;
	}
	inline Statistics&
	Del :: statistics() {
		return del_->statistics_;
	}
	inline Log*
	Del :: log() {
		return del_->log_;
	}

	inline owl :: func :: Owl*&
	Del :: owlFunc() {
		return owlFunc_;
	}
	inline owl :: man :: Owl*&
	Del :: owlMan() {
		return owlMan_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Del :: commitSuicide() {
		delete this;
	}
	Size_t
	Del :: getVolume() const
	{
		Size_t volume = 0;
		volume += file_.getVolume();
		volume += getAggregateVolume (path_);
		volume += getAggregateVolume (parser_);
		volume += getAggregateVolume (source_);
		volume += getAggregateVolume (owlMan_);
		volume += getAggregateVolume (owlFunc_);
		volume += getAggregateVolume (log_);

		volume += timers_.getVolume();
		volume += volume_.getVolume();
		volume += statistics_.getVolume();
		return volume;
	}
	Size_t
	Del :: getSizeOf() const {
		return sizeof (Del);
	}
	void
	Del :: show (String& string) const
	{
		if (path_ == NULL) {
			string << "file <none>" << space;
		} else {
			string << "file" << space;
			string << *path_ << space;
		}
		string << "is done in" << space << timers_.total() << endLine;
		string << endLine;

		try {
			if (Config :: showTimings()) {
				timers_.show (string);
				string << endLine;
			}
			if (Config :: showMath()) {
				//Math :: show (string);
				string << endLine;
			}
			if (Config :: showVolume() || Config :: showMemory()) {
				volume_.show (string);
			}
			if (Config :: showStatistics()) {
				statistics_.show (string);
			}
		} catch (const Error* error) {
			cout << *error << endl;
			delete error;
		} catch (const OutOfMemory& error) {
			cout << error << endl;
		} catch (const std :: exception& e) {
			cout << "exception: " << e.what() << endl;
		} catch (...) {
			cout << "exception." << endl;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Del :: proceed()
	{
		read();
		if (!Config :: translate()) {
			if (Config :: solve()) {
				solve();
			}
			if (Config :: minimize()) {
				minimize();
			}
			if (Config :: decompose()) {
				decompose();
			}
			verify();
		}
		if (Config :: outputToStdout()) {
			outputToStd();
		}
		if (Config :: write()) {
			write();
		}
		writeLog();
	}
	void
	Del :: read()
	{
		if (Config :: generateRandomSource()) {
			source_ = source :: Source :: createRandom ();
		} else {
			switch (Config :: inputFormat()) {
			case Config :: DEL_FORMAT :
				if (Config :: verbosity() > Config :: VERBOSE_MIN) {
					std :: cout << "reading ... " << std :: flush;
				}
				timers_.read().start();
				source_ = const_cast<del :: Source*>(parser_->parse (*path_));
				timers_.read().stop();
				if (Config :: verbosity() > Config :: VERBOSE_MIN) {
					std :: cout << "done in " << timers_.read() << std :: endl;
				}
				break;
			case Config :: MAN_FORMAT :
				owlMan_ = new owl :: man :: Owl (this);
				owlMan_->read();
				source_ = owlMan_->getSource()->createSource();
				break;
			case Config :: FUNC_FORMAT :
				owlFunc_= new owl :: func :: Owl (this);
				owlFunc_->read();
				source_ = owlFunc_->getSource()->createSource();
				break;
			}
		}
	}
	void
	Del :: solve()
	{
		if (!source_->isSolvable()) {
			return;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "solving ... " << std :: flush;
		}
		timers_.solve().start();
		source_->solve();
		timers_.solve().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.solve() << std :: endl;
		}
	}
	void
	Del :: minimize()
	{
		if (!source_->isMinimizable()) {
			return;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "minimizing ... " << std :: flush;
		}
		timers_.minimize().start();
		source_->minimize();
		timers_.minimize().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.minimize() << std :: endl;
		}
	}
	void
	Del :: decompose()
	{
		if (!source_->isDecomposable()) {
			return;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "decomposing ... " << std :: flush;
		}
		timers_.execute().start();
		source_->decompose();
		timers_.execute().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.execute() << std :: endl;
		}
	}
	void
	Del :: verify()
	{
		if (!source_->isVerifiable()) {
			return;
		}
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
	void
	Del :: write()
	{
		if (!source_->isWritable()) {
			return;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "writing ... ";
			if (Config :: outputFormat() == Config :: DEL_FORMAT) {
				std :: cout << std :: flush;
			} else {
				std :: cout << std :: endl;
			}
		}
		//std :: cout << *source_ << std ::endl;
		source_->write();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done." << std :: endl;
		}
	}
	void
	Del :: writeLog()
	{
		if (log_ != NULL) {
			statistics_.show (log_->message (Log :: DECOMPOSITION_LOG));
			log_->write();
		}
	}
	void
	Del :: outputToStd()
	{
		//timers_.solve().start();
		std :: cout << "<output>" << std :: endl;
		std :: cout << *source_ << std :: endl;
		//timers_.solve().stop();
		std :: cout << "</output>" << std :: endl;
	}

	bool
	Del :: releaseHeap()
	{
		bool success = true;
		try {
			Memory :: heap().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << std :: endl << chars :: TAB << exception.what() << ": ";
				std :: cout << exception.getLeak() << " bytes are lost ";
			}
			success = false;
		} catch (std :: exception& exception) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << exception.what() << std :: endl;
			}
			success = false;
		} catch (...) {
			success = false;
		}
		return success;
	}
	bool
	Del :: releaseStack()
	{
		bool success = true;
		try {
			Memory :: pile().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout  << std :: endl << chars :: TAB << exception.what() << ": ";
				std :: cout << exception.getLeak() << " bytes are lost ";
			}
			success = false;
		} catch (std :: exception& exception) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << exception.what() << std :: endl;
			}
			success = false;
		} catch (...) {
			success = false;
		}
		return success;
	}
	bool
	Del :: releaseStandard()
	{
		bool success = true;
		try {
			Memory :: standard().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout  << std :: endl << chars :: TAB << exception.what() << ": ";
				std :: cout << exception.getLeak() << " bytes are lost ";
			}
			success = false;
		} catch (std :: exception& exception) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << exception.what() << std :: endl;
			}
			success = false;
		} catch (...) {
			success = false;
		}
		return success;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	Del* Del :: del_ = NULL;
}

#endif /*DEL_DEL_CPP_*/

/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_Mm.cpp                                                */
/* Description:     mm decompiler                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MM_CPP_
#define MM_MM_CPP_

#include <exception>

#include "mm/ast/mm_ast.cpp"
#include "mm/auxiliary/mm_auxiliary.cpp"
#include "mm/expression/mm_expression.cpp"
#include "mm/interface/mm_interface.cpp"
#include "mm/lexer/mm_lexer.cpp"
#include "mm/math/mm_math.cpp"
#include "mm/parser/mm_parser.cpp"

namespace mm {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

	Mm :: Mm() :
	file_ (Config :: getSource().getString()),
	path_ (new Path (file_)),
	parser_ (new Parser_()),
	cutParser_ (new CutParser_()),
	source_ (NULL),
	cutSource_ (NULL),
	target_ (NULL),
	timers_ (),
	volume_ (this),
	status_ (SUCCESS)
	{
		Math :: init();
		Table :: init();
		Corrector :: init();
	}
	Mm :: ~ Mm()
	{
		Corrector :: release();
		Table :: release();
		Math :: release();
		deleteAggregateObject (target_);
		deleteAggregateObject (source_);
		deleteAggregateObject (cutSource_);
		deleteAggregateObject (parser_);
		deleteAggregateObject (cutParser_);
		deleteAggregateObject (path_);
		object :: Object :: release();
		Config :: release();
	}

using std :: endl;
using std :: cout;

	void
	Mm :: run()
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
			status_ = OUT_OF_MEMORY;
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

	Mm :: Status_
	Mm :: getStatus() const {
		return status_;
	}
	void
	Mm :: showStart() const
	{
		switch (Config :: getRunMode()) {
		case Config :: CHECK_WORK :
			std :: cout << "checking"; break;
		case Config :: TRANSLATE_WORK :
			std :: cout << "translating"; break;
		case Config :: CUT_WORK :
			std :: cout << "cutting"; break;
		default : break;
		}
		std :: cout << " file " << *path_ << " ... ";
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
		} else {
			std :: cout << std :: flush;
		}
	}
	void
	Mm :: showFinal() const
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

	Mm :: Status_
	Mm :: initMemory()
	{
		Status_ status = SUCCESS;
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "initializing ... " << std :: flush;
		}
		try {
			Memory :: standard().create();
			Memory :: heap().create();
		} catch (OutOfMemory&) {
			status = Mm :: INIT_ERROR;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << ((status == SUCCESS) ? "done." : "failed.") << std :: endl;
		}
		return status;
	}
	Mm :: Status_
	Mm :: releaseMemory()
	{
		bool success = true;
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "releasing ... " << std :: flush;
		}
		try {
			Memory :: heap().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			std :: cout << std :: endl << chars :: TAB << exception.what() << ": ";
			std :: cout << exception.getLeak() << " bytes are lost ";
			success = false;
		} catch (std :: exception& exception) {
			std :: cout << exception.what() << std :: endl;
			success = false;
		} catch (...) {
			success = false;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << (success ? "done." : "failed.") << std :: endl;
		}
		return (success ? SUCCESS : RELEASE_ERROR);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Mm :: commitSuicide() {
		delete this;
	}
	Size_t
	Mm :: getVolume() const
	{
		Size_t volume = 0;
		volume += file_.getVolume();
		volume += getAggregateVolume (path_);
		volume += getAggregateVolume (parser_);
		volume += getAggregateVolume (cutParser_);
		volume += getAggregateVolume (source_);
		volume += getAggregateVolume (cutSource_);
		volume += getAggregateVolume (target_);
		volume += timers_.getVolume();
		volume += volume_.getVolume();
		return volume;
	}
	Size_t
	Mm :: getSizeOf() const {
		return sizeof (Mm);
	}
	void
	Mm :: show (String& string) const
	{
		/*string << "file" << space << *path_ << space;
		string << "is ";
		switch (Config :: getRunMode()) {
		case Config :: CHECK_WORK :
			string << "checked"; break;
		case Config :: TRANSLATE_WORK :
			string << "translated"; break;
		default :
			string << "done"; break;
		}
		string << " in" << space << timers_.total() << endLine;

		if (Config :: showTimings()) {
			string << endLine;
			timers_.show (string);
		}
		if (Config :: showMath()) {
			string << endLine;
			Math :: show (string);
		}
		if (Config :: showVolume() || Config :: showMemory()) {
			string << endLine;
			volume_.show (string);
		}*/
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Mm :: process ()
	{
		timers_.total().start();
		switch (Config :: getRunMode()) {
		case Config :: CUT_WORK :
			cutRead();
			cutWrite();
			break;
		case Config :: CHECK_WORK :
			read();
			check();
			break;
		case Config :: TRANSLATE_WORK :
			read();
			check();
			translate();
			write();
			break;
		default:
			break;
		}
		timers_.total().stop();
	}
	void
	Mm :: read ()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "reading ... " << std :: flush;
		}
		timers_.read().start ();
		source_ = parser_->parse (path_);
		timers_.read().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.read() << std :: endl;
		}
	}
	void
	Mm :: check ()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "checking ... " << std :: flush;
		}
		timers_.check().start();
		source_->check();
		timers_.check().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.check() << std :: endl;
		}
	}
	void
	Mm :: translate ()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "translating ... " << std :: flush;
		}
		timers_.translate().start();
		target_ = dynamic_cast<const Target*>(source_->translate());
		timers_.translate().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.translate() << std :: endl;
		}
	}
	void
	Mm :: write ()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "writing ... " << std :: flush;
		}
		timers_.write().start();
		target_->write();
		timers_.write().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.write() << std :: endl;
		}
	}
	void
	Mm :: cutRead()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "reading ... " << std :: flush;
		}
		timers_.read().start ();
		cutSource_ = cutParser_->parse (path_);
		timers_.read().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.read() << std :: endl;
		}
	}
	void
	Mm :: cutWrite()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "writing ... " << std :: flush;
		}
		timers_.write().start();
		cutSource_->write();
		timers_.write().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timers_.write() << std :: endl;
		}
	}
}

#endif /*MM_MM_CPP_*/

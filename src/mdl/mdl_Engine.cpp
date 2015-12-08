/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_Engine.cpp                                           */
/* Description:     mdl translator/prover engine                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_ENGINE_CPP_
#define MDL_ENGINE_CPP_

#include <exception>

#include "mdl/auxiliary/mdl_auxiliary.hpp"
#include "mdl/math/mdl_math.hpp"
#include "mdl/parser/mdl_parser.hpp"
#include "mdl/mdl_Engine.hpp"

namespace mdl {

using namespace exception;

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	Engine :: Engine() :
	format_ (),
	subFormat_ (format_),
	path_ (NULL),
	timers_ (),
	log_ (),
	state_ (IDLE),
	status_ (SUCCESS),
	finished_ (false)
	{
		if (engine_ != NULL) {
			subFormat_.message() << "mdl already is initialized." << endLine;
			status_ = GENERAL_FAILURE;
			subFormat_.showMessage();
		}
		engine_ = this;
	}
	Engine :: ~ Engine()
	{
		Format format;
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			format.message() << "deleting";
			format.showStart();
		}
		Timers :: release().start(); {
			Prover :: release();
			Source :: release();
			Refactorer :: release();
			deleteAggregateObject (path_);
			engine_ = NULL;
		}
		Timers :: release().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			format.showFinal();
		}
	}

	bool
	Engine :: execute (Action_ action)
	{
		bool result = true; //< Success.
		if ((Source :: get() == NULL) && (action != doFellTree) && (action != doRead)) {
			subFormat_.message() << "action failed: no source is provided";
			subFormat_.showMessage();
			status_ = INPUT_ERROR;
			result = false;
		} else {
			try {
				action();
			} catch (const Error* error) {
				timers_.stopAll();
				subFormat_.message() << *error << endLine;
				subFormat_.showMessage();
				status_ = static_cast<Status_>(error->getType());
				delete error;
				result = false;
			} catch (const OutOfMemory& error) {
				timers_.stopAll();
				subFormat_.message() << error << endLine;
				subFormat_.showMessage();
				subFormat_.message() << endLine;
				switch (error.getClass()) {
				case OutOfMemory :: HEAP    :
					Config :: showMemory (Config :: SHOW_MEMORY_INFO_HEAP).value() = true;
					break;
				case OutOfMemory :: STACK   :
					Config :: showMemory (Config :: SHOW_MEMORY_INFO_STACK).value() = true;
					break;
				case OutOfMemory :: BOXED   :
					Config :: showMemory (Config :: SHOW_MEMORY_INFO_BOXED).value() = true;
					break;
				case OutOfMemory :: STANDARD:
					Config :: showMemory (Config :: SHOW_MEMORY_INFO_STANDARD).value() = true;
					break;
				default : break;
				}
				Memory :: show (subFormat_.message());
				status_ = OUT_OF_MEMORY;
				result = false;
			} catch (const std :: exception& exception) {
				timers_.stopAll();
				subFormat_.message() << exception.what() << endLine;
				subFormat_.showMessage();
				status_ = GENERAL_FAILURE;
				result = false;
			} catch (...) {
				timers_.stopAll();
				subFormat_.message() << "unresolved exception." << endLine;
				subFormat_.showMessage();
				status_ = GENERAL_FAILURE;
				result = false;
			}
		}
		return result;
	}
	void
	Engine :: clear()
	{
		Math   :: clear();
		Table  :: clear();
		Prover :: clear();
		Source :: clear();
		if (path_ != NULL) {
			path_->commitSuicide();
			path_ = NULL;
		}
		log_.clear();
		status_ = SUCCESS;
		finished_ = false;
	}

	void
	Engine :: run()
	{
		timers_.total().start();

		clear();
		if (!execute (doRead)) { goto end; }

		switch (Config :: getRunMode()) {
		case config :: PROVE_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doProve)) { goto end; }
			break;
		case config :: CHECK_WORK :
			if (!execute (doCheck)) { goto end; }
			break;
		case config :: TRANSLATE_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doTranslate)) { goto end; }
			break;
		case config :: COMPRESS_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doCompress)) { goto end; }
			break;
		case config :: REPROVE_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doReprove)) { goto end; }
			break;
		case config :: REFACTOR_WORK :
			if (Config :: checkBeforeRefactoring()) {
				if (!execute (doCheck)) { goto end; }
			}
			if (!execute (doRefactor)) { goto end; }
			if (!execute (doCheck)) { goto end; }
			break;
		case config :: LEARN_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doLearn)) { goto end; }
			break;
		case config :: TUNE_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doTune)) { goto end; }
			break;
		case config :: BENCHMARK_WORK :
			if (!execute (doCheck)) { goto end; }
			if (!execute (doBenchmark)) { goto end; }
			break;
		case config :: LOOKUP_WORK :
			if (!execute (doLookup)) { goto end; }
			break;
		case config :: MINE_WORK :
			if (!execute (doMine)) { goto end; }
			break;
		default : break;
		}
		if (Config :: useWriting()) {
			if (!execute (doWrite)) { goto end; }
		}
		log_.write();

		end :
		timers_.total().stop();
		finished_ = true;
	}

	// Main actions :
	inline void
	Engine :: read()
	{
		clear();
		execute (doRead);
	}
	inline void
	Engine :: translate() {
		execute (doTranslate);
	}
	inline void
	Engine :: prove() {
		execute (doProve);
	}
	inline void
	Engine :: compress() {
		execute (doCompress);
	}
	inline void
	Engine :: reprove() {
		execute (doReprove);
	}
	inline void
	Engine :: refactor() {
		execute (doRefactor);
	}
	inline void
	Engine :: learn() {
		execute (doLearn);
	}
	inline void
	Engine :: tune() {
		execute (doTune);
	}
	inline void
	Engine :: benchmark() {
		execute (doBenchmark);
	}
	inline void
	Engine :: lookup() {
		execute (doLookup);
	}
	inline void
	Engine :: mine() {
		execute (doMine);
	}
	inline void
	Engine :: check() {
		execute (doCheck);
	}
	inline void
	Engine :: write() {
		execute (doWrite);
	}

	// Interactive proving actions:
	inline void
	Engine :: plantTree() {
		execute (doPlantTree);
	}
	inline void
	Engine :: growTree() {
		execute (doGrowTree);
	}
	inline void
	Engine :: fellTree() {
		execute (doFellTree);
	}
	inline void
	Engine :: infoTree() {
		execute (doInfoTree);
	}
	inline void
	Engine :: confirmProof() {
		execute (doConfirmProof);
	}

	inline Engine :: State_
	Engine :: getState() const {
		return state_;
	}
	inline Engine :: Status_
	Engine :: getStatus() const {
		return status_;
	}
	inline const Timers&
	Engine :: getTimers() const {
		return timers_;
	}
	inline const Log&
	Engine :: getLog() const {
		return log_;
	}
	inline Timers&
	Engine :: timers() {
		return timers_;
	}
	inline Log&
	Engine :: log() {
		return log_;
	}

	void
	Engine :: showStart() const
	{
		switch (Config :: getRunMode()) {
		case config :: PROVE_WORK :
			format_.message() << "proving"; break;
		case config :: CHECK_WORK :
			format_.message() << "checking"; break;
		case config :: TRANSLATE_WORK :
			format_.message() << "translating"; break;
		case config :: COMPRESS_WORK :
			format_.message() << "compressing"; break;
		case config :: REPROVE_WORK :
			format_.message() << "reproving"; break;
		case config :: REFACTOR_WORK :
			format_.message() << "refactoring"; break;
		case config :: LEARN_WORK :
			format_.message() << "learning"; break;
		case config :: TUNE_WORK :
			format_.message() << "tuning"; break;
		case config :: BENCHMARK_WORK :
			format_.message() << "benchmarking"; break;
		}
		format_.message() << " file " << Config :: getSource();
		format_.showStart();
	}
	void
	Engine :: showFinal() const
	{
		format_.showFinal();
		try {
			if (Config :: showTimings()) {
				subFormat_.message() << timers_ << endLine;
				subFormat_.showMessage();
			}
			if (Config :: showMath()) {
				Math :: show (subFormat_.message());
				subFormat_.showMessage();
			}
			if (Config :: showVolume() || Config :: showMemoryBalance()) {
				Volume :: show (subFormat_.message());
				subFormat_.message() << endLine;
				subFormat_.showMessage();
			}
			if (Config :: showMemory())  {
				subFormat_.message() << endLine;
				Memory :: show (subFormat_.message());
				subFormat_.showMessage();
			}
		} catch (const Error* error) {
			subFormat_.message() << *error << endLine;
			subFormat_.showMessage();
			delete error;
		} catch (const OutOfMemory& error) {
			subFormat_.message() << error << endLine;
			subFormat_.showMessage();
		} catch (const std :: exception& e) {
			subFormat_.message() << "exception: " << e.what() << endLine;
			subFormat_.showMessage();
		} catch (...) {
			subFormat_.message() << "unresolved exception." << endLine;
			subFormat_.showMessage();
		}
	}

	inline const Engine*
	Engine :: getEngine() {
		return engine_;
	}
	inline Engine*
	Engine :: get() {
		return engine_;
	}
	Engine :: Status_
	Engine :: initMemory()
	{
		Status_ result = SUCCESS;
		Timer timer;
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			std :: cout << "initializing memory ... " << std :: flush;
		}
		Timers :: init().start();
		try {
			const Size_t
				stackVolume = Config :: getStackVolume();
			Memory :: standard().create();
#ifndef USE_STANDARD_HEAP
			Memory :: heap().create();
#endif
			Memory :: pile().create (stackVolume);
			if (Config :: useProver() && !Config :: proveInHeap()) {
				const Size_t
					proverVolume = Config :: getProverVolume();
				const Size_t
					reserveVolume = Config :: getReserveVolume();
				Memory :: boxed().create (proverVolume, reserveVolume);
			}
		} catch (OutOfMemory&) {
			result = Engine :: INIT_ERROR;
		}
		Timers :: init().stop();
		if (result != SUCCESS) {
			std :: cout << std :: endl;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			std :: cout << "done in " << Timers :: init() << std :: endl;
		}
		return result;
	}
	Engine :: Status_
	Engine :: releaseMemory()
	{
		bool success = true;
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			std :: cout << "releasing memory ... " << std :: flush;
		}
		Timers :: release().start();

		Math :: release();
		Table :: release();
		Config :: release();
		object :: Object :: release();
		form :: block :: Proof :: release();
		lexer :: Location :: deletePositionList();

		success &= releaseHeap();
		success &= releaseStack();
		success &= releaseBoxed();
		success &= releaseStandard();

		Timers :: release().stop();
		if (!success) {
			std :: cout << std :: endl;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			std :: cout << "done in " << Timers :: release() << std :: endl;
		}
		return (success ? SUCCESS : RELEASE_ERROR);
	}
	inline void
	Engine :: showMemory()
	{
		if (engine_ != NULL) {
			Volume :: show (engine_->subFormat_.message());
			engine_->subFormat_.message() << endLine;
			engine_->subFormat_.showMessage();
		}
	}

	// object :: Object implementation
	void
	Engine :: commitSuicide() {
		delete this;
	}
	Size_t
	Engine :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += getAggregateVolume (path_);
		volume += timers_.getVolume();
		volume += log_.getVolume();
		volume += getSizeOf();
		return volume;
	}
	Size_t
	Engine :: getSizeOf() const {
		return sizeof (Engine);
	}
	void
	Engine :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	inline void
	Engine :: setState (State_ state) {
		state_ = state;
	}

	// Main actions:
	void
	Engine :: doRead()
	{
		Engine :: get()->setState (READING);
		doParseSource();
		if (!Config :: shallowParsing()) {
			doParseExpressions();
		}
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doParseSource()
	{
		Engine :: get()->subFormat_.setVerbosity (Config :: VERBOSE_MED);
		Engine :: get()->subFormat_.message() << "reading";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.read().start();
		Path* path = new Path (Config :: getSource());
		Engine :: get()->path_ = path;
		Parser* parser = new Parser (true);
		parser->parse (path);
		parser->commitSuicide();
		Engine :: get()->timers_.read().stop();
		Engine :: get()->subFormat_.showFinal();
	}
	void
	Engine :: doParseExpressions()
	{
		if (Config :: localParsing()) {
			return;
		}
		Engine :: get()->subFormat_.message() << "building";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.build().start();
		Source :: get()->build();
		Engine :: get()->timers_.build().stop();
		Engine :: get()->subFormat_.showFinal();
	}
	inline void
	Engine :: doTranslate() {  // nothing is needed for this
	}
	void
	Engine :: doProve()
	{
		Engine :: get()->setState (PROVING);
		if (Config :: locationIsSet()) {
			Prover :: create (Engine :: get()->subFormat_);
		}
		Engine :: get()->subFormat_.message() << "proving";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.prove().start();
		if (Config :: locationIsSet()) {
			const Time timeLimit = Config :: getTimeLimit();
			Prover :: get()->prove (timeLimit);
		} else {
			Source :: get()->prove();
		}
		Prover :: get()->dump();
		Engine :: get()->timers_.prove().stop();
		Engine :: get()->subFormat_.showFinal();
		if (Config :: locationIsSet()) {
			Prover :: release();
		}
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doCheck()
	{
		Engine :: get()->setState (CHECKING);
		Engine :: get()->subFormat_.message() << "checking";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.check().start();
		Source :: get()->check();
		Engine :: get()->timers_.check().stop();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doCompress()
	{
		Engine :: get()->setState (COMPRESSING);
		Engine :: get()->subFormat_.message() << "compressing";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.compress().start();
		Source :: get()->compress();
		Engine :: get()->timers_.compress().stop();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doReprove()
	{
		Engine :: get()->setState (REPROVING);
		Prover :: create (Engine :: get()->subFormat_);
		Engine :: get()->subFormat_.message() << "reproving";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.reprove().start();
		if (Config :: locationIsSet()) {
			const Time timeLimit = Config :: getTimeLimit();
			Prover :: get()->reprove (timeLimit);
		} else {
			Source :: get()->reprove();
		}
		Engine :: get()->timers_.reprove().stop();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doRefactor()
	{
		Engine :: get()->setState (REFACTORING);
		Refactorer :: create (Engine :: get()->subFormat_);
		Engine :: get()->subFormat_.message() << "refactoring";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.reprove().start(); {
			mdl :: Source* source = Source :: get();
			Refactorer :: get()->refactor (source);
		}
		Engine :: get()->timers_.reprove().stop();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doLearn()
	{
		Engine :: get()->setState (LEARNING);
		Engine :: get()->timers_.learn().start();
		study :: Teacher teacher (Engine :: get()->format_);
		Time timeLimit = Config :: getTimeLimit();
		teacher.teach (timeLimit);
		Engine :: get()->timers_.learn().stop();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doTune()
	{
		Engine :: get()->setState (TUNING);
		Engine :: get()->timers_.tune().start();
		study :: Tuner tuner (Engine :: get()->format_);
		Time timeLimit = Config :: getTimeLimit();
		tuner.tune (timeLimit);
		Engine :: get()->timers_.tune().stop();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doBenchmark()
	{
		Engine :: get()->setState (BENCHING);
		Engine :: get()->timers_.benchmark().start();
		study :: Benchmark benchmark (Engine :: get()->format_);
		Time timeLimit = Config :: getTimeLimit();
		benchmark.benchmark (timeLimit, true);
		Engine :: get()->timers_.benchmark().stop();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doLookup()
	{
		Engine :: get()->setState (LOOKUPING);
		if (!Source :: get()->lookup()) {
			Engine :: get()->format_.message() << "lookup failed" << endLine;
			Engine :: get()->format_.showMessage();
		}
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doMine()
	{
		Engine :: get()->setState (MINING);
		switch (Config :: getMiningMode()) {
		case Config :: MINE_OUTLINE :
			Source :: get()->mine();
			break;
		case Config :: MINE_TYPE_SYSTEM :
			Math :: types()->mine();
			break;
		case Config :: MINE_STRUCTURE :
			Math :: theories()->mine();
			break;
		case Config :: MINE_NOTHING :
			break;
		default : break;
		}
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doWrite()
	{
		Engine :: get()->setState (WRITING);
		Engine :: get()->subFormat_.message() << "writing";
		Engine :: get()->subFormat_.showStart();
		Engine :: get()->timers_.write().start();
		Source :: get()->write();
		Engine :: get()->timers_.write().stop();
		Engine :: get()->subFormat_.showFinal ();
		Engine :: get()->setState (IDLE);
	}

	// Interactive proving actions:
	void
	Engine :: doPlantTree()
	{
		if (Prover :: get() == NULL || !Prover :: get()->provingIsStarted()) {
			Engine :: get()->subFormat_.message() << "starting prover failed: prover is already started";
			Engine :: get()->subFormat_.showMessage();
			return;
		}
		Engine :: get()->setState (PLANTING_TREE);
		Prover :: create (Engine :: get()->subFormat_);
		Engine :: get()->subFormat_.message() << "planting the tree";
		Engine :: get()->subFormat_.showStart();
		Prover :: get()->plantTree();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doGrowTree()
	{
		if (Prover :: get() == NULL || !Prover :: get()->provingIsStarted()) {
			Engine :: get()->subFormat_.message() << "growing the tree failed: prover was not start";
			Engine :: get()->subFormat_.showMessage();
			return;
		}
		Engine :: get()->setState (GROWING_TREE);
		Engine :: get()->subFormat_.message() << "growing the tree";
		Engine :: get()->subFormat_.showStart();
		Prover :: get()->growTree();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doFellTree()
	{
		if (Prover :: get() == NULL || !Prover :: get()->provingIsStarted()) {
			if (Config :: verbosity() > Config :: VERBOSE_MED) {
				Engine :: get()->subFormat_.message() << "stopping prover fails: prover was not start";
				Engine :: get()->subFormat_.showMessage();
			}
			return;
		}
		Engine :: get()->setState (FELLING_TREE);
		Engine :: get()->subFormat_.message() << "felling the tree";
		Engine :: get()->subFormat_.showStart();
		Prover :: get()->fellTree();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doInfoTree()
	{
		if (Prover :: get() == NULL || !Prover :: get()->provingIsStarted()) {
			Engine :: get()->subFormat_.message() << "info failed: prover was not start";
			Engine :: get()->subFormat_.showMessage();
			return;
		}
		Engine :: get()->setState (DOING_INFO_TREE);
		Engine :: get()->subFormat_.message() << "gathering info about the tree";
		Engine :: get()->subFormat_.showStart();
		String& outputBuffer =
			Config :: runConsole() ?
			Console :: get()->outputBuffer() :
			Server  :: get()->outputBuffer();
		Prover :: get()->infoTree (outputBuffer);
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}
	void
	Engine :: doConfirmProof()
	{
		if (Prover :: get() == NULL || !Prover :: get()->provingIsStarted()) {
			Engine :: get()->subFormat_.message() << "proving was not start." << endLine;
			Engine :: get()->subFormat_.showMessage();
			return;
		}
		Engine :: get()->setState (CONFIRMING_PROOF);
		Engine :: get()->subFormat_.message() << "confirming the proof";
		Engine :: get()->subFormat_.showStart();
		Prover :: get()->confirmProof();
		Engine :: get()->subFormat_.showFinal();
		Engine :: get()->setState (IDLE);
	}

	bool
	Engine :: releaseHeap()
	{
		bool success = true;
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
		return success;
	}
	bool
	Engine :: releaseStack()
	{
		bool success = true;
		try {
			Memory :: pile().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			std :: cout  << std :: endl << chars :: TAB << exception.what() << ": ";
			std :: cout << exception.getLeak() << " bytes are lost ";
			success = false;
		} catch (std :: exception& exception) {
			std :: cout << exception.what() << std :: endl;
			success = false;
		} catch (...) {
			success = false;
		}
		return success;
	}
	bool
	Engine :: releaseBoxed()
	{
		bool success = true;
		try {
			Memory :: boxed().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			std :: cout  << std :: endl << chars :: TAB << exception.what() << ": ";
			std :: cout << exception.getLeak() << " bytes are lost ";
			success = false;
		} catch (std :: exception& exception) {
			std :: cout << exception.what() << std :: endl;
			success = false;
		} catch (...) {
			success = false;
		}
		return success;
	}
	bool
	Engine :: releaseStandard()
	{
		bool success = true;
		try {
			Memory :: standard().destroy();
		} catch (memory :: MemoryLeaks& exception) {
			std :: cout  << std :: endl << chars :: TAB << exception.what() << ": ";
			std :: cout << exception.getLeak() << " bytes are lost ";
			success = false;
		} catch (std :: exception& exception) {
			std :: cout << exception.what() << std :: endl;
			success = false;
		} catch (...) {
			success = false;
		}
		return success;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	Engine* Engine :: engine_ = NULL;

	template<class S>
	void
	showInfo (S& string, bool volume, bool balance, bool difference)
	{
		if (Config :: showTimings() && (Engine :: get() != NULL)) {
			string << Engine :: get()->getTimers() << chars :: NEW_LINE;
		}
		if (Config :: showMath()) {
			Math :: show (string);
		}
		if (Config :: showVolume()) {
			Volume :: show (string, volume, balance, difference);
		}
		if (Config :: showMemory())  {
			string << chars :: NEW_LINE;
			Memory :: show (string);
		}
	}
	void
	showInfo (bool volume, bool balance, bool difference) {
		showInfo<std :: ostream> (std :: cout, volume, balance, difference);
	}
}

#endif /*MDL_ENGINE_CPP_*/

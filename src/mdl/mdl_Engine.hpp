/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_Engine.hpp                                           */
/* Description:     mdl translator/prover engine                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/parser/mdl_parser.hpp"

namespace mdl {

class Engine :
	public object :: Object,
	public Scalar<Engine> {
public :
	Engine();
	virtual ~ Engine();

	enum Status_ {
		SUCCESS           = Error :: NONE,
		LEXER_ERROR       = Error :: LEXER,
		SYNTAX_ERROR      = Error :: PARSER,
		SEMANTIC_ERROR    = Error :: SEMANTIC,
		UNIFICATION_ERROR = Error :: UNIFICATION,
		DISJOINTEDS_ERROR = Error :: DISJOINTEDS,
		TRANSLATOR_ERROR  = Error :: TRANSLATOR,
		PROVER_ERROR      = Error :: PROVER,
		INPUT_ERROR       = Error :: INPUT,
		OUTPUT_ERROR      = Error :: OUTPUT,
		INIT_ERROR,
		RELEASE_ERROR,
		OUT_OF_MEMORY,
		GENERAL_FAILURE
	};

	enum State_ {
		IDLE        = 0,
		READING     = 1,
		TRASLATING  = 2,
		PROVING     = 3,
		COMPRESSING = 4,
		REPROVING   = 5,
		REFACTORING = 6,
		LEARNING    = 7,
		TUNING      = 8,
		BENCHING    = 9,
		LOOKUPING   = 10,
		MINING      = 11,
		CHECKING    = 12,
		WRITING     = 13,
		PLANTING_TREE = 14,
		GROWING_TREE  = 15,
		FELLING_TREE  = 16,
		DOING_INFO_TREE  = 17,
		CONFIRMING_PROOF = 18
	};

	typedef void Action_(void);
	bool execute (Action_);
	void clear();

	// Runs engine in the one-fold mode
	void run();

	// Main actions :
	void read();
	void translate();
	void prove();
	void compress();
	void reprove();
	void refactor();
	void learn();
	void tune();
	void benchmark();
	void lookup();
	void mine();
	void check();
	void write();

	// Interactive proving actions:
	void plantTree();
	void growTree();
	void fellTree();
	void infoTree();
	void confirmProof();

	State_  getState() const;
	Status_ getStatus() const;
	const Timers& getTimers() const;
	const Log& getLog() const;
	Timers& timers();
	Log& log();

	void showStart() const;
	void showFinal() const;

	static const Engine* getEngine();
	static Engine* get();
	static Status_ initMemory();
	static Status_ releaseMemory();
	static void showMemory();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void setState (State_);

	friend void doRead();
	friend void doPparseSource();
	friend void doParseExpressions();

	// Main actions :
	static void doRead();
	static void doParseSource();
	static void doParseExpressions();
	static void doTranslate();
	static void doProve();
	static void doCompress();
	static void doReprove();
	static void doRefactor();
	static void doLearn();
	static void doTune();
	static void doBenchmark();
	static void doLookup();
	static void doMine();
	static void doCheck();
	static void doWrite();

	// Interactive proving actions:
	static void doPlantTree();
	static void doGrowTree();
	static void doFellTree();
	static void doInfoTree();
	static void doConfirmProof();

	//void startServer();

	static bool releaseHeap();
	static bool releaseStack();
	static bool releaseBoxed();
	static bool releaseStandard();

	mutable Format format_;
	mutable Format subFormat_;
	Path*   path_;

	Timers  timers_;
	Log     log_;
	State_  state_;
	Status_ status_;
	bool    finished_;

	friend class auxiliary :: Volume;
	friend class parser :: Source;
	static Engine* engine_;
};

template<class S>
void showInfo
(
	S&,
	bool volume = false,
	bool balance = false,
	bool difference = false
);
void showInfo
(
	bool volume = false,
	bool balance = false,
	bool difference = false
);


}



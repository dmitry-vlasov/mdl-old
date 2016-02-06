/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_Del.hpp                                              */
/* Description:     del translator/prover                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/parser/del_parser.hpp"
#include "del/owl/del_owl.hpp"

namespace del {

class Del :
	public Object,
	public Scalar<Del> {
public :
	Del();
	virtual ~ Del();

	enum Status_ {
		SUCCESS          = Error :: NONE,
		LEXER_ERROR      = Error :: LEXER,
		SYNTAX_ERROR     = Error :: PARSER,
		SEMANTIC_ERROR   = Error :: SEMANTIC,
		INPUT_ERROR      = Error :: INPUT,
		OUTPUT_ERROR     = Error :: OUTPUT,
		INIT_ERROR,
		RELEASE_ERROR,
		OUT_OF_MEMORY,
		GENERAL_FAILURE
	};

	void run();

	Status_ getStatus() const;
	const Timers& getTimers() const;
	Timers& timers();

	static Del* del();
	static const Del* getDel();

	static Status_ initMemory();
	static Status_ releaseMemory();

	static void showMemory();
	static Volume& volume();
	static Statistics& statistics();
	static Log* log();

	owl :: func :: Owl*& owlFunc();
	owl :: man :: Owl*& owlMan();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void proceed();
	void read();
	void solve();
	void minimize();
	void decompose();
	void verify();
	void write();
	void writeLog();
	void outputToStd();

	static bool releaseHeap();
	static bool releaseStack();
	static bool releaseStandard();

	const String file_;
	const Path* path_;
	parser :: Source* parser_;
	Source*   source_;

	owl :: man :: Owl* owlMan_;
	owl :: func :: Owl* owlFunc_;
	Log* log_;

	Timers timers_;
	Volume volume_;
	Statistics statistics_;
	Status_ status_;

	friend class auxiliary :: Volume;
	static Del* del_;
};

}



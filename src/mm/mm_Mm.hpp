/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_Mm.hpp                                                */
/* Description:     mm decompiler                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "parser/mm_parser.hpp"

namespace mm {

class Mm : public object :: Object, public Scalar<Mm> {
public :
	Mm();
	virtual ~ Mm();

	enum Status_ {
		SUCCESS          = Error :: NONE,
		LEXER_ERROR      = Error :: LEXER,
		PARSER_ERROR     = Error :: PARSER,
		SEMANTIC_ERROR   = Error :: SEMANTIC,
		CHECKER_ERROR    = Error :: CHECKER,
		TRANSLATOR_ERROR = Error :: TRANSLATOR,
		INPUT_ERROR      = Error :: INPUT,
		OUTPUT_ERROR     = Error :: OUTPUT,
		MISC_ERROR       = Error :: MISC,
		INIT_ERROR,
		RELEASE_ERROR,
		OUT_OF_MEMORY,
		GENERAL_FAILURE
	};

	void run();

	Status_ getStatus() const;

	void showStart() const;
	void showFinal() const;

	static Status_ initMemory();
	static Status_ releaseMemory();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void process ();
	void read();
	void check();
	void translate();
	void write();

	void cutRead();
	void cutWrite();

	typedef
		parser :: Source Parser_;
	typedef
		cut :: parser :: Source CutParser_;
	typedef
		cut :: Source CutSource_;

	const String file_;
	const Path* const path_;
	Parser_* const parser_;
	CutParser_* const cutParser_;
	const Source* source_;
	const CutSource_* cutSource_;
	const Target* target_;

	Timers  timers_;
	Volume  volume_;
	Status_ status_;

	friend class auxiliary :: Volume;
};

}



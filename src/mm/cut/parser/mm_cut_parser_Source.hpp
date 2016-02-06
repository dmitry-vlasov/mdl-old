/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_parser_Source.hpp                                 */
/* Description:     mm source file cutting parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/cut/mm_cut.dpp"
#include "mm/cut/lexer/mm_cut_lexer.hpp"

namespace mm {
namespace cut {
namespace parser {

class Source :
	public object :: Object,
	public Scalar<Source> {
public :
	Source ();
	virtual ~ Source();

	const cut :: Source* parse (const Path* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void open();
	void close();
	void parseContents();

	Lexer* lexer_;
	Path*  path_;

	// internal part
	Location location_;
	parser :: Chapter* chapterParser_;
	parser :: Section* sectionParser_;

	// external part
	source :: Source* source_;
	const source :: Header* header_;
	const source :: Content* content_;
	source :: Chapter* chapter_;
	source :: Section* section_;
	const Includable* prevChapter_;
	const Includable* prevSection_;
};

}
}
}



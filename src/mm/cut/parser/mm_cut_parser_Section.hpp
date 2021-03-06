/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_parser_Section.hpp                                */
/* Description:     mm cutter section parser                                 */
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

class Section :
	public object :: Object,
	public Scalar<Section> {
public :
	Section();
	virtual ~ Section();

	source :: Section* parse
	(
		const source :: Source*,
		const source :: Chapter*,
		Lexer*
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	Location location_;

	// external part
	const source :: Header* header_;
	const source :: Content* content_;
};

}
}
}



/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_Source.hpp                                     */
/* Description:     metamath source parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_SOURCE_HPP_
#define MM_PARSER_SOURCE_HPP_

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {

class Source :
	public object :: Object,
	public Scalar<Source> {
public :
	Source (const bool = true);
	virtual ~ Source();

	const mm :: source :: Source* parse (const Path* const);
	mm :: source :: Block* parse
	(
		const mm :: source :: Include* const,
		mm :: source :: Block*
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void open();
	void close();

	const bool isTop_;
	Lexer* lexer_;

	// internal part
	parser :: Block*  blockParser_;
	Location location_;

	// external part
	const mm :: source :: Include* include_;
	mm :: source :: Source* source_;
	mm :: source :: Block* block_;
};

}
}

#endif /*MM_PARSER_SOURCE_HPP_*/

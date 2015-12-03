/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Source.hpp                                    */
/* Description:     source parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_SOURCE_HPP_
#define MDL_PARSER_SOURCE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {

class Source :
	public object :: Object,
	public Scalar<Source> {
public :
	Source (const bool = false);
	virtual ~ Source();

	mdl :: Source* parse (const mdl :: Path*);
	static Source* get();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void open (const Path*);
	void close (const Path*);

	const bool isTop_;
	Lexer* lexer_;

	// internal part
	parser :: Import* importParser_;
	parser :: Theory* theoryParser_;
	parser :: Source* sourceParser_;
	parser :: Contents*  contentsParser_;

	// external part
	mdl :: Theory* rootTheory_;

	static Source* parser_;
 };

}
}

#endif /*MDL_PARSER_SOURCE_HPP_*/

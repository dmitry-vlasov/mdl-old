/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Theory.hpp                                    */
/* Description:     theory contents parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_THEORY_HPP_
#define DEL_PARSER_THEORY_HPP_

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/parser/del_parser.dpp"

namespace del {
namespace parser {

class Theory :
	public Object,
	public Scalar<Theory> {
public :
	Theory();
	virtual ~ Theory();

	const del :: Theory* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void parseSet (Lexer*);
	void parseTerm (Lexer*);
	void parseFile (Lexer*);

	// internal part
	parser :: Formula* formulaParser_;

	// external part
	Location location_;
	const del :: Comments* comments_;
	value :: Theory name_;
	del :: Theory* theory_;
};

}
}

#endif /*DEL_PARSER_THEORY_HPP_*/

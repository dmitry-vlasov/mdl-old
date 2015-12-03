/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Minimize.hpp                                  */
/* Description:     question parser                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_MINIMIZE_HPP_
#define DEL_PARSER_MINIMIZE_HPP_

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/parser/del_parser.dpp"

namespace del {
namespace parser {

class Minimize :
	public Object,
	public Scalar<Minimize> {
public :
	Minimize();
	virtual ~ Minimize();

	const del :: Minimize* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	value :: Theory theory_;
	const del :: Comments* comments_;
};

}
}

#endif /*DEL_PARSER_MINIMIZE_HPP_*/

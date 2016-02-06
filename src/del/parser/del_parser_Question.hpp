/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Question.hpp                                  */
/* Description:     question parser                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/parser/del_parser.dpp"

namespace del {
namespace parser {

class Question :
	public Object,
	public Scalar<Question> {
public :
	Question();
	virtual ~ Question();

	const del :: Question* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: Formula* formulaParser_;

	// external part
	Location location_;
	value :: Theory theory_;
	const del :: Formula* formula_;
	const del :: Comments* comments_;
};

}
}



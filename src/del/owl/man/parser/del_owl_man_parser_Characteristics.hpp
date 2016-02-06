/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Characteristics.hpp                   */
/* Description:     manchester OWL characteristics parser                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/parser/del_owl_man_parser.dpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

class Characteristics :
	public Object,
	public Scalar<Characteristics> {
public :
	Characteristics();
	virtual ~ Characteristics();

	void parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
};

}
}
}
}



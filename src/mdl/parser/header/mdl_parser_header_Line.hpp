/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Line.hpp                               */
/* Description:     line parser                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace header {

class Line :
	public object :: Object,
	public Scalar<Line> {
public :
	Line();
	virtual ~ Line();

	template<class T, class TF, Token :: Type token>
	T* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: Identificator* identificatorParser_;
	parser :: Expression* expressionParser_;

	// external part
	Location location_;
	index :: Arity index_;
	mdl :: Identificator* type_;
	array :: Expression* expression_;
};

}
}
}



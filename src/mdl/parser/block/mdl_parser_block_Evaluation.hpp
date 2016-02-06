/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Evaluation.hpp                          */
/* Description:     assertion evaluation parser                              */
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
namespace block {

class Evaluation :
	public object :: Object,
	public Scalar<Evaluation> {
public :
	Evaluation();
	virtual ~ Evaluation();

	mdl :: Evaluation* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_FUNCTION_VECTOR_CAPACITY = 16
	};
	// internal part
	parser :: Identificator* identificatorParser_;
	parser :: evaluation :: Function* functionParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	value :: Name name_;
	mdl :: Identificator* identificator_;
	mdl :: evaluation :: parser :: vector :: Function functionVector_;
};

}
}
}



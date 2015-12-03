/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Import.hpp                                    */
/* Description:     import parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_IMPORT_HPP_
#define MDL_PARSER_IMPORT_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {

class Import :
	public object :: Object,
	public Scalar<Import> {
public :
	Import();
	virtual ~ Import();

	mdl :: Import* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: Identificator* identificatorParser_;

	// external part
	Location location_;
	mdl :: Identificator* identificator_;
};

}
}

#endif /*MDL_PARSER_IMPORT_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Constant.hpp                            */
/* Description:     constant parser                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_CONSTANT_HPP_
#define MDL_PARSER_BLOCK_CONSTANT_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace parser {
namespace block {

class Constant :
	public object :: Object,
	public Scalar<Constant> {
public :
	Constant();
	virtual ~ Constant();

	mdl :: Constant* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	String* parseEntry (Lexer*);

	// external part
	Location location_;
	mdl :: Comments* comments_;
	String* symbol_;
	String* ascii_;
	String* latex_;
};

}
}
}

#endif /*MDL_PARSER_BLOCK_CONSTANT_HPP_*/

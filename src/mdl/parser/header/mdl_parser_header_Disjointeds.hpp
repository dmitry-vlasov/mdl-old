/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Disjointeds.hpp                        */
/* Description:     disjointeds parser                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_DISJOINTEDS_HPP_
#define MDL_PARSER_HEADER_DISJOINTEDS_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace header {

class Disjointeds :
	public object :: Object,
	public Scalar<Disjointeds> {
public :
	Disjointeds();
	virtual ~ Disjointeds();

	mdl :: Disjointeds* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: header :: Disjointed* disjointedParser_;

	// external part
	vector :: parser :: Disjointed disjointedVector_;
	enum {
		INITIAL_DISJOINTED_VECTOR_CAPACITY = 8
	};
};

}
}
}

#endif /*MDL_PARSER_HEADER_DISJOINTEDS_HPP_*/

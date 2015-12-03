/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Reference.hpp                           */
/* Description:     proof reference parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_REFERENCE_HPP_
#define MDL_PARSER_PROOF_REFERENCE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace proof {

class Reference :
	public object :: Object,
	public Scalar<Reference> {
public :
	Reference();
	virtual ~ Reference();

	mdl :: proof :: Reference* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	Location location_;

	// external part
	value :: Kind kind_;
	index :: Step index_;
};

}
}
}

#endif /*MDL_PARSER_PROOF_REFERENCE_HPP_*/

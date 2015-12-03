/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       mm_parser_Inclusion.hpp                                  */
/* Description:     inclusion parser                                         */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_INCLUSION_HPP_
#define SMM_PARSER_INCLUSION_HPP_

#include "smm/interface/smm_interface.hpp"
#include "smm/parser/smm_parser.dpp"
#include "smm/lexer/smm_lexer.hpp"

namespace smm {
namespace parser {

class Inclusion :
	public object :: Object,
	public Scalar<Inclusion> {
public :
	Inclusion();
	virtual ~ Inclusion();

	const smm :: Inclusion* parse (Lexer* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	String path_;
	Location location_;
	enum {
		INITIAL_PATH_CAPACITY = 64
	};
};

}
}

#endif /*SMM_PARSER_INCLUSION_HPP_*/

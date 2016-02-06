/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Proof.hpp                                     */
/* Description:     smm proof parser                                         */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/smm_interface.hpp"
#include "smm/parser/smm_parser.dpp"
#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source_Reference.hpp"

namespace smm {
namespace parser {

class Proof :
	public object :: Object,
	public Scalar<Proof> {
public :
	Proof();
	virtual ~ Proof();

	const smm :: Proof* parse (Lexer* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Location location_;

	// external part
	vector :: Reference* referenceVector_;
};

}
}



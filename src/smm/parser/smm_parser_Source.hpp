/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Source.hpp                                    */
/* Description:     smm source parser                                        */
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

namespace smm {
namespace parser {

class Source :
	public object :: Object,
	public Scalar<Source> {
public :
	Source ();
	virtual ~ Source();

	const smm :: Source* parse (const String&);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void open (const String&);
	void close (const String&);
	void parseContents();

	Lexer* lexer_;

	typedef
		Line<Token :: CONSTANT, false>
		Constant_;

	// internal part
	Location location_;
	Constant_* constantsParser_;
	Assertion* assertionParser_;
	Inclusion* inclusionParser_;
	Source*    sourceParser_;

	// external part
	const source :: Inclusion* inclusion_;
	smm :: Source* source_;
};

}
}



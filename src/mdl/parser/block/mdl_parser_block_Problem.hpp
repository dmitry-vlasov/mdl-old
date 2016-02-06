/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Problem.hpp                             */
/* Description:     problem parser                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/parser/block/mdl_parser_block_Assertion.hpp"

namespace mdl {
namespace parser {
namespace block {

class Problem :
	public Assertion<vector :: parser :: Provable>,
	public Scalar<Problem> {
public :
	Problem();
	virtual ~ Problem();

	mdl :: Assertion* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		Assertion<vector :: parser :: Provable>
		Ancestor_;
};

}
}
}



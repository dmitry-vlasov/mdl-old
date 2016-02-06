/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Assertion.hpp                                 */
/* Description:     assertion parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/parser/del_parser.dpp"

namespace del {
namespace parser {

class Assertion :
	public Object,
	public Scalar<Assertion> {
public :
	Assertion();
	virtual ~ Assertion();

	const del :: Assertion* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	value :: Theory theory_;
	value :: Signature signature_;
	vector :: value :: Symbol components_;
	bool isStrong_;
	const del :: Comments* comments_;
	enum {
		INITIAL_COMPONENTS_CAPACITY = 16
	};
};

}
}



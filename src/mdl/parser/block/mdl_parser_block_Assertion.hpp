/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Assertion.hpp                           */
/* Description:     assertion parser                                         */
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

template<class PV>
class Assertion : public object :: Object {
public :
	Assertion();
	virtual ~ Assertion();

	template<class PI, class PF>
	void parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	typedef PV PropositionVector_;

	void parseHypotheses (Lexer*, mdl :: Theory*);
	template<class PI, class PF>
	void parsePropositions (Lexer*, mdl :: Theory*);
	void parseComments (Lexer*);

	// external part
	Location location_;
	lexer :: Indent barIndent_;
	value :: Name name_;
	mdl :: Variables* variables_;
	mdl :: Disjointeds* disjointeds_;
	vector :: parser :: Hypothesis hypothesisVector_;
	PropositionVector_ propositionVector_;

protected :
	// internal part
	parser :: header :: Variables* variablesParser_;
	parser :: header :: Disjointeds* disjointedsParser_;
	parser :: header :: Line* lineParser_;

	// external part
	const mdl :: Comments* comments_;

private :
	enum {
		INITIAL_LINE_VECTOR_CAPACITY = 8
	};
};

}
}
}



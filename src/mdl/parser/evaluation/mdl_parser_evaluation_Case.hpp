/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_evaluation_Case.hpp                           */
/* Description:     FRiS case parameter parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_CASE_HPP_
#define MDL_PARSER_HEADER_CASE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace evaluation {

class Case :
	public object :: Object,
	public Scalar<Case> {
public :
	Case();
	virtual ~ Case();

	mdl :: evaluation :: Case* parse
	(
		Lexer*,
		bool& sign,
		const bool firstPass,
		mdl :: Theory*
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_PATH_CAPACITY = 4
	};

	// internal part
	parser :: Identificator* identificatorParser_;

	// external part
	Location location_;
	bool sign_;
	mdl :: Identificator* identificator_;
	value :: Name name_;
	vector :: value :: Integer path_;
};

}
}
}

#endif /*MDL_PARSER_HEADER_CASE_HPP_*/

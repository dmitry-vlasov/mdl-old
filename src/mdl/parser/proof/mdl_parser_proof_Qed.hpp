/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Qed.hpp                                 */
/* Description:     proof q.e.d. parser                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_QED_HPP_
#define MDL_PARSER_PROOF_QED_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace proof {

class Qed :
	public object :: Object,
	public Scalar<Qed> {
public :
	Qed();
	virtual ~ Qed();

	mdl :: proof :: Qed* parse
	(
		Lexer*,
		mdl :: Theory*,
		mdl :: proof :: Line*
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	const mdl :: Comments* comments_;
	value :: Kind kind_;
	index :: Arity prop_;
	index :: Step step_;
};

}
}
}

#endif /*MDL_PARSER_PROOF_QED_HPP_*/

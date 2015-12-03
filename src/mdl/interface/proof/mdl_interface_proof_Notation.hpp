/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Notation.hpp                         */
/* Description:     abstract interface for notations in proof                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_NOTATION_HPP_
#define MDL_INTERFACE_PROOF_NOTATION_HPP_

#include "mdl/interface/proof/mdl_interface_proof_Line.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Notation : virtual public Line {
public :
	virtual value :: Literal getLiteral() const = 0;

	virtual mdl :: Variables* getVariables() = 0;
	virtual Term* getAbbreviation() = 0;
	virtual Term* getMeaning() = 0;

	virtual const mdl :: Variables* getVariables() const = 0;
	virtual const Term* getAbbreviation() const = 0;
	virtual const Term* getMeaning() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_NOTATION_HPP_*/

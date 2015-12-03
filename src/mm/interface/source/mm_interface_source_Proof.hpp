/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Proof.hpp                            */
/* Description:     abstract interface for metamath proof                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_SOURCE_PROOF_HPP_
#define MM_INTERFACE_SOURCE_PROOF_HPP_

#include "interface/object/mm_interface_object.hpp"
#include "expression/mm_expression.hpp"

namespace mm {
namespace interface {
namespace source {

class Proof : public object :: Verifiable {
public :
	virtual void setAssertion (const Assertion* const) = 0;
	virtual void addReference (const Reference* const) = 0;
	virtual const Expression* getFinalExpression() const = 0;
	virtual bool newVariable (const value :: Literal) const = 0;
	virtual void addComments (const Comments*) = 0;
};

}
}
}

#endif /*MM_INTERFACE_SOURCE_PROOF_HPP_*/

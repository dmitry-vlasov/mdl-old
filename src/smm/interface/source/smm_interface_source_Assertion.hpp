/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_interface_source_Assertion.hpp                       */
/* Description:     abstract interface for smm assertion                     */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_INTERFACE_SOURCE_ASSERTION_HPP_
#define SMM_INTERFACE_SOURCE_ASSERTION_HPP_

#include "smm/interface/object/smm_interface_object.hpp"
#include "smm/expression/smm_expression.hpp"

namespace smm {
namespace interface {
namespace source {

class Assertion : public object :: Verifiable {
public :
	virtual const Expression* getDisjointed (const index :: Arity) const = 0;
	virtual const Expression* getEssential (const index :: Arity) const = 0;
	virtual const Expression* getFloating (const index :: Arity) const = 0;
	virtual const Expression* getInner (const index :: Arity) const = 0;

	virtual index :: Arity getDisjointedArity() const = 0;
	virtual index :: Arity getEssentialArity() const = 0;
	virtual index :: Arity getFloatingArity() const = 0;
	virtual index :: Arity getInnerArity() const = 0;

	virtual const Expression* getProposition() const = 0;
	virtual const Proof* getProof() const = 0;
	virtual bool areDisjointed (const value :: Literal, const value :: Literal) const = 0;

	virtual index :: Assertion getIndex() const = 0;
	virtual void showHeader (String&) const = 0;
	virtual void showName (String&) const = 0;

};

}
}
}

#endif /*SMM_INTERFACE_SOURCE_ASSERTION_HPP_*/

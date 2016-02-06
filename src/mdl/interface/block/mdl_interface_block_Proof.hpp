/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Proof.hpp                            */
/* Description:     proof abstract interface                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object.hpp"
#include "mdl/interface/proof/mdl_interface_proof_Scoping.hpp"

namespace mdl {
namespace interface {
namespace block {

class Proof :
	public proof :: Scoping,
	public object :: Identifiable {
public :
	virtual bool isCompressed() const = 0;
	virtual index :: Step  getLength() const = 0;
	virtual index :: Arity getQedArity() const = 0;

	virtual void addStep (proof :: Step*) = 0;
	virtual void addVariable (proof :: Variable*) = 0;
	virtual void addQed (proof :: Qed*) = 0;

	virtual proof :: Step* getStep (const index :: Step) = 0;
	virtual proof :: Qed*  getQed (const index :: Arity) = 0;
	virtual proof :: Line* getFirst() = 0;
	virtual proof :: Line* getLast() = 0;
	virtual const proof :: Step* getStep (const index :: Step) const = 0;
	virtual const proof :: Qed*  getQed (const index :: Arity) const = 0;
	virtual const proof :: Line* getFirst() const = 0;
	virtual const proof :: Line* getLast() const = 0;
};

}
}
}



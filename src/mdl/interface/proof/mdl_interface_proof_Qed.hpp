/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Qed.hpp                              */
/* Description:     abstract interface for qed statements in proof           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/proof/mdl_interface_proof_Line.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Qed : virtual public Line {
public :
	virtual index :: Arity  getIndexProp() const = 0;
	virtual index :: Step   getIndexStep() const = 0;
	virtual Provable* getProp() = 0;
	virtual Step* getStep() = 0;
	virtual const Provable* getProp() const = 0;
	virtual const Step* getStep() const = 0;
};

}
}
}



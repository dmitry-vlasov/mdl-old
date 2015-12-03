/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Line.hpp                             */
/* Description:     abstract interface for proof line                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_LINE_HPP_
#define MDL_INTERFACE_PROOF_LINE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"
#include "mdl/interface/proof/mdl_interface_proof_Scoping.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Line :
	virtual public object :: Verifiable,
	virtual public proof :: Scoping {
public :
	enum Sort {
		STEP = Token :: STEP,
		QED  = Token :: QED,
		VARIABLE  = Token :: VARIABLE,
		NOTATION  = Token :: NOTATION
	};
	virtual Sort getSort() const = 0;
	virtual void incIndex (const index :: Step) = 0;
	virtual void decIndex (const index :: Step) = 0;
	virtual void setNext (Line*) = 0;
	virtual void setPrev (Line*) = 0;
	virtual Line* getNext() = 0;
	virtual Line* getPrev() = 0;
	virtual const Line* getNext() const = 0;
	virtual const Line* getPrev() const = 0;
	virtual const Location& getLocation() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_LINE_HPP_*/

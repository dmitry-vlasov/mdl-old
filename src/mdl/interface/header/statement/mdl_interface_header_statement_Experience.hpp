/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Expirience.hpp            */
/* Description:     abstract interface for expirience of assertions          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_STATEMENT_EXPERIENCE_HPP_
#define MDL_INTERFACE_HEADER_STATEMENT_EXPERIENCE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

class Experience : public object :: Object {
public :
	typedef
			mdl :: vector :: proof :: Step
			StepVector_;

	virtual index :: Step getSize() const = 0;
	virtual void addPositive (mdl :: proof :: Step*) = 0;
	virtual void addNegative (mdl :: proof :: Step*) = 0;
	virtual StepVector_& positiveSteps() = 0;
	virtual StepVector_& negativeSteps() = 0;
	virtual const StepVector_& positiveSteps() const = 0;
	virtual const StepVector_& negativeSteps() const = 0;
};

}
}
}
}


#endif /*MDL_INTERFACE_HEADER_STATEMENT_EXPERIENCE_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_evaluation_Function.hpp                    */
/* Description:     abstract interface for evaluation of propositions        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_EVALUATION_FUNCTION_HPP_
#define MDL_INTERFACE_EVALUATION_FUNCTION_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace evaluation {

class Function : public object :: Buildable {
public :
	virtual Term* getTerm() = 0;
	virtual Evaluation* getEvaluation() = 0;

	virtual const Term* getTerm() const = 0;
	virtual const Evaluation* getEvaluation() const = 0;
};

}
}
}


#endif /*MDL_INTERFACE_EVALUATION_FUNCTION_HPP_*/

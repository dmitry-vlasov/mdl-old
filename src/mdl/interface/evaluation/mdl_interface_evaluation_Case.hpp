/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_evaluation_Case.hpp                        */
/* Description:     abstract interface for proposition usage cases           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_EVALUATION_CASE_HPP_
#define MDL_INTERFACE_EVALUATION_CASE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace evaluation {

class Case : public object :: Buildable {
public :
	virtual bool getSign() const = 0;
	virtual mdl :: proof :: Step* getStep() = 0;
	virtual const mdl :: proof :: Step* getStep() const = 0;
};

}
}
}


#endif /*MDL_INTERFACE_EVALUATION_CASE_HPP_*/

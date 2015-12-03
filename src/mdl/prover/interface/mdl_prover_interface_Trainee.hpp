/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Trainee.hpp                         */
/* Description:     abstract interface for trainable evaluator of fitness    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_INTERFACE_TRAINEE_HPP_
#define MDL_PROVER_INTERFACE_TRAINEE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Trainee : public object :: Object  {
public :
	typedef A Allocator_;
	typedef Node<Allocator_> Node_;

	virtual void learn() = 0;
};

}
}
}


#endif /*MDL_PROVER_INTERFACE_TRAINEE_HPP_*/

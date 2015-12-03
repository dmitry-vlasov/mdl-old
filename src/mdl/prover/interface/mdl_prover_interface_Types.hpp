/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Types.hpp                           */
/* Description:     basic types for a prover                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_INTERFACE_TYPES_HPP_
#define MDL_PROVER_INTERFACE_TYPES_HPP_

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Types : public Base<A> {
public :
	typedef A Allocator_;

	typedef Evidences<Allocator_> Evidences_;
	typedef Evidence<Allocator_> Evidence_;
	typedef Node<Allocator_>  Node_;
	typedef Proof<Allocator_> Proof_;

	typedef
		typename mdl :: vector :: Vector
		<
			const Evidences_*,
			storage :: ByValue,
			allocator :: Stack
		>
		Matrix_;
};

}
}
}

#endif /*MDL_PROVER_INTERFACE_TYPES_HPP_*/

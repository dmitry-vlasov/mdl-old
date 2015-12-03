/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Downhood.hpp                    */
/* Description:     a downhood of a point in a proof                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_DOWNHOOD_HPP_
#define MDL_FORM_EVALUATION_LEXP_DOWNHOOD_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

template<class A>
class Downhood :
	public object :: Object,
	public Scalar<Downhood<A> > {
public :
	typedef A Allocator_;
	typedef prover :: Types<Allocator_> Types_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Downhood (const mdl :: proof :: Step*);
	Downhood (const Node_*);
	Downhood (const Downhood&);
	virtual ~ Downhood();

	value :: Real getDistance (const Downhood&, const Factors&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	class Tree_;

	const mdl :: proof :: Step* step_;
	const Node_* node_;
	const Tree_* tree_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_DOWNHOOD_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Uphood.hpp                      */
/* Description:     an uphood of a point in a proof                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_UPHOOD_HPP_
#define MDL_FORM_EVALUATION_LEXP_UPHOOD_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

template<class A>
class Uphood :
	public object :: Object,
	public Scalar<Uphood<A> > {
public :
	typedef A Allocator_;
	typedef prover :: Types<Allocator_> Types_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Uphood (const mdl :: proof :: Step*);
	Uphood (const Node_*);
	Uphood (const Uphood&);
	virtual ~ Uphood();

	value :: Real getDistance (const Uphood&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		typename expression :: Tree
		<
			value :: Integer,
			storage :: ByValue,
			expression :: node :: container :: Singleton,
			allocator :: Heap
		>
		Tree_;

	void build();
	void build (const mdl :: proof :: Step*, const value :: Integer depth = 0);
	void build (const Node_*, const value :: Integer depth = 0);

	const mdl :: proof :: Step* step_;
	const Node_* node_;
	Tree_* tree_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_UPHOOD_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Vector.hpp                      */
/* Description:     vector of points                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_VECTOR_HPP_
#define MDL_FORM_EVALUATION_LEXP_VECTOR_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

template<class A>
class Vector :
	public object :: Object,
	public Scalar<Vector<A> > {
public :
	typedef A Allocator_;
	typedef prover :: Types<Allocator_> Types_;
	typedef Point<Allocator_> Point_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Vector (const value :: Integer);
	Vector (const mdl :: evaluation :: vector :: Case&);
	virtual ~ Vector();

	void addPoint (const Point_*);
	value :: Real getDistanceTo (const Point_*, const Factors&) const;
	value :: Real getDistanceTo (const Point_*, const bool sign, const Factors&) const;
	const value :: Integer getSize() const;
	const Point_* getPoint (const value :: Integer) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Fris;

	typedef
		mdl :: vector :: Vector
		<
			const Point_,
			storage :: ByPointer,
			allocator :: Heap
		>
		Points_;

	Points_ points_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_VECTOR_HPP_*/

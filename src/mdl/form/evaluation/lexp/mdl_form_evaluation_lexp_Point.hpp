/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Point.hpp                       */
/* Description:     a proof step  with premises as a set                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_POINT_HPP_
#define MDL_FORM_EVALUATION_LEXP_POINT_HPP_

#include "mdl/form/evaluation/lexp/mdl_form_evaluation_lexp_Factors.hpp"

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

template<class A>
class Point :
	public object :: Object,
	public Scalar<Point<A> > {
public :
	typedef A Allocator_;
	typedef prover :: Types<Allocator_> Types_;
	typedef Uphood<Allocator_> Uphood_;
	typedef Downhood<Allocator_> Downhood_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Point (const mdl :: evaluation :: Case*);
	Point
	(
		const mdl :: proof :: Step*,
		const bool sign = true
	);
	Point
	(
		const Node_*,
		const bool sign = true
	);
	Point (const Point&);
	virtual ~ Point();

	const mdl :: proof :: Step* getStep() const;
	bool getSign() const;
	bool isPositive() const;
	bool isNegative() const;
	value :: Real getDistance (const Point*, const Factors&) const;
	mdl :: evaluation :: Case* createCase() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const mdl :: proof :: Step* step_;
	const bool sign_;
	const Uphood_   uphood_;
	const Downhood_ downhood_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_POINT_HPP_*/

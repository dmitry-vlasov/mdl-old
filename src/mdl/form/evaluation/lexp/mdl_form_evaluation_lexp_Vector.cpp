/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Vector.cpp                      */
/* Description:     vector of points                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_VECTOR_CPP_
#define MDL_FORM_EVALUATION_LEXP_VECTOR_CPP_

#include "math.h"

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Vector<A> :: Vector (const value :: Integer capacity) :
	points_ (capacity) {
	}
	template<class A>
	Vector<A> :: Vector (const mdl :: evaluation :: vector :: Case& caseVector) :
	points_ (caseVector.getSize())
	{
		for (value :: Integer i = 0; i < caseVector.getSize(); ++ i) {
			const mdl :: evaluation :: Case* _case = caseVector.getValue (i);
			if (_case->getStep() == NULL) {
				Error* error = new Error (Error :: SEMANTIC, "illegal case in FRiS evaluation function\n");
				error->message() << "case: " << *_case << manipulator :: endLine;
				throw error;
			}
			points_.add (new Point_ (_case));
		}
	}
	template<class A>
	Vector<A> :: ~ Vector() {
	}

	template<class A>
	inline void
	Vector<A> :: addPoint (const Point_* point) {
		points_.add (new Point_ (*point));
	}
	template<class A>
	value :: Real
	Vector<A> :: getDistanceTo (const Point_* point_1, const Factors& factors) const
	{
		value :: Real minDistance = -1;
		bool firstPass = true;
		for (value :: Integer i = 0; i < points_.getSize(); ++ i) {
			const Point_* point_2 = points_.getValue (i);
			const value :: Real dist = point_1->getDistance (point_2, factors);
			if ((dist < minDistance) || firstPass) {
				minDistance = dist;
				firstPass = false;
			}
		}
		return minDistance;
	}
	template<class A>
	value :: Real
	Vector<A> :: getDistanceTo
	(
		const Point_* point_1,
		const bool sign,
		const Factors& factors
	) const
	{
		value :: Real minDistance = -1;
		bool firstPass = true;
		for (value :: Integer i = 0; i < points_.getSize(); ++ i) {
			const Point_* point_2 = points_.getValue (i);
			if (point_2->getSign() != sign) {
				continue;
			}
			const value :: Real dist = point_1->getDistance (point_2, factors);
			if ((dist < minDistance) || firstPass) {
				minDistance = dist;
				firstPass = false;
			}
		}
		return minDistance;
	}
	template<class A>
	inline const value :: Integer
	Vector<A> :: getSize() const {
		return points_.getSize();
	}
	template<class A>
	inline const typename Vector<A> :: Point_*
	Vector<A> :: getPoint (const value :: Integer i) const {
		return points_.getValue (i);
	}


using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class A>
	void
	Vector<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Vector<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += points_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Vector<A> :: getSizeOf() const {
		return sizeof (Vector);
	}
	template<class A>
	void
	Vector<A> :: show (String& string) const
	{

	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_VECTOR_CPP_*/

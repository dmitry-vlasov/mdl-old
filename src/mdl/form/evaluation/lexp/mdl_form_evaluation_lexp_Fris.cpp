/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Fris.cpp                        */
/* Description:     Fris function                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_FRIS_CPP_
#define MDL_FORM_EVALUATION_LEXP_FRIS_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Fris<A> :: Fris (const value :: Integer capacity) :
	sign_ (false),
	factors_ (),
	vector_ (new Vector_ (capacity)) {
	}
	template<class A>
	inline
	Fris<A> :: Fris (const bool sign) :
	sign_ (sign),
	factors_ (),
	vector_ (NULL) {
	}
	template<class A>
	inline
	Fris<A> :: Fris (const mdl :: evaluation :: vector :: Case& caseVector) :
	sign_ (false),
	factors_ (),
	vector_ (new Vector_ (caseVector)) {
	}
	template<class A>
	inline
	Fris<A> :: Fris
	(
		const mdl :: evaluation :: vector :: Case& caseVector,
		const Factors& factors
	) :
	sign_ (false),
	factors_ (factors),
	vector_ (new Vector_ (caseVector)) {
	}
	template<class A>
	Fris<A> :: ~ Fris() {
		deleteAggregateObject (vector_);
	}

	template<class A>
	inline void
	Fris<A> :: addPoint (const Point_* point) {
		vector_->addPoint (point);
	}
	template<class A>
	value :: Real
	Fris<A> :: classify (const Node_* node) const
	{
		if (isConst()) {
			return sign_ ? 1 : -1;
		}
		Point_ point (node);

		const value :: Real distanceToPositive = vector_->getDistanceTo (&point, true, factors_);
		const value :: Real distanceToNegative = vector_->getDistanceTo (&point, false, factors_);
		const value :: Real sum = distanceToNegative + distanceToPositive;
		const value :: Real dif = distanceToNegative - distanceToPositive;

		const value :: Real fris = (sum == 0) ? dif : dif / sum;
		return fris;
	}
	template<class A>
	bool
	Fris<A> :: isConst() const {
		return (vector_ == NULL);
	}
	template<class A>
	inline bool
	Fris<A> :: getSign() const {
		return sign_;
	}
	template<class A>
	inline const typename Fris<A> :: Vector_*
	Fris<A> :: getVector() const {
		return vector_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class A>
	void
	Fris<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Fris<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += factors_.getVolume();
		volume += getAggregateVolume (vector_);
		return volume;
	}
	template<class A>
	Size_t
	Fris<A> :: getSizeOf() const {
		return sizeof (Fris);
	}
	template<class A>
	void
	Fris<A> :: show (String& string) const
	{
		if (isConst()) {
			string << "const " << (sign_ ? "true" : "false") << " FRiS function";
		} else {
			vector_->show (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_FRIS_CPP_*/

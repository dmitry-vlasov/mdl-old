/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Point.cpp                       */
/* Description:     a proof step  with premises as a set                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Point<A> :: Point (const mdl :: evaluation :: Case* _case) :
	step_ (_case->getStep()),
	sign_ (_case->getSign()),
	uphood_ (_case->getStep()),
	downhood_ (_case->getStep()) {
	}
	template<class A>
	inline
	Point<A> :: Point
	(
		const mdl :: proof :: Step* step,
		const bool sign
	) :
	step_ (step),
	sign_ (sign),
	uphood_ (step),
	downhood_ (step) {
	}
	template<class A>
	inline
	Point<A> :: Point
	(
		const Node_* node,
		const bool sign
	) :
	step_ (NULL),
	sign_ (sign),
	uphood_ (node),
	downhood_ (node) {
	}
	template<class A>
	inline
	Point<A> :: Point (const Point& point) :
	step_ (point.step_),
	sign_ (point.sign_),
	uphood_ (point.uphood_),
	downhood_ (point.downhood_) {
	}
	template<class A>
	Point<A> :: ~ Point() {
	}

	template<class A>
	const mdl :: proof :: Step*
	Point<A> :: getStep() const {
		return step_;
	}
	template<class A>
	bool
	Point<A> :: getSign() const {
		return sign_;
	}
	template<class A>
	bool
	Point<A> :: isPositive() const {
		return sign_;
	}
	template<class A>
	bool
	Point<A> :: isNegative() const {
		return !sign_;
	}
	template<class A>
	value :: Real
	Point<A> :: getDistance (const Point* point, const Factors& factors) const
	{
		const value :: Real
			upDistance = uphood_.getDistance (point->uphood_);
		const value :: Real
			downDistance = downhood_.getDistance (point->downhood_, factors);
		return
			upDistance * factors.getAlpha() +
			downDistance * (1 - factors.getAlpha());
	}
	template<class A>
	inline mdl :: evaluation :: Case*
	Point<A> :: createCase() const {
		return new form :: evaluation :: term :: Case
			(
				const_cast<mdl :: proof :: Step*>(step_),
				sign_
			);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class A>
	void
	Point<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Point<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += uphood_.getVolume();
		volume += downhood_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Point<A> :: getSizeOf() const {
		return sizeof (Point);
	}
	template<class A>
	void
	Point<A> :: show (String& string) const
	{
		mdl :: evaluation :: Case* _case_ = createCase();
		string << "point: " << *_case_ << " ";
		_case_->commitSuicide();
		return;

		string << "point ";
		string << (sign_ ? "(+)" : "(-)") << " :" << endLine;
		string << "-------------------------------------" << endLine;
		string << uphood_<< endLine;
		string << downhood_<< endLine;
		string << "-------------------------------------" << endLine;
		string << endLine;
 	}
}
}
}
}



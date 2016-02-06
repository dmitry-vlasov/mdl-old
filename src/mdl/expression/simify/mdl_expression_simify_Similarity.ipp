/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Similarity.ipp                     */
/* Description:     class which represents similarity of expressions         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace simify {

	/****************************
	 *		Public members
	 ****************************/

	template<class U>
	inline
	Similarity<U> :: Similarity ()  :
	direct_ (0),
	inverse_ (0) {
	}
	template<class U>
	inline
	Similarity<U> :: Similarity (const Similarity& similarity) :
	direct_ (similarity.direct_),
	inverse_ (similarity.inverse_) {
	}
	template<class U>
	inline
	Similarity<U> :: Similarity (const Unit_& unit) :
	direct_ (unit.getFirst().getLength()),
	inverse_ (unit.getSecond().getLength()) {
	}

	template<class U>
	inline bool
	Similarity<U> :: none() const {
		return (direct_ == 0) && (inverse_  == 0);
	}
	template<class U>
	inline value :: Integer
	Similarity<U> :: getDirect() const {
		return direct_;
	}
	template<class U>
	inline value :: Integer
	Similarity<U> :: getInverse() const {
		return inverse_;
	}
	template<class U>
	inline typename Similarity<U> :: InverseSimilarity_
	Similarity<U> :: inverse() const {
		return InverseSimilarity_ (inverse_, direct_);
	}

	template<class U>
	inline void
	Similarity<U> :: operator = (const Similarity& similarity)
	{
		direct_ = similarity.direct_;
		inverse_ = similarity.inverse_;
	}
	template<class U>
	inline void
	Similarity<U> :: operator += (const Similarity similarity)
	{
		direct_ += similarity.direct_;
		inverse_ += similarity.inverse_;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U>
	inline
	Similarity<U> :: Similarity (const value :: Integer direct, const value :: Integer inverse) :
	direct_ (direct),
	inverse_ (inverse) {
	}
}
}
}



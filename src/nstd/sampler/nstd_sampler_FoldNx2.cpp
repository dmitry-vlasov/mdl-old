/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_FoldNx2.cpp                                 */
/* Description:     fold N x 2 sample generator                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace sampler {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	FoldNx2<A> :: FoldNx2
	(
		Sample_& sample,
		const Integer n
	) :
	size_ (sample.getSize()),
	n_ (n),
	sample_ (sample),
	countFolds_ (0),
	countIterations_ (0),
	side_ (true) {
	}
	template<class A>
	FoldNx2<A> :: ~ FoldNx2() {
	}

	template<class A>
	bool
	FoldNx2<A> :: generate (const Integer learningAtLeast)
	{
		if (countFolds_ < n_) {
			generateFold2 (countFolds_ + 1, side_);
			side_ = !side_;
			if (side_) {
				++ countFolds_;
			}
			if (sample_.isMeaningful (learningAtLeast)) {
				++ countIterations_;
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	template<class A>
	inline void
	FoldNx2<A> :: reset()
	{
		countIterations_ = 0;
		countFolds_ = 0;
		side_ = true;
		sample_.clear();
	}
	template<class A>
	inline Integer
	FoldNx2<A> :: getCount() const {
		return countIterations_;
	}
	template<class A>
	inline Integer
	FoldNx2<A> :: getIterations() const
	{
		if (size_ == 0) {
			return 0;
		} else {
			return 2 * ((n_ < (size_ - 1)) ? n_ : (size_ - 1));
		}
	}
	template<class A>
	Integer
	FoldNx2<A> :: getIterations (const Integer size) const
	{
		if (size_ % 2 == 0) {
			if (size_ / 2 == size) {
				return 2 * n_;
			} else {
				return 0;
			}
		} else {
			if (size_ / 2 == size) {
				return n_;
			} else if (1 + size_ / 2 == size) {
				return n_;
			} else {
				return 0;
			}
		}
	}
	template<class A>
	inline Real
	FoldNx2<A> :: getLearningSize() const {
		return static_cast<Real>(size_) / 2;
	}

	template<class A>
	template<class S>
	void
	FoldNx2<A> :: show (S& string) const {
		string << n_ << "X2 fold";
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	// object :: Object implementation
	template<class A>
	void
	FoldNx2<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	FoldNx2<A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	FoldNx2<A> :: getSizeOf() const {
		return sizeof (FoldNx2);
	}
	template<class A>
	void
	FoldNx2<A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	FoldNx2<A> :: generateFold2 (const int k, const bool includeSide)
	{
		sample_.clear();
		bool side = true;
		//int counter = 0;
		for (int i = 0; i < size_; ++ i) {
			if (i % k == 0) {
				side = !side;
			}
			if (side == includeSide) {
				sample_.control_->add (i);
			} else {
				sample_.learning_->add (i);
			}
			//++ counter;
		}
	}
}
}



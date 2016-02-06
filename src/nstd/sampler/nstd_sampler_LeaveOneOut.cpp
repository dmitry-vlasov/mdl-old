/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_LeaveOneOut.cpp                             */
/* Description:     Leave One Out (LOO) sample generator                     */
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
	LeaveOneOut<A> :: LeaveOneOut (Sample_& sample) :
	sample_ (sample),
	size_ (sample.getSize()),
	count_ (0) {
	}
	template<class A>
	LeaveOneOut<A> :: ~ LeaveOneOut() {
	}

	template<class A>
	bool
	LeaveOneOut<A> :: generate()
	{
		if (count_ < size_) {
			sample_.clear();
			for (int i = 0; i < size_; ++ i) {
				if (i == count_) {
					sample_.control_->add (i);
				} else {
					sample_.learning_->add (i);
				}
			}
			++ count_;
			return true;
		} else {
			return false;
		}
	}

	template<class A>
	inline void
	LeaveOneOut<A> :: reset()
	{
		count_ = 0;
		sample_.clear();
	}
	template<class A>
	inline Integer
	LeaveOneOut<A> :: getCount() const {
		return count_;
	}
	template<class A>
	inline Integer
	LeaveOneOut<A> :: getIterations() const {
		return size_;
	}
	template<class A>
	Integer
	LeaveOneOut<A> :: getIterations (const Integer size) const
	{
		if (size == (size_ - 1)) {
			return size_;
		} else {
			return 0;
		}
	}
	template<class A>
	inline Real
	LeaveOneOut<A> :: getLearningSize() const {
		return size_ - 1;
	}

	template<class A>
	template<class S>
	void
	LeaveOneOut<A> :: show (S& string) const {
		string << "Leave One Out (LOO)";
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	// object :: Object implementation
	template<class A>
	void
	LeaveOneOut<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	LeaveOneOut<A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	LeaveOneOut<A> :: getSizeOf() const {
		return sizeof (LeaveOneOut);
	}
	template<class A>
	void
	LeaveOneOut<A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}



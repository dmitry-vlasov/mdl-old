/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_sampler_Sampler.cpp                                 */
/* Description:     sample generator                                         */
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
	Sampler<A> :: Sampler
	(
		const Integer size,
		const Mode_ mode
	) :
	mode_ (mode),
	size_ (size),
	sample_ (size),
	leaveOneOut_ (new LeaveOneOut_ (sample_)),
	foldNx2_( new FoldNx2_ (sample_)) {
	}
	template<class A>
	Sampler<A> :: ~ Sampler()
	{
		deleteAggregateObject (leaveOneOut_);
		deleteAggregateObject (foldNx2_);
	}

	template<class A>
	bool
	Sampler<A> :: generate (const Integer learningAtLeast)
	{
		//std :: cout  << sample_ << std :: endl;
		bool result = false;
		switch (mode_) {
		case LEAVE_ONE_OUT_MODE : result = leaveOneOut_->generate(); break;
		case FOLD_NX2_MODE      : result = foldNx2_->generate (learningAtLeast);     break;
		default                 : break;
		}
		//std :: cout  << sample_ << std :: endl;
		return result;
	}

	template<class A>
	inline Integer
	Sampler<A> :: getCount() const
	{
		switch (mode_) {
		case LEAVE_ONE_OUT_MODE : return leaveOneOut_->getCount();
		case FOLD_NX2_MODE      : return foldNx2_->getCount();
		default                 : return 0;
		}
	}
	template<class A>
	inline Integer
	Sampler<A> :: getIterations() const
	{
		switch (mode_) {
		case LEAVE_ONE_OUT_MODE : return leaveOneOut_->getIterations();
		case FOLD_NX2_MODE      : return foldNx2_->getIterations();
		default                 : return 0;
		}
	}
	template<class A>
	inline Integer
	Sampler<A> :: getIterations (const Integer size) const
	{
		switch (mode_) {
		case LEAVE_ONE_OUT_MODE : return leaveOneOut_->getIterations (size);
		case FOLD_NX2_MODE      : return foldNx2_->getIterations (size);
		default                 : return 0;
		}
	}

	template<class A>
	inline Real
	Sampler<A> :: getLearningSize() const
	{
		switch (mode_) {
		case LEAVE_ONE_OUT_MODE : return leaveOneOut_->getLearningSize();
		case FOLD_NX2_MODE      : return foldNx2_->getLearningSize();
		default                 : return 0;
		}
	}
	template<class A>
	inline typename Sampler<A> :: Sample_&
	Sampler<A> :: getSample() {
		return sample_;
	}
	template<class A>
	inline void
	Sampler<A> :: reset()
	{
		leaveOneOut_->reset();
		foldNx2_->reset();
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Sampler<A> :: show (S& string) const
	{
		string << "sampler:" << endLine;
		switch (mode_) {
		case LEAVE_ONE_OUT_MODE :
			string << tab << *leaveOneOut_; break;
		case FOLD_NX2_MODE :
			string << tab << *foldNx2_ << endLine; break;
		default : break;
		}
	}

	// object :: Object implementation
	template<class A>
	void
	Sampler<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Sampler<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += sample_.getVolume();
		volume += getAggregateVolume (leaveOneOut_);
		volume += getAggregateVolume (foldNx2_);
		return volume;
	}
	template<class A>
	Size_t
	Sampler<A> :: getSizeOf() const {
		return sizeof (Sampler);
	}
	template<class A>
	void
	Sampler<A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}



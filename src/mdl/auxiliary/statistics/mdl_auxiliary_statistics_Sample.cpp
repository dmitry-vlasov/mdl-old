/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_statistics_Sample.cpp                      */
/* Description:     sample class for statistics data                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace statistics {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Sample :: Sample (const Size_t initialSampleCapacity) :
	sample_ (initialSampleCapacity),
	lastValue_ (),
	max_(- value :: EXTREMELY_LARGE),
	min_(+ value :: EXTREMELY_LARGE),
	average_ (0),
	dispersion_ (0),
	sigma_ (0),
	updated_ (false),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Sample :: ~ Sample() {
	}

	void
	Sample :: add (const double value)
	{
		pthread_mutex_lock (&mutex_);
		updated_ = true;
		if ((max_ < value) || (sample_.isEmpty())) {
			max_ = value;
		}
		if ((min_ > value) || (sample_.isEmpty())) {
			min_ = value;
		}
		lastValue_ = value;
		sample_.add (value);
		pthread_mutex_unlock (&mutex_);
	}
	inline double
	Sample :: getLastValue() const {
		return lastValue_;
	}
	Size_t
	Sample :: getSize() const {
		return sample_.getSize();
	}

	double
	Sample :: relativize (const double value) const
	{
		update();
		if (average_ != 0) {
			return value / average_;
		} else {
			return value;
		}
	}
	double
	Sample :: normalize (const double value) const
	{
		update();
		if (sigma_ != 0) {
			return (value - average_) / sigma_;
		} else {
			return value - average_;
		}
	}
	double
	Sample :: relativize() const
	{
		update();
		if (average_ != 0) {
			return lastValue_ / average_;
		} else {
			return lastValue_;
		}
	}
	double
	Sample :: normalize() const
	{
		update();
		if (sigma_ != 0) {
			return (lastValue_ - average_) / sigma_;
		} else {
			return lastValue_ - average_;
		}
	}

	inline double
	Sample :: getMax() const {
		return max_;
	}
	inline double
	Sample :: getMin() const {
		return min_;
	}
	inline double
	Sample :: getAverage() const
	{
		update();
		return average_;
	}
	inline double
	Sample :: getDispersion() const
	{
		update();
		return dispersion_;
	}
	inline double
	Sample :: getSigma() const
	{
		update();
		return sigma_;
	}
	inline bool
	Sample :: updated() const {
		return updated_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class S>
	void
	Sample :: showBrief (S& string) const
	{
		update();
		string << "size = " << sample_.getSize() << ", ";
		string << "average = " << average_ << ", ";
		string << "sigma = " << sigma_;
	}

	// nstd :: Object implementation
	void
	Sample :: commitSuicide() {
		delete this;
	}
	Size_t
	Sample :: getVolume() const {
		return sample_.getVolume();
	}
	Size_t
	Sample :: getSizeOf() const {
		return sizeof (Sample);
	}
	void
	Sample :: show (nstd :: String<>& string) const {
		showBrief (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Sample :: update() const
	{
		if (!updated_) {
			return;
		}
		calculateAverage();
		calculateDispersion();
		updated_ = false;
	}

	void
	Sample :: calculateAverage() const
	{
		double sum = 0;
		const Size_t size = sample_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const double value = sample_.getValue (i);
			sum += value;
		}
		average_ = sum / size;
	}
	void
	Sample :: calculateDispersion() const
	{
		double sum = 0;
		const Size_t size = sample_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			double value = sample_.getValue (i);
			double delta = value - average_;
			sum += delta * delta;
		}
		dispersion_ = sum / size;
		sigma_ = sqrt (dispersion_);
	}
}
}
}



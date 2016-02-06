/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Teacher_Estimating.cpp                   */
/* Description:     a class for a complex time estimation                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace study {
namespace teach {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Teacher :: Estimating :: Estimating
	(
		Format& format,
		const value :: Integer precision,
		const value :: Integer grouping
	) :
	format_ (format),
	sampleSize_ (value :: undefined :: INTEGER),
	precision_ (precision),
	grouping_ (grouping) {
	}
	Teacher :: Estimating :: ~ Estimating() {
	}

	bool
	Teacher :: Estimating :: estimateSize (const Time timeLimit)
	{
		format_.message() << "estimating";
		format_.showStart();

		Timing timing (format_, sampleSize_, precision_, grouping_);
		equation :: Interval interval (SAMPLE_SIZE_MAX, true);
		equation :: Monotonic :: solve<Timing&> (timeLimit, sampleSize_, timing, interval);

		if (sampleSize_ > Math :: assertions()->getTheoremNumber()) {
			sampleSize_ = Math :: assertions()->getTheoremNumber();
		}
		format_.message() << "sample size = " << sampleSize_;
		format_.showFinal();
		return (sampleSize_ >= SAMPLE_SIZE_MIN);
	}
	inline value :: Integer
	Teacher :: Estimating :: getSampleSize() const {
		return sampleSize_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	// object :: Object implementation
	void
	Teacher :: Estimating :: commitSuicide() {
		delete this;
	}
	Size_t
	Teacher :: Estimating :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		return volume;
	}
	Size_t
	Teacher :: Estimating :: getSizeOf() const {
		return sizeof (Estimating);
	}
	void
	Teacher :: Estimating :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}



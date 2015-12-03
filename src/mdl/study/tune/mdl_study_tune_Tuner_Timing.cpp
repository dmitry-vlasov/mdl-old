/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Tuner_Timing.cpp                          */
/* Description:     a class with a time estimation for tuning algorithm      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_TUNER_TIMING_CPP_
#define MDL_STUDY_TUNE_TUNER_TIMING_CPP_

namespace mdl {
namespace study {
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Tuner :: Timing :: Timing
	(
		Format& format,
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	) :
	format_ (format, true),
	sampleSize_ (sampleSize),
	maxPrecision_ (maxPrecision) {
	}
	Tuner :: Timing :: ~ Timing() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	Time
	Tuner :: Timing :: estimate
	(
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	)
	{
		Time estimatedTime = 0;
		estimatedTime += Sample :: estimateTime (sampleSize);
		estimatedTime += tune :: Precision :: estimateTime (sampleSize, maxPrecision);
		estimatedTime += tune :: Grouping :: estimateTime (sampleSize, maxPrecision);
		return estimatedTime;
	}
	inline Time
	Tuner :: Timing :: operator() (const value :: Integer sampleSize) const
	{
		sampleSize_ = sampleSize;
		return estimate (sampleSize_, maxPrecision_);
	}

	void
	Tuner :: Timing :: show (const bool full)
	{
		format_.message() << "time estimation for ";
		format_.message() << "sample size = " << sampleSize_ <<  ", ";
		format_.message() << "max precision = " << maxPrecision_ << " ";
		format_.showMessage();
		format_.message() << "total time estimated:  ";
		format_.message() << estimate (sampleSize_, maxPrecision_) << " s.";
		format_.showMessage();
		if (full) {
			format_.message() << "--------------------------";
			format_.showMessage();
			format_.message() << tab << "estimated sample time: ";
			format_.message() << Sample :: estimateTime (sampleSize_) << " s.";
			format_.showMessage();

			format_.message() << tab << "estimated precision time: ";
			format_.message() << tune :: Precision :: estimateTime (sampleSize_, maxPrecision_) << " s.";
			//tune :: Precision :: showEstimatedTimes (string, format_, sampleSize_, maxPrecision_);
			format_.showMessage();

			format_.message() << tab << "estimated grouping time:  ";
			format_.message() << tune :: Grouping :: estimateTime (sampleSize_, maxPrecision_) << " s.";
			//tune :: Grouping :: showEstimatedTimes (string, format_, sampleSize_, maxPrecision_);
			format_.showMessage();
			format_.message() << "--------------------------";
			format_.showMessage();
		}
	}

	// object :: Object implementation
	void
	Tuner :: Timing :: commitSuicide() {
		delete this;
	}
	Size_t
	Tuner :: Timing :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		return volume;
	}
	Size_t
	Tuner :: Timing :: getSizeOf() const {
		return sizeof (Timing);
	}
	void
	Tuner :: Timing :: show (String& string) const {
		//show (string, sampleSize_, maxPrecision_, true);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MDL_STUDY_TUNE_TUNER_TIMING_CPP_*/

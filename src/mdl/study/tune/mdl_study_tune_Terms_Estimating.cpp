/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Terms_Estimating.cpp                      */
/* Description:     a class for a complex time estimation                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_TERMS_ESTIMATING_CPP_
#define MDL_STUDY_TUNE_TERMS_ESTIMATING_CPP_

namespace mdl {
namespace study {
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Terms :: Estimating :: Estimating (Format& format, const Terms* tuner) :
	format_ (format, true),
	subFormat_ (format_, true),
	tuner_ (tuner),
	percentVector_ (100),
	maxThresholdVector_ (100),
	percent_ (10),
	maxThreshold_ (10)
	{
	}
	Terms :: Estimating :: ~ Estimating() {
	}

	void
	Terms :: Estimating :: estimatePercentAndMaxThreshold (const Time timeLimit)
	{
		format_.message() << "estimating percent and  max threshold";
		format_.showStart();

		evaluateDependency (timeLimit);
		const value :: Integer
			optimalIndex = evaluateOptimum();

		maxThreshold_ = maxThresholdVector_.getValue (optimalIndex);
		percent_ = percentVector_.getValue (optimalIndex);

		subFormat_.message() << "estimated percent = " << percent_;
		subFormat_.showMessage();
		subFormat_.message() << "estimated max threshold = " << maxThreshold_;
		subFormat_.showMessage();

		format_.showFinal();
	}
	inline value :: Real
	Terms :: Estimating :: getPercent() const {
		return percent_;
	}
	inline value :: Real
	Terms :: Estimating :: getMaxThreshold() const {
		return maxThreshold_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	// object :: Object implementation
	void
	Terms :: Estimating :: commitSuicide() {
		delete this;
	}
	Size_t
	Terms :: Estimating :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += percentVector_.getVolume();
		volume += maxThresholdVector_.getVolume();
		return volume;
	}
	Size_t
	Terms :: Estimating :: getSizeOf() const {
		return sizeof (Estimating);
	}
	void
	Terms :: Estimating :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Terms :: Estimating :: evaluateDependency (const Time timeLimit)
	{
		//std :: cout << std :: endl;
		//std :: cout << "max precision --> size: " << std :: endl;
		//std :: cout << "---------------------" << std :: endl;
		for (
				value :: Real maxThreshold = MAX_THRESHOLD_MIN;
				maxThreshold <= MAX_THRESHOLD_MAX;
				maxThreshold += MAX_THRESHOLD_STEP
			)
		{
			value :: Real percent = 1;
			Timing timing (format_, tuner_, percent, maxThreshold);
			equation :: Interval interval (100, true);
			equation :: Monotonic :: solve<Timing&> (timeLimit, percent, timing, interval);
			//std :: cout << maxThreshold << ",\t" << percent << "\t";
			if (percent == 0) {
				//std :: cout << std :: endl;
				break;
			}
			maxThresholdVector_.add (maxThreshold);
			percentVector_.add (percent);

			//std :: cout << "(*)" << std :: endl;
		}
	}
	value :: Integer
	Terms :: Estimating :: evaluateOptimum() const
	{
		const value :: Real deltaThreshold =
				maxThresholdVector_.getLastValue() - maxThresholdVector_.getFirstValue();
		const value :: Real deltaPercent =
				percentVector_.getFirstValue() - percentVector_.getLastValue();

		if (deltaPercent == 0) {
			return maxThresholdVector_.getSize() - 1;
		} else {
			const value :: Real alpha = deltaThreshold / deltaPercent;

			value :: Integer minIndex = 0;
			value :: Real minBeta = 0;

			/*std :: cout << std :: endl;
			std :: cout << "alpha = " << alpha << std :: endl;
			std :: cout << "beta = " << std :: endl;
			std :: cout << "----------- " << std :: endl;*/
			for (value :: Integer i = 0; i < maxThresholdVector_.getSize(); ++ i) {
				const value :: Real threshold = maxThresholdVector_.getValue (i);
				const value :: Real percent = percentVector_.getValue (i);
				const value :: Real normPercent = percent * alpha;
				const value :: Real beta = threshold + normPercent;
				if ((i == 0) || (beta < minBeta)) {
					minBeta = beta;
					minIndex = i;
				}
				/*std :: cout << "i = " << i << ",\t";
				std :: cout << "percent = " << percent << ",\t";
				std :: cout << "n_percent = " << normPercent << ",\t";
				std :: cout << "max_threchold = " << threshold << ",\t";
				std :: cout << "beta = " << beta << ",\t";
				std :: cout << "\t" << std :: endl;*/
			}
			return minIndex;
		}
	}
}
}
}

#endif /*MDL_STUDY_TUNE_TERMS_ESTIMATING_CPP_*/

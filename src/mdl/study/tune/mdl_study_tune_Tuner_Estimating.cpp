/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Tuner_Estimating.cpp                      */
/* Description:     a class for a complex time estimation                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_TUNER_ESTIMATING_CPP_
#define MDL_STUDY_TUNE_TUNER_ESTIMATING_CPP_

namespace mdl {
namespace study {
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Tuner :: Estimating :: Estimating (Format& format) :
	format_ (format, true),
	subFormat_ (format_, true),
	sizeVector_ (MAX_PRECISION_MAX - MAX_PRECISION_MIN),
	maxPrecisionVector_ (MAX_PRECISION_MAX - MAX_PRECISION_MIN),
	sampleSize_ (value :: undefined :: INTEGER),
	maxPrecision_ (value :: undefined :: INTEGER)
	{
	}
	Tuner :: Estimating :: ~ Estimating() {
	}

	bool
	Tuner :: Estimating :: estimateSizeAndPrecision (const Time timeLimit)
	{
		format_.message() << "estimating sample size and maxPrecision";
		format_.showStart();

		evaluateDependency (timeLimit);

		if (sizeVector_.getSize() <= 1) {
			return false;
		}
		const value :: Integer
			optimalIndex = evaluateOptimum();

		maxPrecision_ = maxPrecisionVector_.getValue (optimalIndex);
		sampleSize_ = sizeVector_.getValue (optimalIndex);

		subFormat_.message() << "estimated sample size = " << sampleSize_;
		subFormat_.showMessage();
		subFormat_.message() << "estimated maxPrecision = " << maxPrecision_;
		subFormat_.showMessage();

		format_.showFinal();
		return true;
	}
	inline value :: Integer
	Tuner :: Estimating :: getSampleSize() const {
		return sampleSize_;
	}
	inline value :: Integer
	Tuner :: Estimating :: getMaxPrecision() const {
		return maxPrecision_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	// object :: Object implementation
	void
	Tuner :: Estimating :: commitSuicide() {
		delete this;
	}
	Size_t
	Tuner :: Estimating :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += sizeVector_.getVolume();
		volume += maxPrecisionVector_.getVolume();
		return volume;
	}
	Size_t
	Tuner :: Estimating :: getSizeOf() const {
		return sizeof (Estimating);
	}
	void
	Tuner :: Estimating :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Tuner :: Estimating :: evaluateDependency (const Time timeLimit)
	{
		#ifdef DEBUG_TUNER_ESTIMATING
		std :: cout << std :: endl;
		std :: cout << "max precision --> size: " << std :: endl;
		std :: cout << "---------------------" << std :: endl;
		#endif
		for (
				value :: Integer maxPrecision = MAX_PRECISION_MIN;
				maxPrecision < MAX_PRECISION_MAX;
				maxPrecision += MAX_PRECISION_STEP
			)
		{
			value :: Integer size = SAMPLE_SIZE_MIN;
			Timing timing (format_, size, maxPrecision);
			equation :: Interval interval (SAMPLE_SIZE_MAX, true);
			equation :: Monotonic :: solve<Timing&> (timeLimit, size, timing, interval);

			if (size > Math :: assertions()->getTheoremNumber()) {
				size = Math :: assertions()->getTheoremNumber();
			}
			maxPrecisionVector_.add (maxPrecision);
			sizeVector_.add (size);

			#ifdef DEBUG_TUNER_ESTIMATING
			std :: cout << maxPrecision << ",\t" << size << std :: endl;
			#endif
			if (size < SAMPLE_SIZE_MIN) {
				break;
			}
		}
	}
	value :: Integer
	Tuner :: Estimating :: evaluateOptimum() const
	{
		const value :: Real deltaPrecision =
				maxPrecisionVector_.getLastValue() - maxPrecisionVector_.getFirstValue();
		const value :: Real deltaSize =
				sizeVector_.getFirstValue() - sizeVector_.getLastValue();
		if (deltaSize == 0) {
			return maxPrecisionVector_.getSize() - 1;
		} else {
			const value :: Real alpha = deltaPrecision / deltaSize;

			value :: Integer minIndex = 0;
			value :: Real minBeta = 0;

			#ifdef DEBUG_TUNER_ESTIMATING
			std :: cout << std :: endl;
			std :: cout << "alpha = " << alpha << std :: endl;
			std :: cout << "beta = " << std :: endl;
			std :: cout << "----------- " << std :: endl;
			#endif

			for (value :: Integer i = 0; i < maxPrecisionVector_.getSize(); ++ i) {
				const value :: Real maxPrecision = maxPrecisionVector_.getValue (i);
				const value :: Real size = sizeVector_.getValue (i);
				const value :: Real normSize = size * alpha;
				const value :: Real beta = maxPrecision + normSize;
				if ((i == 0) || (beta < minBeta)) {
					minBeta = beta;
					minIndex = i;
				}

				#ifdef DEBUG_TUNER_ESTIMATING
				std :: cout << "i = " << i << ",\t";
				std :: cout << "size = " << size << ",\t";
				std :: cout << "n_size = " << normSize << ",\t";
				std :: cout << "max_prec = " << maxPrecision << ",\t";
				std :: cout << "beta = " << beta << ",\t";
				std :: cout << "\t" << std :: endl;
				#endif
			}
			return minIndex;
		}
	}
}
}
}

#endif /*MDL_STUDY_TUNE_TUNER_ESTIMATING_CPP_*/

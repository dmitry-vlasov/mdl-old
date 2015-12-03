/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Tuner.cpp                                 */
/* Description:     a class with a tuning (meta-learning) algorithm          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_TUNER_CPP_
#define MDL_STUDY_TUNE_TUNER_CPP_

namespace mdl {
namespace study {
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Tuner :: Tuner (Format&  format) :
	format_ (format, true),
	benchmark_ (new Benchmark (format)),

	sample_ (new Sample (format_)),
	termTuner_ (new tune :: Terms (format_, sample_)),
	precisionTuner_ (new tune :: Precision (format_, sample_)),
	groupingTuner_ (new tune :: Grouping (format_, sample_)),

	estimating_ (new Estimating (format_)),
	sampleSize_ (value :: undefined :: INTEGER),
	maxPrecision_ (value :: undefined :: INTEGER),

	optimalThreshold_ (value :: undefined :: INTEGER),
	optimalPrecision_ (value :: undefined :: INTEGER),
	optimalGrouping_ (value :: undefined :: INTEGER) {
	}
	Tuner :: ~ Tuner()
	{
		deleteAggregateObject (benchmark_);
		deleteAggregateObject (sample_);
		deleteAggregateObject (termTuner_);
		deleteAggregateObject (precisionTuner_);
		deleteAggregateObject (groupingTuner_);
		deleteAggregateObject (estimating_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;

	void
	Tuner :: tune (Time& timeLimit)
	{
		if (!benchmark_->isDone()) {
			format_.message() << "no benchmarking was done, tuning canceled.";
			format_.showMessage();
			return;
		}
		format_.message() << "tuning";
		format_.showStart (timeLimit);
		Time limit = timeLimit;
		format_.message() << "tuning time limit = " << limit << ", ";

		if (!estimating_->estimateSizeAndPrecision (timeLimit * stepTimeFractions_ [OPTIMIZE_STEP])) {
			format_.message() << "no suitable sample size / max precision was found, tuning canceled.";
			format_.showMessage();
			format_.message() << "Try to increase time limit";
			format_.showMessage();
			return;
		}
		sampleSize_ = estimating_->getSampleSize();
		maxPrecision_ = estimating_->getMaxPrecision();

		Timing timing (format_, sampleSize_, maxPrecision_);
		timing.show (true);

		buildSample (limit, sampleSize_);
		tuneLeafs (limit);
		tuneOptimization (limit);
		Timers :: misc().clear();
		if (Config :: tune()) {
			writeOptions();
		}
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
	}

	inline value :: Integer
	Tuner :: getOptimalThreshold() const {
		return optimalThreshold_;
	}
	inline value :: Integer
	Tuner :: getOptimalPrecision() const {
		return optimalPrecision_;
	}
	inline value :: Integer
	Tuner :: getOptimalGrouping() const {
		return optimalGrouping_;
	}

	/*void
	Tuner :: cleanUp()
	{
		for (value :: Integer i = 0; i < Math :: evaluations()->getSize(); ++ i) {
			mdl :: Evaluation*
				evaluation = Math :: evaluations()->get (i);
			evaluation->setToDefault();
		}
	}*/

	// object :: Object implementation
	void
	Tuner :: commitSuicide() {
		delete this;
	}
	Size_t
	Tuner :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += getAggregateVolume (benchmark_);
		volume += getAggregateVolume (sample_);
		volume += getAggregateVolume (termTuner_);
		volume += getAggregateVolume (precisionTuner_);
		volume += getAggregateVolume (groupingTuner_);
		volume += getAggregateVolume (estimating_);
		return volume;
	}
	Size_t
	Tuner :: getSizeOf() const {
		return sizeof (Tuner);
	}
	void
	Tuner :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Tuner :: buildSample (Time& limit, const value :: Integer sampleSize)
	{
		Time sampleBuildLimit = limit * phaseTimeFractions_ [SAMPLE_BUILD_PHASE];
		limit -= sampleBuildLimit;
 		sample_->build (sampleSize, sampleBuildLimit);
 		limit += sampleBuildLimit;
	}
	void
	Tuner :: tuneLeafs (Time& limit)
	{
		Time leafLimit = limit * stepTimeFractions_ [LEAF_STEP];
		limit -= leafLimit;
		optimalThreshold_ = termTuner_->tune (leafLimit);
		limit += leafLimit;
	}
	void
	Tuner :: tuneOptimization (Time& limit)
	{
		Time precisionLimit = limit * phaseTimeFractions_ [PRECISION_PHASE];
		limit -= precisionLimit;
		optimalPrecision_ = precisionTuner_->tune (precisionLimit, maxPrecision_);
		limit += precisionLimit;

		Time groupingLimit = limit * phaseTimeFractions_ [GROUPING_PHASE];
		limit -= groupingLimit;
		optimalGrouping_  = groupingTuner_->tune (groupingLimit, optimalPrecision_, maxPrecision_);
		limit += groupingLimit;
	}

	void
	Tuner :: writeOptions() const
	{
		if (Config :: getTarget().isUndefined()) {
			return;
		}
		Config :: target().provideDirectory();
		Output output (Config :: getTarget().getString().c_str());
		output.open();

		option :: Integer& threshold = Config :: getIntegerOption (Config :: THRESHOLD);
		threshold.value() = optimalThreshold_;
		threshold.show (output.buffer());

		output.buffer() << " " << endLine;

		option :: Integer& precision = Config :: getIntegerOption (Config :: PRECISION);
		precision.value() = optimalPrecision_;
		precision.show (output.buffer());

		output.buffer() << " " << endLine;

		option :: Integer& grouping = Config :: getIntegerOption (Config :: GROUPING);
		grouping.value() = optimalGrouping_;
		grouping.show (output.buffer());

		output.buffer() << " " << endLine;

		output.close();
	}

	/*********************************
	 *		Private static members
	 *********************************/

	value :: Real Tuner :: stepTimeFractions_ [STEPS_NUM] =
	{
		0.3, // LEAF
		0.7, // OPTIMIZATION
	};
	value :: Real Tuner :: phaseTimeFractions_ [PHASES_NUM] =
	{
		0.1, // SAMPLE_BUILD
		0.2, // GLOBAL_ROOT
		0.7, // LOCAL_ROOT
	};
}
}
}

#endif /*MDL_STUDY_TUNE_TUNER_CPP_*/

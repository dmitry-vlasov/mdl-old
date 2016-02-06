/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Teacher.cpp                              */
/* Description:     a class with global learning algorithm                   */
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
	Teacher :: Teacher (Format& format) :
	format_ (format),
	benchmark_ (new Benchmark (format)),
	threshold_  (Config :: getInteger (Config :: THRESHOLD)),
	precision_  (Config :: getInteger (Config :: PRECISION)),
	grouping_   (Config :: getInteger (Config :: GROUPING)),
	sampleSize_ (Config :: getInteger (Config :: SAMPLE_SIZE)),
	estimating_ (new Estimating (format_, precision_, grouping_)) {
	}
	Teacher :: ~ Teacher()
	{
		deleteAggregateObject (benchmark_);
		deleteAggregateObject (estimating_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;

	void
	Teacher :: teach (Time& timeLimit)
	{
		/*if (!benchmark_->isDone()) {
			format_.message() << "no benchmarking was done, learning canceled.";
			format_.showMessage();
			return;
		}*/
		Time limit = timeLimit;
		format_.message() << "learning, time limit = " << limit;
		format_.showStart();
		Sample sample (format_);

		/*if (!estimating_->estimateSize (limit * stepTimeFractions_ [OPTIMIZE_STEP])) {
			format_.message() << "no suitable sample size was found, learning canceled.";
			format_.showMessage();
			format_.message() << "Try to increase time limit";
			format_.showMessage();
			return;
		} else {
			sampleSize_ = estimating_->getSampleSize();
		}*/

		Time sampleBuildTimeLimit = limit * phaseTimeFractions_ [SAMPLE_BUILD_PHASE];
		limit -= sampleBuildTimeLimit;
		sample.build (sampleSize_, sampleBuildTimeLimit);
		limit += sampleBuildTimeLimit;

		Terms termTeacher (format_, &sample);

		Time termTimeLimit = limit * stepTimeFractions_ [LEAF_STEP];
		limit -= termTimeLimit;
		termTeacher.teach (termTimeLimit, threshold_);
		limit += termTimeLimit;

		const value :: Real quantum = 1 / static_cast<value :: Real>(precision_);

		Optimization optimizationTeacher (format_, &sample);

		Time precisionTimeLimit = limit * phaseTimeFractions_ [PRECISION_PHASE];
		limit -= precisionTimeLimit;
		optimizationTeacher.teach (precisionTimeLimit, quantum, 1);
		limit += precisionTimeLimit;

		Time groupingTimeLimit = limit * phaseTimeFractions_ [GROUPING_PHASE];
		limit -= groupingTimeLimit;
		optimizationTeacher.teach (groupingTimeLimit, quantum, grouping_);
		limit += groupingTimeLimit;

		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
	}

	// object :: Object implementation
	void
	Teacher :: commitSuicide() {
		delete this;
	}
	Size_t
	Teacher :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += getAggregateVolume (benchmark_);
		volume += getAggregateVolume (estimating_);
		return volume;
	}
	Size_t
	Teacher :: getSizeOf() const {
		return sizeof (Teacher);
	}
	void
	Teacher :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	value :: Real Teacher :: stepTimeFractions_ [STEPS_NUM] =
	{
		0.3, // LEAF
		0.7, // OPTIMIZATION
	};
	value :: Real Teacher :: phaseTimeFractions_ [PHASES_NUM] =
	{
		0.1, // SAMPLE_BUILD
		0.2, // GLOBAL_ROOT
		0.7, // LOCAL_ROOT
	};
}
}
}



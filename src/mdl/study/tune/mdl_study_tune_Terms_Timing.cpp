/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Terms_Timing.cpp                          */
/* Description:     a class with a time estimation for tuning algorithm      */
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
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Terms :: Timing :: Timing
	(
		Format& format,
		const Terms* tuner,
		const value :: Real percent,
		const value :: Real maxThreshold
	) :
	format_ (format, true),
	tuner_ (tuner),
	percent_ (percent),
	maxThreshold_ (maxThreshold) {
		format_.setPrintableSubformat();
	}
	Terms :: Timing :: ~ Timing() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	Time
	Terms :: Timing :: estimate
	(
		const value :: Real percent,
		const value :: Real maxThreshold
	) const
	{
		const value :: Real step = (maxThreshold_ - THRESHOLD_MIN) / THRESHOLD_CYCLES;
		Time estimatedTime = 0;
		for (
				value :: Real threshold = THRESHOLD_MIN;
				threshold <= maxThreshold;
				threshold += step
			)
		{
			Time iterationTime = estimateOneIteration (percent, threshold);
			estimatedTime += iterationTime * TIME_RESERVE_FACTOR;
		}
		estimatedTime += estimateFinalLearningTime (percent, maxThreshold_);
		return estimatedTime;
	}
	inline value :: Real
	Terms :: Timing :: operator() (const value :: Real percent) const
	{
		percent_ = percent;
		return estimate (percent_, maxThreshold_);
	}

	void
	Terms :: Timing :: show (const bool full)
	{
		format_.message() << "time estimation for ";
		format_.message() << "percent = " << percent_ << ", ";
		format_.message() << "max threshold = " << maxThreshold_ << " ";
		format_.showMessage();
		format_.message() << "total time estimated:  " << estimate (percent_, maxThreshold_) << " s.";
		format_.showMessage();
		if (full) {
			format_.message() << "--------------------------";
			format_.showMessage();

			format_.message() << tab << "iteration time:      ";
			format_.message() << estimateOneIteration (percent_, maxThreshold_);
			format_.message() << " s.";
			format_.showMessage();

			format_.message() << tab << "final learning time: ";
			format_.message() << estimateFinalLearningTime (percent_, maxThreshold_) << " s.";
			format_.showMessage();

			format_.message() << "--------------------------";
			format_.showMessage();
		}
	}

	// object :: Object implementation
	void
	Terms :: Timing :: commitSuicide() {
		delete this;
	}
	Size_t
	Terms :: Timing :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		return volume;
	}
	Size_t
	Terms :: Timing :: getSizeOf() const {
		return sizeof (Timing);
	}
	void
	Terms :: Timing :: show (String& string) const {
		//show (string, percent_, maxThreshold_, true);
	}

	/****************************
	 *		Private members
	 ****************************/

	Time
	Terms :: Timing :: estimateOneIteration
	(
		const value :: Real percent,
		const value :: Real threshold
	) const
	{
		Time iterationTime = 0;
		for (value :: Integer i = 0; i < tuner_->sample_->getSecondary().getSize(); ++ i) {
			const value :: Integer index = tuner_->sample_->getSecondary().getValue (i);
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (index);
			const statement :: Experience*
				experience = proposition->getExperience();
			const value :: Integer experienceSize = experience->getSize();
			const value :: Integer scaledSize = experienceSize * percent / 100;
			const Time
				teachTime = lexp :: Tuner :: estimateTime
				(
					scaledSize,
					threshold
				);
			iterationTime += teachTime;
			iterationTime += Benchmark :: get()->fris()->getCreateTimePolynomialX()->eval (scaledSize);
			iterationTime += Benchmark :: get()->fris()->getDeleteTimePolynomialX()->eval (scaledSize);
		}
		return iterationTime;
	}
	Time
	Terms :: Timing :: estimateFinalLearningTime
	(
		const value :: Real percent,
		const value :: Real threshold
	) const
	{
		Time finalLearningTime = 0;
		for (value :: Integer i = 0; i < tuner_->sample_->getSecondary().getSize(); ++ i) {
			const value :: Integer index = tuner_->sample_->getSecondary().getValue (i);
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (index);
			const statement :: Experience*
				experience = proposition->getExperience();
			const value :: Integer experienceSize = experience->getSize();
			const value :: Integer scaledSize = experienceSize * percent / 100;
			finalLearningTime += Benchmark :: get()->fris()->getCreateTimePolynomialX()->eval (scaledSize);
			finalLearningTime += Benchmark :: get()->fris()->getTeachTimePolynomialXY()->eval (scaledSize, threshold);
			finalLearningTime += Benchmark :: get()->fris()->getResultTimePolynomialX()->eval (scaledSize);
			finalLearningTime += Benchmark :: get()->fris()->getDeleteTimePolynomialX()->eval (scaledSize);
		}
		return finalLearningTime;
	}
	void
	Terms :: Timing :: showEstimatedIterationTimes
	(
		String& string,
		const value :: Real percent,
		const value :: Real threshold
	) const
	{
		for (value :: Integer i = 0; i < tuner_->sample_->getSecondary().getSize(); ++ i) {
			const value :: Integer index = tuner_->sample_->getSecondary().getValue (i);
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (index);
			const statement :: Experience*
				experience = proposition->getExperience();
			const value :: Integer experienceSize = experience->getSize();
			const value :: Integer scaledSize = experienceSize * percent / 100;
			Time iterationTime = 0;
			const Time
				teachTime = lexp :: Tuner :: estimateTime
				(
					scaledSize,
					threshold
				);
			iterationTime += teachTime;
			iterationTime += Benchmark :: get()->fris()->getCreateTimePolynomialX()->eval (scaledSize);
			iterationTime += Benchmark :: get()->fris()->getDeleteTimePolynomialX()->eval (scaledSize);

			format_.typeIndent (string);
			string << tab << tab << "for ";
			proposition->getAssertion()->replicateName (string);
			string << " estimated iteration time: " << iterationTime << " s, ";
			string << endLine;
		}
	}
	void
	Terms :: Timing :: showEstimatedFinalLearningTimes
	(
		String& string,
		const value :: Real percent
	) const
	{
		for (value :: Integer i = 0; i < tuner_->sample_->getSecondary().getSize(); ++ i) {
			const value :: Integer index = tuner_->sample_->getSecondary().getValue (i);
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (index);
			const statement :: Experience*
				experience = proposition->getExperience();
			const value :: Integer experienceSize = experience->getSize();
			const value :: Integer scaledSize = experienceSize * percent / 100;
			Time wholeTime = 0;
			wholeTime += Benchmark :: get()->fris()->getCreateTimePolynomialX()->eval (scaledSize);
			wholeTime += Benchmark :: get()->fris()->getTeachTimePolynomialX()->eval (scaledSize);
			wholeTime += Benchmark :: get()->fris()->getResultTimePolynomialX()->eval (scaledSize);
			wholeTime += Benchmark :: get()->fris()->getDeleteTimePolynomialX()->eval (scaledSize);

			format_.typeIndent (string);
			string << tab << tab << "for ";
			proposition->getAssertion()->replicateName (string);
			string << " estimated time: " << wholeTime << " s, ";
			string << endLine;
		}
	}
}
}
}



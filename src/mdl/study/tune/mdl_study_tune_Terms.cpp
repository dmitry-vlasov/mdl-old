/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Terms.cpp                                 */
/* Description:     teaching terms                                           */
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
	Terms :: Terms
	(
		Format& format,
		Sample* sample
	) :
	format_ (format),
	subFormat_ (format_),
	subSubFormat_ (subFormat_),

	sample_ (sample),
	teacher_ (new teach :: Terms (subFormat_, sample)),

	estimating_ (new Estimating (format_, this)),
	percent_ (10),
	maxThreshold_ (20),

	optimalThreshold_ (0)
	{
		//subSubFormat_.setVerbosity (Config :: VERBOSE_EXT);
		teacher_->format_.setVerbosity (Config :: VERBOSE_EXT);
	}
	Terms :: ~ Terms()
	{
		deleteAggregateObject (teacher_);
		deleteAggregateObject (estimating_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	value :: Integer
	Terms :: tune (Time& timeLimit)
	{
		lexp :: Tuner :: init();
		format_.message() << "FRiS tuning";
		format_.showStart (timeLimit);
		value :: Real optimalFitness = 0;

		estimating_->estimatePercentAndMaxThreshold (timeLimit);
		percent_ = estimating_->getPercent();
		maxThreshold_ = estimating_->getMaxThreshold();

		Timing timing (format_, this, percent_, maxThreshold_);
		timing.show (true);

		const value :: Real step = (maxThreshold_ - THRESHOLD_MIN) / THRESHOLD_CYCLES;

		Timer timer;
		timer.start();
		for (
			value :: Real threshold = THRESHOLD_MIN;
			threshold <= maxThreshold_;
			threshold += step
			)
		{
			subFormat_.message() << "threshold = " << threshold;
			subFormat_.showStart();
			const value :: Real
				fitness = evalFitness (threshold);
			subFormat_.message() << "fitness = " << fitness;
			subFormat_.showFinal();
			if ((threshold == THRESHOLD_MIN) || (fitness < optimalFitness)) {
				optimalFitness = fitness;
				optimalThreshold_ = threshold;
			}
			if (format_.getTimer().getSeconds() > timeLimit) {
				break;
			}
		}
		timer.stop();
		subFormat_.message() << "done in " << timer;
		subFormat_.showMessage();
		subFormat_.message() << "teaching with threshold = " << optimalThreshold_;
		subFormat_.showStart();

		value :: Real limit = timeLimit - format_.getTimer().getSeconds();
		teacher_->teach (limit, optimalThreshold_, false);
		subFormat_.showFinal();

		format_.showFinal();
		format_.message() << "fitness = " << teacher_->sample_->getFitness().eval() << "%";
		format_.showMessage();

		lexp :: Tuner :: release();
		timeLimit -= format_.getTimer().getSeconds();
		return optimalThreshold_;
	}

	// object :: Object implementation
	void
	Terms :: commitSuicide() {
		delete this;
	}
	Size_t
	Terms :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += subSubFormat_.getVolume();
		volume += getAggregateVolume (teacher_);
		volume += getAggregateVolume (estimating_);
		return volume;
	}
	Size_t
	Terms :: getSizeOf() const {
		return sizeof (Terms);
	}
	void
	Terms :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

#ifdef MULTY_THREADED
	value :: Real
	Terms :: evalFitnessMultyThreaded (const value :: Real threshold)
	{
		const value :: Integer threadCount = Config :: getConcurrency (Config :: THREADS);
		pthread_t  threads [threadCount];
		Arguments_ arguments [threadCount];
		for (int i = 0; i < threadCount; ++ i) {
			arguments [i].threadIndex_ = i;
			arguments [i].threadCount_ = threadCount;
			arguments [i].percent_ = percent_;
			arguments [i].threshold_ = threshold;
			arguments [i].sample_ = teacher_->sample_;
			arguments [i].subSubFormat_ = NULL; // new Format (subFormat_);
			pthread_create (threads + i, NULL, tuneInThread, reinterpret_cast<void*>(arguments + i));
		}
		Error* error = NULL;
		value :: Real sumFitness = 0;
		value :: Real sumCounter = 0;
		for (int i = 0; i < threadCount; ++ i) {
			Result_* result = NULL;
			pthread_join (threads [i], reinterpret_cast<void**>(&result));
			sumFitness += result->fitness_;
			sumCounter += result->counter_;
			if (result->error_ != NULL) {
				result->error_->setNext (error);
				error = result->error_;
			}
			delete result;
		}
		if (error == NULL) {
			return (sumCounter == 0) ? 1 : sumFitness / sumCounter;
		} else {
			throw error;
		}
	}
#endif

	value :: Real
	Terms :: evalFitness (const value :: Real threshold)
	{
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			return evalFitnessSingleThreaded (threshold);
		} else {
			return evalFitnessMultyThreaded (threshold);
		}
		#else
		return evalFitnessSingleThreaded (threshold);
		#endif
	}
	value :: Real
	Terms :: evalFitnessSingleThreaded (const value :: Real threshold)
	{
		const value :: Name name = Config :: experience();
		value :: Real sumFitness = 0;
		value :: Integer sumCounter = 0;
		const value :: Integer testSize = teacher_->sample_->getSecondary().getSize();
		for (value :: Integer i = 0; i < testSize; ++ i) {
			value :: Integer test = teacher_->sample_->getSecondary().getValue (i);
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (test);
			proposition->getAssertion()->getEvaluation (Config :: experience());
			mdl :: evaluation :: Function*
				function = proposition->getEvaluation (name);
			mdl :: evaluation :: Term*
				term = function->getTerm();
			statement :: Experience*
				experience = proposition->getExperience();
			subSubFormat_.message() << "evaluating " << i << " ";
			subSubFormat_.message() << "fris of " ;
			proposition->getAssertion()->replicateName (subSubFormat_.message());
			subSubFormat_.message() << " , exp. size = " << experience->getSize();
			subSubFormat_.showStart();
			value :: Real fitness = 0;
			value :: Integer counter = 0;
			evalTermFitness
			(
				term,
				experience,
				percent_,
				threshold,
				fitness,
				counter
			);
			subSubFormat_.message() << "fitness = " << fitness;
			subSubFormat_.showFinal();
			sumFitness += fitness;
			sumCounter += counter;
		}
		const value :: Real result = (sumCounter == 0) ? 1 : sumFitness / sumCounter;
		return result;
	}

	void
	Terms :: evalTermFitness
	(
		mdl :: evaluation :: Term* term,
		statement :: Experience* experience,
		value :: Real percent,
		value :: Real threshold,
		value :: Real& sumFitness,
		value :: Integer& counter
	)
	{
		typedef
			mdl :: form :: evaluation :: term :: Lexp
			LexpTerm;
		LexpTerm*
			lexpTerm = dynamic_cast<LexpTerm*>(term);
		if (lexpTerm == NULL) {
			for (value :: Integer i = 0; i < term->getArity(); ++ i) {
				mdl :: evaluation :: Term* subterm = term->getSubTerm (i);
				evalTermFitness (subterm, experience, percent, threshold, sumFitness, counter);
			}
		} else {
			lexp :: Tuner tuner (experience, percent);
			const value :: Real fitness = tuner.tune (threshold);
			sumFitness += fitness;
			++ counter;
		}
	}

	/**********************
	 *		Functions
	 **********************/

#ifdef MULTY_THREADED
	void* tuneInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		const value :: Name name = Config :: experience();
		Terms :: Arguments_* arguments = reinterpret_cast<Terms :: Arguments_*>(pointer);
		Format* subSubFormat = arguments->subSubFormat_;
		const value :: Integer threadCount = arguments->threadCount_;
		value :: Real sumFitness = 0;
		value :: Integer sumCounter = 0;
		for (value :: Integer i = 0; i < arguments->sample_->getSecondary().getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			try {
				const index :: Assertion
					j = arguments->sample_->getSecondary().getValue (i);
				mdl :: Proposition*
					proposition = Math :: propositions()->get (j);
				mdl :: evaluation :: Function*
					function = proposition->getEvaluation (name);
				mdl :: evaluation :: Term*
					term = function->getTerm();
				statement :: Experience*
					experience = proposition->getExperience();
				if (subSubFormat != NULL) {
					subSubFormat->message() << "evaluating " << i << " ";
					subSubFormat->message() << "fris of " ;
					proposition->getAssertion()->replicateName (subSubFormat->message());
					subSubFormat->showStart();
				}
				value :: Real fitness = 0;
				value :: Integer counter = 0;
				Terms :: evalTermFitness
				(
					term,
					experience,
					arguments->percent_,
					arguments->threshold_,
					fitness,
					counter
				);
				if (subSubFormat != NULL) {
					subSubFormat->message() << "fitness = " << fitness;
					subSubFormat->showFinal();
				}
				sumFitness += fitness;
				sumCounter += counter;
			} catch (Error* e) {
				error = e;
				break;
			} catch (std :: exception& exception) {
				error = new Error (Error :: SEMANTIC, exception.what());
				break;
			} catch (...) {
				error = new Error (Error :: SEMANTIC, "unknown exception.");
				break;
			}
		}
		Memory :: pile().releaseThread();
		return new Terms :: Result_ (sumFitness, sumCounter, error);
	}
#endif
}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Terms.cpp                                */
/* Description:     teaching leaf terms                                      */
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
	Terms :: Terms
	(
		Format& supFormat,
		Sample* sample
	) :
	format_ (supFormat),
	subFormat_ (format_),
	sample_ (sample) {
		//format_.setVerbosity (Config :: VERBOSE_MED);
		//subFormat_.setVerbosity (Config :: VERBOSE_MED);
		//subFormat_.setVerbosity (Config :: VERBOSE_EXT);
	}
	Terms :: ~ Terms() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	void
	Terms :: teach
	(
		Time& timeLimit,
		const value :: Integer threshold,
		const bool evalFitness
	)
	{
		lexp :: Teacher :: init();
		format_.message() << "leaf learinig";
		format_.showStart();
		if (Config :: learn ()) {
			teachAll (timeLimit, threshold);
		} else {
			teachSample (timeLimit, threshold);
		}
		if (evalFitness) {
			format_.message() << "fitness = " << sample_->getFitness().eval();
		}
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
		lexp :: Teacher :: release();
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
	void
	Terms :: teachMultiThreaded
	(
		void* func (void*),
		Time timeLimit,
		const value :: Integer threshold
	)
	{
		const value :: Integer threadCount = Config :: getConcurrency (Config :: THREADS);
		pthread_t  threads [threadCount];
		Arguments_ arguments [threadCount];
		for (int i = 0; i < threadCount; ++ i) {
			arguments [i].threadIndex_ = i;
			arguments [i].threadCount_ = threadCount;
			arguments [i].threshold_ = threshold;
			arguments [i].timeLimit_ = timeLimit;
			arguments [i].sample_ = sample_;
			arguments [i].subFormat_ = NULL; //new Format (format_);
			if (arguments [i].subFormat_ != NULL) {
				arguments [i].subFormat_->setVerbosity (Config :: VERBOSE_EXT);
			}
			pthread_create (threads + i, NULL, func, reinterpret_cast<void*>(arguments + i));
		}
		Error* error = NULL;
		for (int i = 0; i < threadCount; ++ i) {
			Error* err = NULL;
			pthread_join (threads [i], reinterpret_cast<void**>(&err));
			if (err != NULL) {
				err->setNext (error);
				error = err;
			}
		}
		if (error != NULL) {
			throw error;
		}
	}
#endif

	inline void
	Terms :: teachAll (Time timeLimit, const value :: Integer threshold)
	{
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			teachAllSingleThreaded (timeLimit, threshold);
		} else {
			teachMultiThreaded (teachAllInThread, timeLimit, threshold);
		}
		#else
			teachAllSingleThreaded (timeLimit, threshold);
		#endif
	}
	inline void
	Terms :: teachSample (Time timeLimit, const value :: Integer threshold)
	{
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			teachSampleSingleThreaded (timeLimit, threshold);
		} else {
			teachMultiThreaded (teachSampleInThread, timeLimit, threshold);
		}
		#else
			teachSampleSingleThreaded (timeLimit, threshold);
		#endif
	}

	void
	Terms :: teachAllSingleThreaded (Time timeLimit, const value :: Integer threshold)
	{
		Timer timer;
		timer.start();
		const value :: Integer size = Math :: propositions()->getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (i);
			const value :: Name
				theoremName = proposition->getAssertion()->getName();
			if (Config :: excludeAssertion() == theoremName) {
				continue;
			}
			Time propLimit = timeLimit / (size - i);
			teachProposition (propLimit, proposition, threshold, &subFormat_);
			timeLimit -= timer.getSeconds();
		}
		timer.stop();
	}
	void
	Terms :: teachSampleSingleThreaded (Time timeLimit, const value :: Integer threshold)
	{
		Timer timer;
		timer.start();
		const value :: Integer size = sample_->getSecondary().getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const index :: Assertion
				j = sample_->getSecondary().getValue (i);
			mdl :: Proposition*
				proposition = Math :: propositions()->get (j);
			Time propLimit = timeLimit / (size - i);
			teachProposition (propLimit, proposition, threshold, &subFormat_);
			timeLimit -= timer.getSeconds();
		}
	}

	void
	Terms :: teachProposition
	(
		Time timeLimit,
		mdl :: Proposition* proposition,
		const value :: Integer threshold,
		Format* subFormat
	)
	{
		const value :: Name name = Config :: experience();
		proposition->getAssertion()->getEvaluation (name);
		mdl :: evaluation :: Function*
			function = proposition->getEvaluation (name);
		mdl :: evaluation :: Term*
			term = function->getTerm();
		statement :: Experience*
			experience = proposition->getExperience();

		if (subFormat != NULL) {
			subFormat->message() << "proposition ";
			subFormat->message() << proposition->getIndex() << " of ";
			proposition->getAssertion()->replicateName (subFormat->message());
			subFormat->showStart();
		}
		teachTerm (timeLimit, term, experience, threshold, subFormat);
		if (subFormat != NULL) {
			subFormat->showFinal();
		}
	}
	void
	Terms :: teachTerm
	(
		Time timeLimit,
		mdl :: evaluation :: Term* term,
		statement :: Experience* experience,
		value :: Integer threshold,
		Format* subFormat
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
				teachTerm (timeLimit, subterm, experience, threshold, subFormat);
			}
		} else {
			typedef
				LexpTerm :: Fris_
				FrisFunc;
			lexp :: Teacher* teacher = new lexp :: Teacher (experience);
			teacher->teachLimited (timeLimit, threshold);
			FrisFunc* frisFunc = teacher->createResult();
			teacher->commitSuicide ();
			lexpTerm->setFris (frisFunc);

			//Lexp :: teach (lexpTerm, experience, threshold, subFormat);
		}
	}

	/**********************
	 *		Functions
	 **********************/

#ifdef MULTY_THREADED
	void*
	teachAllInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		Terms :: Arguments_* arguments = reinterpret_cast<Terms :: Arguments_*>(pointer);
		const value :: Integer threadCount = arguments->threadCount_;
		for (value :: Integer i = 0; i < Math :: propositions()->getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			try {
				mdl :: Proposition*
					proposition = Math :: propositions()->getDescending (i);
				const value :: Name
					theoremName = proposition->getAssertion()->getName();
				if (Config :: excludeAssertion() == theoremName) {
					continue;
				}
				Terms :: teachProposition
				(
					arguments->timeLimit_,
					proposition,
					arguments->threshold_,
					arguments->subFormat_
				);
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
		return error;
	}
	void*
	teachSampleInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		Terms :: Arguments_* arguments = reinterpret_cast<Terms :: Arguments_*>(pointer);
		const value :: Integer threadCount = arguments->threadCount_;
		for (value :: Integer i = 0; i < arguments->sample_->getSecondary().getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			try {
				const index :: Assertion
					j = arguments->sample_->getSecondary().getValue (i);
				mdl :: Proposition*
					proposition = Math :: propositions()->get (j);
				Terms :: teachProposition
				(
					arguments->timeLimit_,
					proposition,
					arguments->threshold_,
					arguments->subFormat_
				);
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
		return error;
	}
#endif

}
}
}



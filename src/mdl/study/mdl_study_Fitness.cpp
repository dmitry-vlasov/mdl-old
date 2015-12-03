/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_Fitness.cpp                                    */
/* Description:     a set of trees - for fitness evaluation                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_FITNESS_CPP_
#define MDL_STUDY_FITNESS_CPP_

namespace mdl {
namespace study {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Fitness :: Fitness (Format& format, Sample* sample) :
	format_ (format),
	subFormat_ (format_),
	treeVector_ (NULL),
	sample_ (sample) {
		//subFormat_.setVerbosity (Config :: VERBOSE_EXT);
		//subFormat_.setVerbosity (Config :: VERBOSE_MIN);
	}
	Fitness :: ~ Fitness() {
		deleteAggregateObject (treeVector_);
	}

using manipulator :: mode;

	void
	Fitness :: showTrees() const
	{
		String message (1024);
		prover :: Mode m;
		m.setValue (prover :: Mode :: SHOW_UP_TREE_CARD);
		m.setValue (prover :: Mode :: SHOW_UP_TREE_LEVELS);
		m.setValue (prover :: Mode :: SHOW_UP_TREE_LEVELS_CARD);
		message << mode << m;
		for (value :: Integer i = 0; i < treeVector_->getSize(); ++ i) {
			Tree_* tree = treeVector_->getValue (i);
			tree->show (message);
		}
		std :: cout << message << std :: endl;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;

	value :: Real
	Fitness :: eval (const Sample_* sample) const
	{
		if (sample == NULL) {
			return evalAll();
		} else {
			return evalFor (sample);
		}
	}

using manipulator :: iterate;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Fitness :: commitSuicide() {
		delete this;
	}
	Size_t
	Fitness :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += getAggregateVolume (treeVector_);
		return volume;
	}
	Size_t
	Fitness :: getSizeOf() const {
		return sizeof (Fitness);
	}
	void
	Fitness :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Fitness :: build (Time& timeLimit)
	{
		if (treeVector_ != NULL) {
			delete treeVector_;
		}
		treeVector_ = new TreeVector_ (sample_->getPrimary().getSize());

		format_.message() << "building test trees";
		format_.showStart (timeLimit);

		Time limit = timeLimit;
		const value :: Integer size = sample_->getPrimary().getSize();
		for (index :: Assertion k = 0; k < size; ++ k) {
			const value :: Integer index = sample_->getPrimary().getValue (k);
			const mdl :: Assertion* assertion = Math :: assertions()->getTheorem (index);
			if (assertion->getName() == Config :: excludeAssertion()) {
				continue;
			}
			Time treeLimit = limit / (size - k);

			addTree (assertion, treeLimit, size);

			limit -= format_.getTimer().getSeconds();
		}
		format_.showFinal();
		format_.message() << "fitness = " << eval() << "%";
		format_.showMessage();
		timeLimit -= format_.getTimer().getSeconds();
	}
	void
	Fitness :: addTree
	(
		const mdl :: Assertion* assertion,
		const Time timeLimit,
		const value :: Integer size
	)
	{
		enum {
			TREE_SIZE_TO_SAMPLE_SIZE_FACTOR = 1024 * 4
		};
		const value :: Integer sizeLimit = size * TREE_SIZE_TO_SAMPLE_SIZE_FACTOR;

		const form :: Theorem* theorem = dynamic_cast<const form :: Theorem*>(assertion);
		for (value :: Integer i = 0; i < theorem->getProofVector().getSize(); ++ i) {
			const mdl :: Proof* proof = theorem->getProofVector().getValue (i);
			for (index :: Arity j = 0; j < proof->getQedArity(); ++ j) {
				const mdl :: proof :: Qed* qed = proof->getQed (j);
				const mdl :: proof :: Step* step = qed->getStep();
				mdl :: proof :: Question* question = const_cast<mdl :: proof :: Step*>(step)->questionSelf();
				Format subSubFormat (subFormat_, true);
				//Tree_* tree = new Tree_ (subFormat_, subSubFormat, const_cast<mdl :: proof :: Step*>(step));
				Tree_* tree = new Tree_ (subFormat_, subSubFormat, question);
				tree->init();
				tree->getTimers()->switchOff();
				subFormat_.message() << "building a tree for ";
				theorem->replicateName (subFormat_.message());
				subFormat_.showStart();
				tree->growUpForLearning (timeLimit, sizeLimit);
				if (subFormat_.isPrintable()) {
					prover :: Mode newMode;
					prover :: Mode oldMode (subFormat_.message().getMode());
					newMode.setValue (prover :: Mode :: SHOW_UP_TREE_CARD);
					newMode.setValue (prover :: Mode :: SHOW_UP_TREE_EXP_VOLUME);
					//newMode.setValue (prover :: Mode :: SHOW_UP_TREE_LEVELS_CARD);
					//newMode.setValue (prover :: Mode :: SHOW_UP_TREE_LEVELS);
					subFormat_.message() << mode << newMode;
					tree->show (subFormat_.message());
					subFormat_.message() << mode << oldMode;
				}
				subFormat_.showFinal();
				treeVector_->add (tree);
			}
			break;
		}
	}

#ifdef MULTY_THREADED
	value :: Real
	Fitness :: evalAllMultyThreaded() const
	{
		const value :: Integer threadCount = Config :: getConcurrency (Config :: THREADS);
		pthread_t  threads [threadCount];
		Arguments_ arguments [threadCount];
		for (int i = 0; i < threadCount; ++ i) {
			arguments [i].threadIndex_ = i;
			arguments [i].threadCount_ = threadCount;
			arguments [i].trees_ = treeVector_;
			pthread_create (threads + i, NULL, &evalAllInThread, reinterpret_cast<void*>(arguments + i));
		}

		value :: Real sumFitness = 0;
		for (int i = 0; i < threadCount; ++ i) {
			Result_* result = NULL;
			pthread_join (threads [i], reinterpret_cast<void**>(&result));
			sumFitness += result->fitness_;
			delete result;
		}
		return sumFitness / treeVector_->getSize();
	}
	value :: Real
	Fitness :: evalForMultyThreaded (const Sample_* sample) const
	{
		const value :: Integer threadCount = Config :: getConcurrency (Config :: THREADS);
		pthread_t  threads [threadCount];
		Arguments_ arguments [threadCount];
		for (int i = 0; i < threadCount; ++ i) {
			arguments [i].sample_ = sample;
			arguments [i].threadIndex_ = i;
			arguments [i].threadCount_ = threadCount;
			arguments [i].trees_ = treeVector_;
			pthread_create (threads + i, NULL, &evalForInThread, reinterpret_cast<void*>(arguments + i));
		}

		Error* error = NULL;
		value :: Real sumFitness = 0;
		for (int i = 0; i < threadCount; ++ i) {
			Result_* result = NULL;
			pthread_join (threads [i], reinterpret_cast<void**>(&result));
			sumFitness += result->fitness_;
			if (result->error_ != NULL) {
				result->error_->setNext (error);
				error = result->error_;
			}
			delete result;
		}
		if (error == NULL) {
			return sumFitness / sample->getSize();
		} else {
			throw error;
		}
	}
#endif

	inline value :: Real
	Fitness :: evalAll() const
	{
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			return evalAllSingleThreaded();
		} else {
			return evalAllMultyThreaded();
		}
		#else
		return evalAllSingleThreaded();
		#endif
	}
	inline value :: Real
	Fitness :: evalFor (const Sample_* sample) const
	{
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			return evalForSingleThreaded (sample);
		} else {
			return evalForMultyThreaded (sample);
		}
		#else
		return evalForSingleThreaded (sample);
		#endif
	}

	value :: Real
	Fitness :: evalAllSingleThreaded() const
	{
		value :: Real sumFitness = 0;
		for (value :: Integer i = 0; i < treeVector_->getSize(); ++ i) {
			const Tree_* tree = treeVector_->getValue (i);
			const value :: Real fitness = tree->evalFitness();
			sumFitness += fitness;
		}
		return sumFitness / treeVector_->getSize();
	}
	value :: Real
	Fitness :: evalForSingleThreaded (const Sample_* sample) const
	{
		value :: Real sumFitness = 0;
		for (value :: Integer i = 0; i < sample->getSize(); ++ i) {
			const value :: Integer index = sample->getIndex (i);
			const Tree_* tree = treeVector_->getValue (index);
			const value :: Real fitness = tree->evalFitness();
			sumFitness += fitness;
		}
		return sumFitness / sample->getSize();
	}

	/**********************
	 *		Functions
	 **********************/

#ifdef MULTY_THREADED
	void* evalAllInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		Fitness :: Arguments_* arguments = reinterpret_cast<Fitness :: Arguments_*>(pointer);
		value :: Real sumFitness = 0;
		const value :: Integer threadCount = arguments->threadCount_;
		for (value :: Integer i = 0; i < arguments->trees_->getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			try {
				const Fitness :: Tree_* tree = arguments->trees_->getValue (i);
				const value :: Real fitness = tree->evalFitness();
				sumFitness += fitness;
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
		return new Fitness :: Result_ (sumFitness, error);
	}
	void* evalForInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		Fitness :: Arguments_* arguments = reinterpret_cast<Fitness :: Arguments_*>(pointer);
		value :: Real sumFitness = 0;
		const value :: Integer threadCount = arguments->threadCount_;
		typedef
			sampler :: Sample<allocator :: Heap>
			Sample_;

		const Sample_* sample = arguments->sample_;

		for (value :: Integer i = 0; i < sample->getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			try {
				const value :: Integer index = sample->getIndex (i);
				const Fitness :: Tree_* tree = arguments->trees_->getValue (index);
				const value :: Real fitness = tree->evalFitness();
				sumFitness += fitness;
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
		return new Fitness :: Result_ (sumFitness, error);
	}
#endif

}
}

#endif /*MDL_STUDY_FITNESS_CPP_*/

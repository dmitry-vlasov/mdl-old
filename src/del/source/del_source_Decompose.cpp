/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Decompose.cpp                                 */
/* Description:     question                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Decompose :: Decompose
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory theoryName,
		const value :: Signature signatureName,
		const bool isStrong
	) :
	location_ (location),
	comments_ (comments),
	theoryName_ (theoryName),
	signatureName_ (signatureName),
	theory_ (Math :: theories()->get (theoryName_)),
	delta_ (Math :: signatures()->get (signatureName_)),
	deltaExpanded_ (delta_->clone()),

	initialTheory_ (NULL),
	minimalTheory_ (NULL),
	normalTheory_ (NULL),
	primitiveTheory_ (NULL),
	decomposedTheory_ (NULL),
	assembledTheory_ (NULL),

	TcupTdelta_ (NULL),
	TcupTdeltaExpansion_ (NULL),
	TcupTdeltaModel_ (NULL),

	signature_ (NULL),
	sigma_ (new source :: Signature<>()),
	epsilon_ (new source :: Signature<>()),
	theta_ (new source :: Signature<>()),

	decomposition_ (NULL),
	trivialDecomposition_ (INITIAL_SIGNATURE_DECOMPOSITION_CAPACITY),
	nontrivialDecomposition_ (INITIAL_SIGNATURE_DECOMPOSITION_CAPACITY)
	{
		const source :: Signature<>&
			signature = dynamic_cast<const source :: Signature<>&>(*theory_->getSignature());
		signature_ = new source :: Signature<>(signature);
	}
	inline
	Decompose :: Decompose
	(
		const del :: Theory* theory,
		const del :: Signature* delta,
		const bool isStrong
	) :
	location_ (),
	comments_ (NULL),
	theoryName_ (theory->getName()),
	signatureName_ (delta->getName()),
	theory_ (theory),
	delta_ (delta),
	deltaExpanded_ (delta_->clone()),

	initialTheory_ (NULL),
	minimalTheory_ (NULL),
	normalTheory_ (NULL),
	primitiveTheory_ (NULL),
	decomposedTheory_ (NULL),
	assembledTheory_ (NULL),

	TcupTdelta_ (NULL),
	TcupTdeltaExpansion_ (NULL),
	TcupTdeltaModel_ (NULL),

	signature_ (NULL),
	sigma_ (new source :: Signature<>()),
	epsilon_ (new source :: Signature<>()),
	theta_ (new source :: Signature<>()),

	decomposition_ (NULL),
	trivialDecomposition_ (INITIAL_SIGNATURE_DECOMPOSITION_CAPACITY),
	nontrivialDecomposition_ (INITIAL_SIGNATURE_DECOMPOSITION_CAPACITY)
	{
		const source :: Signature<>&
			signature = dynamic_cast<const source :: Signature<>&>(*theory_->getSignature());
		signature_ = new source :: Signature<>(signature);
	}
	Decompose :: ~ Decompose()
	{
		deleteAggregateObject (comments_);

		deleteAggregateObject (initialTheory_);
		deleteAggregateObject (minimalTheory_);
		deleteAggregateObject (normalTheory_);
		deleteAggregateObject (primitiveTheory_);
		deleteAggregateObject (decomposedTheory_);
		deleteAggregateObject (assembledTheory_);

		deleteAggregateObject (TcupTdelta_);
		deleteAggregateObject (TcupTdeltaExpansion_);
		deleteAggregateObject (TcupTdeltaModel_);
		deleteAggregateObject (deltaExpanded_),

		deleteAggregateObject (signature_);
		deleteAggregateObject (sigma_);
		deleteAggregateObject (epsilon_);
		deleteAggregateObject (theta_);
	}

	const del :: Decompose*
	Decompose :: current() {
		return current_;
	}

using manipulator :: endLine;

	// del :: Decompose implementation
	const del :: Theory*
	Decompose :: getMinimalTheory() const {
		return minimalTheory_;
	}
	const del :: Theory*
	Decompose :: getNormalTheory() const {
		return normalTheory_;
	}
	const del :: Theory*
	Decompose :: getPrimitiveTheory() const {
		return primitiveTheory_;
	}
	const del :: Theory*
	Decompose :: getDecomposedTheory() const {
		return decomposedTheory_;
	}
	const del :: Theory*
	Decompose :: getAssembledTheory() const {
		return assembledTheory_;
	}
	const del :: Expansion*
	Decompose :: getDeltaExpansion() const {
		return TcupTdeltaExpansion_;
	}
	const del :: Theory*
	Decompose :: getDeltaTheory() const {
		return TcupTdelta_;
	}
	const del :: Model*
	Decompose :: getDeltaModel() const {
		return TcupTdeltaModel_;
	}
	const del :: Decomposition*
	Decompose :: decompose() const
	{
		const value :: Integer
			partialDecompositionFactor = Config :: partialDecompositionFactor();
		if (partialDecompositionFactor == value :: undefined :: INTEGER) {
			processTheory();
		} else {
			const value :: Integer theorySize = theory_->getSize();
			for (value :: Integer i = 0; i < theorySize / partialDecompositionFactor; ++ i) {
				const value :: Integer partialSize = i * (theorySize / partialDecompositionFactor);
				if (Config :: verbose()) {
					std :: cout << std :: endl;
					std :: cout << "processing theory part of size: " << partialSize << std :: endl;
				}
				processTheory (partialSize);
				const_cast<Decompose*>(this)->clear();
			}
		}
		return decomposition_;
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Decompose :: replicate (String& string) const
	{
		return;
		if (comments_ != NULL) {
			comments_->translate (string);
		}
		string << location_.getIndent();
		string << Token :: decompose_ << space;
		string << Token :: theory_ << space;
		string << Token :: openBracket_;
		string << Table :: theories()->get (theoryName_);
		string << Token :: comma_ << space;
		string << Table :: signatures()->get (signatureName_);
		string << Token :: closeBracket_ << space << endLine;
		string << endLine;
	}
	void
	Decompose :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Decompose :: commitSuicide() {
		delete this;
	}
	Size_t
	Decompose :: getSizeOf() const {
		return sizeof (Decompose);
	}
	Size_t
	Decompose :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);

		volume += getAggregateVolume (initialTheory_);
		volume += getAggregateVolume (minimalTheory_);
		volume += getAggregateVolume (normalTheory_);
		volume += getAggregateVolume (primitiveTheory_);
		volume += getAggregateVolume (decomposedTheory_);
		volume += getAggregateVolume (assembledTheory_);

		volume += getAggregateVolume (TcupTdelta_);
		volume += getAggregateVolume (TcupTdeltaExpansion_);
		volume += getAggregateVolume (TcupTdeltaModel_);
		volume += getAggregateVolume (deltaExpanded_);

		volume += getAggregateVolume (signature_);
		volume += getAggregateVolume (sigma_);
		volume += getAggregateVolume (epsilon_);
		volume += getAggregateVolume (theta_);

		volume += trivialDecomposition_.getVolume();
		volume += nontrivialDecomposition_.getVolume();
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Decompose :: processTheory (const value :: Integer partialSize) const
	{
		Timers :: decomposing().start();
		try {
			Table :: pushVariables();
			current_ = this;
			//std :: cout << std :: endl << "-----------------------------------" << std :: endl;
			startTheory (partialSize);
			if (Config :: partialDecompositionFactor() == value :: undefined :: INTEGER) {
				compileTheory (theory_, false);
			}
			//std :: cout << *theory_ << std :: endl;
			minimizeTheory();
			//std :: cout << *minimalTheory_ << std :: endl;
			normalizeTheory();
			//std :: cout << *normalTheory_ << std :: endl;
			primitivizeTheory();
			//std :: cout << *primitiveTheory_ << std :: endl;
			decomposeTheory();
			//std :: cout << *decomposedTheory_ << std :: endl;
			assembleTheory();
			//std :: cout << *assembledTheory_ << std :: endl;
			if (Config :: partialDecompositionFactor() == value :: undefined :: INTEGER) {
				decomposition_ = compileTheory (assembledTheory_, true);
			}
			finishTheory();

			//std :: cout << *decomposition << std :: endl;
			//std :: cout << *theory_ << std :: endl;
			//std :: cout << *assembledTheory_ << std :: endl;
			if ((decomposition_ != NULL) && Config :: verify() ) {
				if (decomposition_->verify())  {
					std :: cout << "verification - successful." << std :: endl;
				} else {
					std :: cout << "verification - failure." << std :: endl;
				}
			}
			//std :: cout << std :: endl << std :: endl;
			//std :: cout << std :: endl << "-----------------------------------" << std :: endl;
			//std :: cout << std :: endl << std :: endl << std :: endl << std :: endl;

			current_ = NULL;
			Table :: popVariables();
		} catch (exception :: OutOfTime& outOfTime) {
			if (Config :: verbose()) {
				std :: cout << "failed to decompose theory " << Table :: theories()->get (theoryName_) << " ";
				std :: cout << "up to the signature " << Table :: signatures()->get (signatureName_) << " : ";
				std :: cout << "out of time." << std :: endl;
			}
		} catch (Error*) {
			if (delta_ != NULL) {
				std :: cout << *delta_ << std :: endl;
			}
			showAllTheories();
			throw;
		}
		Timers :: decomposing().stop();
	}
	void
	Decompose :: startTheory (const value :: Integer partialSize) const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
			std :: cout << chars :: TAB << "performing decomposition of: ";
			const value :: Theory name = theory_->getName();
			const String& nameString = Table :: theories()->get (name);
			std :: cout << nameString << std :: endl;
		}
		Del :: statistics().push();
		const value :: Theory name = theory_->getName();
		const String& nameString = Table :: theories()->get (name);
		Del :: statistics().data()->setTheory (name);
		if (partialSize == value :: undefined :: INTEGER) {
			initialTheory_ = theory_->clone();
		} else {
			const Theory* theory = dynamic_cast<const Theory*>(theory_);
			initialTheory_ = new Theory (*theory, partialSize);
		}
		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << "//  DECOMPOSING THEORY: " << nameString << endLine;
		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << endLine;
		//Del :: log()->message() << *theory_ << endLine;
		Del :: statistics().data()->setOriginalTheorySize (theory_->getSize());
	}
	void
	Decompose :: minimizeTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << "minimizing ... " << std :: flush;
		}
		Del :: del()->timers().minimize().start();
		minimalTheory_ = initialTheory_->clone();
		minimalTheory_->minimize();
		Del :: del()->timers().minimize().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << Del :: del()->timers().minimize() << std :: endl;
		}
		Del :: statistics().data()->minimizeTimer() = Del :: del()->timers().minimize();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        MINIMAL THEORY:             */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *minimalTheory_ << endLine;
		Del :: statistics().data()->setMinimalTheorySize (minimalTheory_->getSize());

		//std :: cout << "minimalTheory_ = " << std :: endl;
		//std :: cout << *minimalTheory_ << std :: endl << std :: endl;
	}
	void
	Decompose :: normalizeTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << "normalizing ... " << std :: flush;
		}
		Del :: del()->timers().normalize().start();
		normalTheory_ = minimalTheory_->clone();
		normalTheory_->normalize();
		Del :: del()->timers().normalize().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << Del :: del()->timers().normalize() << std :: endl;
		}
		Del :: statistics().data()->normalizeTimer() = Del :: del()->timers().normalize();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        NORMAL THEORY:              */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *normalTheory_ << endLine;
		Del :: statistics().data()->setNormalTheorySize (normalTheory_->getSize());

		//std :: cout << "normalTheory_ = " << std :: endl;
		//std :: cout << *normalTheory_ << std :: endl << std :: endl;
	}
	void
	Decompose :: primitivizeTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << "primitivizing ... " << std :: flush;
		}
		Del :: del()->timers().primitivize().start();
		primitiveTheory_ = normalTheory_->clone();
		primitiveTheory_->primitivize (const_cast<del :: Signature*>(deltaExpanded_));
		primitiveTheory_->normalize();
		Del :: del()->timers().primitivize().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << Del :: del()->timers().primitivize() << std :: endl;
		}
		Del :: statistics().data()->primitivizeTimer() = Del :: del()->timers().primitivize();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        PRIMITIVE THEORY:           */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *primitiveTheory_ << endLine;
		Del :: statistics().data()->setPrimitiveTheorySize (primitiveTheory_->getSize());

		//std :: cout << "primitiveTheory_ = " << std :: endl;
		//std :: cout << *primitiveTheory_ << std :: endl << std :: endl;
	}
	void
	Decompose :: decomposeTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << "decomposing ... " << std :: flush;
		}
		Del :: del()->timers().decompose().start();
		prepareDeltaCopy();
		prepareModel();
		decomposedTheory_ = primitiveTheory_->clone();
		decomposedTheory_->decompose (deltaExpanded_);
		Del :: del()->timers().decompose().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB;
			std :: cout << "done in " << Del :: del()->timers().decompose() << std :: endl;
		}
		Del :: statistics().data()->decomposeTimer() = Del :: del()->timers().decompose();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        DECOMPOSED THEORY:          */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *decomposedTheory_ << endLine;

		//std :: cout << "decomposedTheory_ = " << std :: endl;
		//std :: cout << *decomposedTheory_ << std :: endl << std :: endl;

		Del :: statistics().data()->setDecomposedTheorySize (decomposedTheory_->getSize());
	}
	void
	Decompose :: assembleTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << "assembling ... " << std :: flush;
		}
		Del :: del()->timers().assemble().start();
		assembledTheory_ = decomposedTheory_->clone();
		assembledTheory_->assemble (deltaExpanded_);
		assembledTheory_->repair();

		Del :: del()->timers().assemble().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << Del :: del()->timers().assemble() << std :: endl;
		}
		Del :: statistics().data()->assembleTimer() = Del :: del()->timers().assemble();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        ASSEMBLED THEORY:           */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *assembledTheory_ << endLine;

		//std :: cout << "assembledTheory_ = " << std :: endl;
		//std :: cout << *assembledTheory_ << std :: endl;

		Del :: statistics().data()->setAssembledTheorySize (assembledTheory_->getSize());
	}
	void
	Decompose :: finishTheory() const
	{
		const value :: Theory name = theory_->getName();
		const String& nameString = Table :: theories()->get (name);

		const value :: Integer
			decompositionQuality = evalQuality();
		Del :: statistics().data()->setDecompositionQuality (decompositionQuality);

		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << "//  THEORY: " << nameString << " IS FINISHED" << endLine;
		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << endLine << endLine << endLine;
		Del :: log()->message() << endLine << endLine << endLine;
	}
	void
	Decompose :: prepareDeltaCopy() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "arranging T u T* ... " << std :: flush;
		}
		Timer timer;
		timer.start();
		TcupTdelta_ = primitiveTheory_->clone();
		TcupTdeltaExpansion_ = new source :: Expansion<>(delta_);
		TcupTdelta_->makeDeltaCopy (TcupTdeltaExpansion_);
		TcupTdelta_->unite (primitiveTheory_, false);
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << timer << std :: endl;
		}
	}
	void
	Decompose :: prepareModel() const
	{
		TcupTdeltaModel_ = new model :: Structure<>();
		try {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << chars :: TAB << chars :: TAB;
				std :: cout << "building model ... " << std :: flush;
			}
			Timer timer;
			timer.start();
			TcupTdeltaModel_->build (TcupTdelta_);
			timer.stop();
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << "done in " << timer;
				std :: cout << ". Model volume = ";
				memory :: Unit :: show (std :: cout, TcupTdeltaModel_->getVolume());
				std :: cout << std :: endl;
			}

			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << std :: endl << chars :: TAB << chars :: TAB;
				std :: cout << "overbuilding model ... " << std :: flush;
			}
			timer.start();
			TcupTdeltaModel_->build (TcupTdelta_);
			timer.stop();
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				std :: cout << "done in " << timer;
				std :: cout << ". Model volume = ";
				memory :: Unit :: show (std :: cout, TcupTdeltaModel_->getVolume());
				std :: cout << std :: endl;
			}
		} catch (Error* error) {
			std :: cout << "TcupTdelta_ = " << *TcupTdelta_ << std :: endl;
			throw error;
		}
	}
	void
	Decompose :: clear()
	{
		deleteAggregateObject (initialTheory_);
		deleteAggregateObject (minimalTheory_);
		deleteAggregateObject (normalTheory_);
		deleteAggregateObject (primitiveTheory_);
		deleteAggregateObject (decomposedTheory_);
		deleteAggregateObject (assembledTheory_);

		deleteAggregateObject (TcupTdelta_);
		deleteAggregateObject (TcupTdeltaExpansion_);
		deleteAggregateObject (TcupTdeltaModel_);
		deleteAggregateObject (deltaExpanded_),

		deleteAggregateObject (signature_);
		deleteAggregateObject (sigma_);
		deleteAggregateObject (epsilon_);
		deleteAggregateObject (theta_);

		deltaExpanded_ = delta_->clone();
		sigma_ = new source :: Signature<>();
		epsilon_ = new source :: Signature<>();
		theta_ = new source :: Signature<>();
	}

	const del :: Decomposition*
	Decompose :: compileTheory (const del :: Theory* theory, const bool isFinal) const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (isFinal) {
				std :: cout << chars :: TAB << "computing syntactic decomposition";
			} else {
				std :: cout << chars :: TAB << "preliminary syntactic decomposition";
			}
			std :: cout <<  " ... " << std :: flush;
		}
		Del :: del()->timers().compile().start();
		const del :: Decomposition* decomposition = compile (theory, isFinal);
		Del :: del()->timers().compile().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << Del :: del()->timers().compile() << std :: endl;
		}
		Del :: statistics().data()->compileTimer() = Del :: del()->timers().compile();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        COMPILED THEORY:            */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;

		return decomposition;
	}

	const del :: Decomposition*
	Decompose :: compile (const del :: Theory* theory, const bool isFinal) const
	{
		Memory :: stack().push();
		TheoryPartition_ theoryPartition (INITIAL_THEORY_PARTITION_CAPACITY);
		partitionTheory (theory, theoryPartition, isFinal);
		completeDecomposition (theoryPartition, isFinal);
		const del :: Decomposition*
			decomposition = createTheoryDecomposition (theoryPartition, theory, isFinal);
		Memory :: stack().pop();
		return decomposition;
	}
	void
	Decompose :: partitionTheory
	(
		const del :: Theory* theory,
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const
	{
		FormulaVector_* deltaComponent = new FormulaVector_ (INITIAL_FORMULA_VECTOR_CAPACITY);
		theoryPartition.add (deltaComponent);
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "partitioning theory ... " << std :: flush;
		}
		Timer timer;
		timer.start();
		Timers :: startProgress();
		for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				Del :: getDel()->getTimers().showProgress (i, theory->getSize());
			}
			const del :: Formula* formula = theory->getFormula (i)->clone();
			bool joinedComponents [theoryPartition.getSize()];
			value :: Integer index = value :: undefined :: INTEGER;

			if (formula->getSignature()->isSubset (delta_)) {
				for (value :: Integer j = 0; j < theoryPartition.getSize(); ++ j) {
					joinedComponents [j] = false;
				}
				index = 0;
			} else {
				for (value :: Integer j = 1; j < theoryPartition.getSize(); ++ j) {
					joinedComponents [j] = false;
					FormulaVector_* component = theoryPartition.getValue (j);
					if (isConnected (formula, component)) {
						joinedComponents [j] = true;
						if (index == value :: undefined :: INTEGER) {
							index = j;
						}
					}
				}
			}
			if (index != value :: undefined :: INTEGER) {
				FormulaVector_* growComponent = theoryPartition.getValue (index);
				growComponent->add (formula);
				for (value :: Integer j = theoryPartition.getSize() - 1; j > index ; -- j) {
					if (joinedComponents [j]) {
						FormulaVector_* component = theoryPartition.getValue (j);
						growComponent->unite (*component);
						theoryPartition.remove (j);
					}
				}
			} else {
				FormulaVector_* newComponent = new FormulaVector_ (INITIAL_FORMULA_VECTOR_CAPACITY);
				theoryPartition.add (newComponent);
				newComponent->add (formula);
			}
		}
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
			std :: cout << chars :: TAB;
		}
		Timers :: stopProgress();
	}
	bool
	Decompose :: isConnected (const del :: Formula* formula_1, const FormulaVector_* component) const
	{
		const del :: Signature*
			signature = formula_1->getSignature();
		for (value :: Integer i = 0; i < signature->cardinality(); ++ i) {
			const del :: Symbol&
				symbol = signature->getSymbol (i);
			if (delta_->containsSymbol (symbol)) {
				continue;
			}
			for (value :: Integer j = 0; j < component->getSize(); ++ j) {
				const del :: Formula*
					formula_2 = component->getValue (j);
				if (formula_2->isConnected (symbol)) {
					return true;
				}
			}
		}
		return false;
	}
	const del :: Decomposition*
	Decompose :: createTheoryDecomposition
	(
		const TheoryPartition_& theoryPartition,
		const del :: Theory* theory,
		const bool isFinal
	) const
	{
		const bool isOriginalTheory = (theory == theory_);
		Decomposition* decomposition =
				isFinal ?
				new source :: Decomposition (theory_->getName(), delta_->getName(), true) :
				NULL;
		const String& nameString = Table :: theories()->get (theory_->getName());
		String deltaNameString (nameString);
		deltaNameString << "_Delta";

		for (value :: Integer i = 0; i < theoryPartition.getSize(); ++ i) {
			FormulaVector_* formulaVector = theoryPartition.getValue (i);
			if (formulaVector->isEmpty()) {
				continue;
			}
			value :: Theory name =
				isFinal ?
				(
					(i == 0) ?
					Table :: theories()->add (deltaNameString):
					Table :: theories()->fresh (nameString)
				):
				value :: undefined :: THEORY;
			source :: Theory* theory = new source :: Theory (name, isFinal);
			for (value :: Integer j = 0; j < formulaVector->getSize(); ++ j) {
				const del :: Formula* formula = formulaVector->getValue (j);
				theory->addFormula (formula);
			}
			formulaVector->clear();
			/*std :: cout << "FUCK!!!" << std :: endl;
			theory->assembleConjunctions (false);
			theory->assembleEqualities (false);
			std :: cout << "!!!FUCK" << std :: endl;*/

			const value :: Integer
				theoryCardinality = theory->getSize();
			Del :: statistics().data()->theoryDecomposition (isOriginalTheory).add (theoryCardinality);

			const del :: Signature*
				signature = theory->getSignature (true);
			const value :: Integer
				signatureCardinality = signature->getSize();

			if (isFinal) {
				nontrivialDecomposition_.add (signature->clone());
			} else {
				trivialDecomposition_.add (signature->clone());
			}
			Del :: statistics().data()->signatureDecomposition (isOriginalTheory).add (signatureCardinality);

			theory->setName (name);
			if (isFinal) {
				Math :: source()->get()->addTheory (theory);
				decomposition->addComponent (name);
			} else {
				theory->commitSuicide();
			}
		}
		return decomposition;
	}
	void
	Decompose :: completeDecomposition
	(
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const
	{
		del :: Signature* missingSignature = computeMissingSignature (theoryPartition);
		completeMissingFromDelta (missingSignature, theoryPartition, isFinal);
		completeMissingNotFromDelta (missingSignature, theoryPartition, isFinal);
		missingSignature->commitSuicide();
	}
	del :: Signature*
	Decompose :: computeMissingSignature (const TheoryPartition_& theoryPartition) const
	{
		del :: Signature* unitedSignature = new source :: Signature<allocator :: Heap>();

		for (value :: Integer i = 0; i < theoryPartition.getSize(); ++ i) {
			const FormulaVector_* formulaVector = theoryPartition.getValue (i);
			for (value :: Integer j = 0; j < formulaVector->getSize(); ++ j) {
				const del :: Formula* formula = formulaVector->getValue (j);
				const del :: Signature* formulaSignature = formula->getSignature();
				unitedSignature->join (formulaSignature);
			}
		}
		del :: Signature* missingSignature = theory_->getSignature (true)->clone();
		missingSignature->subtract (unitedSignature);
		unitedSignature->commitSuicide();
		return missingSignature;
	}
	void
	Decompose :: completeMissingFromDelta
	(
		const del :: Signature* missingSignature,
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const
	{
		del :: Signature* missingFromDelta = missingSignature->clone();
		missingFromDelta->intersect (delta_);

		if (missingFromDelta->getSize() > 0) {
			for (value :: Integer i = 0; i < missingFromDelta->getSize(); ++ i) {
				const del :: Symbol missingSymbol = missingFromDelta->getSymbol (i);
				const del :: Formula* tautology = formula :: Subset :: createTautology (missingSymbol);
				theoryPartition.getValue (0)->add (tautology);
			}
		}
		missingFromDelta->commitSuicide();
	}
	void
	Decompose :: completeMissingNotFromDelta
	(
		const del :: Signature* missingSignature,
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const
	{
		del :: Signature* missingNotFromDelta = missingSignature->clone();
		missingNotFromDelta->subtract (delta_);

		for (value :: Integer i = 0; i < missingNotFromDelta->getSize(); ++ i) {
			const del :: Symbol missingSymbol = missingNotFromDelta->getSymbol (i);
			const del :: Formula* tautology = formula :: Subset :: createTautology (missingSymbol);
			FormulaVector_* newComponent = new FormulaVector_ (INITIAL_FORMULA_VECTOR_CAPACITY);
			theoryPartition.add (newComponent);
			newComponent->add (tautology);
		}
		missingNotFromDelta->commitSuicide();
	}

	void
	Decompose :: showAllTheories() const
	{
		showTheory (theory_, "theory");
		showTheory (minimalTheory_, "minimal theory");
		showTheory (normalTheory_, "normal theory");
		showTheory (primitiveTheory_, "primitive theory");
		showTheory (decomposedTheory_, "decomposed theory");
		showTheory (assembledTheory_, "assembled theory");
	}
	void
	Decompose :: showTheory (const del :: Theory* theory, const char* header) const
	{
		if (theory != NULL) {
			std :: cout << std :: endl;
			std :: cout << std :: endl;
			std :: cout << header << " : " << std :: endl;
			std :: cout << *theory << std:: endl;
		}
	}

	value :: Integer
	Decompose :: evalQuality() const
	{
		if (nontrivialDecomposition_.isEmpty()) {
			return 1;
		}
		const value :: Integer size = trivialDecomposition_.getSize();
		value :: Integer result = 0;
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Signature* trivialComponent = trivialDecomposition_.getValue (i);
			result += evalQuality (trivialComponent);
		}
		return result / size;
	}
	value :: Integer
	Decompose :: evalQuality (const del :: Signature* trivialComponent) const
	{
		value :: Integer result = 0;
		for (value :: Integer i = 0; i < nontrivialDecomposition_.getSize(); ++ i) {
			const del :: Signature* nontrivialComponent = nontrivialDecomposition_.getValue (i);
			if (nontrivialComponent->isSubset (trivialComponent)) {
				++ result;
			}
		}
		return result;
	}

	/***********************************
	 *		Static private attributes
	 ***********************************/

	const del :: Decompose* Decompose :: current_ = NULL;
}
}



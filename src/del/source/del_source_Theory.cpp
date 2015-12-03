/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Theory.cpp                                    */
/* Description:     contents of a theory                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_THEORY_CPP_
#define DEL_SOURCE_THEORY_CPP_

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Theory :: Theory () :
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: THEORY),
	formulae_ (INITIAL_FORMULAE_CAPACITY),
	signature_ (NULL),
	isNormal_ (false),
	isMinimal_ (false),
	isPrimitive_ (false),
	isDecomposed_(false),
	isAssembled_ (false),
	isForOutput_ (false) {
	}
	inline
	Theory :: Theory (const value :: Theory name, const bool isForOutput) :
	location_ (),
	comments_ (NULL),
	name_ (name),
	formulae_ (INITIAL_FORMULAE_CAPACITY),
	signature_ (NULL),
	isNormal_ (false),
	isMinimal_ (false),
	isPrimitive_ (false),
	isDecomposed_(false),
	isAssembled_ (false),
	isForOutput_ (isForOutput)
	{
		if (name == value :: undefined :: THEORY) {
			return;
		}
		value :: Theory n = Math :: theories()->add (this);
		if (n != name_) {
			std :: cout << *this << std :: endl;
			const del :: Theory* th = Math :: theories()->get (n);
			std :: cout << *th << std :: endl;
			std :: cout << "name = " << Table :: theories()->get (name_) << std :: endl;
			std :: cout << "n = " << Table :: theories()->get (n) << std :: endl;
		}
	}
	inline
	Theory :: Theory
	(
		const Location& location,
		const del :: Comments* const comments,
		const value :: Theory name,
		const bool isForOutput
	) :
	location_ (location),
	comments_ (comments),
	name_ (name),
	formulae_ (INITIAL_FORMULAE_CAPACITY),
	signature_ (NULL),
	isNormal_ (false),
	isMinimal_ (false),
	isPrimitive_ (false),
	isDecomposed_(false),
	isAssembled_ (false),
	isForOutput_ (isForOutput)
	{
		if (name == value :: undefined :: THEORY) {
			return;
		}
		value :: Theory n = Math :: theories()->add (this);
		if (n != name_) {
			std :: cout << *this << std :: endl;
			const del :: Theory* th = Math :: theories()->get (n);
			std :: cout << *th << std :: endl;
			std :: cout << "name = " << Table :: theories()->get (name_) << std :: endl;
			std :: cout << "n = " << Table :: theories()->get (n) << std :: endl;
		}
	}
	inline
	Theory :: Theory (const Theory& theory) :
	location_ (theory.location_),
	comments_ (NULL),
	name_ (theory.name_),
	formulae_ (theory.formulae_.getSize()),
	signature_ (theory.getSignature()->clone()),
	isNormal_ (theory.isNormal_),
	isMinimal_ (theory.isMinimal_),
	isPrimitive_ (theory.isPrimitive_),
	isDecomposed_(theory.isDecomposed_),
	isAssembled_ (theory.isAssembled_),
	isForOutput_ (theory.isForOutput_)
	{
		for (value :: Integer i = 0; i < theory.formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula = theory.formulae_.getValue (i)->clone();
			formulae_.add (formula);
		}
	}
	inline
	Theory :: Theory (const Theory& theory, const value :: Integer size) :
	location_ (theory.location_),
	comments_ (NULL),
	name_ (theory.name_),
	formulae_ (size),
	signature_ (NULL),
	isNormal_ (theory.isNormal_),
	isMinimal_ (theory.isMinimal_),
	isPrimitive_ (theory.isPrimitive_),
	isDecomposed_(theory.isDecomposed_),
	isAssembled_ (theory.isAssembled_),
	isForOutput_ (theory.isForOutput_)
	{
		const value :: Integer s = (theory.getSize() < size) ? theory.getSize() : size;
		for (value :: Integer i = 0; i < s; ++ i) {
			const del :: Formula* const
				formula = theory.formulae_.getValue (i)->clone();
			formulae_.add (formula);
		}
		getSignature (true);
	}
	Theory :: ~ Theory()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (signature_);
	}

	Theory*
	Theory :: createRandom (const del :: Signature* signature)
	{
		const value :: Integer size = Config :: getTheorySize();
		return createRandom (signature, size);
	}
	Theory*
	Theory :: createRandom (const del :: Signature* signature, const value :: Integer size)
	{
		const value :: Theory name = Table :: theories()->fresh ("th");
		Theory* theory = new Theory (name);
		for (value :: Integer i = 0; i < size; ++ i) {
			del :: Formula*
				formula = formula :: Formula :: createRandom (signature);
			while (formula->isTrivial()) {
				formula->commitSuicide();
				formula = formula :: Formula :: createRandom (signature);
			}
			theory->addFormula (formula);
		}
		return theory;
	}

	// del :: Theory implementation
	const Writable*
	Theory :: translate() const
	{
		switch (Config :: outputFormat()) {
		case Config :: MAN_FORMAT : {
			return translateToManFormat();
		}
		case Config :: FUNC_FORMAT : {
			return translateToFuncFormat();
		}
		}
	}
	void
	Theory :: extendWithCopies (const del :: Signature* delta)
	{
		//std :: cout << std :: endl;
		//std :: cout << "delta = " << *delta << std :: endl;
		const value :: Integer size = formulae_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_.getValue (i));
			if (formula->extendWithCopies (this, delta)) {
				//std :: cout << "extended: " << *formula << std :: endl;
			}
		}
	}
	void
	Theory :: repair()
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_.getValue (i));
			if (formula->hasInvalidKind()) {
				formulae_ [i] = formula->clone();
				deleteObject (formula);
			}
		}
	}
	void
	Theory :: assemble (const del :: Signature* delta)
	{
		assembleTheoryFirst();
		while (assembleTheorySecond (delta, true));
		while (assembleTheorySecond (delta, false));
		removeRedundant();
		isAssembled_ = false;
		while (!isAssembled_) {
			isAssembled_ = assembleEqualities (false);
		}
		removeRedundant();
		denormalizeFormulas();
	}

	const del :: Signature*
	Theory :: computeDelta (const value :: Integer threshold) const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB;
			std :: cout << "computing delta ..." << std :: flush;
		}
		Timer timer;
		timer.start();
		if (signature_ == NULL) {
			getSignature();
		}
		const value :: Integer signatureCardinality = signature_->cardinality();
		value :: Integer cohesionArray [signatureCardinality];
		value :: Integer maxCohesion = 0;
		value :: Integer sumCohesion = 0;
		Timers :: startProgress();
		for (value :: Integer i = 0; i < signatureCardinality; ++ i) {
			Timers :: checkOutOfTime();
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				Del :: getDel()->getTimers().showProgress (i, signatureCardinality, timer);
			}
			const del :: Symbol
				symbol = signature_->getSymbol (i);
			const value :: Integer
				cohesion = computeCohesion (symbol);
			cohesionArray [i] = cohesion;
			maxCohesion = (maxCohesion < cohesion) ? cohesion : maxCohesion;
			sumCohesion += cohesion;
		}
		Timers :: stopProgress();
		const double
			averageSymbolRadius = static_cast<double>(sumCohesion) / signatureCardinality;
		const value :: Signature
			nameDelta = Table :: signatures()->fresh ("delta");
		del :: Signature* const
			delta = new source :: Signature<allocator :: Heap>(nameDelta);
		Math :: signatures()->add (delta);
		value :: Integer cohesionThreshold = 0;
		switch (Config :: getDeltaGenerationMode()) {
		case Config :: PERCENT_OF_MAX_COHESION :
			cohesionThreshold = maxCohesion * threshold / 100; break;
		case Config :: PERCENT_OF_RELATIVE_COHESION :
			cohesionThreshold = signatureCardinality * threshold / 100; break;
		}
		for (value :: Integer i = 0; i < signature_->cardinality(); ++ i) {
			const del :: Symbol
				symbol = signature_->getSymbol (i);
			if (cohesionArray [i] >= cohesionThreshold) {
				delta->addSymbol (symbol);
			}
		}
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
		}
		Del :: log ()->message (Log :: AUTOMATIC_DELTA_LOG) << "Delta signature computed:" << endLine << endLine;
		if (delta->getSize() > 0) {
			delta->replicate (Del :: log ()->message (Log :: AUTOMATIC_DELTA_LOG));
			Del :: log ()->message (Log :: AUTOMATIC_DELTA_LOG) << endLine << endLine;
		} else {
			Del :: log ()->message (Log :: AUTOMATIC_DELTA_LOG) << "No such delta." << endLine << endLine;
		}
		Del :: log ()->message (Log :: AUTOMATIC_DELTA_LOG) << "Average symbol radius: ";
		Del :: log ()->message (Log :: AUTOMATIC_DELTA_LOG) << averageSymbolRadius << endLine;
		return delta;
	}
	bool
	Theory :: isEqual (const del :: Theory* theory) const
	{
		const value :: Integer
			size = theory->getSize();
		if (formulae_.getSize() != size) {
			return false;
		}
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Formula*
				formula = formulae_.getValue (i);
			if (!theory->containsFormula (formula)) {
				return false;
			}
		}
		return true;
	}
	bool
	Theory :: isEquivalent (const del :: Theory* theory, const bool showDifference) const
	{
		const del :: Signature* signature_1 = this->getSignature (true);
		const del :: Signature* signature_2 = theory->getSignature (true);
		//if (!signature_1->isEqual (signature_2)) {
		if (false) {
			std :: cout << "theory_1: " << *theory << std :: endl;
			std :: cout << "theory_2: " << *this << std :: endl;
			std :: cout << "signature: " << std :: endl;
			std :: cout << *signature_1 << std :: endl;
			std :: cout << "is not equal to: " << std :: endl;
			std :: cout << *signature_2 << std :: endl;
			std :: cout << std :: endl;
			std :: cout << "/**************************************/" << std :: endl;
			std :: cout << "/*        VERIFICATION FAIL:          */" << std :: endl;
			std :: cout << "/**************************************/" << std :: endl;
			std :: cout << std :: endl;
			return false;
		}

		const bool d_1 = this->entails (theory, showDifference);
		const bool d_2 = theory->entails (this, showDifference);
		const bool result = (d_1 && d_2);
		if (!result && showDifference) {
			std :: cout << std :: endl;
			std :: cout << "/**************************************/" << std :: endl;
			std :: cout << "/*        VERIFICATION FAIL:          */" << std :: endl;
			std :: cout << "/**************************************/" << std :: endl;
			std :: cout << std :: endl;
		}
		return result;
	}
	bool
	Theory :: entails (const del :: Theory* theory, const bool showDifference) const
	{
		for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
			const del :: Formula* const
				formula = theory->getFormula (i);
			if (!entails (formula, showDifference)) {
				return false;
			}
		}
		return true;
	}
	bool
	Theory :: entails (const del :: Formula* f, const bool showDifference) const
	{
		del :: Formula* formula = f->clone();
		del :: Theory* theory = clone();
		formula->setPrimitivized (false);
		formula->primitivize (theory, NULL, false);
		theory->normalize();
		Memory :: stack().push();
		Model* model = new model :: Structure<allocator :: Stack>(theory);

		const bool result = formula->isTrue (model);
		if (!result && showDifference) {
			std :: cout << std :: endl;
			std :: cout << "theory: " << std :: endl;
			std :: cout << *theory << std :: endl;
			std :: cout << "does not entail: " << std :: endl;
			std :: cout << *f;
			std :: cout << std :: endl;
		}
		model->commitSuicide();
		Memory :: stack().pop();

		theory->commitSuicide();
		formula->commitSuicide();
		return result;
	}
	const del :: Signature*
	Theory :: getSignature (const bool force) const
	{
		if (signature_ != NULL) {
			if (force) {
				const_cast<del :: Signature*>(signature_)->commitSuicide();
			} else {
				return signature_;
			}
		}
		del :: Signature* const
			signature = new source :: Signature<>();
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			const del :: Signature* const
				sigma = formula->getSignature (force);
			signature->join (sigma);
		}
		signature_ = signature;
		return signature_;
	}
	value :: Theory
	Theory :: getName() const {
		return name_;
	}
	void
	Theory :: setName (const value :: Theory name) {
		name_ = name;
	}
	void
	Theory :: primitivize (del :: Signature* signature)
	{
		primitivizeFormulas (signature);
		repair();
	}
	void
	Theory :: normalize()
	{
		normalizeFormulas();
		transformFormulas();
		repair();
	}
	void
	Theory :: minimize()
	{
		fastMinimization();
		repair();
	}
	void
	Theory :: decompose (const del :: Signature* signature)
	{
		primaryDecomposition (signature);
		repair();
		secondaryDecomposition (signature);
		repair();
	}

	void
	Theory :: makeDeltaCopy (const del :: Expansion* expansion)
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_.getValue (i));
			formula->makeDeltaCopy (expansion);
		}
	}
	void
	Theory :: makeDeltaCopy (const del :: Signature* delta)
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_.getValue (i));
			formula->makeDeltaCopy (delta);
		}
	}
	void
	Theory :: addFormula (const del :: Formula* const formula) {
		formulae_.add (formula);
	}
	void
	Theory :: removeFormula (const del :: Formula* formula_1)
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula_2 = formulae_.getValue (i);
			if (formula_2 == NULL) {
				continue;
			}
			if (formula_1->isEqual (formula_2)) {
				formulae_.remove (i);
				const_cast<del :: Formula*>(formula_2)->commitSuicide();
				return;
			}
		}
	}
	bool
	Theory :: containsFormula (const del :: Formula* formula_1) const
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula_2 = formulae_.getValue (i);
			if (formula_2 == NULL) {
				continue;
			}
			if (formula_1->isEqual (formula_2)) {
				return true;
			}
		}
		return false;
	}
	void
	Theory :: deleteFormula (const value :: Integer index)
	{
		del :: Formula* const
			formula = const_cast<del :: Formula*>(formulae_.getValue (index));
		formulae_.remove (index);
		formula->commitSuicide();
	}
	value :: Integer
	Theory :: getSize() const {
		return formulae_.getSize();
	}
	const del :: Formula*
	Theory :: getFormula (const value :: Integer i) const {
		return formulae_.getValue (i);
	}
	void
	Theory :: replaceTerm (const del :: Term* oldTerm, const del :: Term* newTerm)
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_.getValue (i));
			if (formula == NULL) {
				continue;
			}
			formula->replace (oldTerm, newTerm);
		}
	}
	void
	Theory :: unite (const del :: Theory* theory, const bool removeDuplicateFormulas)
	{
		for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
			const del :: Formula* const
				formula = theory->getFormula (i);
			if (removeDuplicateFormulas) {
				if (!contains (formula)) {
					formulae_.add (formula->clone());
				}
			} else {
				formulae_.add (formula->clone());
			}
		}
	}
	bool
	Theory :: isNormal() const {
		return isNormal_;
	}
	bool
	Theory :: isMinimal() const {
		return isMinimal_;
	}
	bool
	Theory :: isPrimitive() const {
		return isPrimitive_;
	}
	bool
	Theory :: isDecomposed() const {
		return isDecomposed_;
	}
	bool
	Theory :: isAssembled() const {
		return isAssembled_;
	}
	bool
	Theory :: isForOutput() const {
		return isForOutput_;
	}
	void
	Theory :: showDifference (const del :: Theory* theory) const
	{
		for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
			const del :: Formula* const
				formula = theory->getFormula (i);
			if (!contains (formula)) {
				std :: cout << i << " -- " << *formula << std :: endl;
			}
		}
	}

	// del :: Cloneable implementation
	del :: Theory*
	Theory :: clone() const {
		return new Theory (*this);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Theory :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent();
		string << Token :: theory_ << space;
		if (name_ != value :: undefined :: THEORY) {
			string << Table :: theories()->get (name_) << space;
		}
		string << Token :: equality_ << space;
		string << Token :: openBrace_ << endLine;
		const value :: Integer size = formulae_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			if (formula->getLocation().getIndent().isEmpty()) {
				string << tab;
			}
			formula->replicate (string);
			if (i < size - 1) {
				string << Token :: comma_;
			}
			string << endLine;
		}
		string << Token :: closeBrace_ << endLine << endLine;
	}
	void
	Theory :: translate (String& string) const
	{
		const Writable* owlSource = translate();
		owlSource->replicate (string);
		const_cast<Writable*>(owlSource)->commitSuicide();
	}
	void
	Theory :: show (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent();
		string << Token :: theory_ << space;
		if (name_ != value :: undefined :: THEORY) {
			string << Table :: theories()->get (name_) << space;
		}
		string << Token :: equality_ << space;
		string << Token :: openBrace_ << endLine;
		const value :: Integer size = formulae_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			if (formula->getLocation().getIndent().isEmpty()) {
				string << tab;
			}
			formula->show (string);
			if (i < size - 1) {
				string << Token :: comma_;
			}
			string << endLine;
		}
		string << Token :: closeBrace_ << endLine;
	}

	// Object implementation
	void
	Theory :: commitSuicide() {
		delete this;
	}
	Size_t
	Theory :: getVolume() const
	{
		Size_t volume = 0;
		volume += formulae_.getVolume();
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (signature_);
		return volume;
	}
	Size_t
	Theory :: getSizeOf() const {
		return sizeof (Theory);
	}

	/****************************
	 *		Private members
	 ****************************/

	// primitivization routines
	void
	Theory :: primitivizeFormulas (del :: Signature* signature)
	{
		isPrimitive_ = false;
		const value :: Integer size = formulae_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			Timers :: checkOutOfTime();
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_.getValue (i));
			del :: Formula* const
				clone = const_cast<del :: Formula*>(formula->clone());
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				Del :: getDel()->getTimers().showProgress (i, formulae_.getSize());
			}
			if (clone->primitivize (this, signature)) {
				formula->commitSuicide();
				formulae_.getReference (i) = NULL;
			}
			clone->commitSuicide();
		}
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Integer j = (size - 1) - i;
			if (formulae_.getValue (j) == NULL) {
				formulae_.remove (j);
			}
		}
		isPrimitive_ = true;
	}
	/*
	void
	Theory :: primitivizeFormulas (del :: Signature* signature)
	{
		isPrimitive_ = false;
		while (!isPrimitive_) {
			isPrimitive_ = true;
			for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
				Timers :: checkOutOfTime();

				del :: Formula* const
					formula = const_cast<del :: Formula*>(formulae_.getValue (i));
				del :: Formula* const
					clone = const_cast<del :: Formula*>(formula->clone());
				Del :: getDel()->getTimers().showProgress (i, formulae_.getSize());
				if (clone->primitivize (this, signature)) {
					formula->commitSuicide();
					formulae_.remove (i);
					isPrimitive_ = false;
					clone->commitSuicide();
					break;
				} else {
					clone->commitSuicide();
				}
			}
		}
		isPrimitive_ = true;
	}
	 */

	// normalization routines
	void
	Theory :: normalizeFormulas()
	{
		isNormal_ = false;
		while (!isNormal_) {
			isNormal_ = true;
			for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
				Timers :: checkOutOfTime();
				del :: Formula* const
					formula = const_cast<del :: Formula*>(formulae_.getValue (i));
				formula->simplify();
				/*if (Config :: verbosity() > Config :: VERBOSE_MIN) {
					Del :: getDel()->getTimers().showProgress (i, formulae_.getSize());
				}*/

				if (!formula->isPreNormal()) {
					/*if (Counter :: stop()) {
						std :: cout << "--------------------" << std :: endl;
						std :: cout << "before:" << std :: endl;
						std :: cout << "formula: " << *formula << std :: endl;
						std :: cout << *this << std :: endl;
					}*/
					formula->normalize (this);
					formulae_.remove (i);
					/*if (Counter :: stop()) {
						std :: cout << "after:" << std :: endl;
						std :: cout << *this << std :: endl;
						std :: cout << "--------------------" << std :: endl;
						std :: cout << std :: endl << std :: endl << std :: endl << std :: endl;
					}*/
					formula->commitSuicide();
					isNormal_ = false;
					break;
				}
			}
		}
	}
	void
	Theory :: transformFormulas()
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			if (formula->isNormal()) {
				continue;
			}
			switch (formula->getKind()) {
			case del :: Formula :: SIMPLE_SUB_KIND :
				formulae_[i] = new formula :: normal :: Simple (formula); break;
			case del :: Formula :: CONJ_SUB_KIND :
				formulae_[i] = new formula :: normal :: Conjunction (formula); break;
			case del :: Formula :: RIGHT_SUB_KIND :
				formulae_[i] = new formula :: normal :: RightExists (formula); break;
			case del :: Formula :: LEFT_SUB_KIND :
				formulae_[i] = new formula :: normal :: LeftExists (formula); break;
			default :
				Error* error = new Error (Error :: SEMANTIC);
				error->message() << "non-normal formula" << endLine;
				throw error;
			}
			deleteObject (formula);
		}
	}

	// decomposition routines
	void
	Theory :: primaryDecomposition (const del :: Signature* signature)
	{
		const value :: Integer size = formulae_.getSize();
		del :: Formula* formulas [size];
		for (value :: Integer i= 0; i < size; ++ i) {
			formulas [i] = const_cast<del :: Formula*>(formulae_ [i]);
			formulae_ [i] = NULL;
		}
		formulae_.clear();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "primary decomposition ... " << std :: flush;
		}
		Timer timer;
		timer.start();
		Timers :: startProgress();
		for (value :: Integer i = 0; i < size; ++ i) {
			Timers :: checkOutOfTime();
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				Del :: getDel()->getTimers().showProgress (i, size, "", true);
			}
			del :: Formula* const
				formula = formulas [i];
			if (formula->decompose (this, signature, true)) {
				formula->commitSuicide();
			} else {
				formulae_.add (formula);
			}
		}
		Timers :: stopProgress();
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
		}
	}
	void
	Theory :: secondaryDecomposition (const del :: Signature* signature)
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "secondary decomposition ... " << std :: flush;
		}
		Timer timer;
		timer.start();
		Timers :: startProgress();
		const value :: Integer size = formulae_.getSize();
		for (value :: Integer i= 0; i < size; ++ i) {
			Timers :: checkOutOfTime();
			if (Config :: verbosity() > Config :: VERBOSE_MIN) {
				(Del :: getDel()->getTimers().showProgress (i, size, "", true));
			}
			del :: Formula* const
				formula = const_cast<del :: Formula*>(formulae_ [i]);
			Timer t;
			t.start();
			formula->decompose (this, signature, false);
			t.stop();
			if (t.getSeconds() > 2) {
				std :: cout << std :: endl;
				std :: cout << "formula " << *formula << " ";
				std :: cout << "decomposed in " << t << std :: endl;
			}
		}
		Timers :: stopProgress();
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
		}
	}

	// assembling routines
	bool
	Theory :: assembleConjunctions (const bool inDefinitions)
	{
		if (formulae_.getSize() < 2) {
			return true;
		}
		bool result = true;
		bool conjunctionsAreAssembled = false;
		int c = 0;
		while (!conjunctionsAreAssembled) {
			conjunctionsAreAssembled = true;

			//Del :: getDel()->getTimers().showProgress (c, formulae_.getSize());
			//std :: cout << "iteration: " << c ++ << ", formulae_.getSize() = " << formulae_.getSize() << std :: endl;

			for (value :: Integer i = 0; i < formulae_.getSize() - 1; ++ i) {
				del :: Formula* const
					formula_1 = const_cast<del :: Formula*>(formulae_.getValue (i));

				//std :: cout << "formula (" << i << ") = " << *formula_1 << std :: endl;

				for (value :: Integer j = i + 1; j < formulae_.getSize(); ++ j) {
					del :: Formula* const
						formula_2 = const_cast<del :: Formula*>(formulae_.getValue (j));

					conjunctionsAreAssembled = assembleConjunctions (inDefinitions, formula_1, formula_2);
					if (!conjunctionsAreAssembled) {
						formulae_.remove (j);
						result = false;
						break;
					}
				}
				if (!conjunctionsAreAssembled) {
					formulae_.remove (i);
					break;
				}
			}
		}
		return result;
	}
	bool
	Theory :: assembleConjunctions
	(
		const bool inDefinitions,
		del :: Formula* formula_1,
		del :: Formula* formula_2
	)
	{
		const bool isSubset_1 = (formula_1->getType() == del :: Formula :: SUBSET_TYPE);
		const bool isSubset_2 = (formula_2->getType() == del :: Formula :: SUBSET_TYPE);
		if (!isSubset_1 || !isSubset_2) {
			return true;
		}
		const bool isEqual = formula_1->getTerm (0)->isEqual (formula_2->getTerm (0));
		if (!isEqual) {
			return true;
		}
		if (formula_1->getTerm (0)->getKind() == del :: Term :: TOP_KIND) {
			return true;
		}
		const bool isVariable = (formula_1->getTerm (0)->getKind() == del :: Term :: VARIABLE_KIND);
		if (inDefinitions) {
			if (!isVariable) {
				return true;
			}
			const Symbol variable = formula_1->getTerm (0)->getSymbol();
			if (!variable.isTemporary() || variable.isTop()) {
				return true;
			}
		}
		const del :: Term* term_1 = formula_1->getTerm (0)->clone();
		const del :: Term* terms [2] = {
			formula_1->getTerm (1)->clone(),
			formula_2->getTerm (1)->clone()
		};
		const del :: Term*
			term_2 = new term :: Intersect (terms, 2);
		term_2 = const_cast<del :: Term*>(term_2)->simplify();
		del :: Formula* conjunction =
			new formula :: Subset (Location(), term_1, term_2);
		if (!containsFormula (conjunction)) {
			addFormula (conjunction);
		} else {
			conjunction->commitSuicide();
		}
		formula_1->commitSuicide();
		formula_2->commitSuicide();
		return false;
	}
	bool
	Theory :: assembleEqualities (const bool inDefinitions)
	{
		if (formulae_.getSize() < 2) {
			return true;
		}
		bool result = true;
		bool definitionsAreAssembled = false;
		while (!definitionsAreAssembled) {
			definitionsAreAssembled = true;
			for (value :: Integer i = 0; i < formulae_.getSize() - 1; ++ i) {
				del :: Formula* const
					formula_1 = const_cast<del :: Formula*>(formulae_.getValue (i));
				//Del :: getDel()->getTimers().showProgress (i, formulae_.getSize());
				for (value :: Integer j = i + 1; j < formulae_.getSize(); ++ j) {
					del :: Formula* const
						formula_2 = const_cast<del :: Formula*>(formulae_.getValue (j));

					definitionsAreAssembled = assembleEqualities (inDefinitions, formula_1, formula_2);
					if (!definitionsAreAssembled) {
						formulae_.remove (j);
						result = false;
						break;
					}
				}
				if (!definitionsAreAssembled) {
					formulae_.remove (i);
					break;
				}
			}
		}
		return result;
	}
	bool
	Theory :: assembleEqualities
	(
		const bool inDefinitions,
		del :: Formula* formula_1,
		del :: Formula* formula_2
	)
	{
		const bool isEqual_1 = formula_1->getTerm (0)->isEqual (formula_2->getTerm (1));
		const bool isEqual_2 = formula_1->getTerm (1)->isEqual (formula_2->getTerm (0));

		if (!(isEqual_1 && isEqual_2)) {
			return true;
		}
		const del :: Term* term_1 = formula_1->getTerm (0);
		const del :: Term* term_2 = formula_1->getTerm (1);

		const bool isVariable_1 = (term_1->getKind() == del :: Term :: VARIABLE_KIND);
		const bool isVariable_2 = (term_2->getKind() == del :: Term :: VARIABLE_KIND);
		const bool oneIsVariable = (isVariable_1 || isVariable_2);

		if (inDefinitions) {
			if (!oneIsVariable) {
				return true;
			}
			const Symbol variable =
				isVariable_1 ?
				formula_1->getTerm (0)->getSymbol() :
				formula_2->getTerm (0)->getSymbol();
			if (!variable.isTemporary()) {
				return true;
			}
		}

		del :: Formula* definition =
			(oneIsVariable && inDefinitions) ?
			static_cast<del :: Formula*>(new formula :: Definition (Location(), term_1->clone(), term_2->clone())) :
			static_cast<del :: Formula*>(new formula :: Identity (Location(), term_1->clone(), term_2->clone()));
		if (!containsFormula (definition)) {
			addFormula (definition);
		} else {
			definition->commitSuicide();
		}
		formula_1->commitSuicide();
		formula_2->commitSuicide();
		return false;
	}
	void
	Theory :: denormalizeFormulas()
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			if (!formula->isNormal()) {
				continue;
			}
			formulae_[i] = new formula :: Subset (formula);
			deleteObject (formula);
		}
	}
	void
	Theory :: removeRedundant (const bool findDuplicate, const bool findConjTautology)
	{
		const value :: Integer size = formulae_.getSize();
		const value :: Integer maxIndex = size - 1;
		value :: Integer j = 0;
		for (value :: Integer i = 0; i < size; ++ i) {
			j = maxIndex - i;
			const del :: Formula* const
				formula = formulae_.getValue (j);
			const bool isTautology = formula->getTerm (0)->isEqual (formula->getTerm (1));
			if (isTautology) {
				formulae_.remove (j);
				deleteObject (formula);
				continue;
			}
			bool isDuplicated = false;
			if (!isTautology && findDuplicate) {
				for (value :: Integer k = 0; k < j; ++ k) {
					const del :: Formula* const
						formula_prime = formulae_.getValue (k);
					if (formula->isEqual (formula_prime)) {
						isDuplicated = true;
						break;
					}
				}
			}
			if (isDuplicated) {
				formulae_.remove (j);
				deleteObject (formula);
				continue;
			}
			if (findConjTautology) {
				const del :: Term* term_0 = formula->getTerm (0);
				if (term_0->getKind() != del :: Term :: INTERSECT_KIND) {
					continue;
				}
				const del :: Term* term_1 = formula->getTerm (1);
				for (value :: Integer k = 0; k < term_0->getSize(); ++ k) {
					const del :: Term*
						subterm = term_0->getSubterm (k);
					if (subterm->isEqual (term_1)) {
						formulae_.remove (j);
						deleteObject (formula);
						break;
					}
				}
			}
		}
	}
	void
	Theory :: assembleTheoryFirst()
	{
		const value :: Integer size = formulae_.getSize();
		const value :: Integer maxIndex = size - 1;
		value :: Integer j = 0;
		for (value :: Integer i = 0; i < size; ++ i) {
			j = maxIndex - i;
			const del :: Formula* const
				formula = formulae_.getValue (j);
			if (formula->isPrimary() || !formula->isDefinition()) {
				continue;
			}
			const del :: Term*
				term_0 = formula->getTerm (0);
			const del :: Term*
				term_1 = formula->getTerm (1);

			if ((term_0->getKind() == del :: Term :: VARIABLE_KIND) &&
				term_0->getSymbol().isTemporary()) {
				formulae_.remove (j);
				deleteObject (formula);
			}
		}
	}
	bool
	Theory :: assembleTheorySecond (const del :: Signature* delta, const bool assembleDeltaTerms)
	{
		bool result = false;
		const value :: Integer size = formulae_.getSize();
		const value :: Integer maxIndex = size - 1;
		value :: Integer j = 0;
		for (value :: Integer i = 0; i < size; ++ i) {
			j = maxIndex - i;
			const del :: Formula* const
				formula = formulae_.getValue (j);
			if (formula->isPrimary() || !formula->isDefinition()) {
				continue;
			}
			const del :: Term*
				term_1 = formula->getTerm (1);
			const del :: Term*
				term_0 = formula->getTerm (0);
			const bool isOk =
				(!assembleDeltaTerms || term_0->isOfSignature (delta)) && !term_0->hasTemporarySymbols();

			if ((term_1->getKind() == del :: Term :: VARIABLE_KIND) &&
				term_1->getSymbol().isTemporary() && isOk) {
				formulae_.remove (j);
				replaceTerm (term_1, term_0);
				deleteObject (formula);
				result = true;
				continue;
			}
		}
		return result;
	}

	bool
	Theory :: contains (const del :: Formula* formula_1) const
	{
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula_2 = formulae_.getValue (i);
			if (formula_2 == NULL) {
				continue;
			}
			if (formula_1->isEqual (formula_2)) {
				return true;
			}
		}
		return false;
	}
	value :: Integer
	Theory :: computeCohesion (const Symbol symbol) const
	{
		//Memory :: stack().push();
		del :: Signature* jointSignature = new source :: Signature<allocator :: Heap>();

		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			const del :: Signature*
				signature = formula->getSignature();
			if (signature->containsSymbol (symbol)) {
				jointSignature->join (signature);
			}
		}
		const value :: Integer cohesion = jointSignature->cardinality();
		jointSignature->commitSuicide();
		//Memory :: stack().pop();
		return (cohesion > 0) ? cohesion - 1 : 0;
	}

	void
	Theory :: slowMinimization (const bool debug)
	{
		Timers :: startProgress();
		value :: Integer count = 0;
		while (!isMinimal_) {
			isMinimal_ = true;
			for (value :: Integer i = count; i < getSize(); ++ i) {
				Timers :: checkOutOfTime();
				if (Config :: verbosity() > Config :: VERBOSE_MIN) {
					Del :: getDel()->getTimers().showProgress (count, getSize());
				}
				const del :: Formula* const
					formula = formulae_.getValue (i);
				formulae_.remove (i);

				del :: Question* const
					question = new source :: Question (this, formula->clone());

				if (debug) {
					std :: cout << "THEORY: " <<  std :: endl;
					std :: cout << *this << std :: endl;
					std :: cout << "formula = " << *formula << " pointer = " << (void*)formula << std :: endl << std :: endl;
					//std :: cout << "image = " << *image << " pointer = " << (void*)image << std :: endl;
					Counter :: set (1, 1);
					Counter :: inc (1);
				}

				const del :: Answer*
					answer = question->solve();
				if (answer->isPositive()) {
					const_cast<del :: Formula*>(formula)->commitSuicide();
					isMinimal_ = false;
				} else {
					formulae_.insert (formula, i);
					++ count;
				}
				Counter :: dec (1);
				question->commitSuicide();
				const_cast<del :: Answer*>(answer)->commitSuicide();
			}
		}
		Timers :: stopProgress();
	}
	void
	Theory :: fastMinimization()
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
		}
		Del :: log ()->message (Log :: REDUNDANT_AXIOMS_LOG) << "Minimizing theory ";
		Del :: log ()->message (Log :: REDUNDANT_AXIOMS_LOG) << Table :: theories()->get (name_) << "." << endLine;
		Timer timer;
		del :: Theory* theory = clone();
		primitivizationAtMinimization (theory);
		normalizationAtMinimization (theory);
		Memory :: stack().push();
			Model* model = buildAModelAtMinimization (theory);
			set :: Formula* redundantFormulas = redundancyAtMinimization (theory, model);
			if (redundantFormulas->isEmpty()) {
				Del :: log ()->message (Log :: REDUNDANT_AXIOMS_LOG) << "No such axioms." << endLine;
			}
			model->commitSuicide();
			removeRedundantFormulas (redundantFormulas);
		Memory :: stack().pop();
		redundantFormulas->commitSuicide();
		theory->commitSuicide();
		isMinimal_ = true;
	}
	void
	Theory :: primitivizationAtMinimization (del :: Theory* theory)
	{
		Timer timer;
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "primitivizing ... " << std :: flush;
		}
		timer.start();
		theory->primitivize();
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
		}
	}
	void
	Theory :: normalizationAtMinimization (del :: Theory* theory)
	{
		Timer timer;
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "normalizing ... " << std :: flush;
		}
		timer.start();
		theory->normalize();
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
		}
	}
	del :: Model*
	Theory :: buildAModelAtMinimization (del :: Theory* theory)
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "building model ... " << std :: flush;
		}
		Timer timer;
		timer.start();
		Model* model = new model :: Structure<allocator :: Stack>();
		model->build (theory);
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer;
			std :: cout << ". Model volume = ";
			memory :: Unit :: show (std :: cout, model->getVolume());
			std :: cout << std :: endl;
		}
		return model;
	}
	set :: Formula*
	Theory :: redundancyAtMinimization
	(
		del :: Theory* theory,
		del :: Model* model
	)
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB << chars :: TAB;
			std :: cout << "removing redundant ... " << std :: flush;
		}
		set :: Formula* redundant = new set :: Formula();
		Timer timer;
		timer.start();
		Timers :: startProgress();
		Del :: log ()->message (Log :: REDUNDANT_AXIOMS_LOG) << "Minimization, redundant axioms:";
		Del :: log ()->message (Log :: REDUNDANT_AXIOMS_LOG) << endLine << endLine;
		bool minimalAxiomsFound = false;
		const value :: Integer size = theory->getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			Timers :: checkOutOfTime();
			Del :: getDel()->getTimers().showProgress (i, size);
			const del :: Formula* const
				formula = theory->getFormula (i);
			if (!formula->isRoot()) {
				continue;
			}
			const del :: Formula* const
				image = formula->getImage();
			redundant->addValue (image);
			model->clearNodes();
			if (!formula->isTrue (model, redundant)) {
				redundant->removeValue (image);
			} else {
				Del :: log()->message (Log :: REDUNDANT_AXIOMS_LOG) << *image << endLine;
			}
		}
		Timers :: stopProgress();
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
			std :: cout << chars :: TAB;
		}
		return redundant;
	}
	void
	Theory :: removeRedundantFormulas (set :: Formula* redundantFormulas)
	{
		for (int i = getSize() - 1; i >= 0; -- i) {
			const del :: Formula* const
				formula = formulae_.getValue (i);
			const del :: Formula* const
				image = formula->getImage();
			if (redundantFormulas->contains (image)) {
				const_cast<del :: Formula*>(formula)->commitSuicide();
				formulae_.remove (i);
			}
		}
	}

	void
	Theory :: fastPartialMinimization (const bool debug)
	{
		Timers :: startProgress();
		del :: Theory* theory = clone();
		std :: cout << "\tprimitivizing ... (" << getSize() << ") formulas. " << std :: flush;
		theory->primitivize();
		std :: cout << "done." << std :: endl;
		std :: cout << "\tnormalizing ... (" << getSize() << ") formulas. " << std :: flush;
		theory->normalize();
		std :: cout << "done." << std :: endl;
		Memory :: stack().push();
		set :: Formula* untheory = new set :: Formula();
		const del :: Formula* redundant [getSize()];
		value :: Integer c = 0;

		Timer modelBuildTimer;
		modelBuildTimer.start();
		Model* model = new model :: Structure<allocator :: Stack>();

		model->build (theory);
		modelBuildTimer.stop();
		std :: cout << "\tenriched model build time = " << modelBuildTimer << std :: endl;

		std :: cout << "\tenriched model volume = ";
		memory :: Unit :: show (std :: cout, model->getVolume());
		std :: cout << std :: endl;

		Timer minimizerTimer;
		minimizerTimer.start();
		for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
			Timers :: checkOutOfTime();
			//Del :: getDel()->getTimers().showProgress (i, theory->getSize());
			const del :: Formula* const
				formula = theory->getFormula (i);
			if (!formula->isRoot()) {
				continue;
			}
			const del :: Formula* const
				image = formula->getImage();
			untheory->addValue (image);
			model->clearNodes();
			if (formula->isTrue (model, untheory)) {
				redundant [c ++] = formula;
			}
			untheory->removeValue (image);
			if (debug) {
				std :: cout << "untheory = {" << *untheory << "}" << std :: endl;
			}
		}
		minimizerTimer.stop();
		std :: cout << "\tminimizing time = " << minimizerTimer << std :: endl;

		std :: cout << "\tthere are " << c << " independently redundant formulas:" << std :: endl;
		for (value :: Integer i = 0; i < c; ++ i) {
			std :: cout << "\t1-redundant formula: " << *redundant [i] << std :: endl;
		}
		Memory :: stack().pop();
		theory->commitSuicide();
		model->commitSuicide();
		untheory->commitSuicide();
		isMinimal_ = true;
		Timers :: stopProgress();
	}
	void
	Theory :: testMinimization (const value :: Integer factor)
	{
		const value :: Integer size = getSize();
		std :: cout << std :: endl;
		for (value :: Integer i = 0; i < size / factor; ++ i) {
			const value :: Integer size_1 = i * (size / factor);
			Theory* th = new Theory (*this, size_1);
			std :: cout << "minimizing theory of size " << size_1 << std :: endl;
			Timer minimizerTimer;
			minimizerTimer.start();
			th->fastMinimization();
			minimizerTimer.stop();
			th->commitSuicide();
			std :: cout << "\toverall minimizing time = " << minimizerTimer << std :: endl;
			std :: cout << std :: endl;
			std :: cout << std :: endl;
		}
	}

	void
	Theory :: findConjunctiveIndexes (const value :: Integer index, value :: Integer indexes[], value :: Integer& count)
	{
		const value :: Integer size = formulae_.getSize();
		const del :: Formula* currentFormula = formulae_.getValue (index);
		const del :: Term* currentTerm = currentFormula->getTerm (0);
		for (value :: Integer i = index + 1; i < size; ++ i) {
			const del :: Formula* someFormula = formulae_.getValue (i);
			const del :: Term* someTerm = someFormula->getTerm (0);
			if (someTerm->isEqual (currentTerm)) {
				indexes [count ++] = i;
			}
		}
	}
	void
	Theory :: useConjunctiveIndexes (const value :: Integer index, const value :: Integer indexes[], const value :: Integer count)
	{
		const value :: Integer size = formulae_.getSize();
		del :: Formula* currentFormula = const_cast<del :: Formula*>(formulae_.getValue (index));
		const del :: Term* leftTerm = currentFormula->getTerm (0)->clone();
		const del :: Term* rightTerms [count + 1];
		rightTerms [0] = currentFormula->getTerm (1)->clone();
		currentFormula->commitSuicide();
		currentFormula = NULL;
		for (value :: Integer i = 0; i < count; ++ i) {
			const value :: Integer j = count - i - 1;
			const value :: Integer k = indexes [j];
			del :: Formula*& someFormula = const_cast<del :: Formula*&>(formulae_.getReference (k));
			rightTerms [j + 1] = someFormula->getTerm (1)->clone();
			someFormula->commitSuicide();
			someFormula = NULL;
			formulae_.remove (k);
		}
		const del :: Term* conjunction = new source :: term :: Intersect (rightTerms, count + 1);
		conjunction = const_cast<del :: Term*>(conjunction)->simplify();
		const del :: Formula* newFormula = new source :: formula :: Subset (Location(), leftTerm, conjunction);
		formulae_ [index] = newFormula;
	}
	bool
	Theory :: isEquivalence (const del :: Formula* formula_1, const del :: Formula* formula_2)
	{
		const del :: Term* term_1_0 = formula_1->getTerm (0);
		const del :: Term* term_1_1 = formula_1->getTerm (1);
		const del :: Term* term_2_0 = formula_2->getTerm (0);
		const del :: Term* term_2_1 = formula_2->getTerm (1);
		return term_1_0->isEqual (term_2_1) && term_1_1->isEqual (term_2_0);
	}
	bool
	Theory :: createEquivalence (const value :: Integer i, const value :: Integer j)
	{
		del :: Formula* formula_1 = const_cast<del :: Formula*>(formulae_.getValue (i));
		del :: Formula* formula_2 = const_cast<del :: Formula*>(formulae_.getValue (j));
		const del :: Term* term_0 = formula_1->getTerm (0);
		const del :: Term* term_1 = formula_1->getTerm (1);
		if (term_0->isEqual (term_1)) {
			formula_1->commitSuicide();
			formula_2->commitSuicide();
			formulae_.remove (j);
			formulae_.remove (i);
			return false;
		} else {
			const del :: Term* new_term_0 = term_0->clone();
			const del :: Term* new_term_1 = term_1->clone();
			formula_1->commitSuicide();
			formula_2->commitSuicide();
			formulae_.remove (j);
			formulae_.getReference (i) = new source :: formula :: Identity (Location(), new_term_0, new_term_1);
			return true;
		}
	}

	void
	Theory :: reverseFormulas()
	{
		const value :: Integer size = formulae_.getSize();
		const del :: Formula* formulas [size];
		for (value :: Integer i = 0; i < size; ++ i) {
			formulas [i] = formulae_.getValue (i);
		}
		for (value :: Integer i = 0; i < size; ++ i) {
			formulae_ [size - i - 1] = formulas [i];
		}
	}

	// translation routines
	const Writable*
	Theory :: translateToManFormat() const
	{
		const del :: Signature* sig = getSignature (true);
		vector :: Symbol concepts (sig->cardinality());
		vector :: Symbol relations (sig->cardinality());
		for (value :: Integer i = 0; i < sig->cardinality(); ++ i) {
			const Symbol&
				symbol = sig->getSymbol (i);
			if (symbol.isRelation()) {
				relations.add (symbol);
			}
			if (symbol.isVariable()) {
				concepts.add (symbol);
			}
		}
		const String& sourceName = Table :: theories()->get (name_);
		del :: Path path (sourceName);
		path.extension() = "man";

		owl :: man :: source :: Source*
			source = new owl :: man :: source :: Source (path);

		const owl :: man :: source :: Ontology*
			ontology = new owl :: man :: source :: Ontology (sourceName);
		source->addOntology (ontology);

		for (value :: Integer i = 0; i < relations.getSize(); ++ i) {
			const Symbol& relation = relations.getValue (i);
			const owl :: man :: source :: ObjectProperty*
				objectProperty = new owl :: man :: source :: ObjectProperty (relation);
			source->addObjectProperty (objectProperty);
		}

		for (value :: Integer i = 0; i < concepts.getSize(); ++ i) {
			const Symbol& concept = concepts.getValue (i);
			owl :: man :: source :: Class*
				clas = new owl :: man :: source :: Class (concept);
			for (value :: Integer j = 0; j < formulae_.getSize(); ++ j) {
				const del :: Formula*
					formula = formulae_.getValue (j);
				const del :: Term*
					term_0 = formula->getTerm (0);
				const del :: Term*
					term_1 = formula->getTerm (1);
				if ((term_0->getKind() == del :: Term :: VARIABLE_KIND) &&
					(term_0->getSymbol() == concept)) {
					if (formula->getType() == del :: Formula :: SUBSET_TYPE) {
						owl :: man :: source :: Subclass*
							subclas = new owl :: man :: source :: Subclass (clas);
						subclas->addTerm (term_1->clone());
						clas->addSubclass (subclas);
					} else if (formula->getType() == del :: Formula :: EQUALITY_TYPE) {
						owl :: man :: source :: Equivalence*
							equivalence = new owl :: man :: source :: Equivalence (clas);
						equivalence->addTerm (term_1->clone());
						clas->addEquivalence (equivalence);
					}
				}
			}
			source->addClass (clas);
		}
		return source;
	}
	const Writable*
	Theory :: translateToFuncFormat() const
	{
		using namespace owl :: func :: source;
		const owl :: func :: source :: Source* parentSource = Del :: del()->owlFunc()->getSource();
		const Ontology* parentOntology = parentSource->getOntology();

		const String& sourceName = Table :: theories()->get (name_);

		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << chars :: TAB;
			std :: cout << "Writing component " << sourceName << " ... " << std :: flush;
		}

		del :: Path path (sourceName);
		path.extension() = "owl";
		owl :: func :: source :: Source* source = new owl :: func :: source :: Source (path);
		Ontology* ontology = new Ontology (sourceName);

		const owl :: func :: source :: vector :: Prefix&
			prefixes = parentSource->getPrefixes();
		for (value :: Integer i = 0; i < prefixes.getSize(); ++ i) {
			const Prefix* prefix = prefixes.getValue (i);
			source->addPrefix (prefix->clone());
		}

		source->setOntology (ontology);
		const del :: Signature* signature = getSignature (true);
		const value :: Integer signatureCardinality = signature->cardinality();
		Timer timer;
		timer.start();
		Timers :: startProgress();
		for (value :: Integer i = 0; i < signatureCardinality; ++ i) {

			Timers :: checkOutOfTime();
			Del :: getDel()->getTimers().showProgress (i, signatureCardinality, timer);

			const Symbol&
				symbol = signature->getSymbol (i);
			const Declaration*
				declaration = new Declaration
				(
					symbol.isRelation() ?
						Declaration :: OBJECT_PROPERTY :
						Declaration :: CLASS,
					symbol.getString()
				);
			ontology->addDeclaration (declaration);

			const owl :: func :: source :: vector :: AnnotationAssertion&
				annotationAssertions = parentOntology->getAnnotationAssertions();
			for (value :: Integer j = 0; j < annotationAssertions.getSize(); ++ j) {
				const AnnotationAssertion* annotationAssertion = annotationAssertions.getValue (j);
				if (annotationAssertion->relatesTo (symbol)) {
					const AnnotationAssertion* copy = annotationAssertion->clone();
					ontology->addAnnotationAssertion (copy);
				}
			}
		}
		Timers :: stopProgress();
		for (value :: Integer i = 0; i < formulae_.getSize(); ++ i) {
			const del :: Formula*
				formula = formulae_.getValue (i);
			ontology->addFormula (formula->clone());
		}
		timer.stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			if (Timers :: progressShowed()) {
				std :: cout << std :: endl;
				std :: cout << chars :: TAB;
			}
			std :: cout << "done in " << timer << std :: endl;
		}
		return source;
	}

	/*
	void
	Theory :: minimize()
	{
		fastMinimization();
		repair();
		return;

		testMinimization (100);
		repair();
		return;

		//slowMinimization(); return;
		Table :: pushVariables();

		Theory* copy = new Theory (*this);

		const value :: Integer size_1 = getSize();
		std :: cout << std :: endl;
		std :: cout << "\ttheory size = " << size_1 << std :: endl;
		fastMinimization();
		//fastPartialMinimization();
		const value :: Integer size_2 = getSize();
		std :: cout << "\tmin theory size = " << size_2 << std :: endl;
		std :: cout << "\tredundancy = " << (size_1 - size_2) << " formulas." << std :: endl;

		std :: cout << "redundant formulas:" << std :: endl;
		showDifference (copy);
		copy->commitSuicide();

		Table :: popVariables();
		return;

		Theory* copy_1 = new Theory (*this);
		Theory* copy_2 = new Theory (*this);
		Theory* copy_3 = new Theory (*this);
		Theory* copy_4 = new Theory (*this);

		std :: cout << std :: endl;
		std :: cout << "\ttheory size = " << getSize() << std :: endl;
		std :: cout << "\ttheory volume = ";
		memory :: Unit :: show (std :: cout, getVolume());
		std :: cout << std :: endl;


		std :: cout << std :: endl << "\tfast minimization ..." << std :: endl;
		Timer fastTimer;
		fastTimer.start();
		copy_1->fastMinimization();
		fastTimer.stop();
		std :: cout << "\tdone in " << fastTimer << std :: endl << std :: endl;

		std :: cout << "\tslow minimization ..." << std :: endl;
		Timer slowTimer;
		slowTimer.start();
		slowMinimization();
		slowTimer.stop();
		std :: cout << "\tdone in " << slowTimer << std :: endl;

		std :: cout << "redundant formulas:" << std :: endl;
		copy_4->showDifference (copy_1);
		std :: cout << "redundant formulas:" << std :: endl;
		copy_1->showDifference (copy_4);

		//goto end;

		if (!copy_1->isEqual (this)) {
			std :: cout << "WRONG FAST MINIMIZATION" << std :: endl;
			std :: cout << "orig th = " << copy_4->getSize() << std :: endl;
			std :: cout << "fast min size th = " << copy_1->getSize() << std :: endl;
			std :: cout << "slow min size th = " << getSize() << std :: endl;
			std :: cout << "extra formulas in fast min size th:" << std :: endl;
			this->showDifference (copy_1);
			std :: cout << std :: endl;
			std :: cout << "extra formulas in slow min size th:" << std :: endl;
			copy_1->showDifference (this);
			std :: cout << std :: endl << std :: endl;
			/*std :: cout << "^^^^ SLOW MINIMIZATION ^^^^" << std :: endl;
			copy_3->slowMinimization (true);
			std :: cout << std :: endl << std :: endl;* /
			std :: cout << "^^^^ FAST MINIMIZATION ^^^^" << std :: endl;
			copy_2->fastMinimization (true);
			std :: cout << std :: endl << std :: endl;
			/*std :: cout << "wrong minimization" << std :: endl;
			std :: cout << "fast minimal:" << std :: endl;
			std :: cout << *copy_1 << std :: endl;
			std :: cout << "slow minimal:" << std :: endl;
			std :: cout << *this << std :: endl;* /
		}
		end :
		copy_1->commitSuicide();
		copy_2->commitSuicide();
		copy_3->commitSuicide();
		copy_4->commitSuicide();
		isMinimal_ = true;
	}
	 */
}
}

#endif /*DEL_SOURCE_THEORY_CPP_*/

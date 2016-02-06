/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Source.cpp                                    */
/* Description:     source class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/source/del_source_Source.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source
	(
		const Lexer* const lexer,
		const del :: Comments* comments,
		const Path& sourcePath,
		const Path& targetPath
	) :
	lexer_ (lexer),
	sourcePath_ (sourcePath),
	targetPath_ (targetPath),
	commentsStart_ (comments),
	commentsEnd_ (NULL),
	components_ (INITIAL_COMPONENTS_CAPACITY),
	questions_ (INITIAL_QUESTIONS_CAPACITY),
	decomposes_ (INITIAL_DECOMPOSES_CAPACITY),
	minimizes_ (INITIAL_MINIMIZES_CAPACITY),
	assertions_ (INITIAL_ASSERTIONS_CAPACITY),
	theories_ (INITIAL_THEORIES_CAPACITY),
	decompositions_ (INITIAL_DECOMPOSITIONS_CAPACITY),
	output_ (NULL) {
		Math :: source()->add (this);
	}
	inline
	Source :: Source
	(
		const Lexer* const lexer,
		const del :: Comments* commentsStart,
		const Path& sourcePath
	) :
	lexer_ (lexer),
	sourcePath_ (sourcePath),
	targetPath_ (),
	commentsStart_ (commentsStart),
	components_ (INITIAL_COMPONENTS_CAPACITY),
	questions_ (INITIAL_QUESTIONS_CAPACITY),
	decomposes_ (INITIAL_DECOMPOSES_CAPACITY),
	minimizes_ (INITIAL_MINIMIZES_CAPACITY),
	assertions_ (INITIAL_ASSERTIONS_CAPACITY),
	theories_ (INITIAL_THEORIES_CAPACITY),
	decompositions_ (INITIAL_DECOMPOSITIONS_CAPACITY),
	output_ (NULL) {
		Math :: source()->add (this);
	}
	inline
	Source :: Source (const Path& targetPath) :
	lexer_ (NULL),
	sourcePath_ (),
	targetPath_ (targetPath),
	commentsStart_ (NULL),
	components_ (INITIAL_COMPONENTS_CAPACITY),
	questions_ (INITIAL_QUESTIONS_CAPACITY),
	decomposes_ (INITIAL_DECOMPOSES_CAPACITY),
	minimizes_ (INITIAL_MINIMIZES_CAPACITY),
	assertions_ (INITIAL_ASSERTIONS_CAPACITY),
	theories_ (INITIAL_THEORIES_CAPACITY),
	decompositions_ (INITIAL_DECOMPOSITIONS_CAPACITY),
	output_ (NULL) {
		Math :: source()->add (this);
	}
	inline
	Source :: Source() :
	lexer_ (NULL),
	sourcePath_ (),
	targetPath_ (),
	commentsStart_ (NULL),
	components_ (INITIAL_COMPONENTS_CAPACITY),
	questions_ (INITIAL_QUESTIONS_CAPACITY),
	decomposes_ (INITIAL_DECOMPOSES_CAPACITY),
	assertions_ (INITIAL_ASSERTIONS_CAPACITY),
	theories_ (INITIAL_THEORIES_CAPACITY),
	decompositions_ (INITIAL_DECOMPOSITIONS_CAPACITY),
	output_ (NULL) {
		Math :: source()->add (this);
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (lexer_);
		deleteAggregateObject (commentsStart_);
		deleteAggregateObject (commentsEnd_);
		deleteAggregateObject (output_);
	}

	Source*
	Source :: createRandom()
	{
		const value :: Integer theoryCount = Config :: getTheoryCount();
		return createRandom (theoryCount);
	}
	Source*
	Source :: createRandom (const value :: Integer theoryCount)
	{
		const Path path ("random_source.del");
		Source* source = new Source (path);
		const del :: Signature*
			signature = source :: Signature<> :: createRandom();
		source->addSignature (signature);
		const value :: Integer
			deltaThreshold = Config :: getDeltaThreshold();
		for (value :: Integer i = 0; i < theoryCount; ++ i) {
			const del :: Theory*
				theory = source :: Theory :: createRandom (signature);
			const del :: Signature*
				delta = theory->computeDelta (deltaThreshold);
			source->addSignature (delta);
			source->addTheory (theory);
			const del :: Decompose*
				decompose = new source :: Decompose
				(
					theory,
					delta,
					true
				);
			source->addDecompose (decompose);
		}
		return source;
	}

using manipulator :: endLine;

	// del :: Source implementation
	void
	Source :: addAssertion (const del :: Assertion* assertion)
	{
		components_.add (assertion);
		assertions_.add (assertion);
	}
	void
	Source :: addTheory (const del :: Theory* theory) {
		components_.add (theory);
		theories_.add (theory);
	}
	void
	Source :: addQuestion (const del :: Question* question)
	{
		components_.add (question);
		questions_.add (question);
	}
	void
	Source :: addAnswer (const del :: Answer* answer) {
		components_.add (answer);
	}
	void
	Source :: addSignature (const del :: Signature* signature) {
		components_.add (signature);
	}
	void
	Source :: addComments (const del :: Comments* commentsEnd) {
		commentsEnd_ = commentsEnd;
	}
	void
	Source :: addDecompose (const del :: Decompose* decompose)
	{
		components_.add (decompose);
		decomposes_.add (decompose);
	}
	void
	Source :: addDecomposition (const del :: Decomposition* decomposition)
	{
		components_.add (decomposition);
		decompositions_.add (decomposition);
	}
	void
	Source :: addMinimize (const del :: Minimize* minimize)
	{
		components_.add (minimize);
		minimizes_.add (minimize);
	}
	void
	Source :: addMinimization (const del :: Minimization* minimization) {
		components_.add (minimization);
	}
	void
	Source :: solve()
	{
		const value :: Integer size = questions_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Question* const
				question = questions_.getValue (i);
			const del :: Answer* const
				answer = question->solve();
			components_.add (answer);
		}
	}
	void
	Source :: decompose()
	{
		const value :: Integer size = decomposes_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Decompose* const
				decompose = decomposes_.getValue (i);
			const del :: Decomposition* const
				decomposition = decompose->decompose();
			if (decomposition != NULL) {
				components_.add (decomposition);
			}
		}
	}
	void
	Source :: minimize()
	{
		const value :: Integer size = minimizes_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Minimize* const
				minimize = minimizes_.getValue (i);
			const del :: Minimization* const
				minimization = minimize->minimize();
			if (minimization != NULL) {
				components_.add (minimization);
			}
		}
	}
	void
	Source :: verify()
	{
		for (value :: Integer i = 0; i < assertions_.getSize(); ++ i) {
			const del :: Assertion* const
				assertion = assertions_.getValue (i);
			assertion->verify();
		}
		for (value :: Integer i = 0; i < decompositions_.getSize(); ++ i) {
			const del :: Decomposition* const
				decomposition = decompositions_.getValue (i);
			decomposition->verify();
		}
	}
	void
	Source :: write() const
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT :
			writeToDelFormat();  break;
		case Config :: MAN_FORMAT :
			writeToManFormat();  break;
		case Config :: FUNC_FORMAT :
			writeToFuncFormat(); break;
		}
	}
	bool
	Source :: isSolvable() const {
		return (questions_.getSize() > 0);
	}
	bool
	Source :: isDecomposable() const {
		return (decomposes_.getSize() > 0);
	}
	bool
	Source :: isMinimizable() const {
		return (minimizes_.getSize() > 0);
	}
	bool
	Source :: isVerifiable() const {
		return (assertions_.getSize() > 0) || (decompositions_.getSize() > 0);
	}
	bool
	Source :: isWritable() const
	{
		return
			(isDecomposable() || isSolvable() || isMinimizable()) &&
			(!(Config :: outputFormat() == Config :: DEL_FORMAT) || targetPath_.isFile());
	}

	// object :: Writable implementation
	void
	Source :: translate (String& string) const {
		replicate (string);
	}
	void
	Source :: replicate (String& string) const
	{
		if (commentsStart_ != NULL) {
			commentsStart_->replicate (string);
			string << endLine;
		}
		const value :: Integer size = components_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const del :: Writable* const
				component = components_.getValue (i);
			component->replicate (string);
		}
		if (commentsEnd_ != NULL) {
			commentsEnd_->replicate (string);
			string << endLine;
		}
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		volume += components_.getVolume();
		volume += questions_.getVolume();
		volume += decomposes_.getVolume();
		volume += minimizes_.getVolume();
		volume += assertions_.getVolume();
		volume += theories_.getVolume();
		volume += decompositions_.getVolume();
		volume += sourcePath_.getVolume();
		volume += targetPath_.getVolume();
		volume += getAggregateVolume (lexer_);
		volume += getAggregateVolume (output_);
		volume += getAggregateVolume (commentsStart_);
		volume += getAggregateVolume (commentsEnd_);
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Source :: writeToDelFormat() const
	{
		const String& file = targetPath_.getString();
		targetPath_.provideDirectory();
		output_ = new Output (file);
		output_->open();
		if (commentsStart_ != NULL) {
			if (Config :: translate()) {
				commentsStart_->translate (output_->buffer());
			} else {
				commentsStart_->replicate (output_->buffer());
			}
			output_->buffer() << endLine;
		}
		for (value :: Integer i = 0; i < components_.getSize(); ++ i) {
			const del :: Writable* const
				component = components_.getValue (i);
			if (Config :: keepSource()) {
				component->replicate (output_->buffer());
			} else {
				component->write (output_->buffer());
			}
			output_->flush();
		}
		output_->close();
	}
	void
	Source :: writeToManFormat() const
	{
		for (value :: Integer i = 0; i < theories_.getSize(); ++ i) {
			const del :: Theory*
				theory = theories_.getValue (i);
			if (theory->isForOutput()) {
				const Writable*
					writable = theory->translate();
				writable->write();
				const_cast<Writable*>(writable)->commitSuicide();
			}
		}
	}
	void
	Source :: writeToFuncFormat() const
	{
		for (value :: Integer i = 0; i < theories_.getSize(); ++ i) {
			const del :: Theory*
				theory = theories_.getValue (i);
			if (theory->isForOutput()) {
				const Writable*
					writable = theory->translate();
				writable->write();
				const_cast<Writable*>(writable)->commitSuicide();
			}
		}
	}
}
}



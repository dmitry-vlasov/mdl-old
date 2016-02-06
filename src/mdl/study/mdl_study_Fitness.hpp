/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_Fitness.hpp                                    */
/* Description:     a set of trees - for fitness evaluation                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {

class Fitness :
	public object :: Object,
	public Scalar<Fitness> {
public :
	typedef
		typename allocator :: Heap
		Allocator_;
	typedef
		typename prover :: tree :: Tree<Allocator_>
		Tree_;
	typedef
		vector :: Vector
		<
			Tree_,
			storage :: ByPointer,
			allocator :: Heap
		>
		TreeVector_;
	typedef
		typename sampler :: Sample<Allocator_>
		Sample_;

	Fitness (Format&, Sample*);
	virtual ~ Fitness();

	void showTrees() const;
	value :: Real eval (const Sample_* = NULL) const;

	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class Sample;

#ifdef MULTY_THREADED
	friend void* evalAllInThread (void* pointer);
	friend void* evalForInThread (void* pointer);
	struct Arguments_ {
		Arguments_() :
		threadIndex_ (0),
		threadCount_ (0),
		trees_ (NULL) {
		}
		const Sample_* sample_;
		int threadIndex_;
		int threadCount_;
		TreeVector_* trees_;
	};
	struct Result_ {
		Result_ (const value :: Real fitness, Error* error) :
		fitness_ (fitness),
		error_ (error) {
		}
		value :: Real fitness_;
		Error* error_;
	};
	value :: Real evalAllMultyThreaded () const;
	value :: Real evalForMultyThreaded (const Sample_*) const;
#endif

	void build (Time& timeLimit);
	void addTree
	(
		const mdl :: Assertion*,
		const Time timeLimit,
		const value :: Integer size
	);

	value :: Real evalAll () const;
	value :: Real evalFor (const Sample_*) const;

	value :: Real evalAllSingleThreaded () const;
	value :: Real evalForSingleThreaded (const Sample_*) const;

	Format format_;
	Format subFormat_;
	TreeVector_* treeVector_;
	Sample* sample_;
};

#ifdef MULTY_THREADED
	void* evalAllInThread (void* pointer);
	void* evalForInThread (void* pointer);
#endif

}
}



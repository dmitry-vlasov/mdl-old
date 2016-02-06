/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Space.cpp                                    */
/* Description:     general memory space                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace memory {

	/****************************
	 *		Public members
	 ****************************/

	Size_t
	Space :: getUsedVolume ()
	{
		Size_t volume = 0;
		volume += heap_.getUsedVolume();
		volume += boxed_.getUsedVolume();
		volume += standard_.getUsedVolume();
		volume += pile_.getUsedVolume();
		return volume;
	}
	Size_t
	Space :: getOverallVolume ()
	{
		Size_t volume = 0;
		volume += heap_.getOverallVolume();
		volume += boxed_.getOverallVolume();
		volume += standard_.getOverallVolume();
		volume += pile_.getOverallVolume();
		return volume;
	}
	Size_t
	Space :: getAllocatedVolume ()
	{
		Size_t volume = 0;
		volume += heap_.getAllocatedVolume();
		volume += boxed_.getAllocatedVolume();
		volume += standard_.getAllocatedVolume();
		volume += pile_.getAllocatedVolume();
		return volume;
	}
	Size_t
	Space :: getDisposedVolume ()
	{
		Size_t volume = 0;
		volume += heap_.getDisposedVolume();
		volume += boxed_.getDisposedVolume();
		return volume;
	}
	Size_t
	Space :: getFreeVolume ()
	{
		Size_t volume = 0;
		volume += heap_.getFreeVolume();
		volume += boxed_.getFreeVolume();
		volume += pile_.getFreeVolume();
		return volume;
	}

	bool
	Space :: contains (const void* pointer)
	{
		int count = 0;
		if (getHeap().contains (pointer)) {
			++ count;
		}
		if (getStack().contains (pointer)) {
			++ count;
		}
		if (getBoxed().contains (pointer)) {
			++ count;
		}
		if (count > 1) {
			Exception* exception = new Exception ("memory corruption: one pointer in different spaces");
		}
		// We don't count standard allocation memory here
		return (count == 1);
	}
	bool
	Space :: containsInFree (const void* pointer)
	{
		int count = 0;
		if (getHeap().containsInFree (pointer)) {
			++ count;
		}
		if (getStack().containsInFree (pointer)) {
			++ count;
		}
		if (getBoxed().containsInFree (pointer)) {
			++ count;
		}
		if (count > 1) {
			Exception* exception = new Exception ("memory corruption: one pointer in different spaces");
		}
		// We don't count standard allocation memory here
		return (count == 1);
	}
	bool
	Space :: containsInUsed (const void* pointer)
	{
		int count = 0;
		if (getHeap().containsInUsed (pointer)) {
			++ count;
		}
		if (getStack().containsInUsed (pointer)) {
			++ count;
		}
		if (getBoxed().containsInUsed (pointer)) {
			++ count;
		}
		if (count > 1) {
			Exception* exception = new Exception ("memory corruption: one pointer in different spaces");
		}
		// We don't count standard allocation memory here
		return (count == 1);
	}
	const char*
	Space :: whereIs (const void* pointer)
	{
		// By default pointer is in outer space - standard heap
		const char* space = "memory: standard";
		int count = 0;
		if (getHeap().contains (pointer)) {
			++ count;
			if (getHeap().containsInFree (pointer)) {
				space = "memory: heap (free)";
			} else {
				space = "memory: heap (used)";
			}
		}
		if (getStack().contains (pointer)) {
			++ count;
			if (getStack().containsInFree (pointer)) {
				space = "memory: stack (free)";
			} else {
				space = "memory: stack (used)";
			}
		}
		if (getBoxed().contains (pointer)) {
			++ count;
			if (getBoxed().containsInFree (pointer)) {
				space = "memory: boxed (free)";
			} else {
				space = "memory: boxed (used)";
			}
		}
		if (count > 1) {
			Exception* exception = new Exception ("memory corruption: one pointer in different spaces");
		}
		return space;
	}

	inline const unit :: Heap&
	Space :: getHeap() {
		return heap_;
	}
	inline const unit :: Stack&
	Space :: getStack() {
		return pile_.stack();
	}
	inline const unit :: Pile&
	Space :: getPile() {
		return pile_;
	}
	inline const unit :: Boxed&
	Space :: getBoxed() {
		return boxed_;
	}

	inline unit :: Heap&
	Space :: heap() {
		return heap_;
	}
	inline unit :: Stack&
	Space :: stack() {
		return pile_.stack();
	}
	inline unit :: Pile&
	Space :: pile() {
		return pile_;
	}
	inline unit :: Boxed&
	Space :: boxed() {
		return boxed_;
	}
	inline unit :: Standard&
	Space :: standard() {
		return standard_;
	}

	template<class S>
	void
	Space :: show (S& string)
	{
		string << "memory allocation summary:" << chars :: NEW_LINE;
		string << "--------------------------" << chars :: NEW_LINE;
		if (config :: MemoryInfo :: showMemoryDetails()) {
			showDetails (string);
		} else {
			showSummary (string);
		}
		if (config :: MemoryInfo :: showMemoryHeap()) {
			string << chars :: NEW_LINE;
			heap_.show
			(
				string,
				config :: MemoryInfo :: showMemoryDisposed(),
				config :: MemoryInfo :: showMemoryFragmentation()
			);
		}
		if (config :: MemoryInfo :: showMemoryStack()) {
			string << chars :: NEW_LINE;
			pile_.show (string);
		}
		if (config :: MemoryInfo :: showMemoryBoxed()) {
			string << chars :: NEW_LINE;
			boxed_.show (string);
		}
		if (config :: MemoryInfo :: showMemoryStandard()) {
			string << chars :: NEW_LINE;
			standard_.show (string);
		}
		string << chars :: NEW_LINE;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class S>
	void
	Space :: showSummary (S& string)
	{
		const Size_t overall = getOverallVolume();
		string << UsageMessage (overall, overall,              "total     memory") << chars :: NEW_LINE;
		string << UsageMessage (overall, getFreeVolume(),      "free      memory") << chars :: NEW_LINE;
		string << UsageMessage (overall, getAllocatedVolume(), "allocated memory") << chars :: NEW_LINE;
		string << UsageMessage (overall, getDisposedVolume(),  "disposed  memory") << chars :: NEW_LINE;
	}
	template<class S>
	void
	Space :: showDetails (S& string)
	{
		const Size_t overall         = getOverallVolume();
		const Size_t freeVolume      = getFreeVolume();
		const Size_t allocatedVolume = getAllocatedVolume();
		const Size_t disposedVolume  = getDisposedVolume();

		// Total memory distribution
		string << UsageMessage (overall, overall, "total memory    ", chars :: SPACE) << chars :: NEW_LINE;
		if (heap_.isCreated()) {
			string << chars :: TAB << UsageMessage (overall, heap_.getOverallVolume(),     "heap    ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (pile_.isCreated()) {
			string << chars :: TAB << UsageMessage (overall, pile_.getOverallVolume(),     "stack   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (boxed_.isCreated()) {
			string << chars :: TAB << UsageMessage (overall, boxed_.getOverallVolume(),    "boxed   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (standard_.isCreated()) {
			string << chars :: TAB << UsageMessage (overall, standard_.getOverallVolume(), "standard", chars :: SPACE) << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;

		// Free memory distribution
		string << UsageMessage (freeVolume, freeVolume, "free memory     ", chars :: SPACE) << chars :: NEW_LINE;
		if (heap_.isCreated()) {
			string << chars :: TAB << UsageMessage (freeVolume, heap_.getFreeVolume(),     "heap    ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (pile_.isCreated()) {
			string << chars :: TAB << UsageMessage (freeVolume, pile_.getFreeVolume(),     "stack   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (boxed_.isCreated()) {
			string << chars :: TAB << UsageMessage (freeVolume, boxed_.getFreeVolume(),    "boxed   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;

		// Allocated memory distribution
		string << UsageMessage (allocatedVolume, allocatedVolume, "allocated memory", chars :: SPACE) << chars :: NEW_LINE;
		if (heap_.isCreated()) {
			string << chars :: TAB << UsageMessage (allocatedVolume, heap_.getAllocatedVolume(),     "heap    ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (pile_.isCreated()) {
			string << chars :: TAB << UsageMessage (allocatedVolume, pile_.getAllocatedVolume(),     "stack   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (boxed_.isCreated()) {
			string << chars :: TAB << UsageMessage (allocatedVolume, boxed_.getAllocatedVolume(),    "boxed   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (standard_.isCreated()) {
			string << chars :: TAB << UsageMessage (allocatedVolume, standard_.getAllocatedVolume(), "standard", chars :: SPACE) << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;

		// Disposed memory distribution
		string << UsageMessage (disposedVolume, disposedVolume,  "disposed memory ", chars :: SPACE) << chars :: NEW_LINE;
		if (heap_.isCreated()) {
			string << chars :: TAB << UsageMessage (disposedVolume, heap_.getDisposedVolume(),     "heap    ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (pile_.isCreated()) {
			string << chars :: TAB << UsageMessage (disposedVolume, pile_.getDisposedVolume(),     "stack   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (boxed_.isCreated()) {
			string << chars :: TAB << UsageMessage (disposedVolume, boxed_.getDisposedVolume(),    "boxed   ", chars :: SPACE) << chars :: NEW_LINE;
		}
		if (standard_.isCreated()) {
			string << chars :: TAB << UsageMessage (disposedVolume, standard_.getDisposedVolume(), "standard", chars :: SPACE) << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;
	}

	/***********************************
	 *		Private static attributes
	 ***********************************/

	unit :: Heap  Space :: heap_;
	unit :: Pile  Space :: pile_;
	unit :: Boxed Space :: boxed_;
	unit :: Standard Space :: standard_;
}
}



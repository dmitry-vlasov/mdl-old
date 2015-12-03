/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Disposed.cpp                            */
/* Description:     container for disposed memory chunks                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_DISPOSED_CPP_
#define NSTD_MEMORY_UNIT_DISPOSED_CPP_

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Disposed :: Disposed() :
	maxFragmentation_ (0),
	maxLengthSize_ (0),
	free_ (0),
	wasted_ (0),
	vector_ (NULL),
	begins_ (NULL),
	ends_ (NULL),
	lengths_(NULL),
	pool_ (NULL),
	wasCreated_ (false) {
	}

	inline void
	Disposed :: create()
	{
		vector_  = new Vector_ (INITIAL_VECTOR_CAPACITY);
		begins_  = new PointerMap_ (INITIAL_VECTOR_CAPACITY);
		ends_    = new PointerMap_ (INITIAL_VECTOR_CAPACITY);
		lengths_ = new LengthMap_ (INITIAL_VECTOR_CAPACITY);
		pool_    = new IndexesPool_ (INITIAL_POOL_CAPACITY);
		wasCreated_ = true;
	}
	inline void
	Disposed :: destroy()
	{
		if (!wasCreated_) {
			return;
		}
		for (Index_ i = 0; i < lengths_->getSize(); ++ i) {
			Indexes_* indexes = lengths_->getValue (i);
			indexes->commitSuicide();
		}
		for (Index_ i = 0; i < pool_->getSize(); ++ i) {
			Indexes_* indexes = pool_->getValue (i);
			indexes->commitSuicide();
		}
		vector_->commitSuicide();  vector_ = NULL;
		begins_->commitSuicide();  begins_ = NULL;
		ends_->commitSuicide();    ends_ = NULL;
		lengths_->commitSuicide(); lengths_ = NULL;
		pool_->commitSuicide();    pool_ = NULL;

		wasCreated_ = false;
	}

	template<class T>
	const Interval<T>
	Disposed :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		Interval<Type> result = allocateExactly<Type> (size, false);
		if (result.isEmpty()) {
			result = allocateAnyway<Type> (size, false);
		}
		#ifdef DEBUG_DISPOSED
		if (!result.isClear()) {
			show (std :: cout);
			throw exception :: Exception ("allocated space is not clear.");
		}
		if (!result.isEmpty()) {
			free_ -= result.getVolume();
		}
		#else
		free_ -= result.getVolume();
		#endif
		#ifdef DEBUG_DISPOSED
		verifyIntegrity();
		#endif
		return result;
	}
	template<class T>
	const Interval<T>
	Disposed :: allocateVector (const Size_t length, const allocator :: Method method)
	{
		typedef T Type;
		Interval<Type> result = allocateExactly<Type> (length, true);
		if (result.isEmpty() && (method == allocator :: GREEDY)) {
			result = allocateGreedy<Type> (length, true);
		}
		if (result.isEmpty()) {
			result = allocateAnyway<Type> (length, true);
		}
		#ifdef DEBUG_DISPOSED
		if (!result.isClear()) {
			show (std :: cout);
			throw exception :: Exception ("allocated space is not clear.");
		}
		if (!result.isEmpty()) {
			free_ -= result.getVolume();
		}
		#else
		free_ -= result.getVolume();
		#endif
		#ifdef DEBUG_DISPOSED
		verifyIntegrity();
		#endif
		return result;
	}

using manipulator :: endLine;
using manipulator :: tab;

	template<class T>
	void
	Disposed :: dispose (const Interval<T>& in)
	{
		if (in.isNull()) {
			return;
		}
		#ifdef DEBUG_DISPOSED
		verifyIntegrity();
		#endif
		Interval<> interval (in.template beg<Byte_t>(), in.template end<Byte_t>());
		interval.clear();
		if (vector_->getSize() > FRAGMENTATION_THRESHOLD) {
			const Size_t minLength = lengths_->getKey (0);
			if (interval.getVolume() < minLength) {
				wasted_ += interval.getVolume();
			} else {
				wasted_ += minLength;
				free_ -= minLength;
				free_ += interval.getVolume();
				replaceMinimal (interval);
			}
			return;
		}
		free_ += interval.getVolume();
		if (disposeSmart (interval)) {
			#ifdef DEBUG_DISPOSED
			verifyIntegrity();
			#endif
			return;
		}
		const Index_ i = vector_->getSize();
		vector_->add (interval);
		if (vector_->getSize() > maxFragmentation_) {
			maxFragmentation_ = vector_->getSize();
		}
		begins_->add (interval.beg(), i);
		ends_->add (interval.end(), i);
		addLength (interval.getLength(), i);
		#ifdef DEBUG_DISPOSED
		verifyIntegrity();
		#endif
	}

	inline void
	Disposed :: clear ()
	{
		for (Index_ i = 0; i < lengths_->getSize(); ++ i) {
			Indexes_* indexes = lengths_->getValue (i);
			indexes->clear();
			storeIndexes (indexes);
		}
		maxFragmentation_ = 0;
		maxLengthSize_ = 0;
		free_ = 0;
		wasted_ = 0;
		vector_->clear();
		begins_->clear();
		ends_->clear();
		lengths_->clear();
	}
	inline void
	Disposed :: verify() const {
		verifyIntegrity();
	}

	Size_t
	Disposed :: getUsedVolume() const
	{
		Size_t result = 0;
		if (vector_ != NULL) {
			result += Object :: getAggregateVolume (vector_);
			result += Object :: getAggregateVolume (begins_);
			result += Object :: getAggregateVolume (ends_);
			result += Object :: getAggregateVolume (lengths_);
			for (Size_t i = 0; i < lengths_->getSize(); ++ i) {
				const Indexes_* indexes = lengths_->getValue (i);
				result += Object :: getAggregateVolume (indexes);
			}
			result += Object :: getAggregateVolume (pool_);
			for (Size_t i = 0; i < pool_->getSize(); ++ i) {
				const Indexes_* indexes = pool_->getValue (i);
				result += Object :: getAggregateVolume (indexes);
			}
		}
		return result;
	}
	inline Size_t
	Disposed :: getFreeVolume() const {
		return free_;
	}
	inline Size_t
	Disposed :: getWastedVolume() const {
		return wasted_;
	}

	template<class S>
	void
	Disposed :: show (S& string, const Size_t overallVolume, const bool showFragmentation) const
	{
		string << "disposed memory information:" << chars :: NEW_LINE;
		string << "----------------------------" << chars :: NEW_LINE;
		string << UsageMessage (overallVolume, getUsedVolume(),   "used   memory") << chars :: NEW_LINE;
		string << UsageMessage (overallVolume, getFreeVolume(),   "free   memory") << chars :: NEW_LINE;
		string << UsageMessage (overallVolume, getWastedVolume(), "wasted memory") << chars :: NEW_LINE;

		const Index_ fragmentation = vector_->getSize();
		string << "fragmentation:" << chars :: TAB << fragmentation << chars :: TAB;
		string << "of: " << maxFragmentation_ << chars :: TAB;
		const double percentFragm = double (fragmentation * 100) / maxFragmentation_;
		string << "= " << percentFragm << " %";
		string << chars :: NEW_LINE;

		//string << "max lengths size:" << chars :: TAB << maxLengthSize_ << chars :: NEW_LINE;

		if (showFragmentation) {
			string << chars :: NEW_LINE;
			string << "disposed intervals:" << chars :: NEW_LINE;
			string << "-------------------" << chars :: NEW_LINE;
			for (Index_ i = 0; i < fragmentation; ++ i) {
				string << chars :: TAB << vector_->getReference (i) << chars :: NEW_LINE;
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	const Interval<T>
	Disposed :: allocateGreedy (const Size_t length, const bool)
	{
		typedef T Type;
		const Size_t size = length * sizeof (Type);
		const Index_ j = lengths_->findPlace (size);
		const Size_t sizeFound = lengths_->getKey (j);
		if ((j == lengths_->getSize()) ||
			!ignorableDifference (size, sizeFound)) {
			return Interval<Type>();
		} else {
			Indexes_* indexes = lengths_->value (j);
			const Index_ i = indexes->getLastValue();
			Interval<>& interval = vector_->getReference (i);
			Type* const memory = interval.beg<Type>();

			indexes->removeLast();
			if (indexes->isEmpty()) {
				storeIndexes (indexes);
				lengths_->remove (interval.getLength());
			}
			const Size_t newLength = interval.getLength() / sizeof (Type);
			const Size_t allocated = newLength * sizeof (Type);

			if (allocated < sizeFound) {
				begins_->remove (interval.beg());
				interval.shiftBeg (allocated);
				begins_->add (interval.beg(), i);
				addLength (interval.getLength(), i);
			} else {
				begins_->removeDec (interval.beg(), i);
				ends_->removeDec (interval.end(), i);
				decLengths (i);
				vector_->remove (i);
			}
			return Interval<Type> (memory, newLength);
		}
	}
	template<class T>
	const Interval<T>
	Disposed :: allocateExactly (const Size_t param, const bool allocVector)
	{
		typedef T Type;
		const Size_t size = allocVector ? param * sizeof (Type) : param;
		const Size_t length = allocVector ? param : 1;
		Indexes_* indexes = lengths_->find (size);
		if (indexes == NULL) {
			return Interval<Type>();
		} else {
			const Index_ i = indexes->getLastValue();
			const Interval<> interval = vector_->getValue (i);
			Type* const memory = interval.beg<Type>();
			begins_->removeDec (interval.beg(), i);
			ends_->removeDec (interval.end(), i);
			indexes->removeLast();
			if (indexes->isEmpty()) {
				storeIndexes (indexes);
				lengths_->remove (size);
			}
			decLengths (i);
			vector_->remove (i);
			return Interval<Type> (memory, length);
		}
	}
	template<class T>
	const Interval<T>
	Disposed :: allocateAnyway (const Size_t param, const bool allocVector)
	{
		typedef T Type;
		const Size_t size = allocVector ? param * sizeof (Type) : param;
		const Size_t length = allocVector ? param : 1;
		const Index_ j = lengths_->findPlace (size);
		if (j == lengths_->getSize()) {
			return Interval<Type>();
		} else {
			Indexes_* indexes = lengths_->value (j);
			const Index_ i = indexes->getLastValue();

			Interval<>& interval = vector_->getReference (i);
			Type* const memory = interval.beg<Type>();
			begins_->remove (interval.beg());
			indexes->removeLast();
			if (indexes->isEmpty()) {
				storeIndexes (indexes);
				lengths_->remove (interval.getLength());
			}
			interval.shiftBeg (size);
			begins_->add (interval.beg(), i);
			addLength (interval.getLength(), i);

			return Interval<Type> (memory, length);
		}
	}

	template<class T>
	bool
	Disposed :: disposeSmart (const Interval<T>& interval)
	{
		Byte_t* const
			beg = interval.template beg<Byte_t>();
		Byte_t* const
			end = interval.template end<Byte_t>();

		const Index_ index_1 = ends_->find (beg);
		const Index_ index_2 = begins_->find (end);
		const bool endBorder = (index_1 != Undefined<Index_> :: getValue());
		const bool begBorder = (index_2 != Undefined<Index_> :: getValue());

		if (endBorder && !begBorder) {
			disposeEndBorder (beg, end, index_1);
		}
		if (begBorder && !endBorder) {
			disposeBegBorder (beg, end, index_2);
		}
		if (begBorder && endBorder) {
			disposeBothBorders (beg, end, index_1, index_2);
		}
		return (endBorder || begBorder);
	}
	inline void
	Disposed :: disposeEndBorder (Byte_t* beg, Byte_t* end, const Index_ index)
	{
		Interval<>& interval = vector_->getReference (index);
		ends_->remove (beg);
		removeLength (interval.getLength(), index);
		interval.setEnd (end);
		ends_->add (interval.end(), index);
		addLength (interval.getLength(), index);
	}
	inline void
	Disposed :: disposeBegBorder (Byte_t* beg, Byte_t* end, const Index_ index)
	{
		Interval<>& interval = vector_->getReference (index);
		begins_->remove (end);
		removeLength (interval.getLength(), index);
		interval.setBeg (beg);
		begins_->add (interval.beg(), index);
		addLength (interval.getLength(), index);
	}
	void
	Disposed :: disposeBothBorders
	(
		Byte_t* beg, Byte_t* end,
		const Index_ index_1, const Index_ index_2
	)
	{
		Interval<>& interval_1 = vector_->getReference (index_1);
		Interval<>& interval_2 = vector_->getReference (index_2);

		ends_->remove (beg);
		begins_->removeDec (end, index_2);
		ends_->removeDec (interval_2.end(), index_2);

		removeLength (interval_1.getLength(), index_1);
		removeLength (interval_2.getLength(), index_2);
		decLengths (index_2);

		interval_1.setEnd (interval_2.end());
		const Index_ newIndex = (index_1 < index_2) ? index_1 : index_1 - 1;
		ends_->add (interval_1.end(), newIndex);
		addLength (interval_1.getLength(), newIndex);
		vector_->remove (index_2);
	}

	inline void
	Disposed :: addLength (const Size_t length, const Index_ index)
	{
		Indexes_* indexes = lengths_->find (length);
		if (indexes == NULL) {
			indexes = restoreIndexes();
			lengths_->add (length, indexes);
			if (lengths_->getSize() > maxLengthSize_) {
				maxLengthSize_ = lengths_->getSize();
			}
		}
		indexes->add (index);
	}
	inline void
	Disposed :: removeLength (const Size_t length, const Index_ index)
	{
		Indexes_* indexes = lengths_->find (length);
		if (indexes == NULL) {
			return;
		}
		const Index_ i = indexes->find (index);
		indexes->remove (i);
		if (indexes->isEmpty()) {
			storeIndexes (indexes);
			lengths_->remove (length);
		}
	}
	inline void
	Disposed :: decLengths (const Index_ index)
	{
		for (Index_ i = 0; i < lengths_->getSize(); ++ i) {
			Indexes_* const indexes = lengths_->getValue (i);
			Index_ j = indexes->findPlace (index);
			for (Index_ k = j; k < indexes->getSize(); ++ k) {
				-- indexes->getReference (k);
			}
		}
	}
	void
	Disposed :: replaceMinimal (const Interval<> newInterval)
	{
		Indexes_* indexes = lengths_->getValue (0);
		const Index_ index = indexes->getLastValue();
		const Interval<> oldInterval = vector_->getValue (index);
		vector_->getReference (index) = newInterval;

		begins_->replaceKey (oldInterval.beg(), newInterval.beg());
		ends_->replaceKey (oldInterval.end(), newInterval.end());
		indexes->removeLast();
		if (indexes->isEmpty()) {
			storeIndexes (indexes);
			lengths_->remove (oldInterval.getLength());
		}
		addLength (newInterval.getLength(), index);
	}
	inline void
	Disposed :: storeIndexes (Indexes_* indexes) {
		pool_->add (indexes);
	}
	inline Disposed :: Indexes_*
	Disposed :: restoreIndexes()
	{
		if (pool_->isEmpty()) {
			return new Indexes_ (INITIAL_LENGTH_CAPACITY);
		}
		Indexes_* result = pool_->getLastValue();
		pool_->removeLast();
		return result;
	}

	inline void
	Disposed :: verifyIntegrity() const
	{
		const bool verifiedVector = verifyVector();
		const bool verifiedBegins = verifyBegins();
		const bool verifiedEnds = verifyEnds();
		const bool verifiedLengths = verifyLengths();
		const bool verifiedPool = verifyPool();
		const bool verifiedFree = verifyFree();

		bool verified = true;
		verified &= verifiedVector;
		verified &= verifiedBegins;
		verified &= verifiedEnds;
		verified &= verifiedLengths;
		verified &= verifiedPool;
		verified &= verifiedFree;
		if (!verified) {
			std :: cout << std :: endl << std :: endl;
			std :: cout << "Disposed memory verification fail" << std :: endl;
			std :: cout << "---------------------------------" << std :: endl;
			if (!verifiedVector) {
				std :: cout << "\tvector verification fail" << std :: endl;
			}
			if (!verifiedBegins) {
				std :: cout << "\tbegins verification fail" << std :: endl;
			}
			if (!verifiedEnds) {
				std :: cout << "\tends verification fail" << std :: endl;
			}
			if (!verifiedLengths) {
				std :: cout << "\tlengths verification fail" << std :: endl;
			}
			if (!verifiedPool) {
				std :: cout << "\tpool verification fail" << std :: endl;
			}
			if (!verifiedFree) {
				std :: cout << "\tfree verification fail" << std :: endl;
			}
			std :: cout << std :: endl;
			showInside();
			throw std :: exception();
		}
	}
	inline bool
	Disposed :: verifyVector() const
	{
		bool verified = true;
		const Index_ size = vector_->getSize();
		for (Index_ i = 0; i < size; ++ i) {
			const Interval<> interval_1 = vector_->getValue (i);
			if (!interval_1.isValid()) {
				std :: cout << "disposed interval is not valid:" << std :: endl;
				std :: cout << chars :: TAB << "interval = " << interval_1 << std :: endl;
				verified = false;
			}
			if (!interval_1.isClear()) {
				std :: cout << "disposed interval is not clear:" << std :: endl;
				std :: cout << chars :: TAB << "interval = " << interval_1 << std :: endl;
				verified = false;
			}
			for (Index_ j = i + 1; j < size; ++ j) {
				const Interval<> interval_2 = vector_->getValue (j);
				if (!interval_1.isDisjointed (interval_2)) {
					std :: cout << "disposed intervals are not disjointed:" << std :: endl;
					std :: cout << chars :: TAB << "interval_1 = " << interval_1 << std :: endl;
					std :: cout << chars :: TAB << "interval_2 = " << interval_2 << std :: endl;
					verified = false;
				}
			}
		}
		return verified;
	}
	inline bool
	Disposed :: verifyBegins() const
	{
		bool verified = true;
		const Index_ size = vector_->getSize();
		if (begins_->getSize() != size) {
			std :: cout << "begins size is wrong:" << std :: endl;
			std :: cout << chars :: TAB << "vector_->getSize() = " << size << std :: endl;
			std :: cout << chars :: TAB << "begins_->getSize() = " << begins_->getSize() << std :: endl;
			verified = false;
		}
		for (Index_ i = 0; i < size; ++ i) {
			const Interval<> interval = vector_->getValue (i);
			const Index_ indexBeg = begins_->find (interval.beg());
			if (indexBeg != i) {
				std :: cout << "begins index is wrong:" << std :: endl;
				std :: cout << chars :: TAB << "vector_->getSize() = " << size << std :: endl;
				std :: cout << chars :: TAB << "i = " << i << std :: endl;
				std :: cout << chars :: TAB << "vector_->getValue (i) = " << interval << std :: endl;
				std :: cout << chars :: TAB << "begins_->find (interval.beg()) = " << indexBeg << std :: endl;
				if (0 <= indexBeg && indexBeg < size) {
					std :: cout << chars :: TAB << "begins_->getValue (...) = " << vector_->getValue (indexBeg) << std :: endl;
				}
				verified = false;
			}
		}
		return verified;
	}
	inline bool
	Disposed :: verifyEnds() const
	{
		bool verified = true;
		const Index_ size = vector_->getSize();
		if (ends_->getSize() != size) {
			std :: cout << "ends size is wrong:" << std :: endl;
			std :: cout << chars :: TAB << "vector_->getSize() = " << size << std :: endl;
			std :: cout << chars :: TAB << "ends_->getSize() = " << ends_->getSize() << std :: endl;
			verified = false;
		}
		for (Index_ i = 0; i < size; ++ i) {
			const Interval<> interval = vector_->getValue (i);
			const Index_ indexEnd = ends_->find (interval.end());
			if (indexEnd != i) {
				std :: cout << chars :: TAB << "vector_->getSize() = " << size << std :: endl;
				std :: cout << "ends index is wrong:" << std :: endl;
				std :: cout << chars :: TAB << "i = " << i << std :: endl;
				std :: cout << chars :: TAB << "vector_->getValue (i) = " << interval << std :: endl;
				std :: cout << chars :: TAB << "ends_->find (interval.beg()) = " << indexEnd << std :: endl;
				if (0 <= indexEnd && indexEnd < size) {
					std :: cout << chars :: TAB << "ends_->getValue (...) = " << vector_->getValue (indexEnd) << std :: endl;
				}
				verified = false;
			}
		}
		return verified;
	}
	inline bool
	Disposed :: verifyLengths() const
	{
		bool verified = true;
		const Index_ size = vector_->getSize();
		Index_ lengthsCount = 0;
		for (Size_t i = 0; i < lengths_->getSize(); ++ i) {
			const Indexes_* indexes = lengths_->getValue (i);
				lengthsCount += indexes->getSize();
		}
		if (lengthsCount != size) {
			std :: cout << "lengthsCount size is wrong:" << std :: endl;
			std :: cout << chars :: TAB << "vector_->getSize() = " << size << std :: endl;
			std :: cout << chars :: TAB << "lengthsCount = " << lengthsCount << std :: endl;
			verified = false;
		}
		for (Index_ i = 0; i < vector_->getSize(); ++ i) {
			const Interval<> interval = vector_->getValue (i);
			const Size_t length = interval.getLength();
			const Indexes_* indexes = lengths_->find (length);
			const Size_t index = indexes->find (i);
			if ((index == Undefined<Size_t> :: getValue()) ||
				(index >= indexes->getSize())) {
				std :: cout << "length is not found:" << std :: endl;
				std :: cout << chars :: TAB << "vector_->getSize() = " << size << std :: endl;
				std :: cout << chars :: TAB << "i = " << i << std :: endl;
				std :: cout << chars :: TAB << "vector_->getValue (i) = " << interval << std :: endl;
				std :: cout << chars :: TAB << "lengths_->find (interval.lengths()) = " << *indexes << std :: endl;
				verified = false;
			}
		}
		return verified;
	}
	inline bool
	Disposed :: verifyPool() const
	{
		bool verified = true;
		const Index_ size = pool_->getSize();
		for (Size_t i = 0; i < size; ++ i) {
			const Indexes_* indexes = pool_->getValue (i);
			if (!indexes->isEmpty()) {
				std :: cout << "non-empty indexes in the pool:" << std :: endl;
				std :: cout << chars :: TAB << "pool_->getSize() = " << size << std :: endl;
				std :: cout << chars :: TAB << "i = " << i << std :: endl;
				std :: cout << chars :: TAB << "pool_->getValue (i) = " << *indexes << std :: endl;
				verified = false;
			}
		}
		return verified;
	}
	inline bool
	Disposed :: verifyFree() const
	{
		Size_t free = 0;
		if (vector_ != NULL) {
			for (Index_ i = 0; i < vector_->getSize(); ++ i) {
				free += vector_->getReference (i).getVolume();
			}
		}
		if (free_ != free) {
			std :: cout << "wrong free memory value:" << std :: endl;
			std :: cout << chars :: TAB << "free_ = " << free_ << std :: endl;
			std :: cout << chars :: TAB << "free = " << free << std :: endl;
			return false;
		} else {
			return true;
		}
	}

	inline void
	Disposed :: showInside() const
	{
		showVector();
		showBegins();
		showEnds();
		showLengths();
	}
	inline void
	Disposed :: showVector() const
	{
		const Index_ size = vector_->getSize();
		std :: cout << "vector:" << std :: endl;
		std :: cout << "------------------------" << std :: endl;
		std :: cout << chars :: TAB << "size = " << size << std :: endl;
		for (Index_ i = 0; i < size; ++ i) {
			std :: cout << chars :: TAB << i << " = " << vector_->getValue (i) << std :: endl;
		}
		std :: cout << "------------------------" << std :: endl;
		std :: cout << std :: endl;
	}
	inline void
	Disposed :: showBegins() const
	{
		const Index_ size = begins_->getSize();
		std :: cout << "begins:" << std :: endl;
		std :: cout << "------------------------" << std :: endl;
		std :: cout << chars :: TAB << "size = " << size << std :: endl;
		for (Index_ i = 0; i < size; ++ i) {
			const void* beg = begins_->getKey (i);
			std :: cout << chars :: TAB << i << " key = " << beg << ", ";
			std :: cout << "value = " << begins_->getValue (i) << std :: endl;
		}
		std :: cout << "------------------------" << std :: endl;
		std :: cout << std :: endl;
	}
	inline void
	Disposed :: showEnds() const
	{
		const Index_ size = ends_->getSize();
		std :: cout << "ends:" << std :: endl;
		std :: cout << "------------------------" << std :: endl;
		std :: cout << chars :: TAB << "size = " << size << std :: endl;
		for (Index_ i = 0; i < size; ++ i) {
			const void* end = ends_->getKey (i);
			std :: cout << chars :: TAB << i << " key = " << end << ", ";
			std :: cout << "value = " << ends_->getValue (i) << std :: endl;
		}
		std :: cout << "------------------------" << std :: endl;
		std :: cout << std :: endl;
	}
	inline void
	Disposed :: showLengths() const
	{
		const Index_ size = lengths_->getSize();
		std :: cout << "lengths:" << std :: endl;
		std :: cout << "------------------------" << std :: endl;
		std :: cout << chars :: TAB << "size = " << size << std :: endl;
		for (Index_ i = 0; i < size; ++ i) {
			std :: cout << chars :: TAB << i << " key = " << lengths_->getKey (i) << ", ";
			std :: cout << "value = " << *lengths_->getValue (i) << std :: endl;
		}
		std :: cout << "------------------------" << std :: endl;
		std :: cout << std :: endl;
	}
}
}
}

#endif /*NSTD_MEMORY_UNIT_DISPOSED_HPP_*/

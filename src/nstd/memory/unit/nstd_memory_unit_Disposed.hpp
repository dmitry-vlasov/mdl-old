/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Disposed.hpp                            */
/* Description:     container for disposed memory chunks                     */
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
namespace unit {

class Disposed {
public :
	Disposed();

	void create();
	void destroy();

	template<class T>
	const Interval<T> allocateScalar (const Size_t);
	template<class T>
	const Interval<T> allocateVector
	(
		const Size_t,
		const allocator :: Method = allocator :: DEFAULT
	);

	template<class T>
	void dispose (const Interval<T>&);

	void clear ();
	void verify() const;

	Size_t getUsedVolume() const;
	Size_t getFreeVolume() const;
	Size_t getWastedVolume() const;

	template<class S>
	void show (S&, const Size_t  = 0, const bool = false) const;

private :
	enum {
		INITIAL_VECTOR_CAPACITY = size :: KILOBYTE,
		INITIAL_POOL_CAPACITY   = size :: KILOBYTE,
		INITIAL_LENGTH_CAPACITY = 1,
		FRAGMENTATION_THRESHOLD = size :: KILOBYTE * 2,
	};
	typedef
		map :: Scalar
		<
			const Byte_t*,
			Size_t,
			allocator :: Standard
		>
		PointerMap_;
	typedef
		container :: Set
		<
			Size_t,
			container :: storage :: ByValue,
			allocator :: Standard
		>
		Indexes_;
	typedef
		map :: Scalar
		<
			Size_t,
			Indexes_*,
			allocator :: Standard
		>
		LengthMap_;
	typedef
		container :: Vector
		<
			Interval<>,
			container :: storage :: ByValue,
			allocator :: Standard
		>
		Vector_;
	typedef
		container :: Vector
		<
			Indexes_*,
			container :: storage :: ByValue,
			allocator :: Standard
		>
		IndexesPool_;

	typedef Size_t Index_;

	template<class T>
	const Interval<T> allocateGreedy (const Size_t, const bool allocVector);
	template<class T>
	const Interval<T> allocateExactly (const Size_t, const bool allocVector);
	template<class T>
	const Interval<T> allocateAnyway (const Size_t, const bool allocVector);

	template<class T>
	bool disposeSmart (const Interval<T>&);
	void disposeEndBorder (Byte_t*, Byte_t*, const Index_);
	void disposeBegBorder (Byte_t*, Byte_t*, const Index_);
	void disposeBothBorders (Byte_t*, Byte_t*, const Index_, const Index_);

	void addLength (const Size_t length, const Index_ index);
	void removeLength (const Size_t length, const Index_ index);
	void decLengths (const Index_);
	void replaceMinimal (Interval<>);
	void storeIndexes (Indexes_*);
	Indexes_* restoreIndexes();

	void verifyIntegrity() const;
	bool verifyVector() const;
	bool verifyBegins() const;
	bool verifyEnds() const;
	bool verifyLengths() const;
	bool verifyPool() const;
	bool verifyFree() const;

	void showInside() const;
	void showVector() const;
	void showBegins() const;
	void showEnds() const;
	void showLengths() const;

	// Maximum fragmentation.
	Index_ maxFragmentation_;
	Index_ maxLengthSize_;
	Size_t free_;
	Size_t wasted_;

	Vector_*      vector_;
	PointerMap_*  begins_;
	PointerMap_*  ends_;
	LengthMap_*   lengths_;
	IndexesPool_* pool_;

	bool          wasCreated_;
};

}
}
}



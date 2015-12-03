/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Decompose.hpp                                 */
/* Description:     question                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_DECOMPOSE_HPP_
#define DEL_SOURCE_DECOMPOSE_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Decompose :
	public del :: Decompose,
	public Scalar<Decompose> {
public :
	Decompose
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory,
		const value :: Signature,
		const bool isStrong
	);
	Decompose
	(
		const del :: Theory*,
		const del :: Signature*,
		const bool isStrong = true
	);
	virtual ~ Decompose();

	static const del :: Decompose* current();

	// Decompose interface
	virtual const del :: Theory* getMinimalTheory() const;
	virtual const del :: Theory* getNormalTheory() const;
	virtual const del :: Theory* getPrimitiveTheory() const;
	virtual const del :: Theory* getDecomposedTheory() const;
	virtual const del :: Theory* getAssembledTheory() const;

	virtual const del :: Expansion* getDeltaExpansion() const;
	virtual const del :: Theory* getDeltaTheory() const;
	virtual const del :: Model* getDeltaModel() const;
	virtual const del :: Decomposition* decompose() const;

	// Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	void processTheory (const value :: Integer partialSize = value :: undefined :: INTEGER) const;
	void startTheory (const value :: Integer partialSize) const;
	void minimizeTheory() const;
	void normalizeTheory() const;
	void primitivizeTheory() const;
	void decomposeTheory() const;
	void assembleTheory() const;
	void finishTheory() const;
	const del :: Decomposition* compileTheory (const del :: Theory*, const bool isFinal) const;

	void prepareDeltaCopy() const;
	void prepareModel() const;
	void clear();

	typedef
		set :: Set
		<
			const del :: Formula*,
			storage :: ByValue,
			allocator :: Stack
		>
		FormulaVector_;
	typedef
		vector :: Vector
		<
			FormulaVector_,
			storage :: ByPointer,
			allocator :: Stack
		>
		TheoryPartition_;
	enum {
		INITIAL_THEORY_PARTITION_CAPACITY = 32,
		INITIAL_FORMULA_VECTOR_CAPACITY = 32
	};

	const del :: Decomposition* compile (const del :: Theory*, const bool isFinal) const;
	void partitionTheory (const del :: Theory*, TheoryPartition_&, const bool isFinal) const;
	bool isConnected (const del :: Formula*, const FormulaVector_*) const;
	const del :: Decomposition* createTheoryDecomposition
	(
		const TheoryPartition_&,
		const del :: Theory*,
		const bool isFinal
	) const;
	void completeDecomposition
	(
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const;
	del :: Signature* computeMissingSignature (const TheoryPartition_&) const;
	void completeMissingFromDelta
	(
		const del :: Signature* missingSignature,
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const;
	void completeMissingNotFromDelta
	(
		const del :: Signature* missingSignature,
		TheoryPartition_& theoryPartition,
		const bool isFinal
	) const;

	void showAllTheories() const;
	void showTheory (const del :: Theory*, const char* header) const;

	value :: Integer evalQuality() const;
	value :: Integer evalQuality (const del :: Signature*) const;

	const Location location_;
	const del :: Comments* comments_;
	const value :: Theory theoryName_;
	const value :: Signature signatureName_;
	const del :: Theory* theory_;
	const del :: Signature* delta_;
	const del :: Signature* deltaExpanded_;

	mutable del :: Theory* initialTheory_;
	mutable del :: Theory* minimalTheory_;
	mutable del :: Theory* normalTheory_;
	mutable del :: Theory* primitiveTheory_;
	mutable del :: Theory* decomposedTheory_;
	mutable del :: Theory* assembledTheory_;

	mutable del :: Theory* TcupTdelta_;
	mutable del :: Expansion* TcupTdeltaExpansion_;
	mutable del :: Model* TcupTdeltaModel_;

	mutable del :: Signature* signature_;
	mutable del :: Signature* sigma_;
	mutable del :: Signature* epsilon_;
	mutable del :: Signature* theta_;

	mutable const del :: Decomposition* decomposition_;

	enum {
		INITIAL_SIGNATURE_DECOMPOSITION_CAPACITY = 128
	};

	typedef
		vector :: Vector
		<
			const del :: Signature,
			storage :: ByPointer,
			allocator :: Heap
		>
		SignatureDecomposition_;

	mutable SignatureDecomposition_ trivialDecomposition_;
	mutable SignatureDecomposition_ nontrivialDecomposition_;

	static const del :: Decompose* current_;
};

}
}

#endif /*DEL_SOURCE_DECOMPOSE_HPP_*/

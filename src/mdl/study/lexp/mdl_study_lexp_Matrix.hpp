/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Matrix.hpp                                */
/* Description:     distance matrix                                          */
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
namespace lexp {

class Matrix :
	public object :: Object,
	public Scalar<Matrix> {
public :
	typedef
		form :: evaluation :: lexp :: Point<allocator :: Heap>
		Point_;
	typedef
		form :: evaluation :: lexp :: Factors
		Factors_;

	Matrix
	(
		mdl :: vector :: proof :: Step& positive,
		mdl :: vector :: proof :: Step& negative,
		const value :: Real percent
	);
	Matrix
	(
		mdl :: vector :: proof :: Step& positive,
		mdl :: vector :: proof :: Step& negative,
		const value :: Integer maxSize
	);
	Matrix
	(
		mdl :: vector :: proof :: Step& positive,
		mdl :: vector :: proof :: Step& negative
	);
	virtual ~ Matrix();

	void build (const Factors_&);
	void build (const Factors_&, Time& timeLimit);

	value :: Integer getSize() const;
	const Point_* getPoint (const value :: Integer) const;
	value :: Real getDistance (const value :: Integer, const value :: Integer) const;
	void clear();

	bool classify
	(
		const value :: Integer, // x index
		const Sample&           // current sample
	) const;

	value :: Real evalSumFris (const Sample&) const;
	value :: Real evalFris
	(
		const value :: Integer, // x index
		const Sample&           // current sample
	) const;
	value :: Real evalFris
	(
		const value :: Integer, // x index
		const value :: Integer, // y index
		const Sample&           // current sample
	) const;
	value :: Real evalMargin
	(
		const value :: Integer, // x index
		const Sample&           // current sample
	) const;
	value :: Real
	compactnessProfile
	(
		const value :: Integer, // x index
		const Sample&           // current sample
	) const;

	void evalNearest
	(
		value :: Integer nearestPoints[],
		value :: Real distances [],
		const value :: Integer i, // index of x argument
		const Sample&,            // current sample
		const value :: Integer  n // use n nearest
	) const;
	void evalNearestOfSign
	(
		const bool sign,
		value :: Integer nearestPoints[],
		value :: Real distances [],
		const value :: Integer i, // index of x argument
		const Sample&,            // current sample
		const value :: Integer  n // use n nearest
	) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		mdl :: vector :: Vector
		<
			const Point_,
			storage :: ByPointer,
			allocator :: Heap
		>
		Points_;
	typedef
		mdl :: vector :: value :: Real
		Vector_;
	typedef
		mdl :: vector :: Vector
		<
			Vector_,
			storage :: ByPointer,
			allocator :: Heap
		>
		Matrix_;

	bool incSize (const Factors_& factors);

	void evalSimilarity
	(
		value :: Real&,  // positive
		value :: Real&,  // negative
		const value :: Integer, // x index
		const Sample&    // current sample
	) const;

	void showMatrix (String&) const;
	void showPoints (String&) const;
	void showProfile (const Sample&, String&) const;
	void showFRiS (const Sample&, String&) const;

	mdl :: vector :: proof :: Step& positive_;
	mdl :: vector :: proof :: Step& negative_;

	value :: Integer sizePos_;
	value :: Integer sizeNeg_;
	value :: Integer size_;
	const bool isTrivial_;

	Points_ points_;
	Matrix_ matrix_;
};

}
}
}



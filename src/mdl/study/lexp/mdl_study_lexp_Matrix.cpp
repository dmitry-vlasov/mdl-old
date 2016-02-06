/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Matrix.cpp                                */
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

	/****************************
	 *		Public members
	 ****************************/

	Matrix :: Matrix
	(
		mdl :: vector :: proof :: Step& positive,
		mdl :: vector :: proof :: Step& negative,
		const value :: Real percent
	) :
	positive_ (positive),
	negative_ (negative),
	sizePos_ (positive_.getSize() * percent / 100),
	sizeNeg_ (negative_.getSize() * percent / 100),
	size_ (sizePos_ + sizeNeg_),
	isTrivial_ ((sizePos_ == 0) || (sizeNeg_ == 0)),
	points_ (size_),
	matrix_ (size_)
	{
		for (value :: Integer i = 0; i < sizePos_; ++ i) {
			const value :: Integer
				j = i * 100 / percent;
			const mdl :: proof :: Step*
				step = positive_.getValue (j);
			const Point_* point = new Point_ (step, true);
			points_.add (point);
		}
		for (value :: Integer i = 0; i < sizeNeg_; ++ i) {
			const value :: Integer
				j = i * 100 / percent;
			const mdl :: proof :: Step*
				step = negative_.getValue (j);
			const Point_* point = new Point_ (step, false);
			points_.add (point);
		}
	}
	Matrix :: Matrix
	(
		mdl :: vector :: proof :: Step& positive,
		mdl :: vector :: proof :: Step& negative,
		const value :: Integer maxSize
	) :
	positive_ (positive),
	negative_ (negative),
	sizePos_ (positive_.getSize()),
	sizeNeg_ (negative_.getSize()),
	size_ (sizePos_ + sizeNeg_),
	isTrivial_ ((sizePos_ == 0) || (sizeNeg_ == 0)),
	points_ (size_),
	matrix_ (size_)
	{
		if (size_ > maxSize) {
			sizePos_ = sizePos_ * (static_cast<value :: Real>(maxSize) / size_);
			sizeNeg_ = sizeNeg_ * (static_cast<value :: Real>(maxSize) / size_);
			if (sizePos_ + sizeNeg_ < maxSize) {
				++ sizePos_;
			}
			if (sizePos_ + sizeNeg_ < maxSize) {
				++ sizeNeg_;
			}
			size_ = maxSize;
		}
		value :: Real factor = positive_.getSize();
		factor /= sizePos_;
		for (value :: Integer i = 0; i < sizePos_; ++ i) {
			const value :: Integer
				j = i * factor;
			const mdl :: proof :: Step*
				step = positive_.getValue (j);
			const Point_* point = new Point_ (step, true);
			points_.add (point);
		}
		factor = negative_.getSize();
		factor /= sizeNeg_;
		for (value :: Integer i = 0; i < sizeNeg_; ++ i) {
			const value :: Integer
				j = i * factor;
			const mdl :: proof :: Step*
				step = negative_.getValue (j);
			const Point_* point = new Point_ (step, false);
			points_.add (point);
		}
	}
	Matrix :: Matrix
	(
		mdl :: vector :: proof :: Step& positive,
		mdl :: vector :: proof :: Step& negative
	) :
	positive_ (positive),
	negative_ (negative),
	sizePos_ (positive_.getSize()),
	sizeNeg_ (negative_.getSize()),
	size_ (sizePos_ + sizeNeg_),
	isTrivial_ ((sizePos_ == 0) || (sizeNeg_ == 0)),
	points_ (size_),
	matrix_ (size_)
	{
		size_ = (sizeNeg_ < sizePos_) ? sizeNeg_ : sizePos_;
		const mdl :: proof :: Step* step = NULL;;
		const Point_* point = NULL;
		for (value :: Integer i = 0; i < size_; ++ i) {
			step = positive_.getValue (i);
			point = new Point_ (step, true);
			points_.add (point);
			step = negative_.getValue (i);
			point = new Point_ (step, false);
			points_.add (point);
		}
		size_ *= 2;
	}
	Matrix :: ~ Matrix() {
	}

	void
	Matrix :: build (const Factors_& factors)
	{
		/*matrix_.clear();
		for (value :: Integer i = 0; i < size_; ++ i) {
			Vector_* vector = matrix_.push();
			vector->clear();
			const Point_* point_1 = points_.getValue (i);
			for (value :: Integer j = 0; j < size_; ++ j) {
				const Point_* point_2 = points_.getValue (j);
				const value :: Real
					dist = point_1->getDistance (point_2, factors);
				vector->add (dist);
			}
		}
		return;*/
		clear();
		if (size_ <= 1) {
			return;
		}
		for (value :: Integer i = 0; i < (size_ - 1); ++ i) {
			Vector_* row = matrix_.getValue (i);
			row->clear();
			const Point_* point_1 = points_.getValue (i);
			for (value :: Integer j = i + 1; j < size_; ++ j) {
				const Point_* point_2 = points_.getValue (j);
				const value :: Real
					dist = point_1->getDistance (point_2, factors);
				row->getReference (j) = dist;
				Vector_* column = matrix_.getValue (j);
				column->getReference (i) = dist;
			}
		}
	}
	void
	Matrix :: build (const Factors_& factors, Time& timeLimit)
	{
		Timer timer;
		timer.start();
		while (timer.getSeconds() < timeLimit) {
			if (!incSize (factors)) {
				break;
			}
		}
		timer.stop();
		timeLimit -= timer.getSeconds();
	}

	inline value :: Integer
	Matrix :: getSize() const {
		return matrix_.getSize();
	}
	inline const typename Matrix :: Point_*
	Matrix :: getPoint (const value :: Integer i) const {
		return points_.getValue (i);
	}
	inline value :: Real
	Matrix :: getDistance (const value :: Integer i, const value :: Integer j) const {
		return matrix_.getValue (i)->getValue (j);
	}
	void
	Matrix :: clear()
	{
		for (value :: Integer i = 0; i < matrix_.getSize(); ++ i) {
			Vector_* vector = matrix_.getValue (i);
			vector->clear();
		}
		matrix_.clear();
		for (value :: Integer i = 0; i < size_; ++ i) {
			Vector_* vector = matrix_.push();
			for (value :: Integer j = 0; j < size_; ++ j) {
				vector->add (0);
			}
		}
	}

	bool
	Matrix :: classify
	(
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const
	{
		value :: Real fris = evalFris (i, sample);  // positive
		return (fris > 0);
	}

	value :: Real
	Matrix :: evalSumFris (const Sample& sample) const
	{
		value :: Real sum = 0;  // positive
		for (value :: Integer i = 0; i < size_; ++ i) {
			sum += evalFris (i, sample);
		}
		return sum;
	}
	value :: Real
	Matrix :: evalFris
	(
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const
	{
		value :: Real positive = 0;  // positive
		value :: Real negative = 0;  // negative
		evalSimilarity (positive, negative, i, sample);
		return (positive - negative) / (negative + positive);
	}
	value :: Real
	Matrix :: evalFris
	(
		const value :: Integer i, // point_1 index
		const value :: Integer j, // point_2 index
		const Sample& sample      // current sample
	) const
	{
		value :: Real positive = 0;
		value :: Real negative = 0;
		evalSimilarity (positive, negative, i, sample);
		const value :: Real rho_1 = (negative - positive);
		const value :: Real rho_2 = matrix_.getValue (i)->getValue (j);
		return (rho_1 - rho_2) / (rho_1 + rho_2);
	}
	value :: Real
	Matrix :: evalMargin
	(
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const
	{
		value :: Real positive = 0;  // positive
		value :: Real negative = 0;  // negative
		evalSimilarity (positive, negative, i, sample);
		return positive - negative;
	}
	value :: Real
	Matrix :: compactnessProfile
	(
		const value :: Integer n,
		const Sample&  sample
	) const
	{
		const value :: Integer size = sample.getSize();
		value :: Real count = 0;
		for (value :: Integer i = 0; i < size; ++ i) {
			value :: Integer nearestPoints [n];
			value :: Real distances [n];
			evalNearest (nearestPoints, distances, i, sample, n);
			const value :: Integer index = nearestPoints [n - 1];
			if (index == value :: undefined :: INTEGER) {
				continue;
			}
			const Point_* nearestPoint = points_.getValue (index);
			const Point_* currentPoint = points_.getValue (i);
			if (nearestPoint->getSign() != currentPoint->getSign()) {
				++ count;
			}
		}
		return (size == 0) ? 10000 : (count / size);
	}

	void
	Matrix :: evalNearest
	(
		value :: Integer nearestPoints[],
		value :: Real distances [],
		const value :: Integer i, // index of an argument x for point
		const Sample& sample,     // current sample
		const value ::Integer n   // use n nearest points
	) const
	{
		for (value :: Integer k = 0; k < n; ++ k) {
			nearestPoints [k] = value :: undefined :: INTEGER;
			distances [k] = value :: undefined :: INTEGER;
		}
		for (value :: Integer m = 0; m < sample.getSize(); ++ m) {
			const value :: Integer j = sample.getValue (m);
			const value :: Real distance = matrix_.getValue (i)->getValue (j);
			if (i == j) {
				continue;
			}
			for (value :: Integer s = 0; s < n; ++ s) {
				const value :: Integer k = n - 1 - s;
				if (distance >= distances [k]) {
					break;
				}
				if (k < n - 1) {
					nearestPoints [k + 1] = nearestPoints [k];
					distances [k + 1] = distances [k];
				}
				nearestPoints [k] = j;
				distances [k] = distance;
			}
		}
	}
	void
	Matrix :: evalNearestOfSign
	(
		const bool sign,
		value :: Integer nearestPoints[],
		value :: Real distances [],
		const value :: Integer i, // index of an argument x for point
		const Sample& sample,     // current sample
		const value ::Integer n   // use n nearest points
	) const
	{
		for (value :: Integer k = 0; k < n; ++ k) {
			nearestPoints [k] = value :: undefined :: INTEGER;
			distances [k] = value :: undefined :: INTEGER;
		}
		for (value :: Integer m = 0; m < sample.getSize(); ++ m) {
			const value :: Integer j = sample.getValue (m);
			const value :: Real distance = matrix_.getValue (i)->getValue (j);
			const Point_* x = points_.getValue (j);
			if ((i == j) || (x->getSign() != sign)) {
				continue;
			}
			for (value :: Integer s = 0; s < n; ++ s) {
				const value :: Integer k = n - 1 - s;
				if (distance >= distances [k]) {
					break;
				}
				if (k < n - 1) {
					nearestPoints [k + 1] = nearestPoints [k];
					distances [k + 1] = distances [k];
				}
				nearestPoints [k] = j;
				distances [k] = distance;
			}
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Matrix :: commitSuicide() {
		delete this;
	}
	Size_t
	Matrix :: getVolume() const
	{
		Size_t volume = 0;
		volume += points_.getVolume();
		volume += matrix_.getVolume();
		return volume;
	}
	Size_t
	Matrix :: getSizeOf() const {
		return sizeof (Matrix);
	}
	void
	Matrix :: show (String& string) const
	{
		showPoints (string);
		showMatrix (string);
		Sample allPoints (points_.getSize());
		for (value :: Integer i = 0; i < points_.getSize(); ++ i) {
			allPoints.add (i);
		}
		showProfile (allPoints, string);
		showFRiS (allPoints, string);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Matrix :: incSize (const Factors_& factors)
	{
		const value :: Integer size = matrix_.getSize();
		if (size == points_.getSize()) {
			return false;
		}
		const Point_* point_1 = points_.getValue (size);
		const Point_* point_2 = points_.getValue (size + 1);
		Vector_* vector_1 = matrix_.push();
		Vector_* vector_2 = matrix_.push();

		for (value :: Integer i = 0; i < size; ++ i) {
			const Point_* point_0 = points_.getValue (i);
			const value :: Real dist_1 = point_1->getDistance (point_0, factors);
			const value :: Real dist_2 = point_2->getDistance (point_0, factors);
			vector_1->add (dist_1);
			vector_2->add (dist_2);
			Vector_* vector_0 = matrix_.getValue (i);
			vector_0->add (dist_1);
			vector_0->add (dist_2);
		}
		const value :: Real dist_0 = point_1->getDistance (point_2, factors);
		vector_1->add (0);
		vector_2->add (dist_0);
		vector_1->add (dist_0);
		vector_2->add (0);
		return true;
	}

	void
	Matrix :: evalSimilarity
	(
		value :: Real& positive,  // positive
		value :: Real& negative,  // negative
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const
	{
		const value :: Integer n = mdl :: Config :: getClassifierLocalityBoundary();
		value :: Integer nearestPoints [n];
		value :: Real distances [n];
		evalNearest (nearestPoints, distances, i, sample, n);
		positive = 0; negative = 0;
		for (value :: Integer k = 0; k < n; ++ k) {
			const value :: Integer
				j = nearestPoints [k];
			if (j == value :: undefined :: INTEGER) {
				continue;
			}
			const value :: Real
				factor = mdl :: Config :: getClassifierLocalityFactor (k);
			if (points_.getValue (j)->isPositive()) {
				positive += factor;
			}
			if (points_.getValue (j)->isNegative()) {
				negative += factor;
			}
		}
	}

	void
	Matrix :: showMatrix (String& string) const
	{
		string << "Distance matrix (dim = " << size_ << "): " << endLine;
		for (value :: Integer i = 0; i < size_; ++ i) {
			for (value :: Integer j = 0; j < size_; ++ j) {
				const value :: Real
					distance = matrix_.getValue (i)->getValue (j);
				string << tab << distance;
			}
			string << endLine;
		}
		string << endLine;
	}
	void
	Matrix :: showPoints (String& string) const
	{
		string << "Points (dim = " << size_ << "): " << endLine;
		string << "=====================================" << endLine;
		string << endLine;
		for (value :: Integer i = 0; i < size_; ++ i) {
			const Point_* point = points_.getValue (i);
			string << *point << endLine;
		}
		string << endLine;
	}
	void
	Matrix :: showProfile (const Sample& sample, String& string) const
	{
		string << "Compactness Profile: " << endLine;
		for (value :: Integer i = 1; i < sample.getSize(); ++ i) {
			const value :: Real
				profile = compactnessProfile (i, sample);
			//string << "profile (" << i << ") = " << profile << endLine;
			string << profile << tab;
		}
		string << endLine;
	}
	void
	Matrix :: showFRiS (const Sample& sample, String& string) const
	{
		string << "FRiS function: " << endLine;
		for (value :: Integer i = 1; i < sample.getSize(); ++ i) {
			const value :: Real
				fris = evalFris (i, sample);
			string << fris << tab;
		}
		string << endLine;
		const value :: Real sumFris = evalSumFris (sample);
		string << "FRiS sum = " << sumFris << endLine;
	}
}
}
}



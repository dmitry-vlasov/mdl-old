/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Fris.cpp                                  */
/* Description:     FRiS function                                            */
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

	inline
	Fris :: Fris (const Matrix* matrix) :
	matrix_ (matrix) {
	}
	Fris :: ~ Fris() {
	}

	bool
	Fris :: classify
	(
		const value :: Integer i, // point index
		const Sample& positive,
		const Sample& negative
	) const
	{
		value :: Real fris = 0;
		return classify (i, fris, positive, negative);
	}

	bool
	Fris :: classify
	(
		const value :: Integer i, // point index
		value :: Real& fris,      // FRiS value
		const Sample& positive,
		const Sample& negative
	) const
	{
		if (positive.contains (i)) {
			return true;
		}
		if (negative.contains (i)) {
			return false;
		}
		value :: Integer nearestPositive = 0;
		value :: Real distanceToPositive = 0;
		matrix_->evalNearest (&nearestPositive, &distanceToPositive, i, positive, 1);

		value :: Integer nearestNegative = 0;
		value :: Real distanceToNegative = 0;
		matrix_->evalNearest (&nearestNegative, &distanceToNegative, i, negative, 1);

		fris = (distanceToNegative - distanceToPositive) / (distanceToNegative + distanceToPositive);
		return (fris > 0);
	}

	value :: Real
	Fris :: evalSum (const Sample& sample) const
	{
		value :: Real sum = 0;  // positive
		for (value :: Integer i = 0; i < matrix_->getSize(); ++ i) {
			sum += eval (i, sample);
		}
		return sum;
	}
	value :: Real
	Fris :: eval
	(
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const
	{
		const Point_* x = matrix_->getPoint (i);
		const bool sign = x->getSign();
		const value :: Real distToSelfClass = evalAverageDistance (sign, i, sample);
		const value :: Real distToOtherClass = evalAverageDistance (!sign, i, sample);
		return (distToOtherClass - distToSelfClass) / (distToOtherClass + distToSelfClass);
	}
	value :: Real
	Fris :: eval
	(
		const value :: Integer i, // u index
		const value :: Integer j, // x index
		const value :: Integer k  // x' index
	) const
	{
		const value :: Real
			rho_1 = matrix_->getDistance (i, j);
		const value :: Real
			rho_2 = matrix_->getDistance (i, k);
		return (rho_2 - rho_1) / (rho_2 + rho_1);
	}
	value :: Real
	Fris :: evalWithNearestNeibour
	(
		const value :: Integer i, // u index
		const value :: Integer j, // x index
		const Sample& sample      // current sample
	) const
	{
		value :: Integer k = 0;
		value :: Real d = 0;
		matrix_->evalNearest (&k, &d, i, sample, 1);
		const value :: Real
			rho_1 = matrix_->getDistance (i, j);
		const value :: Real
			rho_2 = d;
		return (rho_2 - rho_1) / (rho_2 + rho_1);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Fris :: commitSuicide() {
		delete this;
	}
	Size_t
	Fris :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	Size_t
	Fris :: getSizeOf() const {
		return sizeof (Fris);
	}
	void
	Fris :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	value :: Real
	Fris :: evalAverageDistance
	(
		const bool sign,
		const value :: Integer i, // point index
		const Sample& sample      // current sample
	) const
	{
		const value :: Integer n = mdl :: Config :: getClassifierLocalityBoundary();
		value :: Integer nearestPoints [n];
		value :: Real distances [n];
		matrix_->evalNearestOfSign (sign, nearestPoints, distances, i, sample, n);
		value :: Real averageDistance = 0;
		for (value :: Integer k = 0; k < n; ++ k) {
			const value :: Real
				distance = distances [k];
			averageDistance += distance;
		}
		averageDistance = averageDistance / n;
		return averageDistance;
	}

	void
	Fris :: showFRiS (const Sample& sample, String& string) const
	{
		string << "FRiS function: " << endLine;
		for (value :: Integer i = 1; i < sample.getSize(); ++ i) {
			const value :: Real
				fris = eval (i, sample);
			string << fris << tab;
		}
		string << endLine;
		const value :: Real sumFris = evalSum (sample);
		string << "FRiS sum = " << sumFris << endLine;
	}
}
}
}



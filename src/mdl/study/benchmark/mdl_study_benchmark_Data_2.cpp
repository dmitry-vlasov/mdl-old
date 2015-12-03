/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Data_2.cpp                           */
/* Description:     2 dimensional data for interpolation                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_DATA_2_CPP_
#define MDL_STUDY_BENCHMARK_DATA_2_CPP_

namespace mdl {
namespace study {
namespace benchmark {

	/****************************
	 *		Public members
	 ****************************/

	Data<2> :: Data () :
	counter_ (INITIAL_VECTOR_CAPACITY),
	function_ (INITIAL_VECTOR_CAPACITY),
	xVector_ (INITIAL_VECTOR_CAPACITY),
	yVector_ (INITIAL_VECTOR_CAPACITY),
	zVector_ (INITIAL_VECTOR_CAPACITY) {
	}
	Data<2> :: ~ Data()
	{
		for (value :: Integer i = 0; i < function_.getSize(); ++ i) {
			RealFunctionY_* realFunctionY = function_.getValue (i);
			realFunctionY->commitSuicide();
		}
		for (value :: Integer i = 0; i < counter_.getSize(); ++ i) {
			IntegerFunctionY_* countFunctionY = counter_.getValue (i);
			countFunctionY->commitSuicide();
		}
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	inline void
	Data<2> :: add
	(
		const value :: Real x,
		const value :: Real y,
		const value :: Real z
	)
	{
		addValue (x, y, z);
		incCounter (x, y);
	}
	Data<2> :: Polynomial_2_*
	Data<2> :: interpolate()
	{
		normalize();
		interpolation :: Tuner<2, Allocator_> tuner;
		tuner.setData (xVector_, yVector_, zVector_);
		Polynomial_2_* polynomial = tuner.evalOptimalPolynomial();

		/*interpolation :: Sample<2> sample (xVector_, yVector_, zVector_);
		interpolation :: Gradient<2> gradient (2, 2, sample);

		Polynomial<2>& p = gradient.evaluate();

		std :: cout << std :: endl;
		std :: cout << "gradient:" << std :: endl;
		std :: cout << p << std :: endl;
		std :: cout << "mse grad = ";
		std :: cout << gradient.getApproximation().evalMSE() << std :: endl;

		std :: cout << std :: endl;
		std :: cout << "linear:" << std :: endl;
		std :: cout << *polynomial << std :: endl;
		std :: cout << "mse lin = ";
		std :: cout << tuner.getMse() << std :: endl;*/


		return polynomial;
	}
	Data<2> :: Polynomial_2_*
	Data<2> :: interpolate
	(
		const value :: Integer degreeX,
		const value :: Integer degreeY
	)
	{
		normalize();
		interpolation :: Tuner<2, Allocator_> tuner;
		tuner.setData (xVector_, yVector_, zVector_);
		return tuner.evalPolynomialOfDegree (degreeX, degreeY);
	}

	// object :: Object implementation
	void
	Data<2> :: commitSuicide() {
		delete this;
	}
	Size_t
	Data<2> :: getVolume() const
	{
		Size_t volume = 0;
		volume += function_.getVolume();
		volume += counter_.getVolume();
		for (value :: Integer i = 0; i < function_.getSize(); ++ i) {
			RealFunctionY_* realFunctionY = function_.getValue (i);
			volume += getAggregateVolume (realFunctionY);
		}
		for (value :: Integer i = 0; i < counter_.getSize(); ++ i) {
			IntegerFunctionY_* countFunctionY = counter_.getValue (i);
			volume += getAggregateVolume (countFunctionY);
		}
		volume += xVector_.getVolume();
		volume += yVector_.getVolume();
		volume += zVector_.getVolume();
		return volume;
	}
	Size_t
	Data<2> :: getSizeOf() const {
		return sizeof (Data);
	}
	void
	Data<2> :: show (String& string) const
	{
		string << "data:" << endLine;
		string << "---------------------------" << endLine;
		for (value :: Integer i = 0; i < xVector_.getSize(); ++ i) {
			string << xVector_.getValue (i) << ", " << tab;
			string << yVector_.getValue (i) << ", ";
			string << zVector_.getValue (i) << ", ";
			string << endLine;
		}
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Data<2> :: addValue
	(
		const value :: Real x,
		const value :: Real y,
		const value :: Real z
	)
	{
		RealFunctionY_* realFunctionY = function_.find (x);
		if (realFunctionY == NULL) {
			realFunctionY = new RealFunctionY_ (INITIAL_VECTOR_CAPACITY);
			function_.add (x, realFunctionY);
		}
		RealFunctionY_ :: Index_ index = realFunctionY->findIndex (y);
		if (index == Undefined<RealFunctionY_ :: Index_> :: getValue()) {
			realFunctionY->add (y, z);
		} else {
			realFunctionY->value (index) += z;
		}
	}
	void
	Data<2> :: incCounter
	(
		const value :: Real x,
		const value :: Real y
	)
	{
		IntegerFunctionY_* intFunctionY = counter_.find (x);
		if (intFunctionY == NULL) {
			intFunctionY = new IntegerFunctionY_ (INITIAL_VECTOR_CAPACITY);
			counter_.add (x, intFunctionY);
		}
		IntegerFunctionY_ :: Index_ index = intFunctionY->findIndex (y);
		if (index == Undefined<IntegerFunctionY_ :: Index_> :: getValue()) {
			intFunctionY->add (y, 1);
		} else {
			++ intFunctionY->value (index);
		}
	}
	void
	Data<2> :: normalize()
	{
		for (value :: Integer i = 0; i < function_.getSize(); ++ i) {
			RealFunctionY_* realFunctionY = function_.getValue (i);
			value :: Real x = function_.getKey (i);
			IntegerFunctionY_* countFunctionY = counter_.find (x);
			for (value :: Integer j = 0; j < realFunctionY->getSize(); ++ j) {
				value :: Real y = realFunctionY->getKey (j);
				value :: Real z = realFunctionY->getValue (j);
				value :: Real count = countFunctionY->find (y);
				z /= count;
				xVector_.add (x);
				yVector_.add (y);
				zVector_.add (z);
			}
		}
	}
}
}
}

#endif /*MDL_STUDY_BENCHMARK_DATA_2_CPP_*/

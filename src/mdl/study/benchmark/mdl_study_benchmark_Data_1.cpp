/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Data_1.cpp                           */
/* Description:     1 dimensional data for interpolation                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_DATA_1_CPP_
#define MDL_STUDY_BENCHMARK_DATA_1_CPP_

namespace mdl {
namespace study {
namespace benchmark {

	/****************************
	 *		Public members
	 ****************************/

	Data<1> :: Data () :
	counter_ (INITIAL_VECTOR_CAPACITY),
	function_ (INITIAL_VECTOR_CAPACITY),
	xVector_ (INITIAL_VECTOR_CAPACITY),
	yVector_ (INITIAL_VECTOR_CAPACITY) {
	}
	Data<1> :: ~ Data() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	void
	Data<1> :: add (const value :: Real x, const value :: Real y)
	{
		RealFunction_ :: Index_ index_1 = function_.findIndex (x);
		if (index_1 == Undefined<RealFunction_ :: Index_> :: getValue()) {
			function_.add (x, y);
		} else {
			function_.value (index_1) += y;
		}
		IntegerFunction_ :: Index_ index_2 = counter_.findIndex (x);
		if (index_2 == Undefined<IntegerFunction_ :: Index_> :: getValue()) {
			counter_.add (x, 1);
		} else {
			++ counter_.value (index_2);
		}
	}
	Data<1> :: Polynomial_1_*
	Data<1> :: interpolate()
	{
		normalize();
		interpolation :: Tuner<1, Allocator_> tuner;
		tuner.setData (xVector_, yVector_);
		Polynomial_1_* polynomial = tuner.evalOptimalPolynomial();

		/*interpolation :: Sample<1> sample (xVector_, yVector_);
		interpolation :: Gradient<1> gradient (2, sample);

		Polynomial<1>& p = gradient.evaluate();

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
	Data<1> :: Polynomial_1_*
	Data<1> :: interpolate (const value :: Integer degree)
	{
		normalize();
		interpolation :: Tuner<1, Allocator_> tuner;
		tuner.setData (xVector_, yVector_);
		return tuner.evalPolynomialOfDegree (degree);
	}

	// object :: Object implementation
	void
	Data<1> :: commitSuicide() {
		delete this;
	}
	Size_t
	Data<1> :: getVolume() const
	{
		Size_t volume = 0;
		volume += counter_.getVolume();
		volume += function_.getVolume();
		volume += xVector_.getVolume();
		volume += yVector_.getVolume();
		return volume;
	}
	Size_t
	Data<1> :: getSizeOf() const {
		return sizeof (Data);
	}
	void
	Data<1> :: show (String& string) const
	{
		string << "data:" << endLine;
		string << "---------------------------" << endLine;
		for (value :: Integer i = 0; i < xVector_.getSize(); ++ i) {
			string << xVector_.getValue (i) << ", " << tab;
			string << yVector_.getValue (i) << ", ";
			string << endLine;
		}
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Data<1> :: normalize()
	{
		for (value :: Integer i = 0; i < function_.getSize(); ++ i) {
			const value :: Real x = function_.getKey (i);
			const value :: Real y = function_.getValue (i);
			const value :: Integer count = counter_.find (x);

			xVector_.add (x);
			yVector_.add (y / count);
		}
	}
}
}
}

#endif /*MDL_STUDY_BENCHMARK_DATA_1_CPP_*/

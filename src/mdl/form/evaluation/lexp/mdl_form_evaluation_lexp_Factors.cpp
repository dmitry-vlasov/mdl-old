/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Factors.cpp                     */
/* Description:     factors for distance calculation                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_FACTORS_CPP_
#define MDL_FORM_EVALUATION_LEXP_FACTORS_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Factors :: Factors () :
	alpha_ (mdl :: Config :: getDistanceBalanceFactor()),
	beta_ (mdl :: Config :: getDistanceLocalityFactor (1)),
	gamma_ (INITIAL_FACTORS_CAPACITY) {
		setGamma();
	}
	inline
	Factors :: Factors
	(
		const value :: Real alpha,
		const value :: Real beta
	) :
	alpha_ (alpha),
	beta_ (beta),
	gamma_ (INITIAL_FACTORS_CAPACITY) {
		setGamma();
	}
	inline
	Factors :: Factors (const Factors& distance) :
	alpha_ (distance.alpha_),
	beta_ (distance.beta_),
	gamma_ (distance.gamma_) {
	}
	Factors :: ~ Factors() {
	}

	inline value :: Real
	Factors :: getAlpha() const {
		return alpha_;
	}
	inline value :: Real
	Factors :: getBeta() const {
		return beta_;
	}
	inline value :: Real
	Factors :: getGamma (const value :: Integer i) const {
		return gamma_.getValue (i);
	}

	inline void
	Factors :: setAlpha (const value :: Real alpha) {
		alpha_ = alpha;
	}
	inline void
	Factors :: setBeta (const value :: Real beta) {
		beta_ = beta;
	}
	void
	Factors :: setGamma ()
	{
		gamma_.clear();
		value :: Real factor = 1;
		while (factor > epsilon_) {
			gamma_.add (factor);
			factor *= beta_;
		}
	}

	// object :: Object implementation
	void
	Factors :: commitSuicide() {
		delete this;
	}
	Size_t
	Factors :: getVolume() const
	{
		Size_t volume = 0;
		volume += gamma_.getVolume();
		return volume;
	}
	Size_t
	Factors :: getSizeOf() const {
		return sizeof (Factors);
	}
	void
	Factors :: show (String& string) const {
	}

	/*************************************
	 *		Static Private attributes
	 *************************************/

	value :: Real Factors :: epsilon_ = 0.05;
}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_FACTORS_CPP_*/

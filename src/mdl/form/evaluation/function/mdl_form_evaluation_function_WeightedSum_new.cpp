/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_function_WeightedSum.cpp             */
/* Description:     weighted sum evaluation function for proposition         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace function {

	/****************************
	 *		Public members
	 ****************************/

	inline
	WeightedSum :: WeightedSum
	(
		const index :: Arity index,
		const mdl :: Proposition* proposition,
		mdl :: Evaluation* evaluation
	) :
	Function (index, proposition, evaluation),
	weightedSum_ (NULL)
	{
		initDescriptions();
		initTerms();
	}
	inline
	WeightedSum :: WeightedSum
	(
		const Location& location,
		const index :: Arity index,
		Term_* term,
		mdl :: Theory* theory
	) :
	Function (location, index, term, theory),
	weightedSum_ (dynamic_cast<form :: evaluation :: term :: WeightedSum*>(term_)) {
		initDescriptions();
	}
	WeightedSum :: ~ WeightedSum()
	{
		if (descriptionVector_ != NULL) {
			deleteAggregateObject (descriptionVector_);
			descriptionVector_ = NULL;
		}
	}

	inline form :: evaluation :: term :: WeightedSum*
	WeightedSum :: weightedSum() {
		return weightedSum_;
	}
	inline WeightedSum :: DescriptionVector_*
	WeightedSum :: descriptionVector() {
		return descriptionVector_;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object implementation
	void
	WeightedSum :: commitSuicide() {
		delete this;
	}
	Size_t
	WeightedSum :: getVolume() const
	{
		Size_t volume = 0;
		volume += Function :: getVolume();
		if (!volumeCounted_) {
			volume += getAggregateVolume (descriptionVector_);
			volumeCounted_ = true;
		}
		return volume;
	}
	Size_t
	WeightedSum :: getSizeOf() const {
		return sizeof (WeightedSum);
	}
	void
	WeightedSum :: show (String& string) const {
		replicate (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	WeightedSum :: initTerms()
	{
		const index :: Arity dimension = PARAMETER_VECTOR_DIMENSION;
		const value :: Real weights [dimension] = {
			descriptionVector_->getValue (LEXP)->getDefaultValue(),
			descriptionVector_->getValue (EXP_BARRIER)->getDefaultValue(),
			descriptionVector_->getValue (EXP_CPLX)->getDefaultValue(),
			descriptionVector_->getValue (EXP_SIM)->getDefaultValue(),
			descriptionVector_->getValue (EXP_EQ)->getDefaultValue()
		};
		Term_* terms [dimension] =
		{
			new term :: Lexp (true),
			new term :: Barrier
			(
				new term :: ExpAvg(),
				new term :: ExpDisp(),
				new term :: ExpCplx()
			),
			new term :: ExpCplx(),
			new term :: ExpSim(),
			new term :: ExpEq()
		};

		weightedSum_ = new term :: WeightedSum (dimension, weights, terms);
		term_ = weightedSum_;
		const_cast<form :: header :: statement :: Proposition*>(proposition_)->addEvaluationFunction (this);
		term_->setDepth();
		term_->setProposition (proposition_);
	}
	void
	WeightedSum :: initDescriptions()
	{
		//
		// Default parameter descriptions:
		//
		//   lexp      [def = 1, min = -1, max = 1.01, qtm = 0.25],
		//   barrier   [def = 1, min = -1, max = 1.01, qtm = 0.25],
		//   exp_cplx  [def = 1, min = -1, max = 1.01, qtm = 0.25],
		//   exp_sim   [def = 1, min = -1, max = 1.01, qtm = 0.25],
		//   exp_eq    [def = 1, min = -1, max = 1.01, qtm = 0.25],
		//

		if (descriptionVector_ == NULL) {
			volumeCounted_ = false;
			descriptionVector_ = new DescriptionVector_ (PARAMETER_VECTOR_DIMENSION);

			descriptionVector_->add (new Description_
				(
					Config :: hasRealOption ("lexp_w_default") ? Config :: getReal ("fris_w_default") : 1,
					Config :: hasRealOption ("lexp_w_min")     ? Config :: getReal ("fris_w_min")     : -1,
					Config :: hasRealOption ("lexp_w_max")     ? Config :: getReal ("fris_w_max")     : +1.01,
					Config :: hasRealOption ("lexp_w_quantum") ? Config :: getReal ("fris_w_quantum") : 0.25,
					"lexp"
				)
			);
			descriptionVector_->add (new Description_
				(
					Config :: hasRealOption ("barrier_w_default") ? Config :: getReal ("barrier_w_default") : 1,
					Config :: hasRealOption ("barrier_w_min")     ? Config :: getReal ("barrier_w_min")     : -1,
					Config :: hasRealOption ("barrier_w_max")     ? Config :: getReal ("barrier_w_max")     : +1.01,
					Config :: hasRealOption ("barrier_w_quantum") ? Config :: getReal ("barrier_w_quantum") : 0.25,
					"exp_barrier"
				)
			);
			descriptionVector_->add (new Description_
				(
					Config :: hasRealOption ("exp_cplx_w_default") ? Config :: getReal ("exp_cplx_w_default") : 1,
					Config :: hasRealOption ("exp_cplx_w_min")     ? Config :: getReal ("exp_cplx_w_min")     : -1,
					Config :: hasRealOption ("exp_cplx_w_max")     ? Config :: getReal ("exp_cplx_w_max")     : +1.01,
					Config :: hasRealOption ("exp_cplx_w_quantum") ? Config :: getReal ("exp_cplx_w_quantum") : 0.25,
					"exp_cplx"
				)
			);
			descriptionVector_->add (new Description_
				(
					Config :: hasRealOption ("exp_sim_w_default") ? Config :: getReal ("exp_sim_w_default") : 1,
					Config :: hasRealOption ("exp_sim_w_min")     ? Config :: getReal ("exp_sim_w_min")     : -1,
					Config :: hasRealOption ("exp_sim_w_max")     ? Config :: getReal ("exp_sim_w_max")     : +1.01,
					Config :: hasRealOption ("exp_sim_w_quantum") ? Config :: getReal ("exp_sim_w_quantum") : 0.25,
					"exp_sim"
				)
			);
			descriptionVector_->add (new Description_
				(
					Config :: hasRealOption ("exp_eq_w_default") ? Config :: getReal ("exp_eq_w_default") : 1,
					Config :: hasRealOption ("exp_eq_w_min")     ? Config :: getReal ("exp_eq_w_min")     : -1,
					Config :: hasRealOption ("exp_eq_w_max")     ? Config :: getReal ("exp_eq_w_max")     : +1.01,
					Config :: hasRealOption ("exp_eq_w_quantum") ? Config :: getReal ("exp_eq_w_quantum") : 0.25,
					"exp_eq"
				)
			);
		}
	}

	/**********************************
	 *		Private static members
	 **********************************/

	WeightedSum :: DescriptionVector_*
		WeightedSum :: descriptionVector_ = NULL;
	bool
		WeightedSum :: volumeCounted_ = false;
}
}
}
}



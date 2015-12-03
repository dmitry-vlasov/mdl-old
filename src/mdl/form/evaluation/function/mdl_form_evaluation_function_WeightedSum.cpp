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

#ifndef MDL_FORM_EVALUATION_FUNCTION_WEIGHTED_SUM_CPP_
#define MDL_FORM_EVALUATION_FUNCTION_WEIGHTED_SUM_CPP_

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
		if (descriptionVector_ == NULL) {
			owner_ = this;
			initDescriptions();
		}
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
	weightedSum_ (dynamic_cast<form :: evaluation :: term :: WeightedSum*>(term_))
	{
		if (descriptionVector_ == NULL) {
			owner_ = this;
			initDescriptions();
		}
	}
	WeightedSum :: ~ WeightedSum()
	{
		if (owner_ == this) {
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
		if (owner_ == this) {
			volume += getAggregateVolume (descriptionVector_);
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
			descriptionVector_->getValue (SUB_CPLX)->getDefaultValue(),
			descriptionVector_->getValue (FORKING)->getDefaultValue()
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
			new term :: SubCplx(),
			new term :: Forking()
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
		//   fris      [def = 1,    min = -1, max = 1.01, qtm = 0.25],
		//   e_barrier [def = 1,    min = -1, max = 1.01, qtm = 0.25],
		//   exp_cplx  [def = -0.6, min = -1, max = 1.01, qtm = 0.25],
		//   sub_cplx  [def = -0.4, min = -1, max = 1.01, qtm = 0.25],
		//   forking   [def = -0.2, min = -1, max = 1.01, qtm = 0.25],
		//

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
				Config :: hasRealOption ("exp_barrier_w_default") ? Config :: getReal ("exp_barrier_w_default") : 1,
				Config :: hasRealOption ("exp_barrier_w_min")     ? Config :: getReal ("exp_barrier_w_min")     : -1,
				Config :: hasRealOption ("exp_barrier_w_max")     ? Config :: getReal ("exp_barrier_w_max")     : +1.01,
				Config :: hasRealOption ("exp_barrier_w_quantum") ? Config :: getReal ("exp_barrier_w_quantum") : 0.25,
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
				Config :: hasRealOption ("sub_cplx_w_default") ? Config :: getReal ("sub_cplx_w_default") : 1,
				Config :: hasRealOption ("sub_cplx_w_min")     ? Config :: getReal ("sub_cplx_w_min")     : -1,
				Config :: hasRealOption ("sub_cplx_w_max")     ? Config :: getReal ("sub_cplx_w_max")     : +1.01,
				Config :: hasRealOption ("sub_cplx_w_quantum") ? Config :: getReal ("sub_cplx_w_quantum") : 0.25,
				"sub_cplx"
			)
		);
		descriptionVector_->add (new Description_
			(
				Config :: hasRealOption ("forking_w_default") ? Config :: getReal ("forking_w_default") : 1,
				Config :: hasRealOption ("forking_w_min")     ? Config :: getReal ("forking_w_min")     : -1,
				Config :: hasRealOption ("forking_w_max")     ? Config :: getReal ("forking_w_max")     : +1.01,
				Config :: hasRealOption ("forking_w_quantum") ? Config :: getReal ("forking_w_quantum") : 0.25,
				"forking"
			)
		);
	}

	/**********************************
	 *		Private static members
	 **********************************/

	WeightedSum :: DescriptionVector_*
		WeightedSum :: descriptionVector_ = NULL;
	WeightedSum*
		WeightedSum :: owner_ = NULL;
}
}
}
}

#endif /*MDL_FORM_EVALUATION_FUNCTION_WEIGHTED_SUM_CPP_*/

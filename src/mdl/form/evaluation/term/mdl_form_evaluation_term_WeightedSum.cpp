/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_WeightedWeightedSum.cpp         */
/* Description:     weighted sum evaluation function for proposition         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_WEIGHTED_SUM_CPP_
#define MDL_FORM_EVALUATION_TERM_WEIGHTED_SUM_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	WeightedSum :: WeightedSum
	(
		const index :: Arity dimension,
		const value :: Real weights[],
		Term_* terms[]
	) :
	location_(),
	weightVector_ (weights, dimension),
	termVector_ (terms, dimension) {
	}
	inline
	WeightedSum :: WeightedSum
	(
		const Location& location,
		const vector :: value :: Real& weightVector,
		const mdl :: evaluation :: parser :: vector :: Term& termVector,
		mdl :: Theory* theory
	) :
	location_ (location),
	weightVector_ (weightVector),
	termVector_ (termVector) {
	}
	WeightedSum :: ~ WeightedSum() {
	}

	vector :: value :: Real&
	WeightedSum :: weightVector()
	{
		++ version_;
		return weightVector_;
	}
	void
	WeightedSum :: addTerm (Term_* term) {
		termVector_.add (term);
	}

	// evaluation :: Term implementation
	index :: Arity
	WeightedSum :: getArity() const {
		return termVector_.getSize();
	}
	value :: Real
	WeightedSum :: eval (const HeapNode_* node) const
	{
		value :: Real sum = 0;
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			const Term_*  term = termVector_.getValue (i);
			const value :: Real weight = weightVector_.getValue (i);
			sum += weight * term->eval (node);
		}
		return sum;
	}
	value :: Real
	WeightedSum :: eval (const value :: Real values[]) const
	{
		value :: Real sum = 0;
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			const value :: Real weight = weightVector_.getValue (i);
			sum += weight * values [i];
		}
		return sum;
	}
	WeightedSum :: Term_*
	WeightedSum :: getSubTerm (const index :: Arity i) {
		return termVector_.getValue (i);
	}
	const WeightedSum :: Term_*
	WeightedSum :: getSubTerm (const index :: Arity i) const {
		return termVector_.getValue (i);
	}

	// object :: Buildable implementation
	void
	WeightedSum :: build()
	{
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			Term_*  term = termVector_.getValue (i);
			term->build();
		}
	}

	// object :: Writable implementation
	void
	WeightedSum :: replicate (String& string) const
	{
		string << Indent (depth_ + 2);
		string << Token :: weightedSum_ << space << Token :: openSqBracket_;
		for (value :: Integer i = 0; i < weightVector_.getSize(); ++ i) {
			const value :: Real weight = weightVector_.getValue (i);
			if (((weight < 0) ? - weight : weight) < value :: ALMOST_ZERO) {
				string << '0';
			} else {
				string << weight;
			}

			if (i + 1 < weightVector_.getSize()) {
				string << Token :: comma_ << space;
			}
		}
		string << Token :: closeSqBracket_ << endLine;
		string << Indent (depth_ + 2) << Token :: openBracket_ << endLine;
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			const Term_*  term = termVector_.getValue (i);
			term->replicate (string);
			string << endLine;
		}
		string << Indent (depth_ + 2) << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	WeightedSum :: commitSuicide() {
		delete this;
	}
	Size_t
	WeightedSum :: getVolume() const
	{
		Size_t volume = 0;
		volume += termVector_.getVolume();
		volume += weightVector_.getVolume();
		return volume;
	}
	Size_t
	WeightedSum :: getSizeOf() const {
		return sizeof (WeightedSum);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_WEIGHTED_SUM_CPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Rate.cpp                                 */
/* Description:     rate holder class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_RATE_RATE_CPP_
#define MDL_PROVER_RATE_RATE_CPP_

namespace mdl {
namespace prover {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Rate<A> :: Rate (const Node_* node, const evaluation :: Term* term) :
	node_ (node),
	term_ (term),
	weight_ (0),
	subrates_ (term->getArity()),
	version_(value :: undefined :: INTEGER)
	{
		for (index :: Arity i = 0; i < term->getArity(); ++ i) {
			const evaluation :: Term* subterm = term->getSubTerm (i);
			Rate* subrate = new Rate (node, subterm);
			subrates_.add (subrate);
		}
		weight_ = term_->eval (node);
		version_ = term_->getVersion();
	}
	template<class A>
	Rate<A> :: ~ Rate() {
	}

	template<class A>
	value :: Real
	Rate<A> :: getWeight() const {
		return weight_;
	}
	template<class A>
	value :: Real
	Rate<A> :: eval()
	{
		if (wasChanged()) {
			if (term_->getArity() > 0) {
				value :: Real subweights [term_->getArity()];
				for (index :: Arity i = 0; i < term_->getArity(); ++ i) {
					Rate* subrate = subrates_.getValue (i);
					subweights [i] = subrate->eval();
				}
				weight_ = term_->eval (subweights);
			} else {
				weight_ = term_->eval (node_);
			}
			version_ = term_->getVersion();
		}
		return weight_;
	}
	template<class A>
	bool
	Rate<A> :: wasChanged() const
	{
		if (version_ != term_->getVersion()) {
			return true;
		}
		for (index :: Arity i = 0; i < term_->getArity(); ++ i) {
			Rate* subrate = subrates_.getValue (i);
			if (subrate->wasChanged ()) {
				return true;
			}
		}
		return false;
	}

	// object :: Object implementation
	template<class A>
	void
	Rate<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Rate<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += subrates_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Rate<A> :: getSizeOf() const {
		return sizeof (Rate);
	}
	template<class A>
	void
	Rate<A> :: show (String& string) const
	{
		string << "weight: " << weight_ << ", ";
		string << "version: " << version_ << ", ";
		string << endLine;
		string << "term: " << *term_ << ", ";
	}

	/*******************************
	 *		Overloaded operator
	 *******************************/
}
}
}

#endif /*MDL_PROVER_RATE_RATE_CPP_*/

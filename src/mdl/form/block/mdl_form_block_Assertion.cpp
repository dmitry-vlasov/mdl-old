/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Assertion.cpp                             */
/* Description:     assertion class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_ASSERTION_CPP_
#define MDL_FORM_BLOCK_ASSERTION_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	template<class H, class P>
	inline
	Assertion<H, P> :: Assertion
	(
		const Location& location,
		const mdl :: Comments* comments,
		const lexer :: Indent barIndent,
		const value :: Name name,
		mdl :: Variables* variables,
		mdl :: Disjointeds* disjointeds,
		const ParserHypothesisVector_& hypothesisVector,
		const ParserPropositionVector_& propositionVector,
		mdl :: Theory* theory
	) :
	Ancestor_ (location, comments, name, theory),
	variables_ (variables),
	disjointeds_ (disjointeds),
	hypothesisVector_ (hypothesisVector),
	propositionVector_ (propositionVector),
	evaluationVector_ (INITIAL_EVALUATION_VECTOR_CAPACITY),
	index_ (index :: undefined :: ASSERTION),
	barIndent_(barIndent)
	{
		if (Config :: localParsing()) {
			return;
		}
		try {
			theory_->checkUnused (name_);
			buildVariables();
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	template<class H, class P>
	Assertion<H, P> :: ~ Assertion()
	{
		deleteAggregateObject (variables_);
		deleteAggregateObject (disjointeds_);
	}

	// mdl :: Assertion implementation
	template<class H, class P>
	void
	Assertion<H, P> :: addEvaluation (mdl :: Evaluation* evaluation) {
		evaluationVector_.add  (evaluation);
	}
	template<class H, class P>
	index :: Assertion
	Assertion<H, P> :: getIndex() const {
		return index_;
	}
	template<class H, class P>
	index :: Arity
	Assertion<H, P> :: getHypArity() const {
		return hypothesisVector_.getSize();
	}
	template<class H, class P>
	index :: Arity
	Assertion<H, P> :: getPropArity() const {
		return propositionVector_.getSize();
	}

	template<class H, class P>
	mdl :: Variables*
	Assertion<H, P> :: getVariables() {
		return variables_;
	}
	template<class H, class P>
	mdl :: Disjointeds*
	Assertion<H, P> :: getDisjointeds() {
		return disjointeds_;
	}
	template<class H, class P>
	mdl :: Hypothesis*
	Assertion<H, P> :: getHypothesis (const index :: Arity i) {
		return hypothesisVector_.getValue (i);
	}
	template<class H, class P>
	mdl :: Proposition*
	Assertion<H, P> :: getProposition (const index :: Arity i) {
		return propositionVector_.getValue (i);
	}
	template<class H, class P>
	mdl :: Evaluation*
	Assertion<H, P> :: getEvaluation (const value :: Name name)
	{
		for (value :: Integer i = 0; i < evaluationVector_.getSize(); ++ i) {
			mdl :: Evaluation* evaluation = evaluationVector_.getValue (i);
			if (evaluation->getName() == name) {
				return evaluation;
			}
		}
		mdl :: Evaluation*
			evaluation = new Evaluation (name, this);
		addEvaluation (evaluation);
		Ancestor_ :: contents_->addComponentLast (evaluation);
		return evaluation;
	}

	template<class H, class P>
	const mdl :: Variables*
	Assertion<H, P> :: getVariables() const {
		return variables_;
	}
	template<class H, class P>
	const mdl :: Disjointeds*
	Assertion<H, P> :: getDisjointeds() const {
		return disjointeds_;
	}
	template<class H, class P>
	const mdl :: Hypothesis*
	Assertion<H, P> :: getHypothesis (const index :: Arity i) const {
		return hypothesisVector_.getValue (i);
	}
	template<class H, class P>
	const mdl :: Proposition*
	Assertion<H, P> :: getProposition (const index :: Arity i) const {
		return propositionVector_.getValue (i);
	}
	template<class H, class P>
	const mdl :: Evaluation*
	Assertion<H, P> :: getEvaluation (const value :: Name name) const
	{
		for (value :: Integer i = 0; i < evaluationVector_.getSize(); ++ i) {
			const mdl :: Evaluation* evaluation = evaluationVector_.getValue (i);
			if (evaluation->getName() == name) {
				return evaluation;
			}
		}
		/*mdl :: Evaluation*
			evaluation = new Evaluation (name, this);
		addEvaluation (evaluation);
		const_cast<mdl :: Contents*>(Ancestor_ :: contents_)->addComponentLast (evaluation);
		return evaluation;*/
		return NULL;
	}

using manipulator :: tab;
using manipulator :: space;
using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;

	// object :: Identifiable implementation
	template<class H, class P>
	void
	Assertion<H, P> :: translateName (String& string, const index :: Arity index) const
	{
		if (getKind() == mdl :: Assertion :: AXIOM || getKind() == mdl :: Assertion :: DEFINITION) {
			string << :: smm :: Token :: prefix_a_;
		} else {
			string << :: smm :: Token :: prefix_p_;
		}
		if (Config :: noLabels()) {
			string << propositionVector_.getValue (index)->getTargetIndex();
		} else {
			Identifiable :: translateName (string);
			if (index > 0) {
				string << underline << index + 1;
			}
		}
	}
	template<class H, class P>
	void
	Assertion<H, P> :: replicateName (String& string) const {
		Identifiable :: replicateName (string);
	}

	// object :: Verifiable implementation
	template<class H, class P>
	void
	Assertion<H, P> :: mine (String& string) const
	{
		const char* kind = NULL;
		switch (getKind()) {
		case mdl :: Assertion :: AXIOM :
			if (Config :: getMiningOptions().getValue (Config :: MINE_AXIOMS)) {
				kind = "axiom";
			}
			break;
		case mdl :: Assertion :: DEFINITION :
			if (Config :: getMiningOptions().getValue (Config :: MINE_DEFINITIONS)) {
				kind = "definition";
			}
			break;
		case mdl :: Assertion :: THEOREM :
			if (Config :: getMiningOptions().getValue (Config :: MINE_THEOREMS)) {
				kind = "theorem";
			}
			break;
		case mdl :: Assertion :: PROBLEM :
			if (Config :: getMiningOptions().getValue (Config :: MINE_PROBLEMS)) {
				kind = "problem";
			}
			break;
		}
		if (kind == NULL) {
			return;
		}
		const value :: Integer depth =
			Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) ?
			Identifiable :: getDepth() :
			1;
		string << iterate << depth << tab << "<" << kind << " ";
		Identifiable :: mine (string);
		string << "/>" << endLine;
	}

	// object :: Buildable implementation
	template<class H, class P>
	void
	Assertion<H, P> :: build()
	{
		buildHypothesis();
		buildPropositions();
	}

	// object :: Writable implementation
	template<class H, class P>
	void
	Assertion<H, P> :: translate (String& string) const
	{
		try {
			if (!Config :: removeComments() && (comments_ != NULL)) {
				string << location_.getIndent();
				comments_->translate (string);
			}
			string << :: smm :: Token :: blockBegin_ << endLine;
			variables_->translateVariables (string);
			disjointeds_->translate (string);
			for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
				hypothesisVector_.getValue (i)->translate (string);
			}
			variables_->translateFloatings (string);
			for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
				propositionVector_.getValue (i)->translate (string);
			}
			string << :: smm :: Token :: blockEnd_ << endLine;
			string << endLine;
		} catch (Error* error) {
			error->add (location_,"translation failed");
			throw error;
		}
	}
	template<class H, class P>
	void
	Assertion<H, P> :: replicate (String& string) const
	{
		replicateHeader (string);
		string << location_.getIndent() << Token :: openBrace_<< endLine;
		replicateHypothesis (string);
		if (getHypArity() > 0) {
			replicateBar (string);
		}
		replicatePropositions (string);
		string << location_.getIndent() << Token :: closeBrace_<< endLine;
	}
	template<class H, class P>
	bool
	Assertion<H, P> :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (variables_->lookup()) {
			return true;
		}
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
			if (hypothesisVector_.getValue (i)->lookup()) {
				return true;
			}
		}
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			if (propositionVector_.getValue (i)->lookup()) {
				return true;
			}
		}
		return false;
	}
	template<class H, class P>
	object :: Writable*
	Assertion<H, P> :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		object :: Writable* object = NULL;
		object = variables_->find();
		if (object != NULL) {
			return object;
		}
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
			object = hypothesisVector_.getValue (i)->find();
			if (object != NULL) {
				return object;
			}
		}
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			object = propositionVector_.getValue (i)->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}
	template<class H, class P>
	const object :: Writable*
	Assertion<H, P> :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const object :: Writable* object = NULL;
		object = variables_->find();
		if (object != NULL) {
			return object;
		}
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
			object = hypothesisVector_.getValue (i)->find();
			if (object != NULL) {
				return object;
			}
		}
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			object = propositionVector_.getValue (i)->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}

	// object :: Object implementation
	template<class H, class P>
	Size_t
	Assertion<H, P> :: getSizeOf() const {
		return sizeof (Assertion);
	}
	template<class H, class P>
	Size_t
	Assertion<H, P> :: getVolume() const
	{
		Size_t result = 0;
		result += Identifiable :: getVolume();
		result += getAggregateVolume (variables_);
		result += getAggregateVolume (disjointeds_);
		result += hypothesisVector_.getVolume();
		result += propositionVector_.getVolume();
		result += evaluationVector_.getVolume();
		return result;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class H, class P>
	inline void
	Assertion<H, P> :: replicateHeader (String& string) const
	{
		replicateName (string);
		string << space;
		variables_->replicate (string);
		if (disjointeds_ != NULL) {
			disjointeds_->replicate (string);
		}
		string << endLine;
	}
	template<class H, class P>
	inline void
	Assertion<H, P> :: replicateHypothesis (String& string) const
	{
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); i++) {
			hypothesisVector_.getValue (i)->replicate (string);
		}
	}
	template<class H, class P>
	inline void
	Assertion<H, P> :: replicateBar (String& string) const {
		string << barIndent_ << Token :: horisontalBar_ << endLine;
	}
	template<class H, class P>
	inline void
	Assertion<H, P> :: replicatePropositions (String& string) const
	{
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			propositionVector_.getValue (i)->replicate (string);
		}
	}

	template<class H, class P>
	inline void
	Assertion<H, P> :: buildVariables() {
		variables_->build();
	}
	template<class H, class P>
	void
	Assertion<H, P> :: buildHypothesis()
	{
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
			mdl :: Hypothesis*
				hypothesis = hypothesisVector_.getValue (i);
			hypothesis->build();
		}
	}
	template<class H, class P>
	void
	Assertion<H, P> :: buildPropositions()
	{
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			mdl :: Proposition*
				proposition = dynamic_cast<mdl :: Proposition*>(propositionVector_.getValue (i));
			proposition->build();
		}
	}
	template<class H, class P>
	template<class T>
	void
	Assertion<H, P> :: add (T* assertion)
	{
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
			mdl :: Hypothesis*
				hypothesis = hypothesisVector_.getValue (i);
			hypothesis->setAssertion (assertion);
		}
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			mdl :: Statement*
				proposition = propositionVector_.getValue (i);
			proposition->setAssertion (assertion);
		}
		if (Config :: localParsing()) {
			return;
		}
		index_ = Math :: assertions()->add (assertion);
		theory_->addName (index_, name_);
		theory_->addComponent (assertion);
	}
}
}
}

#endif /*MDL_FORM_BLOCK_ASSERTION_CPP_*/

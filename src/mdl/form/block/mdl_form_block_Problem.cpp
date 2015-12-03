/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Problem.cpp                               */
/* Description:     problem class                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_PROBLEM_CPP_
#define MDL_FORM_BLOCK_PROBLEM_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Problem :: Problem
	(
		const Location& location,
		const mdl :: Comments* comments,
		lexer :: Indent barIndent,
		value :: Name name,
		mdl :: Variables* variables,
		mdl :: Disjointeds* disjointeds,
		const vector :: parser :: Hypothesis& hypothesisVector,
		const vector :: parser :: Provable& propositionVector,
		mdl :: Theory* theory
	) :
	theorem_
	(
		location,
		comments,
		barIndent,
		name,
		variables,
		disjointeds,
		hypothesisVector,
		propositionVector,
		theory,
		this
	),
	proved_ (false) {
	}
	Problem :: ~ Problem() {
	}

	// object :: Provable implementation
	void
	Problem :: addProof (mdl :: Proof* proof) {
		theorem_.addProof (proof);
	}
	mdl :: proof :: Scope*
	Problem :: getScope() {
		return theorem_.getScope();
	}
	vector :: Proof&
	Problem :: getProofVector() {
		return theorem_.getProofVector();
	}
	mdl :: Proof*
	Problem :: getProof (const value :: Name name) {
		return theorem_.getProof (name);
	}
	const mdl :: proof :: Scope*
	Problem :: getScope() const {
		return theorem_.getScope();
	}
	const vector :: Proof&
	Problem :: getProofVector() const {
		return theorem_.getProofVector();
	}
	const mdl :: Proof*
	Problem :: getProof (const value :: Name name) const {
		return theorem_.getProof (name);
	}

	// mdl :: Assertion implementation

	void
	Problem :: addEvaluation (mdl :: Evaluation* evaluation) const {
		theorem_.addEvaluation (evaluation);
	}
	mdl :: Assertion :: Kind
	Problem :: getKind() const {
		return mdl :: Assertion :: PROBLEM;
	}
	index :: Assertion
	Problem :: getIndex() const {
		return theorem_.getIndex();
	}
	index :: Arity
	Problem :: getHypArity() const {
		return theorem_.getHypArity();
	}
	index :: Arity
	Problem :: getPropArity() const {
		return theorem_.getPropArity();
	}

	mdl :: Variables*
	Problem :: getVariables() {
		return theorem_.getVariables();
	}
	mdl :: Disjointeds*
	Problem :: getDisjointeds() {
		return theorem_.getDisjointeds();
	}
	mdl :: Hypothesis*
	Problem :: getHypothesis (const index :: Arity i) {
		return theorem_.getHypothesis (i);
	}
	mdl :: Proposition*
	Problem :: getProposition (const index :: Arity i) {
		return theorem_.getProposition (i);
	}
	mdl :: Evaluation*
	Problem :: getEvaluation (const value :: Name name) {
		return theorem_.getEvaluation (name);
	}

	const mdl :: Variables*
	Problem :: getVariables() const {
		return theorem_.getVariables();
	}
	const mdl :: Disjointeds*
	Problem :: getDisjointeds() const {
		return theorem_.getDisjointeds();
	}
	const mdl :: Hypothesis*
	Problem :: getHypothesis (const index :: Arity i) const {
		return theorem_.getHypothesis (i);
	}
	const mdl :: Proposition*
	Problem :: getProposition (const index :: Arity i) const {
		return theorem_.getProposition (i);
	}
	const mdl :: Evaluation*
	Problem :: getEvaluation (const value :: Name name) const {
		return theorem_.getEvaluation (name);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: underline;

	// object :: Identifiable implementation
	const Location&
	Problem :: getLocation() const {
		return theorem_.getLocation();
	}
	value :: Name
	Problem :: getName() const {
		return theorem_.getName();
	}
	void
	Problem :: translateName (String& string, const index :: Arity index) const {
		theorem_.translateName (string, index);
	}
	void
	Problem :: replicateName (String& string) const {
		theorem_.replicateName (string);
	}
	mdl :: Theory*
	Problem :: getTheory() {
		return theorem_.getTheory();
	}
	mdl :: Identificator*
	Problem :: getIdentificator() {
		return theorem_.getIdentificator();
	}
	const mdl :: Theory*
	Problem :: getTheory() const {
		return theorem_.getTheory();
	}
	const mdl :: Identificator*
	Problem :: getIdentificator() const {
		return theorem_.getIdentificator();
	}

	// object :: Verifiable implementation
	void
	Problem :: check()
	{
		theorem_.check();
		proved_ = theorem_.isVerified();
	}
	void
	Problem :: compress() {
		theorem_.compress();
	}
	void
	Problem :: reprove() {
		prove();
	}
	void
	Problem :: prove()
	{
		if (theorem_.proofVector_.getSize() == 0) {
			mdl :: Proof* proof = new Proof (this);
			theorem_.proofVector_.add (proof);
			theorem_.contents_->addComponentNextTo (proof, this);
		}
	}
	bool
	Problem :: isVerified() const
	{
		proved_ = theorem_.isVerified();
		return proved_;
	}
	void
	Problem :: mine (String& string) const {
		theorem_.mine (string);
	}
	void
	Problem :: setContents (mdl :: Contents* contents)
	{
		mdl :: Assertion :: setContents (contents);
		theorem_.setContents (contents);
	}

	// object :: Buildable implementation
	void
	Problem :: build() {
		theorem_.build();
	}

	// object :: Writable implementation
	void
	Problem :: translate (String& string) const {
		theorem_.translate (string);
	}
	void
	Problem :: replicate (String& string) const
	{
		theorem_.replicateHeader (string, proved_);
		theorem_.replicateBody (string);
	}
	bool
	Problem :: lookup() const {
		return theorem_.lookup();
	}
	object :: Writable*
	Problem :: find() {
		return theorem_.find();
	}
	const object :: Writable*
	Problem :: find() const {
		return theorem_.find();
	}

	// object :: Object implementation
	void
	Problem :: commitSuicide() {
		delete this;
	}
	Size_t
	Problem :: getSizeOf() const {
		return sizeof (Problem);
	}
	Size_t
	Problem :: getVolume() const {
		return theorem_.getVolume();
	}
}
}
}

#endif /*MDL_FORM_BLOCK_PROBLEM_CPP_*/

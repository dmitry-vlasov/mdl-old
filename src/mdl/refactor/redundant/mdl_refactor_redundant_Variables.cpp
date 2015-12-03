/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_redundant_Variables.hpp                     */
/* Description:     remove redundant variables                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_REFACTOR_REDUNDANT_VARIABLES_CPP_
#define MDL_REFACTOR_REDUNDANT_VARIABLES_CPP_

namespace mdl {
namespace refactor {
namespace redundant {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variables :: Variables (Format& format) :
	format_ (format, true),
	subFormat_ (format_, true),
	assertionVariableSet_ (INITIAL_VARIABLE_SET_CAPACITY),
	proofVariableSetVector_ (INITIAL_VARIABLE_SET_VECTOR_CAPACITY) {
	}
	inline
	Variables :: ~ Variables () {
	}

using manipulator :: endLine;

	index :: Arity
	Variables :: removeUnusedVariables (mdl :: Theorem* theoremInterface)
	{
		Theorem_* theorem = dynamic_cast<Theorem_*>(theoremInterface);

		//static form :: Identificator* id = new form :: Identificator ("math.tpgprop2");
		//static index :: Assertion ind = Math :: theories()->getRoot()->getIndex (id);
		//static mdl :: Assertion* th = Math :: assertions()->get (ind);

		index :: Arity unusedVariables = 0;
		collectUsedVariables (theorem);
		Variables_* variables = dynamic_cast<Variables_*>(theorem->getVariables());
		const index :: Arity arity = variables->getSize();
		for (index :: Arity j = 0; j < arity; ++ j) {
			const index :: Arity i = arity - j - 1;
			mdl :: header :: Variable* variable = variables->getVariable (i);
			const Symbol variableSymbol = variable->getSymbol();
			if (!assertionVariableSet_.contains (variableSymbol)) {
				for (index :: Arity k = 0; k < theorem->getProofVector().getSize(); ++ k) {
					const set :: Symbol* proofVariables = proofVariableSetVector_.getValue (k);
					BlockProof_* blockProof = dynamic_cast<BlockProof_*>(theorem->getProofVector().getValue (k));
					Proof_* proof = blockProof->proof_;

					// If 'variable' is used in 'proof', we need to declare it inside 'proof'
					if (setContainsVariableLiteral (proofVariables, variableSymbol)) {
						Location location = proof->getFirst()->getLocation();
						mdl :: proof :: Variable*
						variableCopy = new form :: proof :: Variable
						(
							location,
							new form :: header :: Variable (variableSymbol)
						);
						proof->addVariableFirst (variableCopy);
						//std :: cout << "adding a var: " << *variableCopy << std :: endl;
					}
				}
				variable->commitSuicide();
				++ unusedVariables;
				variables->variableVector_.remove (i);
			}
		}
		return unusedVariables;
	}

	// object :: Object implementation
	void
	Variables :: commitSuicide() {
		delete this;
	}
	Size_t
	Variables :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += assertionVariableSet_.getVolume();
		volume += proofVariableSetVector_.getVolume();
		return volume;
	}
	Size_t
	Variables :: getSizeOf() const {
		return sizeof (Variables);
	}
	void
	Variables :: show (String& string) const
	{
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Variables :: collectUsedVariables (const mdl :: Theorem* theoremInterface)
	{
		const Theorem_* theorem = dynamic_cast<const Theorem_*>(theoremInterface);

		// Collect variables from assertion declaration
		assertionVariableSet_.clear();
		for (index :: Arity i = 0; i < theorem->getHypArity(); ++ i) {
			const array :: Expression* hyp = theorem->getHypothesis (i)->getExpression();
			collectUsedVariables (hyp, &assertionVariableSet_);
		}
		for (index :: Arity i = 0; i < theorem->getPropArity(); ++ i) {
			const array :: Expression* prop = theorem->getProposition (i)->getExpression();
			collectUsedVariables (prop, &assertionVariableSet_);
		}

		// Collect variables from all assertion proofs
		proofVariableSetVector_.clear();
		for (index :: Arity i = 0; i < theorem->getProofVector().getSize(); ++ i) {
			const mdl :: Proof* proof = theorem->getProofVector().getValue (i);
			set :: Symbol* proofVariables = proofVariableSetVector_.push();
			proofVariables->clear();
			collectUsedVariables (proof, proofVariables);
		}
	}
	void
	Variables :: collectUsedVariables (const mdl :: Proof* proof, set :: Symbol* proofVariables)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			const array :: Expression* step = proof->getStep (i)->getExpression();
			collectUsedVariables (step, proofVariables);
		}
	}
	void
	Variables :: collectUsedVariables (const array :: Expression* expression, set :: Symbol* set)
	{
		array :: Expression :: const_Iterator_
			iterator = expression->getBegin();
		while (true) {
			const Symbol symbol = *iterator;
			if (symbol.isVariable()) {
				set->add (symbol);
			}
			if (iterator == expression->getEnd()) {
				break;
			}
			++ iterator;
		}
	}

	bool
	Variables :: setContainsVariableLiteral (const set :: Symbol* set, Symbol variable)
	{
		for (value :: Integer i = 0; i < set->getSize(); ++ i) {
			if (set->getValue (i).getLiteral() == variable.getLiteral()) {
				return true;
			}
		}
		return false;
	}
}
}
}

#endif /*MDL_REFACTOR_REDUNDANT_VARIABLES_CPP_*/

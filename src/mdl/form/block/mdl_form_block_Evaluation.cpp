/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Evaluation.cpp                            */
/* Description:     assertion usage experience                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_EVALUATION_CPP_
#define MDL_FORM_BLOCK_EVALUATION_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Evaluation :: Evaluation
	(
		value :: Name name,
		mdl :: Assertion* assertion
	) :
	form :: Identifiable (name, assertion->getTheory(), false),
	assertionId_ (new form :: Identificator (assertion->getIdentificator())),
	functionVector_ (assertion->getPropArity()),
	assertion_ (assertion)
	{
		Math :: evaluations()->add (this);
		if (Config :: localParsing()) {
			return;
		}
		for (index :: Arity i = 0; i < assertion->getPropArity(); ++ i) {
			DefaultFunction_*
				function = new DefaultFunction_ (i, assertion->getProposition (i), this);
			function->setEvaluation (this);
			function->setAssertion (assertion_);
			functionVector_.add (function);
		}
	}
	inline
	Evaluation :: Evaluation
	(
		const Location& location,
		const mdl :: Comments* comments,
		value :: Name name,
		mdl :: Identificator* identificator,
		const mdl :: evaluation :: parser :: vector :: Function& functionVector,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, name, theory),
	assertionId_ (identificator),
	functionVector_ (functionVector),
	assertion_ (NULL)
	{
		if (!Config :: useProver() && !Config :: useLearning()) {
			return;
		}
		try {
			const index :: Assertion
				index = theory_->getIndex (assertionId_);
			if (index == index :: undefined :: FORM) {
				throw new Error (location_, Error :: SEMANTIC, "reference to undefined assertion");
			}
			assertion_ = Math :: assertions()->get (index);
			for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
				form :: evaluation :: function :: Function*
					function = dynamic_cast<form :: evaluation :: function :: Function*>
						(functionVector_.getValue (i));
				function->setEvaluation (this);
				function->setAssertion (assertion_);
			}
			assertion_->addEvaluation (this);
			Math :: evaluations()->add (this);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	Evaluation :: ~ Evaluation() {
		deleteAggregateObject (assertionId_);
	}

using nstd :: manipulator :: underline;
using nstd :: manipulator :: iterate;
using nstd :: manipulator :: tab;
using nstd :: manipulator :: endLine;

	// mdl :: Evaluation interface
	void
	Evaluation :: setToDefault()
	{
		for (index :: Arity i = 0; i < functionVector_.getSize(); ++ i) {
			mdl :: evaluation :: Function*&
				function = functionVector_.getReference (i);
			function->commitSuicide();
			function = new DefaultFunction_ (i, assertion_->getProposition (i), this);
			form :: Proposition*
				proposition = dynamic_cast<form :: Proposition*>(assertion_->getProposition (i));
			proposition->replaceEvaluationFunction (i, function);
		}
	}
	index :: Arity
	Evaluation :: getSize() const {
		return functionVector_.getSize();
	}
	mdl :: evaluation :: Function*
	Evaluation :: getFunction (const index :: Arity i) {
		return functionVector_.getValue (i);
	}
	const mdl :: evaluation :: Function*
	Evaluation :: getFunction (const index :: Arity i) const {
		return functionVector_.getValue (i);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// object :: Buildable implementation
	void
	Evaluation :: build()
	{
		if (!Config :: useProver() && !Config :: useLearning()) {
			return;
		}
		try {
			for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
				form :: evaluation :: function :: Function*
					function = dynamic_cast<form :: evaluation :: function :: Function*>
						(functionVector_.getValue (i));
				function->build();
			}
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}

	// object :: Writable implementation
	void
	Evaluation :: translate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->translate (string);
			string << endLine;
		}
	}
	void
	Evaluation :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: evaluation_ << space;
		replicateName (string);
		string << Token :: of_ << space;
		assertionId_->replicate (string);
		string << space << Token :: openBrace_ << endLine;
		for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			const mdl :: evaluation :: Function* function = functionVector_.getValue (i);
			function->replicate (string);
		}
		string << location_.getIndent() << Token :: closeBrace_ << endLine;
		string << endLine;
	}
	bool
	Evaluation :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (assertionId_->lookup()) {
			if (Config :: lookupDefinition()) {
				std :: cout << *assertion_;
			} else {
				std :: cout << assertion_->getLocation();
			}
			return true;
		}
		for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			const mdl :: evaluation :: Function* function = functionVector_.getValue (i);
			if (function->lookup()) {
				return true;
			}
		}
		return false;
	}
	object :: Writable*
	Evaluation :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (assertionId_->lookup()) {
			return assertion_;
		}
		object :: Writable* object = NULL;
		for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			mdl :: evaluation :: Function* function = functionVector_.getValue (i);
			object = function->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}
	const object :: Writable*
	Evaluation :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (assertionId_->lookup()) {
			return assertion_;
		}
		const object :: Writable* object = NULL;
		for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			const mdl :: evaluation :: Function* function = functionVector_.getValue (i);
			object = function->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Evaluation :: commitSuicide() {
		delete this;
	}
	Size_t
	Evaluation :: getVolume() const {
		Size_t volume = 0;
		volume += Identifiable :: getVolume();
		volume += getAggregateVolume (assertionId_);
		volume += functionVector_.getVolume();
		return volume;
	}
	Size_t
	Evaluation :: getSizeOf() const {
		return sizeof (Evaluation);
	}
}
}
}

#endif /*MDL_FORM_BLOCK_EVALUATION_CPP_*/

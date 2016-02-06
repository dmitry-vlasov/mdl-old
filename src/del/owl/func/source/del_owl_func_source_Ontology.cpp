/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Ontology.cpp                         */
/* Description:     functional OWL2 ontology source                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"

namespace del {
namespace owl {
namespace func {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Ontology :: Ontology (const String& fullName) :
	location_ (),
	fullName_ (fullName),
	shortName_ (fullName.getSize()),
	annotationVector_ (INITIAL_ANNOTATION_VECTOR_CAPACITY),
	annotationAssertionVector_ (INITIAL_ANNOTATION_ASSERTION_VECTOR_CAPACITY),
	entityAnnotationVector_ (INITIAL_ENTITY_ANNOTATION_VECTOR_CAPACITY),
	declarationVector_ (INITIAL_DECLARATION_VECTOR_CAPACITY),
	transitiveObjectPropertyVector_ (INITIAL_TRANSITIVE_OBJECT_PROPERTY_VECTOR_CAPACITY),
	unrecognizedVector_(INITIAL_UNERCOGNIZED_VECTOR_CAPACITY),

	formulaVector_ (INITIAL_FORMULA_VECTOR_CAPACITY),
	componentVector_ (INITIAL_COMPONENT_VECTOR_CAPACITY) {
		initShortName();
	}
	inline
	Ontology :: Ontology (const Location& location, const String& fullName) :
	location_ (location),
	fullName_ (fullName),
	shortName_ (fullName.getSize()),
	annotationVector_ (INITIAL_ANNOTATION_VECTOR_CAPACITY),
	annotationAssertionVector_ (INITIAL_ANNOTATION_ASSERTION_VECTOR_CAPACITY),
	entityAnnotationVector_ (INITIAL_ENTITY_ANNOTATION_VECTOR_CAPACITY),
	declarationVector_ (INITIAL_DECLARATION_VECTOR_CAPACITY),
	transitiveObjectPropertyVector_ (INITIAL_TRANSITIVE_OBJECT_PROPERTY_VECTOR_CAPACITY),
	unrecognizedVector_(INITIAL_UNERCOGNIZED_VECTOR_CAPACITY),

	formulaVector_ (INITIAL_FORMULA_VECTOR_CAPACITY),
	componentVector_ (INITIAL_COMPONENT_VECTOR_CAPACITY) {
		initShortName();
	}
	Ontology :: ~ Ontology() {
	}

	const del :: Theory*
	Ontology :: createTheory() const
	{
		del :: source :: Theory* theory = NULL;
		if (Config :: inputFormat() == Config :: DEL_FORMAT) {
			theory = new del :: source :: Theory();
		} else {
			const value :: Theory
				id = Table :: theories()->add (shortName_);
			theory = new del :: source :: Theory (id);
		}
		for (value :: Integer i = 0; i < formulaVector_.getSize(); ++ i) {
			const del :: Formula* const
				formulaOWL = formulaVector_.getValue (i);
			const del :: Formula* const
				formulaDel = formulaOWL->clone();
			const_cast<del :: Formula*>(formulaDel)->setImage (formulaDel);
			theory->addFormula (formulaDel);
		}
		addTautologies (theory);
		return theory;
	}

	void
	Ontology :: addAnnotation (const Annotation* annotation)
	{
		annotationVector_.add (annotation);
		componentVector_.add (annotation);
	}
	void
	Ontology :: addAnnotationAssertion (const AnnotationAssertion* annotationAssertion)
	{
		annotationAssertionVector_.add (annotationAssertion);
		componentVector_.add (annotationAssertion);
	}
	void
	Ontology :: addEntityAnnotation (const EntityAnnotation* entityAnnotation)
	{
		entityAnnotationVector_.add (entityAnnotation);
		componentVector_.add (entityAnnotation);
	}
	void
	Ontology :: addDeclaration (const Declaration* declaration)
	{
		declarationVector_.add (declaration);
		componentVector_.add (declaration);
	}
	void
	Ontology :: addTransitiveObjectProperty (const TransitiveObjectProperty* property)
	{
		transitiveObjectPropertyVector_.add (property);
		componentVector_.add (property);
	}
	void
	Ontology :: addUnrecognized(const Unrecognized* unrecognized)
	{
		unrecognizedVector_.add (unrecognized);
		componentVector_.add (unrecognized);
	}
	void
	Ontology :: addFormula (const del :: Formula* formula)
	{
		formulaVector_.add (formula);
		componentVector_.add (formula);
	}

	const vector :: AnnotationAssertion&
	Ontology :: getAnnotationAssertions() const {
		return annotationAssertionVector_;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Ontology :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << del :: Token :: commentBegin_;
		string << Token :: ontology_ << space;
		string << contents_ ;
		string << del :: Token :: commentEnd_ << endLine;*/
	}
	void
	Ontology :: replicate (String& string) const
	{
		correctName();
		string << location_.getIndent() << Token :: ontology_;
		string << Token :: openBracket_ << fullName_ << endLine;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const Writable* component = componentVector_.getValue (i);
			component->replicate (string);
			string << endLine;
		}
		string << Token :: closeBracket_ << endLine;
		string << endLine;
	}

	// object :: Object implementation
	void
	Ontology :: commitSuicide() {
		delete this;
	}
	Size_t
	Ontology :: getVolume() const
	{
		Size_t volume = 0;
		volume += fullName_.getVolume();
		volume += shortName_.getVolume();
		volume += annotationVector_.getVolume();
		volume += annotationAssertionVector_.getVolume();
		volume += entityAnnotationVector_.getVolume();
		volume += declarationVector_.getVolume();
		volume += transitiveObjectPropertyVector_.getVolume();
		volume += unrecognizedVector_.getVolume();
		volume += formulaVector_.getVolume();
		volume += componentVector_.getVolume();
		return volume;
	}
	Size_t
	Ontology :: getSizeOf() const {
		return sizeof (Ontology);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Ontology :: addTautologies (del :: Theory* theory) const
	{
		const del :: Signature*
			signature = theory->getSignature (true);
		for (value :: Integer i = 0; i < declarationVector_.getSize(); ++ i) {
			const Declaration*
				declaration = declarationVector_.getValue (i);
			const String& name = declaration->getName();
			const del :: Formula* tautology = NULL;
			if (declaration->getKind() == Declaration :: CLASS) {
				const value :: Variable concept = Table :: variables()->add (name);
				const Symbol symbol (concept, false);
				if (!signature->containsSymbol (symbol)) {
					tautology = new del :: source :: formula :: Subset
					(
						new del :: source :: term :: Variable (symbol),
						new del :: source :: term :: Variable (symbol)
					);
				}
			}
			if (declaration->getKind() == Declaration :: OBJECT_PROPERTY) {
				const value :: Relation relation = Table :: relations()->add (name);
				const Symbol symbol (relation, true);
				if (!signature->containsSymbol (symbol)) {
					tautology = new del :: source :: formula :: Subset
					(
						new del :: source :: term :: Exists (
							symbol,
							new del :: source :: term :: Top ()
						),
						new del :: source :: term :: Top ()
					);
				}
			}
			if (tautology != NULL) {
				theory->addFormula (tautology);
			}
		}
	}
	void
	Ontology :: correctName() const
	{
		if (fullName_.getLastValue() != '>') {
			value :: Integer index = value :: undefined :: INTEGER;
			for (int i = fullName_.getSize(); i >= 0; -- i) {
				if (fullName_.getValue (i) == '>' ) {
					index = i;
					break;
				}
			}
			if (index != value :: undefined :: INTEGER) {
				for (value :: Integer i = index; i < fullName_.getSize() - 1; ++ i) {
					const char ch = fullName_[i];
					fullName_ [i] = fullName_ [i + 1];
					fullName_ [i + 1] = ch;
				}
			} else {
				fullName_.insert ('<', 0);
				fullName_.add ('>');
			}
		}
	}
	void
	Ontology :: initShortName()
	{
		value :: Integer indexDot = value :: undefined :: INTEGER;
		for (int i = fullName_.getSize(); i >= 0; -- i) {
			if (fullName_.getValue (i) == '.') {
				indexDot = i;
				break;
			}
		}
		value :: Integer indexSlash = value :: undefined :: INTEGER;
		for (int i = fullName_.getSize(); i >= 0; -- i) {
			if ((fullName_.getValue (i) == '/') || (fullName_.getValue (i) == '\\')) {
				indexSlash = i;
				break;
			}
		}
		if (indexDot < indexSlash) {
			indexDot = value :: undefined :: INTEGER;
		}
		if ((indexDot == value :: undefined :: INTEGER) && (indexSlash == value :: undefined :: INTEGER)) {
			for (value :: Integer i = 0; i < fullName_.getSize(); ++ i) {
				shortName_ << fullName_ [i];
			}
		} else if ((indexDot != value :: undefined :: INTEGER) && (indexSlash == value :: undefined :: INTEGER)) {
			for (value :: Integer i = 0; i < indexDot; ++ i) {
				shortName_ << fullName_ [i];
			}
		} else if ((indexDot == value :: undefined :: INTEGER) && (indexSlash != value :: undefined :: INTEGER)) {
			for (value :: Integer i = indexSlash + 1; i < fullName_.getSize(); ++ i) {
				shortName_ << fullName_ [i];
			}
		} else if ((indexDot != value :: undefined :: INTEGER) && (indexSlash != value :: undefined :: INTEGER)) {
			for (value :: Integer i = indexSlash + 1; i < indexDot; ++ i) {
				shortName_ << fullName_ [i];
			}
		}
		if (shortName_.getFirstValue() == '<') {
			shortName_.removeFirst();
		}
		if (shortName_.getLastValue() == '>') {
			shortName_.removeLast();
		}
	}
}
}
}
}



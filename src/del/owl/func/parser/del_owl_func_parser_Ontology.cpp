/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Ontology.cpp                         */
/* Description:     functional OWL2 ontology parser                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_ONTOLOGY_CPP_
#define DEL_OWL_FUNC_PARSER_ONTOLOGY_CPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"
#include "del/owl/func/parser/del_owl_func_parser.hpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Ontology :: Ontology () :
	location_ (),
	name_ (INITIAL_NAME_CAPACITY),
	annotationParser_ (new parser :: Annotation()),
	entityAnnotationParser_ (new parser :: EntityAnnotation()),
	declarationParser_ (new parser :: Declaration()),
	eqClassesParser_ (new parser :: EqClasses()),
	subClassesParser_ (new parser :: SubClasses()),
	unrecognizedParser_ (new parser :: Unrecognized()),
	annotationAssertionParser_ (new parser :: AnnotationAssertion()) {
	}
	Ontology :: ~ Ontology()
	{
		deleteAggregateObject (annotationParser_);
		deleteAggregateObject (entityAnnotationParser_);
		deleteAggregateObject (declarationParser_);
		deleteAggregateObject (eqClassesParser_);
		deleteAggregateObject (subClassesParser_);
		deleteAggregateObject (unrecognizedParser_);
		deleteAggregateObject (annotationAssertionParser_);
	}

using manipulator :: endLine;

	const source :: Ontology*
	Ontology :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		const String&
			name = lexer->getToken();
		source :: Ontology*
			ontology = new source :: Ontology (location_, name);
		while (true) {
			const Token :: Type
				tokenType = lexer->scan();
			switch (tokenType) {
			case Token :: ANNOTATION : {
				const source :: Annotation*
					annotation = annotationParser_->parse (lexer);
				ontology->addAnnotation (annotation);
				break;
			}
			case Token :: ANNOTATION_ASSERTION : {
				const source :: AnnotationAssertion*
					annotationAssertion = annotationAssertionParser_->parse (lexer);
				ontology->addAnnotationAssertion (annotationAssertion);
				break;
			}
			case Token :: ENTITY_ANNOTATION : {
				const source :: EntityAnnotation*
					entityAnnotation = entityAnnotationParser_->parse (lexer);
				ontology->addEntityAnnotation (entityAnnotation);
				break;
			}
			case Token :: DECLARATION : {
				const source :: Declaration*
					declaration = declarationParser_->parse (lexer);
				ontology->addDeclaration (declaration);
				break;
			}
			case Token :: TRANSITIVE_OBJECT_PROPERTY : {
				location_ = lexer->getLocation();
				lexer->scan<Token :: OPEN_BRACKET>();
				lexer->scan<Token :: STRING>();
				const String&
					string = lexer->getToken();
				lexer->scan<Token :: CLOSE_BRACKET>();
				const source :: TransitiveObjectProperty*
					property = new source :: TransitiveObjectProperty (location_, string);
				ontology->addTransitiveObjectProperty (property);
				break;
			}
			case Token :: EQUIVALENT_CLASSES : {
				const del :: Formula*
					eqClasses = eqClassesParser_->parse (lexer);
				ontology->addFormula (eqClasses);
				break;
			}
			case Token :: SUBCLASS_OF : {
				const del :: Formula*
					subClasses = subClassesParser_->parse (lexer);
				ontology->addFormula (subClasses);
				break;
			}
			case Token :: STRING : {
				name_.copy (lexer->getToken());
				const source :: Unrecognized*
					unrecognized = unrecognizedParser_->parse (name_, lexer);
				ontology->addUnrecognized (unrecognized);
				break;
			}
			case Token :: CLOSE_BRACKET : {
				return ontology;
			}
			default :
				Error* error = new Error (lexer->getLocation(), Error :: PARSER);
				error->message() << "syntax error." << endLine;
				error->message() << "token: \"" << lexer->getToken() << "\" was scanned" << endLine;
				error->message() << "wile one of Namespace, Ontology, ObjectProperty, Annotations, Class was expected" << endLine;
				throw error;
			}
		}
		return ontology;
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
		volume += name_.getVolume();
		volume += getAggregateVolume (annotationParser_);
		volume += getAggregateVolume (entityAnnotationParser_);
		volume += getAggregateVolume (declarationParser_);
		volume += getAggregateVolume (eqClassesParser_);
		volume += getAggregateVolume (subClassesParser_);
		volume += getAggregateVolume (unrecognizedParser_);
		volume += getAggregateVolume (annotationAssertionParser_);
		return volume;
	}
	Size_t
	Ontology :: getSizeOf() const {
		return sizeof (Ontology);
	}
	void
	Ontology :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_ONTOLOGY_CPP_*/

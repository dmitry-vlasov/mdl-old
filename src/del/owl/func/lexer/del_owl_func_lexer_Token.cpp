/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_lexer_Token.cpp                             */
/* Description:     functional OWL2 tokens                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace owl {
namespace func {
namespace lexer {

	/********************************
	 *		Public static attributes
	 ********************************/

	const Token Token :: unknown_ (UNKNOWN, "unknown");
	const Token Token :: ontology_ (ONTOLOGY, "Ontology");
	const Token Token :: declaration_ (DECLARATION, "Declaration");
	const Token Token :: class_ (CLASS, "Class");
	const Token Token :: objectProperty_ (OBJECT_PROPERTY, "ObjectProperty");
	const Token Token :: equivalentClasses_ (EQUIVALENT_CLASSES, "EquivalentClasses");
	const Token Token :: objectSomeValuesFrom_ (OBJECT_SOME_VALUES_FROM, "ObjectSomeValuesFrom");
	const Token Token :: objectIntersectionOf_ (OBJECT_INTERSECTION_OF, "ObjectIntersectionOf");
	const Token Token :: subclassOf_ (SUBCLASS_OF, "SubClassOf");
	const Token Token :: owlThing_ (OWL_THING, "owl:Thing");
	const Token Token :: openBracket_ (OPEN_BRACKET, "(");
	const Token Token :: closeBracket_ (CLOSE_BRACKET, ")");
	const Token Token :: string_ (STRING, "<string>");
	const Token Token :: namespace_ (NAMESPACE, "Namespace");
	const Token Token :: label_ (LABEL, "Label");
	const Token Token :: annotation_ (ANNOTATION, "Annotation");
	const Token Token :: entityAnnotation_ (ENTITY_ANNOTATION, "EntityAnnotation");
	const Token Token :: transitiveObjectProperty_ (TRANSITIVE_OBJECT_PROPERTY, "TransitiveObjectProperty");
	const Token Token :: prefix_ (PREFIX, "Prefix");
	const Token Token :: annotationAssertion_ (ANNOTATION_ASSERTION, "AnnotationAssertion");
	const Token Token :: unrecognized_ (UNRECOGNIZED, "<unrecognized>");
	const Token Token :: annotationProperty_ (ANNOTATION_PROPERTY, "AnnotationProperty");
	const Token Token :: eof_ (EOF_, "eof");

	const Token Token :: tokens_[NUMBER_OF_TOKENS] =
	{
		unknown_,              ontology_,             declaration_,
		class_,                objectProperty_,       equivalentClasses_,
		objectSomeValuesFrom_, objectIntersectionOf_, subclassOf_,
		owlThing_,             openBracket_,          closeBracket_,
		string_,               namespace_,            label_,
		annotation_,           entityAnnotation_,     transitiveObjectProperty_,
		prefix_,               annotationAssertion_,  unrecognized_,
		annotationProperty_,   eof_
	};

	/****************************
	 *		Public members
	 ****************************/

	const char*
	Token :: getString (const Type type)
	{
		for (int i = 0 ; i < NUMBER_OF_TOKENS; i ++) {
			if (tokens_[i].getType() == type) {
				return tokens_[i].getString();
			}
		}
		return unknown_.getString();
	}

	// nstd :: Object implementation
	void
	Token :: commitSuicide() {
		delete this;
	}
	nstd :: Size_t
	Token :: getSizeOf() const {
		return sizeof (Token);
	}
	nstd :: Size_t
	Token :: getVolume() const {
		return 0;
	}
	void
	Token :: show (nstd :: String<>& string) const {
		string << getString();
	}
}
}
}
}



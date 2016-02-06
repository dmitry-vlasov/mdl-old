/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_lexer_Token.hpp                             */
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

class Token : public nstd :: Object {
public :
	// owl lexer token types.
	enum Type
	{
		UNKNOWN                  = 0,  ///<  unknown token
		ONTOLOGY                 = 1,  ///< "Ontology"             *
		DECLARATION              = 2,  ///< "Declaration"          *
		CLASS                    = 3,  ///< "Class"                *
		OBJECT_PROPERTY          = 4,  ///< "ObjectProperty"       *
		EQUIVALENT_CLASSES       = 5,  ///< "EquivalentClasses"    *
		OBJECT_SOME_VALUES_FROM  = 6,  ///< "ObjectSomeValuesFrom" *
		OBJECT_INTERSECTION_OF   = 7,  ///< "ObjectIntersectionOf" *
		SUBCLASS_OF              = 8,  ///< "SubClassOf"           *
		OWL_THING                = 9,  ///< "owl:Thing"            *
		OPEN_BRACKET             = 10, ///< "("                    *
		CLOSE_BRACKET            = 11, ///< ")"                    *
		STRING                   = 12, ///<  a string              *
		NAMESPACE                = 13, ///< "Namespace"            *
		LABEL                    = 14, ///< "Label"                *
		ANNOTATION               = 15, ///< "Annotation"           *
		ENTITY_ANNOTATION        = 16, ///< "EntityAnnotation"     *
		TRANSITIVE_OBJECT_PROPERTY = 17, ///< "TransitiveObjectProperty"
		PREFIX                   = 18, ///< "Prefix"               *
		ANNOTATION_ASSERTION     = 19, ///< "AnnotationAssertion"  *
		UNRECOGNIZED             = 20, ///< "unrecognized string"  *
		ANNOTATION_PROPERTY      = 21, ///< "AnnotationProperty"   *
		EOF_                     = 22  ///< end of file
	};

	enum {
		NUMBER_OF_TOKENS = EOF_ + 1
	};

	static const Token unknown_;
	static const Token ontology_;
	static const Token declaration_;
	static const Token class_;
	static const Token objectProperty_;
	static const Token equivalentClasses_;
	static const Token objectSomeValuesFrom_;
	static const Token objectIntersectionOf_;
	static const Token subclassOf_;
	static const Token owlThing_;
	static const Token openBracket_;
	static const Token closeBracket_;
	static const Token string_;
	static const Token namespace_;
	static const Token label_;
	static const Token annotation_;
	static const Token entityAnnotation_;
	static const Token transitiveObjectProperty_;
	static const Token prefix_;
	static const Token annotationAssertion_;
	static const Token unrecognized_;
	static const Token annotationProperty_;
	static const Token eof_;

	Token ();
	Token (const Type, const char* const);
	Token (const Token&);
	virtual ~ Token();

	static const char* getString (const Type);
	const char* getString() const;
	Type getType() const;
	nstd :: Size_t getLength() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual nstd :: Size_t getSizeOf() const;
	virtual nstd :: Size_t getVolume() const;
	virtual void show (nstd :: String<>&) const;

private :
	static const Token tokens_[NUMBER_OF_TOKENS];

	const Type type__;
	const char* const token_;
};

	template<class A>
	nstd :: String<A>&
	operator << (nstd :: String<A>&, const Token&);
}
	using lexer :: Token;
}
}
}

#include "del/owl/func/lexer/del_owl_func_lexer_Token.ipp"
#include "del/owl/func/lexer/del_owl_func_lexer_Token.cpp"



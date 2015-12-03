/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Ontology.hpp                         */
/* Description:     functional OWL2 ontology source                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_ONTOLOGY_HPP_
#define DEL_OWL_FUNC_SOURCE_ONTOLOGY_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace source {

class Ontology :
	public Writable,
	public Scalar<Ontology> {
public :
	Ontology (const String&);
	Ontology (const Location&, const String&);
	virtual ~ Ontology();

	const del :: Theory* createTheory() const;

	void addAnnotation (const Annotation*);
	void addAnnotationAssertion (const AnnotationAssertion*);
	void addEntityAnnotation (const EntityAnnotation*);
	void addDeclaration (const Declaration*);
	void addTransitiveObjectProperty (const TransitiveObjectProperty*);
	void addUnrecognized (const Unrecognized*);
	void addFormula (const del :: Formula*);

	const vector :: AnnotationAssertion&  getAnnotationAssertions() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		del :: vector :: Vector
		<
			const Writable*,
			storage :: ByValue,
			allocator :: Heap
		>
		ComponentVector_;

	void addTautologies (del :: Theory*) const;
	void correctName() const;
	void initShortName();

	const Location location_;
	mutable String fullName_;
	mutable String shortName_;

	vector :: Annotation annotationVector_;
	vector :: AnnotationAssertion annotationAssertionVector_;
	vector :: EntityAnnotation entityAnnotationVector_;
	vector :: Declaration declarationVector_;
	vector :: TransitiveObjectProperty transitiveObjectPropertyVector_;
	vector :: Unrecognized unrecognizedVector_;

	del :: vector :: Formula formulaVector_;
	ComponentVector_ componentVector_;
	enum {
		INITIAL_ANNOTATION_VECTOR_CAPACITY = 32,
		INITIAL_ANNOTATION_ASSERTION_VECTOR_CAPACITY = 1024,
		INITIAL_ENTITY_ANNOTATION_VECTOR_CAPACITY = 32,
		INITIAL_DECLARATION_VECTOR_CAPACITY = 32,
		INITIAL_TRANSITIVE_OBJECT_PROPERTY_VECTOR_CAPACITY = 32,
		INITIAL_UNERCOGNIZED_VECTOR_CAPACITY = 32,
		INITIAL_FORMULA_VECTOR_CAPACITY = 1024,
		INITIAL_COMPONENT_VECTOR_CAPACITY = 1024
	};
};

}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_ONTOLOGY_HPP_*/
